#include "neo_blinky.h"


void neo_blinky(void *pvParameters){

    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    strip.setBrightness(50); // Lower brightness 
    strip.clear();
    strip.show();

    while(1) {                      
        // RED
        strip.setPixelColor(0, strip.Color(255, 0, 0)); 
        strip.show(); 
        vTaskDelay(500); // Wait 0.5s

        // GREEN
        strip.setPixelColor(0, strip.Color(0, 255, 0)); 
        strip.show(); 
        vTaskDelay(500); 

        // BLUE
        strip.setPixelColor(0, strip.Color(0, 0, 255)); 
        strip.show(); 
        vTaskDelay(500); 

        // OFF
        strip.setPixelColor(0, strip.Color(0, 0, 0)); 
        strip.show(); 
        vTaskDelay(500); 
    }
}