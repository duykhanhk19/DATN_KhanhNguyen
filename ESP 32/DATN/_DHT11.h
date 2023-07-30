#ifndef _DHT11__H__
#define _DHT11__H__

#include "DHT.h"
#include "pinout.h"
#include "common.h"
#include <Arduino.h>

#define DHTTYPE DHT11

void initDHT11();
void runDHT11Task(void * parameter);


#endif
