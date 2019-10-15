#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// define two tasks for Blink & AnalogRead
void TaskProducir( void *pvParameters );
void TaskConsumir( void *pvParameters );

SemaphoreHandle_t SemPrender;
SemaphoreHandle_t SemApagar;
SemaphoreHandle_t SemAcceso;
SemaphoreHandle_t SemBuffer;

// the setup function runs once when you press reset or power the board
void setup() {
  
    SemApagar = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the Serial Port
    SemPrender = xSemaphoreCreateMutex();
    xSemaphoreGive( SemPrender );
    SemAcceso = xSemaphoreCreateMutex();
    xSemaphoreGive( SemAcceso );
    xSemaphoreTake( SemApagar ,( TickType_t ) 5 );
    SemBuffer = xSemaphoreCreateCounting( 5, 0 );
    
  // initialize serial communication at 9600 bits per second:

  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskProducir
    ,  (const portCHAR *)"Blink"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  (void *)1000
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

 xTaskCreate(
    TaskProducir
    ,  (const portCHAR *)"Blink"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  (void *)500
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );
    
  xTaskCreate(
    TaskConsumir
    ,  (const portCHAR *) "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  2    // Priority
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/
//uxSemaphoreGetCount( SemBuffer );

void TaskProducir(void *pvParameters )  // This is a task.
{
  
  uint8_t ms=(uint8_t) pvParameters;
  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  while(1) // A Task shall never return or exit.
  {
    if(xSemaphoreTake(SemAcceso,( TickType_t ) 5 )==pdTRUE)
    {
      if(uxSemaphoreGetCount( SemBuffer )!=5)
     {
      xSemaphoreGive(SemBuffer);
      //introducir en la cola
      
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
       // wait for one second
     
      }
      xSemaphoreGive(SemAcceso);
      vTaskDelay( 500 / portTICK_PERIOD_MS );
    }
  }
}

void TaskConsumir(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  while(1) 
  {
    if(xSemaphoreTake(SemAcceso,( TickType_t ) 5 )==pdTRUE)
    {
     if(uxSemaphoreGetCount( SemBuffer )>0)
     {
      xSemaphoreTake(SemBuffer,( TickType_t ) 5 );
      //sacar de la cola y mostrar el dato
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      
      
     }
     xSemaphoreGive(SemAcceso);
     vTaskDelay( 750 / portTICK_PERIOD_MS ); // wait for one second
    }
  }  
}
