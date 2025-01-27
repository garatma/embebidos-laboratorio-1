#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include "sys/alt_irq.h"
#include "system.h"
#include <stdio.h>
#include <stdlib.h>
#define PRIMERO_IN IN0_BASE
#define PRIMERO_OUT OUT0_BASE
#define BITS 8

int indice_actual = 0;
int actual = 0;

// ISR para el timer
void timer_isr(void * context)
{
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_BASE, 0);

	indice_actual = (indice_actual+1) % BITS;

	actual = IORD_ALTERA_AVALON_PIO_DATA(PRIMERO_IN+16*indice_actual);
	IOWR_ALTERA_AVALON_PIO_DATA(OUT_AUX_BASE,actual);

	// printf("actual: %i ",actual);
	// printf("con �ndice actual %i\n", indice_actual);
}

int obtener_posicion_menor()
{
	int menor = 512;
	int actual = 0;
	int posicion = -1;
	for (int i = 0; i < BITS; i++)
	{
		actual = IORD_ALTERA_AVALON_PIO_DATA(PRIMERO_OUT+i*16);
		if (actual < menor)
		{
			menor = actual;
			posicion = i;
		}
	}
	return posicion;
}

void mostrar_entrada()
{
	printf("entrada: ");
	for ( int i = 0; i < BITS; i++)
		printf("%i, ",IORD_ALTERA_AVALON_PIO_DATA(PRIMERO_OUT+i*16));
	printf("\n");
}

void mostrar_salida()
{
	printf("ordenados: ");
	for ( int i = 0; i < BITS; i++)
		printf("%i, ",IORD_ALTERA_AVALON_PIO_DATA(PRIMERO_IN+i*16));
	printf("\n");
}

int main()
{
	for (int i = 0; i < BITS; i++)
		IOWR_ALTERA_AVALON_PIO_DATA(PRIMERO_OUT+16*i, 0);

	// setear timer
	IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_BASE,0xf080);
	IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_BASE,0x2fa);

	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_BASE,7);

	alt_ic_isr_register(TIMER_IRQ_INTERRUPT_CONTROLLER_ID,
                        TIMER_IRQ,
                        timer_isr,0,0x0);

	int entrada = 0;
	int entrada_aux = 0;
	int pos_menor = 0; // �ndice que indica el menor n�mero
	while (1)
	{
		// obtener el valor de los pulsadores
		// si es distinto, almacenarlo
		entrada_aux = IORD_ALTERA_AVALON_PIO_DATA(IN_AUX_BASE);
		if (entrada_aux != entrada)
		{
			entrada = entrada_aux;
			pos_menor = obtener_posicion_menor();
			IOWR_ALTERA_AVALON_PIO_DATA(PRIMERO_OUT+16*pos_menor, entrada);
			mostrar_entrada();
			mostrar_salida();
			printf("\n");
		}
	}
	return 0;
}
