#include "_DHT11.h"

DHT dht(DHTPIN, DHTTYPE);
float temperature = 0, huminity = 0;

extern bool busIsStarted;

void initDHT11(){
  dht.begin();
}

void runDHT11Task(void * parameter){
  while(true){
    if(!busIsStarted) vTaskSuspend(NULL);
    
    temperature = dht.readTemperature();
    huminity = dht.readHumidity(); 

    Serial.print("====== Tem:");
    Serial.print(temperature);
    Serial.print(" , Humi: ");
    Serial.println(huminity);

    vTaskDelay(DURATION_READ_DHT11 / portTICK_PERIOD_MS);
  }  

  vTaskDelete( NULL );
}
