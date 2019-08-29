#include "Arduino.h"
#include "fnqueue.h"

#define TECLA_UP 		0	// botón up del LCD Keypad Shield
#define TECLA_DOWN 		1 	// botón down del LCD Keypad Shield
#define TECLA_LEFT 		2 	// botón left del LCD Keypad Shield
#define TECLA_RIGHT 	3 	// botón right del LCD Keypad Shield
#define TECLA_SELECT 	4	// botón select del LCD Keypad Shield

void key_down_callback(void (*handler)(), int8_t tecla);
void key_up_callback(void (*handler)(), int8_t tecla);

void inicializar_driver_teclado()
{
	// por ahora solo funciona con ADC0.
	ADCSRA |= (1<<ADEN); 	// habilita el ADC.
	ADCSRA |= (1<<ADATE);	// habilita el auto trigger.
	ADCSRA |= (1<<ADIE);	// habilita la interrupción de ADC.

	// inicializar la cola de funciones.
	fnqueue_init();
}
