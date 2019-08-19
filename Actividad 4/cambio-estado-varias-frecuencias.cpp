// diferentes cambios de estado del led, según la entrada

#include <avr/io.h>
#include <util/delay.h>

// Variables:
int buttonState;            // estado del botón
int lastButtonState = 0;    // último estado del botón
int operacion = 0;         // cómo ciclar el led

// mantiene el led encendido
void encendido()
{
    PORTB |= (1<<PB5);
}

// realiza el ciclo H-wait-L-wait con los retardos especificados
// en los parámetros (en milisegundos)
void ciclo(int prendido, int apagado)
{
    PORTB |= (1<<PB5);
    _delay_ms(prendido);
    PORTB &= ~(1<<PB5);
    _delay_ms(apagado);
}

// mantiene el led apagado
void apagado()
{
    PORTB &= ~(1<<PB5);
}

// determina qué ciclo utilizar
void computar_operacion()
{
    // llamar a la función correspondiente
    if ( operacion == 0 ) encendido();
    else if ( operacion == 1 ) ciclo(1000,1000);
    else if ( operacion == 2 ) ciclo(500,500);
    else if ( operacion == 3 ) ciclo(250,250);
    else if ( operacion == 4 ) ciclo(500,1000);
    else if ( operacion == 5 ) apagado();
}

int main()
{
    // inicializar el pin del pulsador como entrada
    DDRD &= ~(1<<DDD2);

    // inicializar el pin del led como salida
    DDRB |= (1<<DDB5);

    while (1)
    {
        // leer el estado del pulsador
        buttonState = PIND & (1<<PD2);

        computar_operacion();

        // si cambió el estado del pulsador
        if ( buttonState != lastButtonState )
        {
            // si no está presionado el pulsador
			if (!buttonState)
			{
                // hubo un key_up
                // pasar al siguiente modo
                operacion++;
                // volver al inicio (ya se usaron todos los modos)
                if ( operacion > 5 ) operacion = 0;
			}
        }
    	// si hubo cambios válidos actualizo el valor de lectura anterior
    	lastButtonState = buttonState;
    }
    return 0;
}
