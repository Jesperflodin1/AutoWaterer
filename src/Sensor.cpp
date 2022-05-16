
#include "GreenhouseController.h"
#include "GreenhouseControllerConfiguration.h"
#include "Sensor.h"
#include <digitalWriteFast.h>

namespace GreenhouseController {

Sensor::Sensor() {
    m_sensorId = GreenhouseControllerConfiguration::getNextSensorId();
}

bool Sensor::enabled() {
    return GreenhouseControllerConfiguration::getEnabled(m_sensorId);
}
bool Sensor::lowHumidity() {
    return m_humidity <= GreenhouseControllerConfiguration::getHumidityLimit(m_sensorId);
}


void Sensor::readHumidity() {

    digitalWriteFast(HUMIDITYPOWER[m_sensorId], HIGH); //Power on humidity sensor
    delay(200);
    m_rawValue = analogRead(HUMIDITYSENS[m_sensorId]);
    delay(200);
    digitalWriteFast(HUMIDITYPOWER[m_sensorId], LOW); //Power off sensor

    // Convert analog values
    // Constrain to calibration values
    m_humidity = constrain(m_rawValue, GreenhouseControllerConfiguration::getCalWet(m_sensorId), GreenhouseControllerConfiguration::getCalDry(m_sensorId));
    // Map between 0 to 100%
    m_humidity = map(m_humidity, GreenhouseControllerConfiguration::getCalWet(m_sensorId), GreenhouseControllerConfiguration::getCalDry(m_sensorId), 100, 0);
}

void Sensor::pump() {
    digitalWriteFast(RELAY[m_sensorId], HIGH);
    delay(GreenhouseControllerConfiguration::getPumpTime(m_sensorId) * 1000);
    digitalWriteFast(RELAY[m_sensorId], LOW);
    m_nPump++; //Count the pumping
}

bool Sensor::intervalTimePassed(const uint32_t& currentMillis, bool autoReset) {
    uint32_t delta = currentMillis - m_prevMillisHumidityCheck;

    delta /= (60UL * 1000UL);

    if (delta >= (uint32_t)GreenhouseControllerConfiguration::getHumidityCheckInterval()) 
    { 
        if (autoReset)
            m_prevMillisHumidityCheck += (uint32_t)GreenhouseControllerConfiguration::getHumidityCheckInterval() * 60UL * 1000UL; //minutes to milliseconds
        return true; 
    } else {
        return false;
    }
    return false;
}
bool Sensor::pumpTimeoutPassed(const uint32_t& currentMillis, bool autoReset) {
    uint32_t delta = currentMillis - m_prevMillisPump;

    delta /= (60UL * 60UL * 1000UL);

    if (delta >= (uint32_t)GreenhouseControllerConfiguration::getPumpTimeout(m_sensorId)) 
    { 
        if (autoReset)
            m_prevMillisPump = currentMillis;
        return true; 
    } else {
        return false;
    }
    return false;
}
bool Sensor::pumpDelayPassed(const uint32_t& currentMillis) {
    uint32_t delta = currentMillis - m_prevMillisPump;

    delta /= (60UL * 60UL * 1000UL);

    if (delta >= (uint32_t)GreenhouseControllerConfiguration::getPumpDelay(m_sensorId)) 
    { 
        return true; 
    } else {
        return false;
    }
    return false;
}
}