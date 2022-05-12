#include "SerialComm.h"

SerialComm::SerialComm(GreenhouseController& controller)
{
    m_controller = &controller;
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

void SerialComm::serialLoop(uint32_t currentMillis)
{
    if (prevMillisPingDelayPassed(currentMillis)) {
        ping();
        // Send sensor readings
        byte sensorBytes[10];
        m_controller->readSerializedSensors(sensorBytes, ',');
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
            strtok(inStr.c_str(), ",");
            char* value = strtok(NULL, "\n");
            uint8_t val = atoi(value);
            m_controller->GreenhouseConfiguration.getGlobalConfig().sethumidityCheckInterval(val);
            sendConfig();
        } else if (cmd == 'E') { // Enable
            strtok(inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            m_controller->GreenhouseConfiguration.getSensorConfig(sensorNr - 1).setEnable(value == 1);
            sendConfig();
        } else if (cmd == 'L') { // Limit
            strtok(inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            m_controller->GreenhouseConfiguration.getSensorConfig(sensorNr - 1).setHumidityLimit(value);
            sendConfig();
        } else if (cmd == 'P') { // Pumptime
            strtok(inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            m_controller->GreenhouseConfiguration.getSensorConfig(sensorNr - 1).setPumpTime(value);
            sendConfig();
        } else if (cmd == 'M') { // Maxpumpings
            strtok(inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            m_controller->GreenhouseConfiguration.getSensorConfig(sensorNr - 1).setMaxPumpings(value);
            sendConfig();
        } else if (cmd == 'T') { // Pumptimeout
            strtok(inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            m_controller->GreenhouseConfiguration.getSensorConfig(sensorNr - 1).setPumpTimeout(value);
            sendConfig();
        } else if (cmd == 'D') { // Pumpdelay
            strtok(inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint8_t value = atoi(strtok(NULL, "\n"));
            m_controller->GreenhouseConfiguration.getSensorConfig(sensorNr - 1).setPumpDelay(value);
            sendConfig();
        } else if (cmd == 'K') { // CalDry
            strtok(inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint16_t value = atol(strtok(NULL, "\n"));
            m_controller->GreenhouseConfiguration.getSensorConfig(sensorNr - 1).setCalDry(value);
            sendConfig();
        } else if (cmd == 'W') { // CalWet
            strtok(inStr.c_str(), ",");
            uint8_t sensorNr = atoi(strtok(NULL, ","));
            uint16_t value = atol(strtok(NULL, "\n"));
            m_controller->GreenhouseConfiguration.getSensorConfig(sensorNr - 1).setCalWet(value);
            sendConfig();
        } else if (cmd == 'R') {
            m_controller->GreenhouseConfiguration.Reset();
            m_controller->GreenhouseConfiguration.Save();
            sendConfig();
        } else if (cmd == 'S') {
            m_controller->GreenhouseConfiguration.Save();
            sendConfig();
        }
    }
}

void SerialComm::sendConfig()
{
    byte configBytes[55];
    m_controller->GreenhouseConfiguration.serializedConfig(configBytes, ',');

    // Serial.println(configBytes);
    for (int i = 0; i < 55; i++)
        Serial.write(configBytes[i]);
    Serial.println();
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