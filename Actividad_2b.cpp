//actividad 2 b
#include <Arduino.h>
void setup() {
    // 1. Configurar Pin 2 (PD2) como ENTRADA (0)
    DDRD &= ~(1 << 2);
    
    // 2. ¡LA MAGIA DEL PULLUP!: Escribimos un 1 en el PORTD de un pin que es entrada.
    // Esto le dice al microcontrolador que active su resistencia interna.
    PORTD |= (1 << 2);

    // 3. Configurar Pin 10 (PB2) como SALIDA (1) para el LED
    DDRB |= (1 << 2);
}

void loop() {
    // 4. Leer el estado del pin 2
    // Ojo acá: Leemos PIND y lo negamos con "!" porque la lógica está invertida.
    // PIND & (1<<2) da 0 (Falso) cuando está presionado. Al negarlo (!), se vuelve Verdadero y entra al if.
    if (!(PIND & (1 << 2))) {
        
        PORTB |= (1 << 2);     // Botón PRESIONADO (Lee 0) -> Encendemos el LED
        
    } else {
        
        PORTB &= ~(1 << 2);    // Botón LIBERADO (Lee 1) -> Apagamos el LED
        
    }
}