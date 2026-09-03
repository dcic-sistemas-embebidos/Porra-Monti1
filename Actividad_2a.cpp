#include <Arduino.h>

// //actividad 2 a
void setup() {
    // Configurar Pin 2 (PD2) como ENTRADA (0)
    DDRD &= ~(1 << 2);
    
    // Configurar Pin 10 (PB2) como SALIDA (1)
    DDRB |= (1 << 5);
}

void loop() {
    // Escuchar el estado del pin 2 usando el registro PIND
    if (PIND & (1 << 2)) {
        // Si la lectura es verdadera (Nivel ALTO / 1), encendemos el LED
        PORTB |= (1 << 5);
    } else {
        // Si la lectura es falsa (Nivel BAJO / 0), apagamos el LED
        PORTB &= ~(1 << 5);
    }
}