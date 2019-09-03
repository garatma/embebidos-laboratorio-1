#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
#include <LiquidCrystal.h>
#define FNQUEUE_LENGTH 16





//----------------------------------critical------------------------------------





static volatile int16_t anidamiento;

void critical_begin(void)
{
    // Verificar que las interrupciones no fueron interrumpidas por fuera del
    // módulo de región crítica. Esto puede suceder cuando se está ejecutando
    // una rutina de interrupción. En este caso, no deshabilitar las
    // interrupciones

    // Lectura atómica del registro
    uint8_t status_register = SREG;
    cli();

    // Si las interrupciones estaban habilitadas, y aún no fueron
    // deshabilitadas por el módulo de región crítica
    // o están deshabilitadas pero por el módulo de región crítica
    //       incrementar el anidamiento.
    if ((anidamiento == 0) && ((status_register & (0x80)) != 0)
            || (anidamiento != 0) && ((status_register & (0x80)) == 0))
    {
        anidamiento++;
    }
    // Si las interrupciones estaban deshabilitadas, y no fué el módulo de
	// región crítica, no hacer nada.
}

void critical_end(void)
{
    uint8_t status_register = SREG;
    cli();

    if (anidamiento > 0) {
        anidamiento--;
        if (anidamiento == 0)
            sei();
    }
    else if ((status_register & 0x80) != 0)
        sei();
}





//---------------------------------fnqueue--------------------------------------





typedef void (*task)();

static task fnqueue_functions[FNQUEUE_LENGTH];
static uint8_t fnqueue_head,
	fnqueue_tail,
	fnqueue_count;

bool fnqueue_init(void)
{
	fnqueue_head = 0;
	fnqueue_tail = 0;
	fnqueue_count = 0;

    return true;
}

bool fnqueue_run(void)
{
    critical_begin();
    if (fnqueue_count > 0)
    {
        critical_end();

        fnqueue_functions[fnqueue_head]();
        critical_begin();
        fnqueue_head = (fnqueue_head + 1) % FNQUEUE_LENGTH;
        fnqueue_count--;
    }
    critical_end();

	return 1;
}

bool fnqueue_add(void (*function)(void))
{
	bool result = false;

    critical_begin();
    if (fnqueue_count < FNQUEUE_LENGTH)
    {
        fnqueue_functions[fnqueue_tail] = function;
        fnqueue_tail = (fnqueue_tail + 1) % FNQUEUE_LENGTH;
        fnqueue_count++;
        result = true;
    }
    critical_end();
    return result;
}





//---------------------------------main-----------------------------------------

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
volatile uint8_t key=255;
volatile uint8_t last_key=255;
volatile uint8_t lock = 0;

// Convert ADC value to key number
uint16_t get_key(unsigned int input)
{
    uint16_t k;
    for (k = 0; k < NUM_KEYS; k++)
        if (input < adc_key_val[k])
            return k;

    if (k >= NUM_KEYS)
        k = 255;     // No valid key pressed

    return k;
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

    fnqueue_init();

    // set up the LCD's number of columns and rows:
    lcd.begin(numCols,numRows);
    analogWrite(10, 100); //Controla intensidad backlight
    lcd.setCursor(0, 0);
    lcd.print("Key Pad Test");
    lcd.setCursor(0, 1);
    lcd.print("Sist.Emb. 2019");
    //delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("Press any key...");

    ADCSRA |= (1 << ADSC);      // iniciar primera conversión.
}

void loop()
{
	fnqueue_run();
}

void procesar_entrada()
{
    key = get_key(ADCL | (ADCH << 8));
    lcd.setCursor(0, 1);
    if ( key > 4 ) lcd.print(msgs_up[last_key]);
    else lcd.print(msgs_down[key]);
    last_key = key;
    ADCSRA |= (1 << ADSC);  // iniciar próxima conversión.
}

ISR(ADC_vect)
{
    fnqueue_add(procesar_entrada);
}
