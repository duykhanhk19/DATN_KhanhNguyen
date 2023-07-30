#ifndef _HCSR04__H__
#define _HCSR04__H__

#include "pinout.h"
#include "common.h"
#include <Arduino.h>

#define SOUND_SPEED 0.034

void initHCSR04();
float getDistance(int trigPin, int echoPin);
void HCSR04RunTask(void *parameter);
void HCSR04RunTask_v2(void *parameter);

#endif
