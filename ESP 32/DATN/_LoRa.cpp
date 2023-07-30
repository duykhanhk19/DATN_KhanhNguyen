#include "_LoRa.h"

Header header = {0, BUS_ID}; 
const char startByte = START_BYTE;
const char endByte = END_BYTE;

LoRaData data;
uint8_t checksum;
int dataSendSize = sizeof(header) + sizeof(data) + sizeof(checksum) + 2 * sizeof(char);
char *dataSend = new char[dataSendSize];
char rcvBuffer[MAX_RCV_BUFFER];
int currRcvBufferLen = 0;

Station dataRcv;
int noOfStations = 3;
int stationList[3] = {59001, 59002, 59003};

int dataReceiveSize = sizeof(Station) + 2 * sizeof(char);

extern float temperature, huminity, longitude, latitude, altitude, speed, bearing;
extern int peoples;

extern bool busIsStarted;

void initLoRa(){
  Serial2.begin(19200);
}

void updateLoRaData(){
  data.temperature = int(temperature);
  data.huminity = int(huminity);
  data.longitude = longitude;
  data.latitude = latitude;
  data.altitude = altitude;
  data.speed = speed;
  data.bearing = bearing;
  data.peoples = peoples;

//  Serial.print("Temp: ");
//  Serial.println(temperature);
//  Serial.print("Humi: ");
//  Serial.println(huminity);
//  Serial.print("Long: ");
//  Serial.println(longitude);
//  Serial.print("Lat: ");
//  Serial.println(latitude);
//  Serial.print("Alt: ");
//  Serial.println(altitude);
//  Serial.print("Speed: ");
//  Serial.println(speed);
}

void calculateCheckSum(){
  checksum = 0;
  for (int i = 1; i <= (sizeof(header) + sizeof(data)); ++i) {
    checksum ^= dataSend[i];
  }
}

void packDataSend(){
  int offset = 0;
  memcpy(&dataSend[offset], &startByte, sizeof(char));
  offset += sizeof(char);
  memcpy(&dataSend[offset], &header, sizeof(header));
  offset += sizeof(header);
  memcpy(&dataSend[offset], &data, sizeof(data));
  offset += sizeof(data);

  calculateCheckSum();
  memcpy(&dataSend[offset], &checksum, sizeof(checksum));
  offset += sizeof(checksum);
  memcpy(&dataSend[offset], &endByte, sizeof(char));
}

void LoRaTransmitterRunTask(void *parameter){
  int i = 0;
  while(true){
    if(!busIsStarted) vTaskSuspend(NULL);
    
    header.seq = 0;
    updateLoRaData();
    packDataSend();
    
//    Serial.print("Send data - ");
//    Serial.println(i);
    Serial2.write(dataSend, dataSendSize);
    
    vTaskDelay(DURATION_SEND_LORA / portTICK_PERIOD_MS);
  }
}

void LoRaReceiverRunTask(void *parameter){
  String received = "";
  int i = 0, j = 0, i1 = 0;
  int counter = 1000;
  while(true){
    if(!busIsStarted) vTaskSuspend(NULL);

    if(counter == 200){
      digitalWrite(LED_STATION_PIN, LOW);
      counter = 1000;
    }
    else if(counter <= 200){
      counter++;
    }
    
    if(Serial2.available() > 0){ 
      if(currRcvBufferLen < MAX_RCV_BUFFER){
        rcvBuffer[currRcvBufferLen++] = Serial2.read();
      }

//      Serial.println("---- Received from pi");
//      for(int i = 0; i < currRcvBufferLen; i++){
//        Serial.print(rcvBuffer[i]);
//      }
//      Serial.println();

      i = 0;
      while(i < currRcvBufferLen && rcvBuffer[i] != '*') i++;
      if(i >= currRcvBufferLen){
        currRcvBufferLen = 0;
        continue;
      }

      i1 = i + 1;
      while(i1 < currRcvBufferLen && rcvBuffer[i1] != '*') i1++;
      if(i1 < currRcvBufferLen && i1 - i <= dataReceiveSize){
        i = 0;
        for(int k = i1; k < currRcvBufferLen; k++){
          rcvBuffer[i++] = rcvBuffer[k];
        }
        currRcvBufferLen = i;

        continue;
      }
      
      j = i + 1;
      while(j < currRcvBufferLen && rcvBuffer[j] != '#') j++;
      if(j >= currRcvBufferLen){
        continue;
      }

      if(j - i == dataReceiveSize - 1){
        memcpy(&dataRcv, &rcvBuffer[i + sizeof(char)], sizeof(Station));

//        Serial.println("++++ ");
//        Serial.println(rcvBuffer[i]);
//        Serial.println(rcvBuffer[j]);
//        Serial.println(dataRcv.id);
//        Serial.println(dataRcv.msg);
//
//        for(int i = 0; i < noOfStations; i++){
          if(ROUTE_ID == dataRcv.id){
//            if(dataRcv.msg == STOP_MSG_NUMBER){
//              Serial.println("Check OKKKKKKKKKKKK");
              header.seq = dataRcv.id;
              updateLoRaData();
              packDataSend();
              digitalWrite(LED_STATION_PIN, HIGH);
              counter = 0;
              Serial2.write(dataSend, dataSendSize);
//            }
          }
//        }

        i = 0;
        for(int k = j + 1; k < currRcvBufferLen; k++){
          rcvBuffer[i++] = rcvBuffer[k];
        }
        currRcvBufferLen = i;
      }
    }
    vTaskDelay(DURATION_RECEIVE_LORA / portTICK_PERIOD_MS);
  }
}
