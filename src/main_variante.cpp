#include <Arduino.h>
#include <avr/io.h>
#include "boton_variante.h"

static bool estadoLed = false;
static uint32_t intervaloBlink = 1000;
static uint32_t ultimoTiempoParpadeo = 0;
static uint8_t modoActual = 1;

// Prototipos locales
static void Parpadear(uint32_t periodo);
void boton_pulsado(uint8_t estado);

void setup() {
    // Configuración Pin 13 / PB5 como salida para el LED
    DDRB |= (1 << DDB5);
    
    // Inicializar driver del botón
    boton_init(boton_pulsado);
}

void loop() {
    // 1. Atender el driver del botón
    boton_loop();

    // 2. Máquina de Estados Finita (FSM)
    switch (modoActual) {
        case 1:
            intervaloBlink = 1000;
            Parpadear(intervaloBlink);
            break;
            
        case 2:
            intervaloBlink = 500;
            Parpadear(intervaloBlink);
            break;

        case 3:
            intervaloBlink = 250;
            Parpadear(intervaloBlink);
            break;

        case 4:
            intervaloBlink = 1500;
            Parpadear(intervaloBlink);
            break;

        case 5: // LED encendido fijo
            PORTB |= (1 << PORTB5);
            break;

        case 6: // LED apagado fijo
            PORTB &= ~(1 << PORTB5);
            break;
            
        default:
            modoActual = 1;
            break;
    }
}

// Callback: Solo actualiza la variable del modo actual
void boton_pulsado(uint8_t estado) {
    modoActual = estado;
}

// Función de parpadeo no bloqueante con millis()
static void Parpadear(uint32_t periodo) {
    if (millis() - ultimoTiempoParpadeo >= periodo) {
        ultimoTiempoParpadeo = millis();
        estadoLed = !estadoLed;
        
        if (estadoLed) {
            PORTB |= (1 << PORTB5);  // Encender
        } else {
            PORTB &= ~(1 << PORTB5); // Apagar
        }
    }
}