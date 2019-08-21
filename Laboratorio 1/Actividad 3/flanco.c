// --------------------------------- flanco.c ----------------------------------

/*
 Código AVR de ejemplo para detectar un flanco
 Se utiliza el hardware del ejemplo Button de Arduino
 http://www.arduino.cc/en/Tutorial/Button
 */

#include <avr/io.h>
#include <util/delay.h>

// variables:
int buttonState;
int lastButtonState = 0;

int main()
{
	// inicializar el pin del pulsador como entrada.
	DDRD &= ~(1<<DDD2);
	// inicializar el pin del led como salida.
	DDRB |= (1<<DDB5);

	while (1)
	{
		//Leer el estado del pulsador
		buttonState = PIND & (1<<PD2);

		// si cambió el estado del pulsador...
		if (buttonState != lastButtonState)
		{
			// si no está presionado el pulsador (se detectó un keyup)...
			if (!buttonState)
			{
				// se modifica el estado del led (toggle vía XOR).
				PORTB ^= (1<<PB5);
			}

			// si hubo cambios válidos actualizo el valor de lectura anterior.
			lastButtonState = buttonState;
		}
	}
	return 0;
}
