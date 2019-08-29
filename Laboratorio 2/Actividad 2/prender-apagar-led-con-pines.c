#include <avr/interrupt.h>

void setup()
{
	pinMode(13, OUTPUT);
	pinMode(8, INPUT);
	pinMode(7, INPUT);
	cli();
	// Enable Ports B and C Pin Change Interrupts
    PCICR |= (1<<PCIE2) | (1<<PCIE0);
    PCMSK0 |= (1<<PCINT0);	// pin 8
    PCMSK2 |= (1<<PCINT23);	// pin 7
	sei();
}

void loop()
{
}

ISR(PCINT0_vect)
{
	digitalWrite(13, HIGH);
}

ISR(PCINT2_vect)
{
	digitalWrite(13, LOW);
}
