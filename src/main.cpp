#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define NEO_PIN 45
#define LED_COUNT 1 

void TaskSingleLED(void *pvParameters) {
  //Initialize the specific GPIO pin for the onboard LED D13
  pinMode(GPIO_NUM_48, OUTPUT);
  
  while(1) {
    //First blink sequence
    digitalWrite(GPIO_NUM_48, HIGH); 
    vTaskDelay(200);      //Stop 200 ticks           
    digitalWrite(GPIO_NUM_48, LOW);  
    vTaskDelay(200);                 
    //Second blink sequence
    digitalWrite(GPIO_NUM_48, HIGH); 
    vTaskDelay(200);                 
    digitalWrite(GPIO_NUM_48, LOW);  
    vTaskDelay(200);                 
    // Long Pause between blink cycles
    // The CPU switches to the NeoPixel task during this 1.5s wait
    vTaskDelay(1500);               
  
  }
}


void neo_blinky(void *pvParameters){
  //Initialize the NeoPixel strip
    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    strip.setBrightness(50); //Setting brightness for the NEOPIXEL 
    strip.clear();
    strip.show();

    while(1) {                      
        // Cycle Colors: RED -> GREEN -> BLUE -> OFF
        // Each state holds for 500ms using non-blocking vTaskDelay
        
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

  // Create the tasks
  // Stack size: 2048 words
  // Priority: 2 (Equal priority means they share CPU time)
  xTaskCreate(TaskSingleLED, "Task LED Control", 2048, NULL, 2, NULL);
  xTaskCreate(TaskSingleLED, "Task LED Control", 2048, NULL, 2, NULL);
  xTaskCreate(neo_blinky, "Task NEO Blinky", 2048, NULL, 2, NULL);
}

void loop() {
  // Serial.println("Hello Custom Board");
}




