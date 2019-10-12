#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// define two tasks for Blink & AnalogRead
void TaskPrender( void *pvParameters );
void TaskApagar( void *pvParameters );

SemaphoreHandle_t SemPrender;

SemaphoreHandle_t SemApagar;

// the setup function runs once when you press reset or power the board
void setup() {
  
    SemApagar = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the Serial Port
    SemPrender = xSemaphoreCreateMutex();
    xSemaphoreGive( SemPrender );
    
    //xSemaphoreGive( SemApagar  );
    
    xSemaphoreTake( SemApagar ,( TickType_t ) 5 );
    
  // initialize serial communication at 9600 bits per second:

  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskPrender
    ,  (const portCHAR *)"Blink"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskApagar
    ,  (const portCHAR *) "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
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

void TaskPrender(void *pvParameters)  // This is a task.
{
  (void) pvParameters;



  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  while(1) // A Task shall never return or exit.
  {
    if(xSemaphoreTake(SemPrender,( TickType_t ) 5 )==pdTRUE)
    {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    xSemaphoreGive(SemApagar);
    }
  }
}

void TaskApagar(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  while(1) 
  {
    if(xSemaphoreTake(SemApagar,( TickType_t ) 5 )==pdTRUE)
    {
     digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
     vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
     xSemaphoreGive(SemPrender);
    }
  }
  
}
