/*
 Código AVR de ejemplo para realizar debounce por Software
 Si bien la estrategia de debounce difiere, el código está inspirado en el
 ejemplo Debounce de Arduino, y el hardware es el utilizado en dicho ejemplo.
 http://www.arduino.cc/en/Tutorial/Debounce
 */

#include <avr/io.h>
#include <util/delay.h>

// variables:
int buttonState;       		// the current reading from the input pin.
int lastButtonState = 0;   	// the previous reading from the input pin.


int main()
{
	// inicializar el pin del pulsador como entrada.
	DDRD &= ~(1<<DDD2);
	// inicializar el pin del led como salida.
	DDRB |= (1<<DDB5);

	while (1)
	{
		// leer el estado del pulsador.
		buttonState = PIND & (1<<PD2);

		// si cambió el estado del pulsador...
		if (buttonState != lastButtonState)
		{
			// se espera un tiempo para evitar leer el ruido del rebote del
			// pulsador.
			_delay_ms(50);

			// se vuelve a leer el estado del pulsador.
			buttonState = PIND & (1<<PD2);

			// si el cambio se mantiene, se interpreta como evento de
			// keydown/keyup válido.
			if (buttonState != lastButtonState)
			{
				// el pulso es válido, se implementa la lógica del sistema.

				// si no está presionado el pulsador (se detectó un keyup)...
				if (!buttonState)
				{
					// Se modifica el estado del led (toggle vía XOR).
					PORTB ^= (1<<PB5);
				}

				// si hubo cambios actualizo el valor de lectura anterior.
				lastButtonState = buttonState;
			}
		}
	}
	return 0;
}
