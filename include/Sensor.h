#ifndef _SENSOR_H
#define _SENSOR_H
//#include "GreenhouseControllerConfiguration.h"

class GreenhouseController;
class GreenhouseControllerConfiguration;

class Sensor {
private:
    uint16_t m_rawValue { 0 };
    uint8_t m_humidity { 0 };
    uint8_t m_nPump { 0 };

    uint8_t m_sensorId { 0 };

    unsigned long m_prevMillisPump { 0 };
    unsigned long m_prevMillisHumidityCheck { 0 }; // time of previous humidity check

public:
    GreenhouseControllerConfiguration* m_Configuration;
    Sensor(uint8_t m_sensorId, GreenhouseControllerConfiguration& config);

    // Check if interval in minutes has passed for this sensor
    bool intervalTimePassed(const uint32_t& currentMillis = millis(), bool autoReset = true);

    // Check if too much time has passed since last water pumping
    bool pumpTimeoutPassed(const uint32_t& currentMillis = millis(), bool autoReset = true);

    // Check if minimum delay has passed
    bool pumpDelayPassed(const uint32_t& currentMillis = millis());

    void readHumidity();
    uint8_t getHumidity() const { return m_humidity; }
    uint16_t getRawHumidity() const { return m_rawValue; }

    void pump();
    uint8_t getPumpings() const { return m_nPump; }
    void resetPumpings() { m_nPump = 0; }

    bool enabled();
    bool lowHumidity();

    void setPrevMillisPump(uint32_t millis) { m_prevMillisPump = millis; }

    uint8_t getID() const { return m_sensorId; }
    uint32_t getPrevMillisPump() const { return m_prevMillisPump; }
    uint32_t getPrevMillisHumidityCheck() const { return m_prevMillisHumidityCheck; }
};

#endif