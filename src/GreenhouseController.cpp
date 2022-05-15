/*
 * GreenhouseController.cpp -- part of the GreenhouseController project.
 *
 * Copyright (C) 2017 Jesper Flodin
 *
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
 * PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE,
 * YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR
 * CORRECTION.
 *
 * Keep in mind that there is no warranty and you are solely
 * responsible for the use of all these cool tools.
 */
#include "GreenhouseController.h"
#include "SerialComm.h"

#include <HardwareSerial.h>

GreenhouseController Greenhouse;
Display ledDisplay;
SerialComm serial { Greenhouse };

void GreenhouseController::begin()
{
    for (int i = 0; i < NUM_SENSORS; i++) {
        pinMode(HUMIDITYPOWER[i], OUTPUT);
        pinMode(HUMIDITYSENS[i], INPUT);
        pinMode(RELAY[i], OUTPUT);
        m_Sensors[i] = Sensor(i, m_GreenhouseConfiguration);
    }
    ledDisplay.begin();
    ledDisplay.showBoot();
    m_GreenhouseConfiguration = GreenhouseControllerConfiguration();
}

void GreenhouseController::readSensors()
{
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (m_Sensors[i].enabled() == true) { // If current sensor is enabled
            m_Sensors[i].readHumidity();
        }
    }
}
// 10 bytes
byte* GreenhouseController::readSerializedSensors(byte* emptyBytes, char delimiter)
{
    emptyBytes[0] = 'S';
    for (int i = 0; i < NUM_SENSORS; i++) {
        m_Sensors[i].readHumidity();
        emptyBytes[1 + 3 * i] = m_Sensors[i].getRawHumidity() & 0xFF;
        emptyBytes[2 + 3 * i] = m_Sensors[i].getRawHumidity() >> 8;
        emptyBytes[3 + 3 * i] = delimiter;
    }
    return emptyBytes;
}

void GreenhouseController::handleSensor(uint8_t sensor)
{
    if (m_Sensors[sensor].enabled() == true) { // If current sensor is enabled
        if (m_Sensors[sensor].intervalTimePassed(currentMillis, true)) {
            m_Sensors[sensor].readHumidity();

            // Serial.print(F("Sensor "));
            // Serial.println(m_Sensors[sensor].getID());

            // Serial.print(F("prevMillisPump: "));
            // Serial.println(m_Sensors[sensor].getPrevMillisPump());

            if (m_Sensors[sensor].pumpDelayPassed(currentMillis)) {
                // Serial.println(F("Reset nPump"));
                m_Sensors[sensor]
                    .resetPumpings();
            }

            // Serial.print(F("getPumpings: "));
            // Serial.println(m_Sensors[sensor].getPumpings());

            // Maxtime elapsed or humidity low
            if (m_Sensors[sensor].pumpTimeoutPassed(currentMillis, false) || (m_Sensors[sensor].lowHumidity() && m_Sensors[sensor].getPumpings() < 2)) {
                // Serial.println(F("Pump triggered"));
                m_Sensors[sensor].setPrevMillisPump(currentMillis);
                ledDisplay.showPump(sensor);
                m_Sensors[sensor].pump();
            }
        }

        if (sensor == (m_lastUpdatedSensor == NUM_SENSORS - 1 ? 0 : m_lastUpdatedSensor + 1)) {
            if (ledDisplay.intervalTimePassed()) {
                m_lastUpdatedSensor = m_lastUpdatedSensor == NUM_SENSORS - 1 ? 0 : m_lastUpdatedSensor + 1;

                ledDisplay.updateDisplay(sensor, m_Sensors[sensor].getHumidity());
            }
        }
    }
}

/* **** standard setup() function **** */
void setup()
{
    Greenhouse = GreenhouseController();
    Greenhouse.begin();
    serial.begin();

    Greenhouse.readSensors();
    Serial.println((long)&Greenhouse, HEX);
    Serial.println((long)Greenhouse.getSensor(0).m_Configuration, HEX);
}

void loop()
{
    Greenhouse.currentMillis = millis();

    if (serial.connected()) {

        serial.serialLoop(Greenhouse.currentMillis);
    } else {
        serial.tryHandshake(Greenhouse.currentMillis);
        if (serial.connected())
            ledDisplay.showUSB();

        for (int i = 0; i < NUM_SENSORS; i++) {
            Greenhouse.handleSensor(i);
        }
    }
}