#include "adc.h"

struct estado_adc adc;

void driver_init()
{
	for ( int8_t i = 0; i < CANTIDAD_CANALES_ADC; i++ )
		adc.canales_incializados[i] = false;
}

bool adc_init(adc_cfg * cfg)
{
	int8_t canal = cfg -> canal;
	int8_t error = false;
	if ( adc.canales_incializados[canal] == false )
	{
		// puedo inicializar el canal porque está "vacío".
		adc.canales_incializados[canal] = true;
		adc.callbacks[canal] = cfg -> callback_conversion_lista;
		// inicializar registros?
	}
	else
		// no se permite inicializar el canal dos veces
		error = true;
	return error;
}
