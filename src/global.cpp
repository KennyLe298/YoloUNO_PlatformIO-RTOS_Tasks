#include "global.h"

// Create a queue capable of holding 5 integers
QueueHandle_t xButtonQueue = xQueueCreate(5, sizeof(int));