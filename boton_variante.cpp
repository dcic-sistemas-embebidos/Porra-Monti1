#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <Arduino.h>

#include "boton_variante.h"

static boton_callback_t boton_pulsado_cb = NULL;
volatile static bool is_button_pressed = false;
volatile static uint8_t estado_actual = 1;
volatile static uint32_t ultimoTiempoInterrupcion = 0;

ISR(INT0_vect) {
    uint32_t tiempoActual = millis();
    
    // Anti-rebote por tiempo (200ms)
    if (tiempoActual - ultimoTiempoInterrupcion > 200) { 
        if (estado_actual >= 6) {
            estado_actual = 1;
        } else {
            estado_actual++;
        }
        ultimoTiempoInterrupcion = tiempoActual;
        is_button_pressed = true; // Notificar al loop
    }
}

void boton_loop(void) {
    if (boton_pulsado_cb == NULL) return;

    if (is_button_pressed) {
        is_button_pressed = false;
        boton_pulsado_cb(estado_actual); // Disparar callback
    }
}

void boton_init(boton_callback_t callback) {
    boton_pulsado_cb = callback;

    // Configuración del Pin 2 (PD2 / INT0) como entrada con Pull-Up
    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PORTD2);

    // Configurar interrupción por flanco de bajada en INT0
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0); 
    
    // Habilitar interrupciones globales
    sei(); 
}