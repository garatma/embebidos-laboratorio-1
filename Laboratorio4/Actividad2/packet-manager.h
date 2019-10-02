#define INICIO 		   '!'
#define FIN 		   '}'
#define OBTENER_TEMP 	0
#define OBTENER_MAX  	1
#define OBTENER_MIN  	2
#define OBTENER_PROM 	3
#define OBTENER_TODO	4
#define RESPONDER_TEMP	5
#define RESPONDER_MAX	6
#define RESPONDER_MIN	7
#define RESPONDER_PROM	8
#define RESPONDER_TODO	9

struct paquete
{
	uint8_t tipo;
	uint8_t longitud;
	uint8_t dato[4];
};

void struct_to_array(struct paquete * paq, uint8_t arreglo[8]);
void array_to_struct(struct paquete * paq, uint8_t arreglo[8]);
void armar_paquete(struct paquete * src, struct paquete * dst, uint8_t dato[4]);
