#include <avr/io.h>
#include <util/delay.h>

// variables
// variable para leer el estado del pulsador
int buttonState = 0;

int main()
{
	//Inicializar el pin del pulsador como entrada
	DDRD &= ~(1<<DDD2);
	//Inicializar el pin del led como salida
	DDRB |= (1<<DDB5);

	while (1)
	{
		//Leer el estado del pulsador
		buttonState = PIND & (1<<PD2);

		if ( buttonState )
		{
			//Si el pulsador está apretado
			//Encender el led
			PORTB |= (1<<PB5);
			//PORTD &= ~(1<<PD2);
		}
		else
		{
			//Apagar el led
			PORTB &= ~(1<<PB5);
			//PORTD |= (1<<PD2);
		}

	}
	return 0;
}
