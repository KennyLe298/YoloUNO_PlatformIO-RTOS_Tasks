#include "button.h"

#define BOOT GPIO_NUM_0


// Press the button and sends messages to the queue
void TaskButtonMonitor(void *pvParameters) {

  pinMode(BOOT, INPUT_PULLUP);
  int buttonState = HIGH;
  int lastButtonState = HIGH;
  unsigned long pressStartTime = 0;
  bool isLongPressSent = false;

  while(1) {
    buttonState = digitalRead(BOOT);

    if (buttonState == LOW && lastButtonState == HIGH) {
      pressStartTime = millis();
      isLongPressSent = false;
    } 
    else if (buttonState == HIGH && lastButtonState == LOW) {
      if (!isLongPressSent) {
        //short press
        Serial.println("Button: SHORT press detected. Sending '1'.");
        int msg = 1;
        xQueueSend(xButtonQueue, &msg, portMAX_DELAY);
      }
    }
    if (buttonState == LOW) {
      if (!isLongPressSent && (millis() - pressStartTime > 1000)) {
        //long press
        Serial.println("Button: LONG press detected. Sending '2'.");
        int msg = 2;
        xQueueSend(xButtonQueue, &msg, portMAX_DELAY);
        isLongPressSent = true;
      }
    }
    
    lastButtonState = buttonState;
    vTaskDelay(50); 
  }
}

//receives signal and do actions
void TaskAction(void *pvParameters) {
  pinMode(GPIO_NUM_48, OUTPUT);
  int ledState = LOW;
  digitalWrite(GPIO_NUM_48, ledState);

  int receivedMsg;

  while(1) {
    if (xQueueReceive(xButtonQueue, &receivedMsg, portMAX_DELAY) == pdTRUE) {
      if (receivedMsg == 1) {

        ledState = 1 - ledState;
        digitalWrite(GPIO_NUM_48, ledState == 1 ? HIGH : LOW);
      
      } else if (receivedMsg == 2) {
        Serial.println("LONG PRESS");
      }
    }
  }
}