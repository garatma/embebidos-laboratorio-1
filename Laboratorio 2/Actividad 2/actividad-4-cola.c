#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "fnqueue.h"

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
	cli();
	// habilitar pin 2 para disparar interrupciones con cambio de flanco.
	EICRA |= (1<<ISC01);
	EIMSK |= (1<<INT0);
	sei();

    // inicializar el pin del 2 como entrada.
    DDRD &= ~(1<<DDD2);
    // inicializar el pin del led como salida.
    DDRB |= (1<<DDB5);

	// inicializar la cola de funciones
	fnqueue_init();

    while (1)
    {
		// desencolar y ejecutar.
		fnqueue_run();
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

	// llamar a la función correspondiente.
	switch (operacion)
	{
		case 1:
			fnqueue_add(&encendido());
			break;
		case 2:
			fnqueue_add(&ciclo(1000,1000));
			break;
		case 3:
			fnqueue_add(&ciclo(500,500));
			break;
		case 4:
			fnqueue_add(&ciclo(250,250));
			break;
		case 5:
			fnqueue_add(&ciclo(500,1000));
			break;
		case 6:
			fnqueue_add(&apagado());
			break;
	}
}
