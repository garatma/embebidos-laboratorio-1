#include <stdbool.h>
#include <stdint.h>
#define CANTIDAD_CANALES_ADC 6


struct struct_adc_cfg
{
	int8_t canal; // canal a configurar
	void (* callback_conversion_lista)(); // función de callback invocada al fi-
										  // nalizar la conversión de un valor.
	// añadir más campos en caso de que sea necesario
};

struct estado_adc
{
	void (* callbacks[CANTIDAD_CANALES_ADC])();
	bool canales_incializados[CANTIDAD_CANALES_ADC];
	bool primera_conversion;
	int8_t canal_actual;
};

typedef struct struct_adc_cfg adc_cfg;

bool adc_init(adc_cfg * cfg); // inicilializa el driver de ADC. adc_cfg es un
							 // struct. auto-trigger o manual, según convenga.
							 // retorna true si se puede inicializar exitosamen-
							 // te, o false en caso contrario. asume que el
							 // struct cfg ya fue declarado.

void driver_init();		// inicializar la estructura interna del driver.
