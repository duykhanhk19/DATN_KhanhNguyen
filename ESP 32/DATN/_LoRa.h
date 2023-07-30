#ifndef _LORA__H__
#define _LORA__H__

#include <HardwareSerial.h>
#include <Arduino.h>
#include <CRC32.h>
#include "pinout.h"
#include "common.h"

struct Header {
  unsigned int seq;
  unsigned int bus_id;
};

struct LoRaData{
   uint8_t temperature;
   uint8_t huminity;
   uint8_t peoples;
   double longitude;
   double latitude;
   float altitude;
   float speed;
   float bearing;
};

struct Station {
  int id;
};

void initLoRa();
void LoRaTransmitterRunTask(void *parameter);
void LoRaReceiverRunTask(void *parameter);
void updateLoRaData();
void calculateCheckSum();
void packDataSend();
void packChecksum();

#endif
