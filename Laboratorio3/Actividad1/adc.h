#include <stdbool.h>
#include <stdint.h>
#define CANTIDAD_CANALES_ADC 6

struct adc_cfg
{
	void (* callback)();
	int8_t canal;
	int16_t valor;
	bool activo;
	bool hay_conversion;
};

bool adc_init(adc_cfg * cfg);
