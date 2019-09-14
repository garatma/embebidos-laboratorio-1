#include <LiquidCrystal.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Arduino.h"
#define CANTIDAD_CANALES_ADC 6
#define FNQUEUE_LENGTH 16

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

struct adc_cfg
{
	void (* callback)(int16_t);
	int8_t canal;
	int16_t valor;
	bool activo;
	bool hay_conversion;
};


struct adc_cfg adc[CANTIDAD_CANALES_ADC];
volatile int8_t canal_actual;
bool inicializado[CANTIDAD_CANALES_ADC] = {false, false,
	 									   false, false,
										   false, false};
int8_t primer_canal;
bool primera_inicializacion = true;

void cambiar_canal(int8_t canal)
{
	// deshabilitar interrupciones?
	switch (canal) {
		case 0:
			ADMUX &= ~(1 << MUX2) && ~(1 << MUX1) && ~(1 << MUX0);	// 000
			break;
		case 1:
			ADMUX &= ~(1 << MUX2) && ~(1 << MUX1); // 00x
			ADMUX |= (1 << MUX0);	// 001
			break;
		case 2:
			ADMUX &= ~(1 << MUX2) && ~(1 << MUX0);	// 0x0
			ADMUX |= (1 << MUX1);	// 010
			break;
		case 3:
			ADMUX &= ~(1 << MUX2);	// 0xx
			ADMUX |= (1 << MUX1) | (1 << MUX0);	// 011
			break;
		case 4:
			ADMUX &= ~(1 << MUX1) && ~(1 << MUX0);	// x00
			ADMUX |= (1 << MUX2);	// 100
			break;
		case 5:
			ADMUX &= ~(1 << MUX1);	// x0x
			ADMUX |= (1 << MUX2) | (1 << MUX0);	// 101
			break;
	}
}

bool adc_init(struct adc_cfg * cfg)
{
	int8_t canal = cfg -> canal;
	bool error = false;
	if ( -1 < canal && canal < CANTIDAD_CANALES_ADC )
	{
	    adc[canal] = *cfg;
	    adc[canal].activo = true;
		inicializado[canal] = true;
		adc[canal].hay_conversion=false;

	    // si no hay conversion iniciar
	    if ( primera_inicializacion )
	    {
	    	canal_actual = canal;
			primer_canal = canal;
	        primera_inicializacion = false;
			fnqueue_init();
			cambiar_canal(canal_actual);
			// configuración báisca y común para todos los canales.
			ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
			ADMUX |= (1 << REFS0);	// voltaje referencia.
			//ADMUX &= ~(1 << ADLAR); // left aligned (sheet: 24.9.3.1/2).
			ADCSRA |= (1 << ADEN);  // enable ADC.
			ADCSRA |= (1 << ADIE);  // habilitar interrupciones.
			ADCSRA |= (1 << ADSC);	// iniciar conversión.
	    }
	}
	else
		error = true;
	return error;
}

// retorna la posición donde está el canal inicializado entre inicio y fin, si
// es que lo encuentra.
int8_t obtener_proximo()
{
	int8_t i=canal_actual+1;
	bool encontre=false;
	while (i<CANTIDAD_CANALES_ADC && !encontre)
	{
		encontre = inicializado[i]==true;
		i++;
	}
	if(!encontre)
	{
		i=0;
		while (i<=canal_actual && !encontre)
		{
			encontre = inicializado[i]==true;
			i++;
		}
	}
	return i-1;
}

void adc_loop()
{
    // para cada canal de adc
    for ( int8_t i = 0; i < CANTIDAD_CANALES_ADC; i++ )
        if ( adc[i].hay_conversion == true )
        {
			adc[i].hay_conversion=false;
            adc[i].callback(adc[i].valor);
        }
}

ISR(ADC_vect)
{
    adc[canal_actual].valor = ADC;
    adc[canal_actual].hay_conversion = true;
    int8_t proximo = obtener_proximo();
    if ( proximo == primer_canal )
        fnqueue_add(adc_loop);
    canal_actual = proximo;
	cambiar_canal(canal_actual);
    ADCSRA |= (1 << ADSC);	// iniciar conversión.
}






LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void callback0(int16_t valor)
{
    lcd.clear();
	lcd.print("0:");
    lcd.print(valor);
}

void callback1(int16_t valor)
{
    lcd.clear();
	lcd.print("1:");
    lcd.print(valor);
}

void callback2(int16_t valor)
{
    lcd.clear();
	lcd.print("2:");
    lcd.print(valor);
}

void callback3(int16_t valor)
{
    lcd.clear();
	lcd.print("3:");
    lcd.print(valor);
}

void callback4(int16_t valor)
{
    lcd.clear();
	lcd.print("4:");
    lcd.print(valor);
}

void callback5(int16_t valor)
{
    lcd.clear();
	lcd.print("5:");
    lcd.print(valor);
}

int main()
{
	init();
	pinMode(10, OUTPUT);

	lcd.begin(16,2);
	analogWrite(10, 255);

	struct adc_cfg adc0, adc1, adc2, adc3, adc4, adc5;

    // adc2.canal = 2;
    // adc2.callback = callback2;
    // adc_init(&adc2);

    // adc4.canal = 4;
	// adc4.callback = callback4;
	// adc_init(&adc4);
   
	// adc0.canal = 0;
	// adc0.callback = callback0;
	// adc_init(&adc0);

	while (1)
		fnqueue_run();
	return 0;
}
