#include "_Button.h"
#include "_HCSR04.h"

bool busIsStarted = false;

extern TaskHandle_t DHT11TaskHandle, HCSR04TaskHandle, GPSTaskHandle, LoRaSendTaskHandle, LoRaReceiveTaskHandle;
extern float temperature, huminity;

void initButton(){
  pinMode(START_BUTTON_PIN, INPUT);
  pinMode(BUTTON_1_PIN, INPUT);
}

void readButtonRunTask(void * parameter){
  int button1State, buttonStartStopState;
  int counter1 = 0, counterStartStop = 0;
  while(true){
    button1State = digitalRead(BUTTON_1_PIN);
    buttonStartStopState = digitalRead(START_BUTTON_PIN);

    if(button1State == HIGH){
      counter1++;
      if(counter1 == NO_OF_BUTTON_DEBOUNCING){
        if(busIsStarted) {
          digitalWrite(LED_STOP_PIN, !digitalRead(LED_STOP_PIN));
        }
      }
      else if(counter1 > NO_OF_BUTTON_DEBOUNCING){
        counter1 = NO_OF_BUTTON_DEBOUNCING + 5;
      }
    }
    else{
      counter1 = 0;
    }

    if(buttonStartStopState == HIGH){
      counterStartStop++;
      if(counterStartStop == NO_OF_BUTTON_DEBOUNCING){
        busIsStarted = !busIsStarted;
        if(busIsStarted){
          temperature = 0; 
          huminity = 0;
  
          vTaskResume(DHT11TaskHandle);
          xTaskCreatePinnedToCore(HCSR04RunTask_v2,"HCSR04RunTask",1024*5,NULL,2,NULL,0);
          vTaskResume(GPSTaskHandle);
          vTaskResume(LoRaSendTaskHandle);
  
          while(Serial2.available() > 0){
            Serial2.read();
          }
          vTaskResume(LoRaReceiveTaskHandle);

          digitalWrite(LED_POWER_PIN, HIGH);
        }
        else{
          digitalWrite(LED_STOP_PIN, LOW);
          digitalWrite(LED_STATION_PIN, LOW);
          digitalWrite(LED_OVERLOAD_PIN, LOW);
          digitalWrite(LED_POWER_PIN, LOW);
        }
      }
      else if(counterStartStop > NO_OF_BUTTON_DEBOUNCING){
        counterStartStop = NO_OF_BUTTON_DEBOUNCING + 5;
      }
    }
    else{
        counterStartStop = 0;
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
