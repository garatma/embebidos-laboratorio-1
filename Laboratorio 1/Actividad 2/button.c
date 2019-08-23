#include <avr/io.h>
#include <util/delay.h>

// variables:
int8_t estado_boton = 0;	//  para leer el estado del pulsador.

int main()
{
	// inicializar el pin del pulsador como entrada.
	DDRD &= ~(1<<DDD2);
	// inicializar el pin del led como salida.
	DDRB |= (1<<DDB5);

	while (1)
	{
		// leer el estado del pulsador.
		estado_boton = PIND & (1<<PD2);

		if( estado_boton )
		{
			// si el pulsador está apretado.
			// encender el led.
			PORTB |= (1<<PB5);
		}
		else
		{
			// apagar el led.
			PORTB &= ~(1<<PB5);
		}
	}
	return 0;
}
