#include <HardwareSerial.h>
#include <Arduino.h>

class SerialComm {
private:
    uint32_t prevMillisPing = 0;
    const uint16_t pingInterval = 500;

public:
    SerialComm();
    bool prevMillisPingDelayPassed(uint32_t currentMillis = millis());
    bool prevMillisPingTimeoutPassed(uint32_t currentMillis = millis());
};