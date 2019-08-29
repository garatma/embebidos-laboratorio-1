#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
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





// variables:
int8_t operacion = 1;              // cómo ciclar el led.

void ciclo()
{
	int16_t apagado,
	 		prendido;

	switch (operacion)
	{
		case 1:
		    PORTB |= (1<<PB5);
			break;
		case 2:
			PORTB |= (1<<PB5);
			_delay_ms(1000);
			PORTB &= ~(1<<PB5);
			_delay_ms(1000);
			break;
		case 3:
			PORTB |= (1<<PB5);
			_delay_ms(500);
			PORTB &= ~(1<<PB5);
			_delay_ms(500);
			break;
		case 4:
			PORTB |= (1<<PB5);
			_delay_ms(500);
			PORTB &= ~(1<<PB5);
			_delay_ms(1000);
			break;
		default:
			PORTB &= ~(1<<PB5);
			break;
	}
}

int main()
{
	cli();
	// habilitar pin 2 para disparar interrupciones con cambio de flanco.
	EICRA |= (1<<ISC01);
	EIMSK |= (1<<INT0);
	sei();

    // inicializar el pin del 2 como entrada.
    DDRD &= ~(1<<DDD2);
    // inicializar el pin del led como salida.
    DDRB |= (1<<DDB5);

	// inicializar la cola de funciones
	fnqueue_init();

    while (1)
    {
		// desencolar y ejecutar.
		fnqueue_run();
    }
    return 0;
}

ISR(INT0_vect)
{
	// pasar al siguiente modo.
	operacion++;
	// volver al inicio (ya se usaron todos los modos).
	if ( operacion > 6 )
		operacion = 1;

	fnqueue_add(ciclo);
}
