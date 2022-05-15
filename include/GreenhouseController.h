#ifndef _GreenhouseController_h
#define _GreenhouseController_h

#include "Display.h"
#include "GreenhouseControllerConfiguration.h"
#include "PinConfiguration.h"
#include "Sensor.h"

class GreenhouseController {

private:
    Sensor m_Sensors[NUM_SENSORS] = { { 0, m_GreenhouseConfiguration }, { 1, m_GreenhouseConfiguration }, { 2, m_GreenhouseConfiguration } };
    uint8_t m_lastUpdatedSensor { NUM_SENSORS - 1 };

public:
    GreenhouseControllerConfiguration m_GreenhouseConfiguration;
    unsigned long currentMillis = 0; // stores the value of millis() in each iteration of loop()

    void begin();

    void readSensors();

    byte* readSerializedSensors(byte* emptyBytes, char delimiter);

    void handleSensor(uint8_t);

    Sensor& getSensor(uint8_t sensor) { return m_Sensors[sensor]; }

    GreenhouseControllerConfiguration& getConfigurationController() { return m_GreenhouseConfiguration; }
};

#endif
