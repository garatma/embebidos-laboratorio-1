#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>
#include "Arduino.h"
#define CANTIDAD_MAXIMA_DATOS 5

void TaskProducir(void * parametros);
void TaskConsumir(void * parametros);

int cont=0;

SemaphoreHandle_t s_acceso, s_libres, s_ocupados;

QueueHandle_t datos;

void setup() {
  Serial.begin(9600);
 
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
      (void *) 100, // tiempo de espera
      1, 
      NULL );

    xTaskCreate(
      TaskProducir,
      (const portCHAR *)"Blink",
      128, 
      (void *) 50, // tiempo de espera
      1, 
      NULL );

    xTaskCreate(
      TaskConsumir,
      (const portCHAR *)"AnalogRead",
      128,
      (void *) 75, // tiempo de espera
      2,
      NULL );
  }
}

void loop()
{
}

// el dato a insertar es el tiempo de espera. en cada iteración, se incrementa
// en uno.
void TaskProducir(void * parametros)  
{
  uint32_t tiempo_espera = (uint32_t) parametros; 
  uint32_t dato = tiempo_espera;
  while(1)
  {
    xSemaphoreTake(s_libres, (TickType_t) portMAX_DELAY);
    xSemaphoreTake(s_acceso, (TickType_t) portMAX_DELAY);
    Serial.print("Productor inserta: ");
    Serial.print(dato);
    Serial.print(". Hay ");
    cont++;
    Serial.print(cont);
    Serial.println(" elementos en la cola.");
    xQueueSend(datos, &dato, portMAX_DELAY);
    xSemaphoreGive(s_ocupados);
    xSemaphoreGive(s_acceso);
    dato++;
    vTaskDelay(tiempo_espera / portTICK_PERIOD_MS);
  }
}

void TaskConsumir(void * parametros)  // This is a task.
{
  uint32_t tiempo_espera = (uint32_t) parametros; 
  uint32_t dato = tiempo_espera;

  while(1)
  {
    xSemaphoreTake(s_ocupados,(TickType_t) portMAX_DELAY);
    xSemaphoreTake(s_acceso, (TickType_t) portMAX_DELAY);

    xQueueReceive(datos, &dato, portMAX_DELAY);
    xSemaphoreGive(s_libres);
    xSemaphoreGive(s_acceso);
    Serial.print("Consumidor remueve: ");
    Serial.print(dato);
    Serial.print(". Hay ");
    cont--;
    Serial.print(cont);
  Serial.println(" elementos en la cola.");
    vTaskDelay(tiempo_espera / portTICK_PERIOD_MS);
  }
}
