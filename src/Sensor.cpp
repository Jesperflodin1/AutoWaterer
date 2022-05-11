#include "GreenhouseController.h"
#include "Sensor.h"

Sensor::Sensor(uint8_t sensorId, GreenhouseControllerConfiguration &config) {
    m_sensorId = sensorId;
    m_Configuration = &config;
}

bool Sensor::enabled() {
    return m_Configuration->getSensorConfig(m_sensorId).enable;
}
bool Sensor::lowHumidity() {
    return m_humidity <= m_Configuration->getSensorConfig(m_sensorId).humidityLimit;
}

void Sensor::readHumidity() {

    digitalWriteFast(HUMIDITYPOWER[m_sensorId], HIGH); //Power on humidity sensor
    delay(200);
    m_rawValue = analogRead(HUMIDITYSENS[m_sensorId]);
    delay(200);
    digitalWriteFast(HUMIDITYPOWER[m_sensorId], LOW); //Power off sensor

    // Convert analog values
    // Constrain to calibration values
    m_humidity = constrain(m_rawValue, m_Configuration->getSensorConfig(m_sensorId).calibrationWet, m_Configuration->getSensorConfig(m_sensorId).calibrationDry);
    // Map between 0 to 100%
    m_humidity = map(m_humidity, m_Configuration->getSensorConfig(m_sensorId).calibrationWet, m_Configuration->getSensorConfig(m_sensorId).calibrationDry, 100, 0);
}

void Sensor::pump() {
    digitalWriteFast(RELAY[m_sensorId], HIGH);
    delay(m_Configuration->getSensorConfig(m_sensorId).pumpTime * 1000);
    digitalWriteFast(RELAY[m_sensorId], LOW);
    m_nPump++; //Count the pumping
}

bool Sensor::intervalTimePassed(const uint32_t& currentMillis, bool autoReset) {
    uint32_t delta = currentMillis - m_prevMillisHumidityCheck;

    delta /= (60UL * 1000UL);

    if (delta >= (uint32_t)m_Configuration->getGlobalConfig().humidityCheckInterval) 
    { 
        if (autoReset)
            m_prevMillisHumidityCheck += (uint32_t)m_Configuration->getGlobalConfig().humidityCheckInterval * 60UL * 1000UL; //minutes to milliseconds
        return true; 
    } else {
        return false;
    }
}
bool Sensor::pumpTimeoutPassed(const uint32_t& currentMillis, bool autoReset) {
    uint32_t delta = currentMillis - m_prevMillisPump;

    delta /= (60UL * 60UL * 1000UL);

    if (delta >= (uint32_t)m_Configuration->getSensorConfig(m_sensorId).pumpTimeout) 
    { 
        if (autoReset)
            m_prevMillisPump = currentMillis;
        return true; 
    } else {
        return false;
    }
}
bool Sensor::pumpDelayPassed(const uint32_t& currentMillis) {
    uint32_t delta = currentMillis - m_prevMillisPump;

    delta /= (60UL * 60UL * 1000UL);

    if (delta >= (uint32_t)m_Configuration->getSensorConfig(m_sensorId).pumpDelay) 
    { 
        return true; 
    } else {
        return false;
    }
}