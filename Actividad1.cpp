#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h> //Estas no las vamos a usar, usamos las otras dos para manejarnos a nivel de registros

int main ()
{
    DDRB |= (1<<5) ; //El pin 5 para el puerto B va a ser de salida

    while(1)
    {
        PORTB |= (1<<5) ; //Le asigno un 1 a la salida al pin 5 del puerto B
        _delay_ms(500) ;
        PORTB &= ~(1<<5) ; //Le asigno un 0 a la salida al pin 5 del puerto B
        _delay_ms(500) ;
    }
}