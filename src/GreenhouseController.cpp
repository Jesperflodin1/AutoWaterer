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
SerialComm serial;

// Setup eeprom, load config values, setup pins, init sensors, init display
GreenhouseController::GreenhouseController()
{
    GreenhouseConfiguration = GreenhouseControllerConfiguration();

    for (int i = 0; i < NUM_SENSORS; i++) {
        pinMode(HUMIDITYPOWER[i], OUTPUT);
        pinMode(HUMIDITYSENS[i], INPUT);
        pinMode(RELAY[i], OUTPUT);
    }

    ledDisplay.begin();
    ledDisplay.showBoot();
    lastUpdatedSensor = NUM_SENSORS - 1;
}

void GreenhouseController::setupSensors()
{
    for (int i = 0; i < NUM_SENSORS; i++) {
        Sensors[i] = Sensor(i, GreenhouseConfiguration);
    }
}

void GreenhouseController::readSensors()
{
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (Sensors[i].enabled() == true) { // If current sensor is enabled
            Sensors[i].readHumidity();
        }
    }
}
// 10 bytes
byte* GreenhouseController::readSerializedSensors(byte* emptyBytes, char delimiter)
{
    emptyBytes[0] = 'S';
    for (int i = 0; i < NUM_SENSORS; i++) {
        Sensors[i].readHumidity();
        emptyBytes[1 + 3 * i] = Sensors[i].getRawHumidity() & 0xFF;
        emptyBytes[2 + 3 * i] = Sensors[i].getRawHumidity() >> 8;
        emptyBytes[3 + 3 * i] = delimiter;
    }
    return emptyBytes;
}

void GreenhouseController::handleSensor(uint8_t sensor)
{
    if (Sensors[sensor].enabled() == true) { // If current sensor is enabled
        if (Sensors[sensor].intervalTimePassed(currentMillis, true)) {
            Sensors[sensor].readHumidity();

            // Serial.print(F("Sensor "));
            // Serial.println(Sensors[sensor].getID());

            // Serial.print(F("prevMillisPump: "));
            // Serial.println(Sensors[sensor].getPrevMillisPump());

            if (Sensors[sensor].pumpDelayPassed(currentMillis)) {
                // Serial.println(F("Reset nPump"));
                Sensors[sensor]
                    .resetPumpings();
            }

            // Serial.print(F("getPumpings: "));
            // Serial.println(Sensors[sensor].getPumpings());

            // Maxtime elapsed or humidity low
            if (Sensors[sensor].pumpTimeoutPassed(currentMillis, false) || (Sensors[sensor].lowHumidity() && Sensors[sensor].getPumpings() < 2)) {
                // Serial.println(F("Pump triggered"));
                Sensors[sensor].setPrevMillisPump(currentMillis);
                ledDisplay.showPump(sensor);
                Sensors[sensor].pump();
            }
        }

        if (sensor == (lastUpdatedSensor == NUM_SENSORS - 1 ? 0 : lastUpdatedSensor + 1)) {
            if (ledDisplay.intervalTimePassed()) {
                lastUpdatedSensor = lastUpdatedSensor == NUM_SENSORS - 1 ? 0 : lastUpdatedSensor + 1;

                ledDisplay.updateDisplay(sensor, Sensors[sensor].getHumidity());
            }
        }
    }
}

// "heartbeat" function, called periodically while connected
/*void CustomHeartbeatCode () {
// Do while connected?
  static uint8_t curSensor = 0;
  readHumidity(curSensor);
  updateDisplay(curSensor, Sensors[curSensor].humidity);
  if (curSensor == NUM_SENSORS-1)
    curSensor = 0;
  else
    curSensor++;
} */

/* **** standard setup() function **** */
void setup()
{

    Greenhouse = GreenhouseController();
    Greenhouse.setupSensors();
    serial.begin();

    Greenhouse.readSensors();
}

void loop()
{
    Greenhouse.currentMillis = millis();
    if (serial.connected()) {

        serial.serialLoop(Greenhouse.currentMillis, Greenhouse);
    } else {
        serial.tryHandshake(Greenhouse.currentMillis);
        if (serial.connected())
            ledDisplay.showUSB();

        for (int i = 0; i < NUM_SENSORS; i++) {
            Greenhouse.handleSensor(i);
        }
    }
}