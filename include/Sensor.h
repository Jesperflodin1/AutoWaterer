#ifndef _SENSOR_H
#define _SENSOR_H
#include "GreenhouseControllerConfiguration.h"

extern GreenhouseControllerConfiguration GreenhouseConfiguration;

class Sensor {
    private:
        uint16_t m_rawValue { 0 };
        uint8_t m_humidity { 0 };
        uint8_t m_nPump { 0 };

        uint8_t m_sensorId { 0 };
        
        unsigned long m_prevMillisPump { 0 };
        unsigned long m_prevMillisHumidityCheck { 0 };    // time of previous humidity check

    public:
        Sensor(uint8_t m_sensorId);

        // Check if interval in minutes has passed for this sensor
        bool intervalTimePassed(uint32_t currentMillis = millis(), bool autoReset = true);
        
        bool pumpTimeoutPassed(uint32_t currentMillis = millis(), bool autoReset = true);
        bool pumpDelayPassed(uint32_t currentMillis = millis());

        void readHumidity();
        uint8_t getHumidity() { return m_humidity; }

        void pump();
        uint8_t getPumpings() { return m_nPump; }
        void resetPumpings() { m_nPump == 0; }
};

#endif