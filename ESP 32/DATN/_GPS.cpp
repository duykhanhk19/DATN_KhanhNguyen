#include "_GPS.h"

TinyGPSPlus gps;

float altitude, speed, bearing;
double longitude, latitude;
extern bool busIsStarted;

void initGPS(){
//  SerialGPS.begin(9600);
//SerialGPS.begin(9600, SERIAL_8N1, GPS_TX, GPS_RX);
//SerialGPS.begin(9600,  EspSoftwareSerial::SWSERIAL_8N1, GPS_TX, GPS_RX);
//SerialGPS.enableIntTx(false);
Serial1.begin(9600, SERIAL_8N1, GPS_TX, GPS_RX);
}

void GPSRunTask(void *parameter){
  while(true){
    if(!busIsStarted) vTaskSuspend(NULL);
    
    if(Serial1.available() > 0){
      if (gps.encode(Serial1.read())) {
        longitude = gps.location.lat();
        latitude = gps.location.lng();
        altitude = gps.altitude.meters();
        speed = gps.speed.kmph();
        bearing = gps.course.deg();

//        Serial.print("+++++ Lon:");
//        Serial.print(longitude);
//        Serial.print(" , Lat: ");
//        Serial.println(latitude);
      }
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
