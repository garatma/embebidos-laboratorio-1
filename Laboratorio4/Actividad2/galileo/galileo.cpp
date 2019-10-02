#include "mraa.hpp"
#include <iostream>
#define INICIO         '!'
#define FIN            '}'
#define OBTENER_TEMP    0
#define OBTENER_MAX     1
#define OBTENER_MIN     2
#define OBTENER_PROM    3
#define OBTENER_TODO    4
#define RESPONDER_TEMP  5
#define RESPONDER_MAX   6
#define RESPONDER_MIN   7
#define RESPONDER_PROM  8
#define RESPONDER_TODO  9
using namespace std;

struct paquete
{
	uint8_t tipo;
	uint8_t longitud;
	uint8_t dato[4];
};

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
                                                                    
int8_t armar_paquete(char que_mostrar, struct paquete * paq)        
{                                                                   
	int8_t error = 0;                                           
	switch (que_mostrar)                                        
	{                                                           
		case 'a':                                           
			paq->tipo = OBTENER_TEMP;                   
			break;                                      
		case 'M':                                           
			paq->tipo = OBTENER_MAX;                    
			break;                                      
		case 'm':     
			paq->tipo = OBTENER_MIN;                           
			break;                                             
		case 'p':                                                  
			paq->tipo = OBTENER_PROM;                          
			break;                                             
		case 't':                                                  
			paq->tipo = OBTENER_TODO;                          
			break;                                             
		case 'q':                                           
			exit(0);                                    
			break;                                      
		default:                                            
			error = 1;                                  
	}                                                           
	paq->longitud = 0;                                          
	return error;                                               
}                                                                   
                                                                    
void salida(char que_mostrar, struct paquete * paq)                 
{                                                                   
	switch (que_mostrar)                                        
	{                                                           
		case 'a':                                           
			printf("Temperatura actual: %iC\n",paq->dato[0]);
			break;                                             
		case 'M':                                                  
			printf("Temperatura maxima: %iC\n",paq->dato[0]);  
			break;                                             
		case 'm':                                                  
			printf("Temperatura minima: %iC\n",paq->dato[0]);  
			break;                                             
		case 'p':                                                  
			printf("Temperatura promedio: %iC\n",paq->dato[0]);
			break;                                             
		case 't':                                                  
			printf("Temperatura actual: %iC\n",paq->dato[0]);  
			printf("Temperatura maxima: %iC\n",paq->dato[1]);
			printf("Temperatura minima: %iC\n",paq->dato[2]);
			printf("Temperatura promedio: %iC\n",paq->dato[3]);
			break;                                           
	}                                                                
}                                                                          
                                                                         
int main()                                                               
{                                                                          
	// Inicializar led conectado a GPIO y controlador de I2C         
	mraa::Gpio* d_pin = NULL;                                        
                                                                           
	d_pin = new mraa::Gpio(3, true, true);                           
                                                                         
	mraa::I2c* i2c;      
	i2c = new mraa::I2c(0);                                            
	i2c->address(8);                                                   
																	   
	uint8_t arreglo[8];                                                
	struct paquete paq;                                                
                                                                           
	char que_mostrar;                                                  
                                                                           
	printf("Que temperatura quiere mostrar? (a=Actual, ");             
	printf("M=maxima, m=Minima, p=Promedio, t=Todo, q=Quit): ");       
	while (1)                                                          
	{                                                                  
		cin >> que_mostrar;                                      
		if ( armar_paquete(que_mostrar, &paq) == 1 )             
			printf("Opcion no reconocida. ");                  
		else                                                     
		{                                                        
			struct_to_array(&paq,arreglo);                     
			i2c->write(arreglo, 8);                          
																 
			i2c->read(arreglo, 8);                             
			array_to_struct(&paq,arreglo);                   
			salida(que_mostrar,&paq);                        
		}                                                          
		printf("Ingrese otra opcion: ");                         
	}              
                                                       
	return 0;                                                        
}                    
