#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main()
{
    // inicializar el pin del led como salida.
    DDRB |= (1<<DDB5);

    while (1)
    {
        // esperar 100 misilegundos.
        _delay_ms(100);
        // toggle del estado del led.
        PORTB ^= (1<<PB5);
    }
    return 0;
}
