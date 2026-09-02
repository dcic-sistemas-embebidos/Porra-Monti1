#ifndef BOTON_H
#define BOTON_H
#include <avr/io.h>
#include <Arduino.h>

void boton_init(void (*callback)());
void boton_loop();

#endif // BOTON_H
