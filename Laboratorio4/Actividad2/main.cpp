#include <Wire.h>
#include "Arduino.h"
#include "adc.h"
#include "fnqueue.h"
#include "packet-manager.h"
#define MAX_MUESTRAS 60

int8_t indice = 0,
	   cantidad_censados = 0;

uint8_t max = 0,
	    min = 125,
	    prom = 0,
	    actual = 0;

uint16_t suma = 0;

float muestras[MAX_MUESTRAS];

volatile int8_t ciclos = 0;
volatile bool leer_temperatura = false;

struct paquete paq;
uint8_t arreglo[8];

void requestEvent() 
{
	struct paquete dst;
	uint8_t datos[4] = {actual, max, min, prom};
	armar_paquete(&paq,&dst,datos);
	struct_to_array(&dst, arreglo);
	Wire.write(arreglo,8);
}

void receiveEvent(int howMany) 
{
	int8_t i = 0;
	while (Wire.available())
	{
		arreglo[i] = Wire.read();
		i++;
	}
	array_to_struct(&paq, arreglo);
}

void convertir_entrada_a_temperatura(int16_t valor)
{
	cli();
	if ( leer_temperatura )
	{
		leer_temperatura = false;
		sei();
		actual = valor/2.048;
		if ( actual < min ) min = actual;
		else if ( actual > max ) max = actual;
		if ( cantidad_censados < MAX_MUESTRAS )
			cantidad_censados++;
		else
			suma -= muestras[indice];

		muestras[indice] = actual;
		suma += actual;
		prom = suma/cantidad_censados;

		indice++;
		if ( indice == MAX_MUESTRAS )
			indice = 0;
	}
	else
		sei();
}

ISR(TIMER2_OVF_vect)
{
	ciclos++;
	if ( ciclos == 62 )
	{
		ciclos = 0;
		leer_temperatura = true;
	}
}

void setup()
{
	for ( int8_t i = 0; i < MAX_MUESTRAS; i++ )
		muestras[i] = 0;

	fnqueue_init();

	struct adc_cfg adc0;
	adc0.canal = 0;
	adc0.callback = &convertir_entrada_a_temperatura;
	adc_init(&adc0);

	TCCR2A = 0;
	TCCR2B = 0;
	TIMSK2 |= (1 << TOIE2);
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);

	Wire.begin(8);
	Wire.onRequest(requestEvent);
	Wire.onReceive(receiveEvent);
	Serial.begin(9600);
}

void loop()
{
	// delay(100);
	fnqueue_run();
}
