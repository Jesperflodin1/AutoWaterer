#ifndef _GreenhouseController_h
#define _GreenhouseController_h

#include "Display.h"
#include "GreenhouseControllerConfiguration.h"
#include "Configuration.h"
#include "Sensor.h"
#include "SerialComm.h"

namespace GreenhouseController {
extern unsigned long currentMillis; // stores the value of millis() in each iteration of loop()

void begin();

void readSensors();

byte* readSerializedSensors(byte* emptyBytes, char delimiter);

void handleSensor(uint8_t);

Sensor& getSensor(uint8_t sensor);
}

#endif
