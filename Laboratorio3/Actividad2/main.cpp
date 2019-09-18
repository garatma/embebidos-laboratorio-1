#include <LiquidCrystal.h>
#include "Arduino.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int8_t i = 0;

int main()
{
	init();
	lcd.begin(16,2);
	lcd.setCursor(0,0);
	Serial.begin(9600);

	while (1)
	{
		if ( Serial.available() > 0 )
		{
			lcd.clear();
			lcd.print(Serial.read());
		}
		if ( Serial.availableForWrite() > 0 )
		{
			Serial.write(i);
			i++;
			if ( i > 255 )
				i = 0;
		}
	}
	return 0;
}

