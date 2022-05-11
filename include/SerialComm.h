#include "GreenhouseControllerConfiguration.h"
#include <HardwareSerial.h>
#include <Arduino.h>

class SerialComm {
private:
    uint32_t m_prevMillisPing = 0;
    const uint16_t m_pingInterval = 200;

    bool m_handshakeDone = false;

    void ping();

public:
    SerialComm();
    bool prevMillisPingDelayPassed(uint32_t currentMillis = millis());
    bool prevMillisPingTimeoutPassed(uint32_t currentMillis = millis());

    void tryHandshake(uint32_t currentMillis);
    void serialLoop(uint32_t currentMillis, GreenhouseControllerConfiguration config);
    void begin();

    bool connected() { return m_handshakeDone; }
};