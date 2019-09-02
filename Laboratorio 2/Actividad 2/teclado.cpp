#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "fnqueue.h"
#include "teclado.h"

volatile struct estructura_teclado estado_teclado_var;

void key_up_callback(void (*handler)(), int16_t tecla)
{
  estado_teclado_var.handlers_up[tecla] = handler;
}

void key_down_callback(void (*handler)(), int16_t tecla)
{
  estado_teclado_var.handlers_down[tecla] = handler;
}

void teclado_init()
{
  estado_teclado_var.last_key = 255;  // no se apretó ninguna tecla

  fnqueue_init(); // inicializar la cola de funciones.

  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADMUX |= (1 << REFS0);      // voltaje referencia.
  ADMUX &= ~(1 << ADLAR);     // left aligned (sheet: 24.9.3.1/2).
  ADCSRA |= (1 << ADATE);
  ADCSRA |= (1 << ADEN);      // enable ADC.
  ADCSRA |= (1 << ADIE);      // habilitar interrupciones.
  ADCSRB &= ~(1 << ADTS2);
  ADCSRB &= ~(1 << ADTS1);
  ADCSRB &= ~(1 << ADTS0);
  sei();
  ADCSRA |= (1 << ADSC);      // iniciar primera conversión.
}

// Convert ADC value to key number
int16_t get_key(unsigned int input)
{
    int16_t k;
    for (k = 0; k < 5; k++)
        if (input < adc_key_val[k])
            return k;

    if (k >= 5)
        k = 255;     // No valid key pressed

    return k;
}

void procesar_entrada()
{
    int16_t key = get_key((ADCL) | (ADCH << 8));
    switch (key)
    {
      case 0:
          estado_teclado_var.handlers_down[1]();
          estado_teclado_var.last_key = key;
          break;
      case 1:
          estado_teclado_var.handlers_down[2]();
          estado_teclado_var.last_key = key;
          break;
      case 2:
          estado_teclado_var.handlers_down[key]();
          estado_teclado_var.last_key = key;
          break;
      case 3:
          estado_teclado_var.handlers_down[key]();
          estado_teclado_var.last_key = key;
          break;
      case 4:
          estado_teclado_var.handlers_down[key]();
          estado_teclado_var.last_key = key;
          break;            
      default:
          estado_teclado_var.handlers_up[estado_teclado_var.last_key]();
          //ADCSRA |= (1 << ADSC);  // iniciar próxima conversión.
          estado_teclado_var.last_key = key;
          break;
    }
    /*if ( key > 4 | key < 0 )
  {
    // key up
    if ( -1 < last_key | last_key < 5 )
      estado_teclado_var.handlers_up[last_key]();
    ADCSRA |= (1 << ADSC);  // iniciar próxima conversión.
  }
    else
  {
    // key down
    estado_teclado_var.handlers_down[key]();
  }*/
}

ISR(ADC_vect)
{
  fnqueue_add(procesar_entrada);
}

