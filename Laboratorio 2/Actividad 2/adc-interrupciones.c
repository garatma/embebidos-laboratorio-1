#include <avr/io.h>

volatile int analogVal;

void setup(){
    Serial.begin(9600);

    ADMUX &= ~(1 << ADLAR);     // left aligned (sheet: 24.9.3.1/2).
    ADMUX |= (1 << REFS0);      // voltaje referencia.
    ADCSRA |= (1 << ADEN);      // enable ADC.
    ADCSRA |= (1 << ADIE);      // habilitar interrupciones.
    sei();

    ADCSRA |= (1 << ADSC);      // iniciar primera conversion.
}

void loop(){
    // enviar valor leido desde la interrupción.
    Serial.println(analogVal);
}

ISR(ADC_vect){
    analogVal = ADCL | (ADCH << 8); // leer valor.

    ADCSRA |= (1 << ADSC);  // iniciar próxima conversion.
}
