#include "GreenhouseController.h"
#include "Sensor.h"

Sensor::Sensor(uint8_t sensorId) {
    m_sensorId = sensorId;
}

void Sensor::readHumidity() {

    digitalWriteFast(HUMIDITYPOWER[sensorId], HIGH); //Power on humidity sensor
    delay(200);
    m_rawValue = analogRead(HUMIDITYSENS[sensorId]);
    delay(200);
    digitalWriteFast(HUMIDITYPOWER[sensorId], LOW); //Power off sensor

    // Convert analog values
    // Constrain to calibration values
    m_humidity = constrain(m_rawValue, GreenhouseConfiguration.getSensorConfig(sensorId).calibrationWet, GreenhouseConfiguration.getSensorConfig(sensorId).calibrationDry);
    // Map between 0 to 100%
    m_humidity = map(m_humidity, GreenhouseConfiguration.getSensorConfig(sensorId).calibrationWet, GreenhouseConfiguration.getSensorConfig(sensorId).calibrationDry, 100, 0);
}

void Sensor::pump() {
    digitalWriteFast(RELAY[sensorId], HIGH);
    delay(GreenhouseConfiguration.getSensorConfig(sensorId).pumpTime * 1000);
    digitalWriteFast(RELAY[sensorId], LOW);
    m_nPump++; //Count the pumping
}

bool Sensor::intervalTimePassed(uint32_t currentMillis, bool autoReset) {
    uint32_t delta = currentMillis - m_prevMillisHumidityCheck;

    delta /= (60UL * 1000UL);

    if (delta >= (uint32_t)GreenhouseConfiguration.getGlobalConfig().humidityCheckInterval) 
    { 
        if (autoReset)
            m_prevMillisHumidityCheck += (uint32_t)GreenhouseConfiguration.getGlobalConfig().humidityCheckInterval * 60UL * 1000UL; //minutes to milliseconds
        return true; 
    } else {
        return false;
    }
}
bool Sensor::pumpTimeoutPassed(uint32_t currentMillis, bool autoReset) {
    uint32_t delta = currentMillis - m_prevMillisPump;

    delta /= (60UL * 60UL * 1000UL);

    if (delta >= (uint32_t)GreenhouseConfiguration.getSensorConfig(m_sensorId).pumpTimeout) 
    { 
        if (autoReset)
            m_prevMillisPump = currentMillis;
        return true; 
    } else {
        return false;
    }
}
bool Sensor::pumpDelayPassed(uint32_t currentMillis) {
    uint32_t delta = currentMillis - m_prevMillisPump;

    delta /= (60UL * 60UL * 1000UL);

    if (delta >= (uint32_t)GreenhouseConfiguration.getSensorConfig(m_sensorId).pumpDelay) 
    { 
        return true; 
    } else {
        return false;
    }
}