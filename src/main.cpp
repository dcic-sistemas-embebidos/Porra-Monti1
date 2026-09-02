/*#include "boton.h"
//esto es la callback que se ejecuta cuando se pulsa el boton
void boton_pulsado() {
  // Lógica del botón pulsado
    PORTB |= (1<<5);     // Enciende el LED usando el operador OR (|)
}

// Otras funciones...

void setup() {
    // Otras inicializaciones
    // ...

    boton_init(boton_pulsado);
}

void loop() {
    // Otras actividades del loop...
    boton_loop();
}

*/

#include <Arduino.h>
#include "boton1.h"

void encender_led_cb(void) {
    PORTB |= (1 << PORTB5);
}

void apagar_led_cb(void) {
    PORTB &= ~(1 << PORTB5);
}

void setup() {
    boton_init(encender_led_cb, apagar_led_cb);
}

void loop() {
    boton_loop();
}