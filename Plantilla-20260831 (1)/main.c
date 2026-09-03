#include "boton.h"
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
