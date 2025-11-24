#ifndef __BUTTON_H__
#define __BUTTON_H__
#include <Arduino.h>
#include "global.h"

void TaskButtonMonitor(void *pvParameters);
void TaskAction(void *pvParameters);

#endif