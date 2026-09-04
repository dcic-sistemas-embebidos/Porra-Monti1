#ifndef BOTON_VARIANTE_H
#define BOTON_VARIANTE_H

#include <stdint.h>

// Definición correcta del callback con parámetro
typedef void (*boton_callback_t)(uint8_t estado);

void boton_init(boton_callback_t callback);
void boton_loop(void);

#endif // BOTON_H