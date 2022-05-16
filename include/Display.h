#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "Configuration.h"

namespace GreenhouseController::Display {
void begin();

// Check if interval in seconds has passed for this sensor
bool intervalTimePassed(const uint32_t& currentMillis = millis(), bool autoReset = true);

void updateDisplay(uint8_t, uint8_t);
void error(uint8_t);

void showBoot();
void showVersion(uint8_t);
void showVersion(uint8_t, uint8_t);
void showPump(uint8_t sensor);
void showUSB();
}

#endif