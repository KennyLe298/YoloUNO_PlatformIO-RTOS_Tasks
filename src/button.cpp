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

    // Detect falling edge (Button Pressed)
    if (buttonState == LOW && lastButtonState == HIGH) {
      pressStartTime = millis();
      isLongPressSent = false;
    } 
    // Detect rising edge (Button Released)
    else if (buttonState == HIGH && lastButtonState == LOW) {
      if (!isLongPressSent) {
        // Short press (< 1000ms)
        Serial.println("Button: SHORT press detected. Sending '1'.");
        int msg = 1;
        // Send message to queue, wait indefinitely if queue is full
        xQueueSend(xButtonQueue, &msg, portMAX_DELAY);
      }
    }
    // Logic for Long Press (Holding button down)
    if (buttonState == LOW) {
      if (!isLongPressSent && (millis() - pressStartTime > 1000)) {
        //long press
        Serial.println("Button: LONG press detected. Sending '2'.");
        int msg = 2;
        xQueueSend(xButtonQueue, &msg, portMAX_DELAY);
        isLongPressSent = true; // flag to send once per press
      }
    }
    
    lastButtonState = buttonState;
    vTaskDelay(50);  // 50ms Debounce delay
  }
}

//receives signal and do actions
void TaskAction(void *pvParameters) {
  pinMode(GPIO_NUM_48, OUTPUT);
  int ledState = LOW;
  digitalWrite(GPIO_NUM_48, ledState);

  int receivedMsg;

  while(1) {
    // Block task until data is available in the Queue
    if (xQueueReceive(xButtonQueue, &receivedMsg, portMAX_DELAY) == pdTRUE) {
      if (receivedMsg == 1) {
        // Short Press: Toggle LED
        ledState = 1 - ledState;
        digitalWrite(GPIO_NUM_48, ledState == 1 ? HIGH : LOW);
      
      } else if (receivedMsg == 2) {
        // Long Press: Print Message
        Serial.println("LONG PRESS");
      }
    }
  }
}