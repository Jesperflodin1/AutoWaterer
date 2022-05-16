#include <HardwareSerial.h>
#include "GreenhouseControllerConfiguration.h"
#include "GreenhouseController.h"
#include "SerialComm.h"

namespace GreenhouseController::SerialComm {
namespace {
    uint32_t m_prevMillisPing = 0;
    const uint16_t m_pingInterval = 2000;

    bool m_handshakeDone = false;

    void ping()
    {
        if (m_handshakeDone)
            Serial.println(F("X"));
        else
            Serial.println(F("Z"));
    }
    void sendConfig()
    {
        byte configBytes[55];
        GreenhouseControllerConfiguration::serializedConfig(configBytes, ',');

        // Serial.println(configBytes);
        for (int i = 0; i < 55; i++)
            Serial.write(configBytes[i]);
        Serial.println();
    }
}

bool connected() { return m_handshakeDone; }
void begin()
{
    Serial.begin(9600);
    // Serial.println(F("Booting..."));
}
void tryHandshake(uint32_t currentMillis)
{
    if (Serial.available() > 0) {
        // incoming?
        int inByte = Serial.read();
        if ((char)inByte == 'Z' || (char)inByte == 'X') {
            m_handshakeDone = true;
        }
    } else if (prevMillisPingDelayPassed(currentMillis)) {
        ping();
    }
}
void serialLoop(uint32_t currentMillis)
{
    if (prevMillisPingDelayPassed(currentMillis)) {
        ping();
        // Send sensor readings
        byte sensorBytes[10];

        GreenhouseController::readSerializedSensors(sensorBytes, ',');
        for (int i = 0; i < 10; i++)
            Serial.write(sensorBytes[i]); // CMD S
        Serial.println();

        /*if (m_handshakeDone && prevMillisPingTimeoutPassed(currentMillis)) {
            // Tear down serial connection, wait for new
            m_handshakeDone = false;
        }*/
    }
    if (Serial.available() > 0) {
        String inStr = Serial.readStringUntil('\n');
        char cmd = inStr.charAt(0);

        if (cmd == 'C') {
            // Send config
            sendConfig();
        } else if (cmd == 'H') { // humidityInterval
            strtok((char*)inStr.c_str(), ",");
            char* value = strtok(NULL, "\n");
            uint8_t val = atoi(value);
            GreenhouseControllerConfiguration::setHumidityCheckInterval(val);
            // sendConfig();
        } else if (cmd == 'E') { // Enable
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            GreenhouseControllerConfiguration::setEnabled(sensorNr - 1, value == 1);
            // sendConfig();
        } else if (cmd == 'L') { // Limit
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            GreenhouseControllerConfiguration::setHumidityLimit(sensorNr - 1, value);
            // sendConfig();
        } else if (cmd == 'P') { // Pumptime
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            GreenhouseControllerConfiguration::setPumpTime(sensorNr - 1, value);
            // sendConfig();
        } else if (cmd == 'M') { // Maxpumpings
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            GreenhouseControllerConfiguration::setMaxPumpings(sensorNr - 1, value);
            // sendConfig();
        } else if (cmd == 'T') { // Pumptimeout
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            GreenhouseControllerConfiguration::setPumpTimeout(sensorNr - 1, value);
            // sendConfig();
        } else if (cmd == 'D') { // Pumpdelay
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            GreenhouseControllerConfiguration::setPumpDelay(sensorNr - 1, value);
            // sendConfig();
        } else if (cmd == 'K') { // CalDry
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint16_t value = atol(strtok(NULL, "\n"));
            GreenhouseControllerConfiguration::setCalDry(sensorNr - 1, value);
            // sendConfig();
        } else if (cmd == 'W') { // CalWet
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint16_t value = atol(strtok(NULL, "\n"));
            GreenhouseControllerConfiguration::setCalWet(sensorNr - 1, value);
            // sendConfig();
        } else if (cmd == 'R') {
            GreenhouseControllerConfiguration::Reset();
            GreenhouseControllerConfiguration::Save();
            sendConfig();
        } else if (cmd == 'S') {
            GreenhouseControllerConfiguration::Save();
            sendConfig();
        }
    }
}
bool prevMillisPingDelayPassed(uint32_t currentMillis)
{
    uint32_t delta = currentMillis - m_prevMillisPing;

    if (delta >= (uint32_t)m_pingInterval) {
        m_prevMillisPing = currentMillis;
        return true;
    } else {
        return false;
    }
}
bool prevMillisPingTimeoutPassed(uint32_t currentMillis)
{
    uint32_t delta = currentMillis - m_prevMillisPing;

    if (delta >= (uint32_t)m_pingInterval * 10) {
        return true;
    } else {
        return false;
    }
}
    }