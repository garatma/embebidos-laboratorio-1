#include <avr/io.h>
#include <util/delay.h>

// variables:
int buttonState = 0;	// para leer el estado del pulsador.

int main()
{
	// inicializar el pin del pulsador como salida para poder controlarlo.
	DDRD |= (1<<DDD2);
	// inicializar el pin del led como salida.
	DDRB |= (1<<DDB5);

	while (1)
	{
		// leer el estado del pulsador.
		buttonState = PORTD & (1<<PD2);

		if ( buttonState )
		{
			// si el pulsador está apretado.
			// encender el led.
			PORTB |= (1<<PB5);
			// simular botón suelto.
			PORTD &= ~(1<<PD2);
		}
		else
		{
			// apagar el led.
			PORTB &= ~(1<<PB5);
			// simular botón apretado.
			PORTD |= (1<<PD2);
		}
	}
	return 0;
}
