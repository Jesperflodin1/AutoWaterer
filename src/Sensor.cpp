#include "Sensor.h"

bool Sensor::intervalTimePassed(uint32_t currentMillis) {
    uint32_t delta = currentMillis - this->prevMillisHumidityCheck;

    delta /= 60000UL;

    //if (delta >= this->config.)
}
bool Sensor::pumpTimeoutPassed(uint32_t currentMillis) {
    uint32_t delta = currentMillis - this->prevMillisPump;
}
bool Sensor::pumpDelayPassed(uint32_t currentMillis) {
    uint32_t delta = currentMillis - this->prevMillisPump;
}