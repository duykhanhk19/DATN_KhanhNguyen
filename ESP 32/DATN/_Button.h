#ifndef __BUTTON__H__
#define __BUTTON__H__

#include "pinout.h"
#include "common.h"
#include <Arduino.h>

void initButton();
void readButtonRunTask(void * parameter);

#endif // __BUTTON__H__
