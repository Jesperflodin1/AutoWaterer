#include <HardwareSerial.h>
#include <Arduino.h>

class SerialComm {
private:
    uint32_t m_prevMillisPing = 0;
    const uint16_t m_pingInterval = 500;

    bool handshakeDone = false;

    void ping();

public:
    SerialComm();
    bool prevMillisPingDelayPassed(uint32_t currentMillis = millis());
    bool prevMillisPingTimeoutPassed(uint32_t currentMillis = millis());

    void serialLoop(uint32_t currentMillis);
};