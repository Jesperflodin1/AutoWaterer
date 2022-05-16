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

namespace GreenhouseController {

namespace {

    Sensor m_Sensors[NUM_SENSORS] {};
    uint8_t m_lastUpdatedSensor { NUM_SENSORS - 1 };
}
Sensor& getSensor(uint8_t sensor) { return m_Sensors[sensor]; }
unsigned long currentMillis = 0;

void begin()
{
    for (int i = 0; i < NUM_SENSORS; i++) {
        pinMode(HUMIDITYPOWER[i], OUTPUT);
        pinMode(HUMIDITYSENS[i], INPUT);
        pinMode(RELAY[i], OUTPUT);
        // m_Sensors[i] = Sensor();
    }
    Display::begin();
    Display::showBoot();
    SerialComm::begin();
}

void readSensors()
{
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (m_Sensors[i].enabled() == true) { // If current sensor is enabled
            m_Sensors[i].readHumidity();
        }
    }
}
// 10 bytes
byte* readSerializedSensors(byte* emptyBytes, char delimiter)
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

void handleSensor(uint8_t sensor)
{
    if (m_Sensors[sensor].enabled() == true) { // If current sensor is enabled
        if (m_Sensors[sensor].intervalTimePassed(currentMillis, true)) {
            m_Sensors[sensor].readHumidity();

            if (m_Sensors[sensor].pumpDelayPassed(currentMillis)) {
                m_Sensors[sensor]
                    .resetPumpings();
            }
            // Maxtime elapsed or humidity low
            if (m_Sensors[sensor].pumpTimeoutPassed(currentMillis, false) || (m_Sensors[sensor].lowHumidity() && m_Sensors[sensor].getPumpings() < 2)) {
                m_Sensors[sensor].setPrevMillisPump(currentMillis);
                Display::showPump(sensor);
                m_Sensors[sensor].pump();
            }
        }

        if (sensor == (m_lastUpdatedSensor == NUM_SENSORS - 1 ? 0 : m_lastUpdatedSensor + 1)) {
            if (Display::intervalTimePassed()) {
                m_lastUpdatedSensor = m_lastUpdatedSensor == NUM_SENSORS - 1 ? 0 : m_lastUpdatedSensor + 1;

                Display::updateDisplay(sensor, m_Sensors[sensor].getHumidity());
            }
        }
    }
}
}