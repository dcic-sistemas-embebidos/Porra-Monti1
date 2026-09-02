#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
//actividad 3

// Variables para el Debouncing
uint8_t estadoEstable = 1;       // El estado limpio y sin rebotes
uint8_t ultimoEstadoLeido = 1;   // La lectura "sucia" inmediata del pin
uint32_t ultimoTiempoRebote = 0; // Guarda el "timestamp" del último cambio detectado
const uint32_t retardoRebote = 50; // Los 50ms de filtro

void setup() {
    DDRD &= ~(1 << 2);   // Pin 2 Entrada
    PORTD |= (1 << 2);   // Pin 2 PULLUP
    DDRB |= (1 << 5);    // Pin 10 Salida (LED)
}

void loop() {
    // 1. Leemos el estado "crudo" actual del pin
    uint8_t lecturaCruda = (PIND & (1 << 2)) ? 1 : 0;

    // 2. Si hubo CUALQUIER cambio (sea ruido de rebote o que apretaste de verdad)
    if (lecturaCruda != ultimoEstadoLeido) {
        // Reseteamos nuestro "cronómetro" guardando el tiempo actual
        ultimoTiempoRebote = millis();
    }

    // 3. Calculamos cuánto tiempo pasó desde ese último cambio.
    // Si pasó más tiempo que nuestro retardo (50ms), significa que la señal ya se estabilizó.
    if ((millis() - ultimoTiempoRebote) > retardoRebote) {
        
        // Si la señal estabilizada es distinta al último estado estable que teníamos guardado:
        if (lecturaCruda != estadoEstable) {
            estadoEstable = lecturaCruda; // Actualizamos nuestro estado oficial
            
            // 4. Si el nuevo estado estable es 0 (PRESIONADO), ejecutamos la acción
            if (estadoEstable == 0) {
                PORTB ^= (1 << 5); // Invertimos el LED con XOR
            }
        }
    }

    // 5. Guardamos la lectura cruda para comparar en la próxima vuelta del loop
    ultimoEstadoLeido = lecturaCruda;
    
    // Acá podrías agregar MÁS código y se ejecutaría a toda velocidad 
    // sin quedarse trabado esperando al botón.
}