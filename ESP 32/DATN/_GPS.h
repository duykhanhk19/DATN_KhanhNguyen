#ifndef _GPS__H__
#define _GPS__H__

#include <TinyGPSPlus.h>
#include "SoftwareSerial.h"
#include <Arduino.h>
#include "pinout.h"
#include "common.h"

void initGPS();
void GPSRunTask(void *parameter);

#endif
