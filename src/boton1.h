#ifndef BOTON1_H
#define BOTON1_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Definición de tipos de punteros a función (callbacks sin parámetros)
typedef void (*callback_led_t)(void);

// Funciones públicas
void boton_init(callback_led_t cb_encender, callback_led_t cb_apagar);
void boton_loop(void);

#endif