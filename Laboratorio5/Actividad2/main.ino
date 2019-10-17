#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>
#include "Arduino.h"
#define CANTIDAD_MAXIMA_DATOS 5

void TaskProducir(void * parametros);
void TaskConsumir(void * parametros);

SemaphoreHandle_t s_acceso, s_libres, s_ocupados;

QueueHandle_t datos;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	while(!Serial);

	datos = xQueueCreate(CANTIDAD_MAXIMA_DATOS,sizeof(uint32_t));
  
	s_libres = xSemaphoreCreateCounting(CANTIDAD_MAXIMA_DATOS,
										CANTIDAD_MAXIMA_DATOS);

    s_ocupados = xSemaphoreCreateCounting(CANTIDAD_MAXIMA_DATOS,0);

	s_acceso = xSemaphoreCreateMutex();
	
	if ( datos != NULL && 
		 s_libres != NULL && 
		 s_ocupados != NULL &&
		 s_acceso != NULL )
	{
		xSemaphoreGive(s_acceso);

		xTaskCreate(
			TaskProducir,
			(const portCHAR *)"Blink",
			128,
			(void *) 100,
			1, 
			NULL );

		xTaskCreate(
			TaskProducir,
			(const portCHAR *)"Blink",
			128, 
			(void *) 50,
			1, 
			NULL );

		xTaskCreate(
			TaskConsumir,
			(const portCHAR *)"AnalogRead",
			128,
			(void *) 75,
			2,
			NULL );
	}
}

void loop()
{
}

void TaskProducir(void * parametros)  
{
 	uint32_t tiempo_espera = (uint32_t) parametros; 
	uint32_t dato = tiempo_espera;

	while(1)
	{
		while (xSemaphoreTake(s_acceso, (TickType_t) portMAX_DELAY) != pdTRUE);
		while (xSemaphoreTake(s_libres, (TickType_t) portMAX_DELAY) != pdTRUE);
		xQueueSend(datos, &dato, portMAX_DELAY);
		xSemaphoreGive(s_ocupados);
		xSemaphoreGive(s_acceso);
		dato++;
		vTaskDelay(tiempo_espera / portTICK_PERIOD_MS);
	}
		

		/*
		if(xSemaphoreTake(SemAcceso,( TickType_t ) 5 )==pdTRUE)
		{
			  if(uxSemaphoreGetCount( SemBuffer )!=5)
			  {
				  xSemaphoreGive(SemBuffer);
				  //introducir en la cola
				  
			  }
			  xSemaphoreGive(SemAcceso);
			  vTaskDelay( 500 / portTICK_PERIOD_MS );
		}
		*/
}

void TaskConsumir(void * parametros)  // This is a task.
{
 	uint32_t tiempo_espera = (uint32_t) parametros; 
	uint32_t dato = tiempo_espera;

	while(1)
	{
		while (xSemaphoreTake(s_acceso, (TickType_t) portMAX_DELAY) != pdTRUE);
		while (xSemaphoreTake(s_ocupados,(TickType_t)portMAX_DELAY) != pdTRUE);
		while (xQueueReceive(datos, &dato, portMAX_DELAY) != pdPASS);
		xSemaphoreGive(s_libres);
		xSemaphoreGive(s_acceso);
		Serial.println(dato);
		vTaskDelay(tiempo_espera / portTICK_PERIOD_MS);
	}
		/*
		if(xSemaphoreTake(SemAcceso,( TickType_t ) 5 )==pdTRUE)
		{
			if(uxSemaphoreGetCount( SemBuffer )>0)
			{
				xSemaphoreTake(SemBuffer,( TickType_t ) 5 );
				//sacar de la cola y mostrar el dato
			}
			xSemaphoreGive(SemAcceso);
			vTaskDelay( 750 / portTICK_PERIOD_MS ); 
		}
		*/
}
