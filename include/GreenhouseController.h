#ifndef _GreenhouseController_h
#define _GreenhouseController_h

#include "Display.h"
#include "GreenhouseControllerConfiguration.h"
#include "PinConfiguration.h"
#include "Sensor.h"

class GreenhouseController {

private:
public:
    GreenhouseControllerConfiguration GreenhouseConfiguration {};
    Sensor Sensors[NUM_SENSORS] = { { 0, GreenhouseConfiguration }, { 1, GreenhouseConfiguration }, { 2, GreenhouseConfiguration } };
    unsigned long currentMillis = 0; // stores the value of millis() in each iteration of loop()
    uint8_t lastUpdatedSensor { NUM_SENSORS - 1 };
    GreenhouseController();
    void setupSensors();

    void readSensors();

    void handleSensor(uint8_t);
};

#endif
