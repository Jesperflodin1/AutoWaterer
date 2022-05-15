#include <HardwareSerial.h>
#include "GreenhouseControllerConfiguration.h"
#include "GreenhouseController.h"
#include "SerialComm.h"

SerialComm::SerialComm(GreenhouseController& controller)
{
    m_Controller = &controller;
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
        ping();
    }
}

void SerialComm::serialLoop(uint32_t currentMillis)
{
    if (prevMillisPingDelayPassed(currentMillis)) {
        ping();
        // Send sensor readings
        byte sensorBytes[10];
        /*Serial.println((long)&m_Controller->m_GreenhouseConfiguration, HEX);
        Serial.println((long)&m_Controller->getConfigurationController(), HEX);
        Serial.println((long)m_Controller, HEX);
        Serial.println((long)&m_Controller->m_GreenhouseConfiguration.StoredConfiguration, HEX);
        Serial.println((long)&m_Controller->m_GreenhouseConfiguration.StoredConfiguration.Data, HEX);
        Serial.println((long)&m_Controller->m_GreenhouseConfiguration.StoredConfiguration.Data.humidityCheckInterval, HEX);
        Serial.println((long)m_Controller->m_GreenhouseConfiguration.getHumidityCheckInterval(), HEX);*/
        m_Controller->getConfigurationController().Reset();
        // Serial.println((long)m_Controller, HEX);
        m_Controller->readSerializedSensors(sensorBytes, ',');
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
            m_Controller->getConfigurationController().setHumidityCheckInterval(val);

            Serial.print(F("."));
            Serial.print(F("H="));
            Serial.println(m_Controller->getConfigurationController().getHumidityCheckInterval());

            sendConfig();
        } else if (cmd == 'E') { // Enable
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            m_Controller->getConfigurationController().setEnabled(sensorNr - 1, value == 1);
            sendConfig();
        } else if (cmd == 'L') { // Limit
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            m_Controller->getConfigurationController().setHumidityLimit(sensorNr - 1, value);
            sendConfig();
        } else if (cmd == 'P') { // Pumptime
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            m_Controller->getConfigurationController().setPumpTime(sensorNr - 1, value);
            sendConfig();
        } else if (cmd == 'M') { // Maxpumpings
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            m_Controller->getConfigurationController().setMaxPumpings(sensorNr - 1, value);

            Serial.print(F("."));
            Serial.print(F("Sensor="));
            Serial.print(sensorNr - 1);
            Serial.print(F("."));
            Serial.print(F("M="));
            Serial.print(m_Controller->getConfigurationController().getMaxPumpings(sensorNr - 1));
            Serial.print(F("."));
            Serial.print(F("D="));
            Serial.println(m_Controller->getConfigurationController().getPumpDelay(sensorNr - 1));

            sendConfig();
        } else if (cmd == 'T') { // Pumptimeout
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            m_Controller->getConfigurationController().setPumpTimeout(sensorNr - 1, value);
            sendConfig();
        } else if (cmd == 'D') { // Pumpdelay
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            m_Controller->getConfigurationController().setPumpDelay(sensorNr - 1, value);

            Serial.print(F("."));
            Serial.print(F("Sensor="));
            Serial.print(sensorNr - 1);
            Serial.print(F("."));
            Serial.print(F("M="));
            Serial.print(m_Controller->getConfigurationController().getMaxPumpings(sensorNr - 1));
            Serial.print(F("."));
            Serial.print(F("D="));
            Serial.println(m_Controller->getConfigurationController().getPumpDelay(sensorNr - 1));

            sendConfig();
        } else if (cmd == 'K') { // CalDry
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint16_t value = atol(strtok(NULL, "\n"));
            m_Controller->getConfigurationController().setCalDry(sensorNr - 1, value);
            sendConfig();
        } else if (cmd == 'W') { // CalWet
            strtok((char*)inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint16_t value = atol(strtok(NULL, "\n"));
            m_Controller->getConfigurationController().setCalWet(sensorNr - 1, value);
            sendConfig();
        } else if (cmd == 'R') {
            m_Controller->getConfigurationController().Reset();
            m_Controller->getConfigurationController().Save();
            sendConfig();
        } else if (cmd == 'S') {
            bool success = m_Controller->getConfigurationController().Save();

            Serial.print(F(".SAVING="));
            Serial.println(success);

            sendConfig();
        }
    }
}

void SerialComm::sendConfig()
{
    byte configBytes[55];
    m_Controller->getConfigurationController().serializedConfig(configBytes, ',');

    // Serial.println(configBytes);
    for (int i = 0; i < 55; i++)
        Serial.write(configBytes[i]);
    Serial.println();
}

void SerialComm::ping()
{
    if (m_handshakeDone)
        Serial.println(F("X"));
    else
        Serial.println(F("Z"));
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