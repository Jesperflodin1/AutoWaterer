#include "GreenhouseControllerConfiguration.h"
#include "GreenhouseController.h"
#include <HardwareSerial.h>
#include <Arduino.h>

class SerialComm {
private:
    uint32_t m_prevMillisPing = 0;
    const uint16_t m_pingInterval = 2000;

    bool m_handshakeDone = false;

    void ping();

public:
    SerialComm();
    bool prevMillisPingDelayPassed(uint32_t currentMillis = millis());
    bool prevMillisPingTimeoutPassed(uint32_t currentMillis = millis());

    void tryHandshake(uint32_t currentMillis);
    void serialLoop(uint32_t currentMillis, GreenhouseController controller);
    void begin();

    bool connected() { return m_handshakeDone; }
};