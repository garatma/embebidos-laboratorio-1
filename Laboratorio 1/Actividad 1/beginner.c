#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

// ====================================
//                ATmega328p
//
//              +--------+
//            --+ o  Vcc +------------
//  LED - PB5 --+        +--
//            --+        +--
//  ------------+ GND    +--
//              +--------+
// ====================================

// define el puerto de I/O para ser usado por el  LED.
#define LED_PORT PB5

int main(void)
{
	// setea el numero de port como salida.
	DDRB |= (1 << LED_PORT);

	while (1)
	{
		PORTB |= (1 << LED_PORT);
		// espera.
		_delay_ms(1000);

		PORTB &= ~(1 << LED_PORT);

		// espera.
		_delay_ms(1000);
	}
	return 0;
}
