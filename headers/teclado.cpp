#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "fnqueue.h"
#include "teclado.h"

volatile struct estructura_teclado estado_teclado_var;

void key_up_callback(void (*handler)(), int16_t tecla)
{
	estado_teclado_var.handlers_up[tecla] = handler;
}

void key_down_callback(void (*handler)(), int16_t tecla)
{
	estado_teclado_var.handlers_down[tecla] = handler;
}

void teclado_init()
{
	estado_teclado_var.last_key = 255;  // no se apretó ninguna tecla
	for ( int i = 0; i < 5; i++ )
	{
		estado_teclado_var.handlers_up[i] = -1;
		estado_teclado_var.handlers_down[i] = -1;
	}
	fnqueue_init(); // inicializar la cola de funciones.

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);// prescaler al máximo.
	ADMUX |= (1 << REFS0);      // voltaje referencia.
	ADMUX &= ~(1 << ADLAR);     // left aligned (sheet: 24.9.3.1/2).
	ADCSRA |= (1 << ADATE);		// habilitar auto trigger.
	ADCSRA |= (1 << ADEN);      // enable ADC.
	ADCSRA |= (1 << ADIE);      // habilitar interrupciones.
	ADCSRB &= ~(1 << ADTS2) & ~(1 << ADTS1) & ~(1 << ADTS0); // habilitar auto-
															 // trigger.
	sei();
	ADCSRA |= (1 << ADSC);      // iniciar primera conversión.
}

// Convert ADC value to key number
int16_t get_key(int16_t input)
{
	int16_t k = 255;
	if ( 0 <= input && input < 5 )
		k = 3;
	else if ( 5 <= input && input < 220 )
	   	k = 0;
	else if ( 220 <= input && input < 360 )
	   	k = 1;
	else if ( 360 <= input && input < 535 )
	   	k = 2;
	else if ( 535 <= input && input < 760 )
	   	k = 4;
	return k;
}

void procesar_entrada()
{
    int16_t key = get_key((ADCL) | (ADCH << 8));
    if ( 0 <= key && key <= 4 )
    {
		if ( estado_teclado_var.handlers_down != -1 )
			estado_teclado_var.handlers_down[key]();
		estado_teclado_var.last_key = key;
    }
    else
	{
		if ( estado_teclado_var.handlers_down != -1 )
		{
			if ( estado_teclado_var.last_key != 255 )
				estado_teclado_var.handlers_up[estado_teclado_var.last_key]();
			estado_teclado_var.last_key = 255;
		}
	}
}

ISR(ADC_vect)
{
	fnqueue_add(procesar_entrada);
}
