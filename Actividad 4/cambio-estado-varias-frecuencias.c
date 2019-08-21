#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

// variables:
int buttonState;            // estado del botón.
int lastButtonState = 0;    // último estado del botón (para detectar cambios).
int operacion = 1;          // cómo ciclar el led.
int interrupcion = 0;       // detecta si, al esperar, se pulsa el botón.

void encendido()
{
    PORTB |= (1<<PB5);
}

/*
 * realiza el ciclo H-wait-L-wait con los retardos especificados. en lugar de
 * esperar todo el tiempo requerido de una vez, se lo divide en segmentos
 * iguales de 10 ms para, al finalizar, verificar si hubo o no un pulso del
 * botón.
 */
void ciclo(int prendido, int apagado)
{
    // prende el led.
    PORTB |= (1<<PB5);
    // ciclo espera-verificación interrupción.
    for (int i = 0; i < prendido/10; i++)
    {
        // esperar 10 ms
        _delay_ms(10);
        // verificar si hubo interrupción.
        if ( !interrupcion )
            interrupcion = PIND & (1<<PD2);
    }

    // apaga el led.
    PORTB &= ~(1<<PB5);
    // ciclo espera-verificación interrupción.
    for (int i = 0; i < apagado/10; i++)
    {
        // esperar 10 ms
        _delay_ms(10);
        // verificar si hubo interrupción.
        if ( !interrupcion )
            interrupcion = PIND & (1<<PD2);
    }
}

void apagado()
{
    PORTB &= ~(1<<PB5);
}

// determina qué ciclo utilizar.
void computar_operacion()
{
    // llamar a la función correspondiente.
    switch (operacion)
    {
        case 1:
            encendido();
            break;
        case 2:
            ciclo(1000,1000);
            break;
        case 3:
            ciclo(500,500);
            break;
        case 4:
            ciclo(250,250);
            break;
        case 5:
            ciclo(500,1000);
            break;
        case 6:
            apagado();
            break;
    }
}

int main()
{
    // inicializar el pin del pulsador como entrada.
    DDRD &= ~(1<<DDD2);
    // inicializar el pin del led como salida.
    DDRB |= (1<<DDB5);

    while (1)
    {
        // leer el estado del pulsador.
        buttonState = PIND & (1<<PD2) | interrupcion;

        computar_operacion();

        // si cambió el estado del pulsador.
        if ( buttonState != lastButtonState )
        {
            // si hay key up.
			if (!buttonState)
			{
                // pasar al siguiente modo.
                operacion++;
                // volver al inicio (ya se usaron todos los modos).
                if ( operacion > 6 ) operacion = 1;
			}

            // si hubo interrupcion: resetear la variable.
            if (interrupcion)
                interrupcion = 0;

        	// si hubo cambios hay que actualizar el valor anterior.
        	lastButtonState = buttonState;
        }
    }
    return 0;
}
