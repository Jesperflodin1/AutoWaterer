#include "SerialComm.h"

SerialComm::SerialComm()
{
}

void SerialComm::serialLoop(uint32_t currentMillis)
{
    if (prevMillisPingTimeoutPassed(currentMillis)) {
        // Tear down serial connection, wait for new
    }
    if (prevMillisPingDelayPassed(currentMillis)) {
        ping();
    }
}

void SerialComm::ping()
{
    Serial.println("Z");
}

bool SerialComm::prevMillisPingDelayPassed(uint32_t currentMillis)
{
    uint32_t delta = currentMillis - m_prevMillisPing;

    if (delta >= (uint32_t)m_pingInterval) {
        m_prevMillisPing += m_pingInterval;
        return true;
    } else {
        return false;
    }
}
bool SerialComm::prevMillisPingTimeoutPassed(uint32_t currentMillis)
{
    uint32_t delta = currentMillis - m_prevMillisPing;

    if (delta >= (uint32_t)m_pingInterval * 6) {
        return true;
    } else {
        return false;
    }
}