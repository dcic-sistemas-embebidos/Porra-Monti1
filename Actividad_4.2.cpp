/* // actividad 4.2
#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

// 1. Declaración GLOBAL y VOLATILE del flag
volatile uint8_t estado = 0; 
volatile uint32_t ultimoTiempoInterrupcion = 0;
uint32_t parpadeo = 1000; 

void setup() {
        // DDRX establece si es entrada o salida
    // PORTX establece el valor de la salida

    // Configuración de pines (PD2 entrada Pull-up, PB5 salida LED)
    DDRD &= ~(1 << 2);
    PORTD |= (1 << 2);
    DDRB |= (1 << 5);

    // Configuración de interrupción (Flanco bajada)
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0); //habilita los pines de interrupción externa
    
    //sei(); // Habilitar interrupciones globales
}
void papadear(uint32_t parpadeo) {


    delay(parpadeo);          // Espera medio segundo
    
    PORTB &= ~(1<<5);    // Apaga el LED usando el operador AND (&)
    
    delay(parpadeo);          // Espera medio segundo con el LED apagado

    PORTB |= (1<<5);     // Enciende el LED usando el operador OR (|)
}

void loop() {
    
   
    switch (estado)
    {
    case 1 :
        parpadeo = 1000;
            
        papadear(parpadeo);          // Espera medio segundo
    
        break;
    case 2:
        parpadeo = 500; // Cambiar el intervalo de parpadeo a 1 segundo
        papadear(parpadeo);
        break;
    case 3:
        parpadeo = 250; // Cambiar el intervalo de parpadeo a 1.5 segundos
        papadear(parpadeo);          // Espera medio segundo

        break;
    case 4:

        parpadeo = 1500; // Cambiar el intervalo de parpadeo a 1.5 segundos
        papadear(parpadeo);          // Espera medio segundo

        break;
    case 5:

        PORTB |= (1<<5);     // Enciende el LED usando el operador OR (|)
        break;
    case 6:
        PORTB &= ~(1<<5);    // Apaga el LED usando el operador AND (&)
        break;


    default:
    
        break;
    }

}

ISR(INT0_vect) {// cuando se dispara la interrupción externa, se accede a esta direccion de memoria y se ejecuta el código que está dentro de la ISR
    uint32_t tiempoActual = millis();
    
    // Seguimos usando el debouncing acá para no levantar banderas falsas
    if (tiempoActual - ultimoTiempoInterrupcion > 50) {
        
        // 4. La ISR hace su único trabajo: Levantar la bandera
        estado++;
        if (estado > 6) {
            estado = 1;
        }        
        ultimoTiempoInterrupcion = tiempoActual;
    }
} */

//Actividad 4.2

#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

// Variables Volatile (se modifican en la interrupción)
volatile uint8_t estado = 0; 
volatile uint32_t ultimoTiempoInterrupcion = 0;

// Variables para el parpadeo y la consola
uint32_t ultimoTiempoParpadeo = 0;
uint32_t intervaloBlink = 1000;
uint8_t estadoAnteriorImpreso = 255; // Empieza en un valor irreal para forzar la primera impresión

void setup() {
    // Inicializamos el puerto Serial a 9600 baudios
    Serial.begin(9600);
    Serial.println("--- Sistema Iniciado ---");
    Serial.println("Esperando primera pulsacion...");

    // Configuración de pines (PD2 entrada Pull-up, PB5 salida LED)
    DDRD &= ~(1 << 2);
    PORTD |= (1 << 2);
    DDRB |= (1 << 5);

    // Configuración de interrupción (Flanco bajada)
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0); 
    
    // Habilitar interrupciones globales
    sei(); 
}

void loop() {
    
    // 1. CONSOLA: Solo imprimimos si el estado cambió
    if (estado != estadoAnteriorImpreso) {
        Serial.print("Boton presionado! Nuevo Estado: ");
        Serial.println(estado);
        estadoAnteriorImpreso = estado; // Actualizamos para no repetir el mensaje
    }

    // 2. ASIGNACIÓN DE TIEMPOS según el estado
    switch (estado) {
        case 1:
            intervaloBlink = 1000;
            break;
        case 2:
            intervaloBlink = 500;
            break;
        case 3:
            intervaloBlink = 250;
            break;
        case 4:
            intervaloBlink = 1500;
            break;
        case 5:
            PORTB |= (1 << 5);  // LED encendido fijo
            break;
        case 6:
            PORTB &= ~(1 << 5); // LED apagado fijo
            break;
    }

    // 3. LÓGICA DE PARPADEO NO BLOQUEANTE (Solo para estados 1 al 4)
    if (estado >= 1 && estado <= 4) {
        
        // Comparamos si ya pasó el tiempo asignado en el switch
        if (millis() - ultimoTiempoParpadeo >= intervaloBlink) {
            
            PORTB ^= (1 << 5); // Invertir el estado del LED (XOR)
            
            ultimoTiempoParpadeo = millis(); // Resetear el cronómetro del LED
        }
    }
}

ISR(INT0_vect) {
    uint32_t tiempoActual = millis();
    
    // Debouncing
    if (tiempoActual - ultimoTiempoInterrupcion > 500) {
        
        estado++;
        if (estado > 6) {
            estado = 1;
        }        
        ultimoTiempoInterrupcion = tiempoActual;
    }
}