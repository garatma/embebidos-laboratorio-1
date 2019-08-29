#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

// variables:
int8_t operacion = 1;              // cómo ciclar el led.

void encendido()
{
    PORTB |= (1<<PB5);
}

void ciclo(int prendido, int apagado)
{
    PORTB |= (1<<PB5);
    _delay_ms(prendido);

    PORTB &= ~(1<<PB5);
	_delay_ms(apagado);
}

void apagado()
{
    PORTB &= ~(1<<PB5);
}

int main()
{
    // inicializar el pin del pulsador como entrada.
    DDRD &= ~(1<<DDD2);
    // inicializar el pin del led como salida.
    DDRB |= (1<<DDB5);

	cli();
	EICRA |= (1<<ISC01);
	EIMSK |= (1<<INT0);
	sei();

    while (1)
    {
		// llamar a la función correspondiente.
	    switch (operacion)
	    {
	        case 1:
	            encendido();
	            break;
	        case 2:
	            ciclo(1000,1000);
	            break;
	        case 3:
	            ciclo(500,500);
	            break;
	        case 4:
	            ciclo(250,250);
	            break;
	        case 5:
	            ciclo(500,1000);
	            break;
	        case 6:
	            apagado();
	            break;
	    }

    }
    return 0;
}

ISR(INT0_vect)
{
	// pasar al siguiente modo.
	operacion++;
	// volver al inicio (ya se usaron todos los modos).
	if ( operacion > 6 )
		operacion = 1;
}
