#include "SerialComm.h"

SerialComm::SerialComm()
{
}

void SerialComm::begin()
{
    Serial.begin(9600);
    // Serial.println(F("Booting..."));
}

void SerialComm::tryHandshake(uint32_t currentMillis)
{
    if (Serial.available() > 0) {
        // incoming?
        int inByte = Serial.read();
        if ((char)inByte == 'Z' || (char)inByte == 'X') {
            m_handshakeDone = true;
        }
    } else if (prevMillisPingDelayPassed(currentMillis)) {
        if (Serial.available() <= 0) {

            ping();
        }
    }
}

void SerialComm::serialLoop(uint32_t currentMillis, GreenhouseControllerConfiguration config)
{
    if (prevMillisPingDelayPassed(currentMillis)) {
        ping();
        // Send sensor readings

        if (m_handshakeDone && prevMillisPingTimeoutPassed(currentMillis)) {
            // Tear down serial connection, wait for new
            m_handshakeDone = false;
        }
    }
    if (Serial.available() > 0) {
        String inStr = Serial.readStringUntil('\n');
        char cmd = inStr.charAt(0);
        if (cmd == 'C') {
            // Send config
            byte configBytes[55];
            config.serializedConfig(configBytes, ',');

            // Serial.println(configBytes);
            for (int i = 0; i < 55; i++)
                Serial.write(configBytes[i]);
            Serial.println();
        } else if (cmd == 'Q') {
        }
    }
}

void SerialComm::ping()
{
    if (m_handshakeDone)
        Serial.println("X");
    else
        Serial.println("Z");
}

bool SerialComm::prevMillisPingDelayPassed(uint32_t currentMillis)
{
    uint32_t delta = currentMillis - m_prevMillisPing;

    if (delta >= (uint32_t)m_pingInterval) {
        m_prevMillisPing = currentMillis;
        return true;
    } else {
        return false;
    }
}
bool SerialComm::prevMillisPingTimeoutPassed(uint32_t currentMillis)
{
    uint32_t delta = currentMillis - m_prevMillisPing;

    if (delta >= (uint32_t)m_pingInterval * 10) {
        return true;
    } else {
        return false;
    }
}