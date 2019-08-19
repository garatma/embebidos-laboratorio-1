// cambio de estado del led cada x milisegundos

#include <avr/io.h>
#include <util/delay.h>

// variable para controlar la cantidad de milisegundos a esperar
int x = 500;

int main()
{
    // inicializar el pin del led como salida
    DDRB |= (1<<DDB5);

    while (1)
    {
        // esperar x misilegundos
        _delay_ms(x);

        // toggle del estado del led
        PORTB ^= (1<<PB5);
    }
    return 0;
}
