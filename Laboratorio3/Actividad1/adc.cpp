#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"
#include "fnqueue.h"

struct estado_adc adc;
volatile int16_t valor_adc;

void driver_init()
{
	fnqueue_init();

	adc.primera_conversion = true;
	for ( int8_t i = 0; i < CANTIDAD_CANALES_ADC; i++ )
		adc.canales_incializados[i] = false;

	// configuración báisca y común para todos los canales.
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);// prescaler al máximo.
	ADMUX |= (1 << REFS0);	// voltaje referencia.
	ADMUX &= ~(1 << ADLAR); // left aligned (sheet: 24.9.3.1/2).
	ADCSRA |= (1 << ADEN);  // enable ADC.
	ADCSRA |= (1 << ADIE);  // habilitar interrupciones.

	sei();
	// ADCSRA |= (1 << ADSC);      // iniciar primera conversión.
	/* ↑ no creo que esté bien. no debería dispararse una conversión si no hay
	 * canales inicializados. debería realizarse la conversión la primera vez
	 * que se inicializa uno, en ese canal y luego alternar entre todos los ini-
	 * cializados
	*/
}

void cambiar_canal(int8_t canal)
{
	// deshabilitar interrupciones?
	switch (canal) {
		case 0:
			ADMUX &= ~(1 << MUX2) && ~(1 << MUX1) && ~(1 << MUX0);	// 000
			break;
		case 1:
			ADMUX &= ~(1 << MUX2) && ~(1 << MUX1); // 00x
			ADMUX |= (1 << MUX0);	// 001
			break;
		case 2:
			ADMUX &= ~(1 << MUX2) && ~(1 << MUX0);	// 0x0
			ADMUX |= (1 << MUX1);	// 010
			break;
		case 3:
			ADMUX &= ~(1 << MUX2);	// 0xx
			ADMUX |= (1 << MUX1) | (1 << MUX0);	// 011
			break;
		case 4:
			ADMUX &= ~(1 << MUX1) && ~(1 << MUX0);	// x00
			ADMUX |= (1 << MUX2);	// 100
			break;
		case 5:
			ADMUX &= ~(1 << MUX1);	// x0x
			ADMUX |= (1 << MUX2) | (1 << MUX0);	// 101
			break;
	}
}

bool adc_init(adc_cfg * cfg)
{
	// permitir que se inicialice el canal dos veces?
	int8_t canal = cfg -> canal;
	int8_t error = false;
	if ( -1 < canal && canal < CANTIDAD_CANALES_ADC )
	{
		adc.canales_incializados[canal] = true;
		adc.callbacks[canal] = cfg -> callback_conversion_lista;
		adc.canal_actual = canal;
		// inicializar registros?
		if ( adc.primera_conversion == true )
		{
			cambiar_canal(canal);
			ADCSRA |= (1 << ADSC);	// iniciar conversión.
			adc.primera_conversion = false;
		}
	}
	else
		error = true;	// canal incorrecto.
	return error;
}

// retorna la posición donde está el canal inicializado entre inicio y fin, si
// es que lo encuentra. sino, retorna -1.
int8_t buscar_canal_inicializado(int8_t inicio, int8_t fin)
{
	int8_t i = inicio,
		   retorno = -1;
	bool encontre_canal_inicializado = false;
	while ( i < fin && encontre_canal_inicializado == false )
	{
		// buscar entre [canal_actual+1,5].
		encontre_canal_inicializado = adc.canales_incializados[i] == true;
		i++;
	}
	if ( encontre_canal_inicializado == true )
		retorno = i-1; // -1 para compensar el último i++.
	return retorno;
}

void procesar_entrada()
{
	// qué hago con valor_adc ?
	// ejecuto la función o la encolo?
	adc.callbacks[adc.canal_actual]();	// ejecutar callback asociada al canal.

	// obtener próximo canal inicializado.
	int8_t proximo_canal = 0;
	proximo_canal = buscar_canal_inicializado(adc.canal_actual + 1,
		 									  CANTIDAD_CANALES_ADC);
	if ( proximo_canal == -1 )
		buscar_canal_inicializado(0, adc.canal_actual); // buscar entre
													//[0, canal_actual]

	adc.canal_actual = proximo_canal;	// actualizo el canal actual.
	cambiar_canal(adc.canal_actual);	// actualizo los registros.
	ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect)
{
	valor_adc = (ADCL) | (ADCH << 8);	// obtener valor del adc.
	fnqueue_add(procesar_entrada);
}
