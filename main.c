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
char msgs_down[5][17] =
{
    " Right Key:  OK ",
    " Up Key:     OK ",
    " Down Key:   OK ",
    " Left Key:   OK ",
    " Select Key: OK "
};
char msgs_up[5][17] =
{
    " Right Key:  NO ",
    " Up Key:     NO ",
    " Down Key:   NO ",
    " Left Key:   NO ",
    " Select Key: NO "
};
uint16_t adc_key_val[5] = {30, 150, 360, 535, 760};
uint8_t NUM_KEYS = 5;
uint16_t adc_key_in;
volatile uint8_t key=-1;
volatile uint8_t last_key=-1;
uint8_t oldkey=-1;

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
	key = get_key(ADCL | (ADCH << 8));// convert into key press
    lcd.setCursor(0, 1);
    if ( last_key == -1 )
    {
        // key Down
        lcd.print(msgs_down[key]);
    }
    else
    {
        // key up
        lcd.print(msgs_up[key]);
    }
    last_key = key;
    ADCSRA |= (1 << ADSC);  // iniciar próxima conversion.
}

void setup()
{
	// inicializar pin 10 como salida
	DDRB |= (1<<DDB2);	//pinMode(10, OUTPUT);

    ADMUX &= ~(1 << ADLAR);     // left aligned (sheet: 24.9.3.1/2).
    ADMUX |= (1 << REFS0);      // voltaje referencia.
    ADCSRA |= (1 << ADEN);      // enable ADC.
    ADCSRA |= (1 << ADIE);      // habilitar interrupciones.
    sei();

    ADCSRA |= (1 << ADSC);      // iniciar primera conversion.
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
	// fnqueue_run();
}
