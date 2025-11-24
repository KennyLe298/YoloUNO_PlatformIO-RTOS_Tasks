#include "global.h"

#include "led_blinky.h"
#include "button.h"
#include "neo_blinky.h"


void setup()
{
  Serial.begin(115200);
  // check_info_File(0);
  //!FIRST CREDIT
  xTaskCreate(TaskSingleLED, "Task LED Control", 2048, NULL, 2, NULL);
  xTaskCreate(neo_blinky, "Task NEO Blink", 2048, NULL, 2, NULL);
  
  //!SECOND CREDIT
  xButtonQueue = xQueueCreate(5, sizeof(int));

  if (xButtonQueue != NULL) {
    // Create the tasks
    xTaskCreate(TaskButtonMonitor, "Button Monitor", 2048, NULL, 1, NULL);
    xTaskCreate(TaskAction, "Action Task", 2048, NULL, 2, NULL);
  } else {
    Serial.println("Failed to create queue");
  }

}

void loop()
{
}