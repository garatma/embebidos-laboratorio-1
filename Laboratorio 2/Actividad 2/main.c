#include <stdbool.h>
#include <stdint.h>
#include <LiquidCrystal.h>



// these constants won't change.  But you can change the size of
// your LCD using them:
const uint8_t numRows = 2;
const uint8_t numCols = 16;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Key message
char msgs[5][17] =
{
    " Right Key:  OK ",
    " Up Key:     OK ",
    " Down Key:   OK ",
    " Left Key:   OK ",
    " Select Key: OK "
};
uint16_t adc_key_val[5] = {30, 150, 360, 535, 760};
uint8_t NUM_KEYS = 5;
uint16_t adc_key_in;
uint16_t key=-1;
uint16_t oldkey=-1;

void dibujar()
{
	lcd.setCursor(0, 1);
	lcd.print(msgs[key]);
}

// Convert ADC value to key number
uint16_t get_key(unsigned int input)
{
    uint16_t k;
    for (k = 0; k < NUM_KEYS; k++)
        if (input < adc_key_val[k])
            return k;

    if (k >= NUM_KEYS)
        k = -1;     // No valid key pressed

    return k;
}

ISR(ADC_vect)
{
    adc_key_in = ADCH;      		// read the value from the sensor
	key = get_key(adc_key_in);	    // convert into key press
	fnqueue_add(dibujar);
}

void setup()
{
	// inicializar pin 10 como salida
	DDRB |= (1<<DDB2);	//pinMode(10, OUTPUT);

	ADCSRA |= (1<<ADEN); 	// habilita el ADC.
	ADCSRA |= (1<<ADATE);	// habilita el auto trigger.
	ADCSRA |= (1<<ADIE);	// habilita la interrupción de ADC.

	sei();
    // set up the LCD's number of columns and rows:
    lcd.begin(numCols,numRows);
    analogWrite(10, 100); //Controla intensidad backlight
    lcd.setCursor(0, 0);
    lcd.print("Key Pad Test");
    lcd.setCursor(0, 1);
    lcd.print("Sist.Emb. 2019");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("Press any key...");
}

void loop()
{
	fnqueue_run();
}
