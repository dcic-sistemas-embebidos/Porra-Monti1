//actividad 4 1 Usamos una interrupción externa para detectar el flanco de bajada del pulsador y encender un LED.
#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

// 1. Declaración GLOBAL y VOLATILE del flag
volatile bool flagPulsador = 0; 
volatile uint32_t ultimoTiempoInterrupcion = 0;
uint32_t parpadeo = 500; 

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

void loop() {
    
    delay(parpadeo);          // Espera medio segundo
    
    PORTB &= ~(1<<5);    // Apaga el LED usando el operador AND (&)
    
    delay(parpadeo);          // Espera medio segundo con el LED apagado

    PORTB |= (1<<5);     // Enciende el LED usando el operador OR (|)

    if (flagPulsador == 1) {
        if (parpadeo == 1000) {
            parpadeo = 500;          // Espera medio segundo
        } else {
            parpadeo = 1000;          // Espera un segundo
        }      
        flagPulsador = 0; 
    }
}

ISR(INT0_vect) {// cuando se dispara la interrupción externa, se accede a esta direccion de memoria y se ejecuta el código que está dentro de la ISR
    uint32_t tiempoActual = millis();
    
    // Seguimos usando el debouncing acá para no levantar banderas falsas
    if (tiempoActual - ultimoTiempoInterrupcion > 50) {
        
        // 4. La ISR hace su único trabajo: Levantar la bandera
        flagPulsador = 1; 
        
        ultimoTiempoInterrupcion = tiempoActual;
    }
}
