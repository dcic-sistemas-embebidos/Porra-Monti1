/* #include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "boton.h"
volatile uint8_t estado = 0; 
volatile uint32_t ultimoTiempoInterrupcion = 0;
uint32_t IntervaloBlink ;
uint32_t ultimoTiempoParpadeo = 0;
bool PRENDER_APAGAR = false ;

static void (*boton_pulsado_cb)() = NULL;

ISR(INT0_vect) {
    // Lógica de la interrupción
        uint32_t tiempoActual = millis();
    
    // Debouncing
    if (tiempoActual - ultimoTiempoInterrupcion > 500) 
    {
        if (estado == 6)
        {
            estado = 1 ;
        }
        else
        {
            estado = (estado + 1) ;
        }
        ultimoTiempoInterrupcion = tiempoActual;
    }
}

void boton_loop()
{
    if (boton_pulsado_cb == NULL) return;

    switch (estado) {
        case 1:
            IntervaloBlink = 1000 ;
            Parpadear(IntervaloBlink) ;
            break;
            
        case 2:
            boton_pulsado_cb(500);
            intervaloBlink = 500;
            break;
        case 3:
            boton_pulsado_cb(250);
            intervaloBlink = 250;
            break;
        case 4:
            boton_pulsado_cb(1500);
            intervaloBlink = 1500;
            break;
        case 5:
            PORTB |= (1 << 5);  // LED encendido fijo
            break;
        case 6:
            PORTB &= ~(1 << 5); // LED apagado fijo
            break;
            
    }
}

void Parpadear(uint32_t P)
{

    if (millis() - ultimoTiempoParpadeo >= P) {
            if (PRENDER_APAGAR)
            {
                callback_encender() ;
                PRENDER_APAGAR = false ;
            }
            else
            {
                callback_apagar() ;
                PRENDER_APAGAR = true ;
            }

            ultimoTiempoParpadeo = millis(); // Resetear el cronómetro del LED
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

*/

#include "boton1.h"
#include <arduino.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Variables de estado
volatile uint8_t estado = 1; // Arrancamos en estado 1
volatile uint32_t ultimoTiempoInterrupcion = 0;

static uint32_t intervaloBlink = 1000;
static uint32_t ultimoTiempoParpadeo = 0;
static bool estadoLed = false;

// Punteros a las callbacks declaradas en el main
static callback_led_t callback_encender = NULL;
static callback_led_t callback_apagar = NULL;

// Declaración privada
static void Parpadear(uint32_t periodo);

ISR(INT0_vect) {
    uint32_t tiempoActual = millis();
    
    // Debouncing (Anti-rebote por hardware/software)
    if (tiempoActual - ultimoTiempoInterrupcion > 200) { 
        if (estado >= 6) {
            estado = 1;
        } else {
            estado++;
        }
        ultimoTiempoInterrupcion = tiempoActual;
    }
}

void boton_init(callback_led_t cb_encender, callback_led_t cb_apagar) {
    // Guardar punteros de las callbacks
    callback_encender = cb_encender;
    callback_apagar = cb_apagar;

    // Configuración PD2 (INT0) como entrada con Pull-up y PB5 como salida
    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PORTD2);
    DDRB |= (1 << DDB5);

    // Configuración de interrupción por flanco de bajada (FALLING)
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0); 

    sei(); // Habilitar interrupciones globales
}

static void Parpadear(uint32_t periodo) {
    if (millis() - ultimoTiempoParpadeo >= periodo) {
        if (estadoLed) {
            if (callback_apagar) callback_apagar();
            estadoLed = false;
        } else {
            if (callback_encender) callback_encender();
            estadoLed = true;
        }
        ultimoTiempoParpadeo = millis();
    }
}

void boton_loop(void) {
    switch (estado) {
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
            if (callback_encender) callback_encender();
            break;

        case 6: // LED apagado fijo
            if (callback_apagar) callback_apagar();
            break;
    }
}