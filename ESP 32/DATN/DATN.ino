#include <Arduino.h>
#include "_DHT11.h"
#include "_HCSR04.h"
#include "_GPS.h"
#include "_LoRa.h"
#include "_LCD.h"
#include "_Button.h"

TaskHandle_t DHT11TaskHandle, HCSR04TaskHandle, GPSTaskHandle, LoRaSendTaskHandle, LoRaReceiveTaskHandle;

void setup() {
//  Serial.begin(9600);

  pinMode(LED_STOP_PIN, OUTPUT);
  pinMode(LED_STATION_PIN, OUTPUT);
  pinMode(LED_OVERLOAD_PIN, OUTPUT);
  pinMode(LED_POWER_PIN, OUTPUT);
  
  initDHT11();
  xTaskCreatePinnedToCore(runDHT11Task,"runDHT11Task",1024*5,NULL,2,&DHT11TaskHandle,0);

  initHCSR04();
  xTaskCreatePinnedToCore(HCSR04RunTask_v2,"HCSR04RunTask",1024*5,NULL,2,&HCSR04TaskHandle,0);

  initGPS();
  xTaskCreatePinnedToCore(GPSRunTask,"GPSRunTask",1024*5,NULL,1,&GPSTaskHandle,0);

  initLoRa();
  xTaskCreatePinnedToCore(LoRaTransmitterRunTask,"LoRaTransmitterRunTask",1024*10,NULL,2,&LoRaSendTaskHandle,1);
  xTaskCreatePinnedToCore(LoRaReceiverRunTask,"LoRaReceiverRunTask",1024*10,NULL,1,&LoRaReceiveTaskHandle,1);

  initLCD();
  xTaskCreatePinnedToCore(LCDRunTask,"LCDRunTask",1024*5,NULL,1,NULL,0);

  initButton();
  xTaskCreatePinnedToCore(readButtonRunTask,"readButtonRunTask",1024*5,NULL,1,NULL,0);
}

void loop() 
{
  delay(10);
}
