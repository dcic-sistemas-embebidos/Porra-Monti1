#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "boton.h"
volatile uint8_t estado = 0; 
volatile uint32_t ultimoTiempoInterrupcion = 0;

static void (*boton_pulsado_cb)() = NULL;
static bool is_button_pressed = false;

ISR(INT0_vect) {
    // Lógica de la interrupción
        uint32_t tiempoActual = millis();
    
    // Debouncing
    if (tiempoActual - ultimoTiempoInterrupcion > 500) {
        is_button_pressed = true;    
        ultimoTiempoInterrupcion = tiempoActual;
    }
}

void boton_loop()
{
    if (boton_pulsado_cb == NULL) return;

    if (is_button_pressed) {
        is_button_pressed = false;
        boton_pulsado_cb();
    }
}

void boton_init(void (*callback)()) {
    
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
    // Otras inicializaciones
    boton_pulsado_cb = callback;

}

