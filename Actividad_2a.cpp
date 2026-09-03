//actividad 2 a
#include <Arduino.h>

// Guardamos el último estado. En PULLUP, arranca en 1.
uint8_t estadoAnterior = 1; 

void setup() {
    // 1. Configurar pines y activar PULLUP interno
    DDRD &= ~(1 << 2);   // Pin 2 Entrada
    PORTD |= (1 << 2);   // Pin 2 PULLUP
    DDRB |= (1 << 2);    // Pin 10 Salida (LED)
}

void loop() {
    // 2. Leemos el pin 2 lo más rápido que puede el microcontrolador
    uint8_t lecturaActual = (PIND & (1 << 2)) ? 1 : 0;

    // 3. Detectamos el flanco de bajada: 
    // ¿Acaba de leer un 0 (presionado) pero antes estaba en 1 (reposo)?
    if (lecturaActual == 0 && estadoAnterior == 1) {
        
        // Ejecutamos la acción única: Invertir el LED
        PORTB ^= (1 << 2); 
        
    }
}