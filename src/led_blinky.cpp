#include "led_blinky.h"

void TaskSingleLED(void *pvParameters) {
  pinMode(GPIO_NUM_48, OUTPUT);
  
  while(1) {
    
    digitalWrite(GPIO_NUM_48, HIGH); 
    vTaskDelay(200);                 
    digitalWrite(GPIO_NUM_48, LOW);  
    vTaskDelay(200);                 

    digitalWrite(GPIO_NUM_48, HIGH); 
    vTaskDelay(200);                 
    digitalWrite(GPIO_NUM_48, LOW);  
    vTaskDelay(200);                 

    vTaskDelay(1500);               
  
  }
}
