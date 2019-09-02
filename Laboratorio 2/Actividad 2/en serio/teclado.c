#include <stdint.h>
#include "fnqueue.h"

volatile int8_t key = 255;
volatile int8_t last_key = 255;


void key_down_callback(void (*handler)(), int8_t tecla);
void key_up_callback(void (*handler)(), int8_t tecla);


void key_up_callback(void (*handler)(), int8_t tecla)
{
	estado_teclado_var -> handlers_up(tecla) = handler;
}

void key_down_callback(void (*handler)(), int8_t tecla)
{
	estado_teclado_var -> handler_down(tecla) = handler;
}

void teclado_init()
{
	// inicializar el estado del teclado.
	estado_teclado estado_teclado_var;
	estado_teclado_var -> key = 255;
	estado_teclado_var -> last_key = 255;

	fnqueue_init(); // inicializar la cola de funciones.

	cli();
	ADMUX &= ~(1 << ADLAR);     // left aligned (sheet: 24.9.3.1/2).
	ADMUX |= (1 << REFS0);      // voltaje referencia.
	ADCSRA |= (1 << ADEN);      // enable ADC.
	ADCSRA |= (1 << ADIE);      // habilitar interrupciones.
	sei();
    ADCSRA |= (1 << ADSC);      // iniciar primera conversión.
}

// Convert ADC value to key number
uint16_t get_key(unsigned int input)
{
    uint16_t k;
    for (k = 0; k < NUM_KEYS; k++)
        if (input < estado_teclado_var -> adc_key_val[k])
            return k;

    if (k >= NUM_KEYS)
        k = 255;     // No valid key pressed

    return k;
}

void procesar_entrada()
{
    int8_t key = get_key(ADCL | (ADCH << 8));
    if ( key > 4 )
	{
		// key up
		estado_teclado_var -> handlers_up[estado_teclado_var -> last_key]();
	}
    else
	{
		// key down
		estado_teclado_var -> handlers_down[key]();
	}
    estado_teclado_var -> last_key = key;
    ADCSRA |= (1 << ADSC);  // iniciar próxima conversión.
}

ISR(ADC_vect()
{
	fnqueue_add(procesar_entrada);
}
