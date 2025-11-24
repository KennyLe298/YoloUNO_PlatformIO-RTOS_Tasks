#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define NEO_PIN 45
#define LED_COUNT 1 

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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  xTaskCreate(TaskSingleLED, "Task LED Control", 2048, NULL, 2, NULL);
  xTaskCreate(neo_blinky, "Task NEO Blinky", 2048, NULL, 2, NULL);
}

void loop() {
  // Serial.println("Hello Custom Board");
}




