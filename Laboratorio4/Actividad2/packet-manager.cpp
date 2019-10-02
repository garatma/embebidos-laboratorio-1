#include <stdint.h>
#include "packet-manager.h"

void struct_to_array(struct paquete * paq, uint8_t arreglo[8])
{
	arreglo[0] = INICIO;
	arreglo[1] = paq->tipo;
	arreglo[2] = paq->longitud;
	for ( int8_t i = 0; i < 4; i++ )
		arreglo[i+3] = paq->dato[i];
	arreglo[7] = FIN;
}

void array_to_struct(struct paquete * paq, uint8_t arreglo[8])
{
	if ( arreglo[0] == INICIO && arreglo[7] == FIN )
	{
		paq->tipo = arreglo[1];
		paq->longitud = arreglo[2];
		for ( int8_t i = 0; i < 4; i++ )
			paq->dato[i] = arreglo[i+3];
	}
}

void armar_paquete(struct paquete * src, struct paquete * dst, uint8_t dato[4])
{
	int8_t longitud = 1;
	switch (src->tipo)
	{
		case OBTENER_TEMP:
			dst->tipo = RESPONDER_TEMP;
			break;
		case OBTENER_MAX:
			dst->tipo = RESPONDER_MAX;
			dato[0] = dato[1];
			break;
		case OBTENER_MIN:
			dst->tipo = RESPONDER_MIN;
			dato[0] = dato[2];
			break;
		case OBTENER_PROM:
			dst->tipo = RESPONDER_PROM;
			dato[0] = dato[3];
			break;
		case OBTENER_TODO:
			dst->tipo = RESPONDER_TODO;
			longitud = 4;
			break;
	}
	dst->longitud = longitud;
	for (int i = 0; i < longitud; i++)
		dst->dato[i] = dato[i];
	for ( int i = longitud; i < 4; i++ )
		dst->dato[i] = 255;
}
