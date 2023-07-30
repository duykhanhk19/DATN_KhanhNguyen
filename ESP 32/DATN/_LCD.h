#ifndef _LCD__H__
#define _LCD__H__

#include "Arduino.h"
#include "pinout.h"
#include <LiquidCrystal_I2C.h>

void initLCD();
void LCDRunTask(void *parameter);

#endif // _LCD__H__
