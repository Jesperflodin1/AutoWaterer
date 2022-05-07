#ifndef _SENSOR_H
#define _SENSOR_H
#include "GreenhouseControllerConfiguration.h"

extern SensorConfiguration config;

class Sensor {
    private:
        uint16_t rawValue;
        uint8_t humidity;

        
        unsigned long prevMillisPump = 0;
        unsigned long prevMillisHumidityCheck = 0;    // time of previous humidity check

        SensorConfiguration config;
    public:
        Sensor();

        // Check if interval in minutes has passed for this sensor
        bool intervalTimePassed(uint32_t currentMillis = millis());
        
        bool pumpTimeoutPassed(uint32_t currentMillis = millis());
        bool pumpDelayPassed(uint32_t currentMillis = millis());

};

#endif