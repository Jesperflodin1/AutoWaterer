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

#include <HardwareSerial.h>

GreenhouseController Greenhouse;
Display ledDisplay;

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

void GreenhouseController::handleSensor(uint8_t sensor)
{
    if (Sensors[sensor].enabled() == true) { // If current sensor is enabled
        if (Sensors[sensor].intervalTimePassed(currentMillis, true)) {
            Sensors[sensor].readHumidity();

            if (Sensors[sensor].pumpDelayPassed(currentMillis)) {
                Sensors[sensor].resetPumpings();
            }

            // Maxtime elapsed or humidity low
            if (Sensors[sensor].pumpTimeoutPassed(currentMillis, true) || (Sensors[sensor].lowHumidity() && Sensors[sensor].getPumpings() < 2)) {
                Sensors[sensor].pump();
            }
        }

        if (sensor == (lastUpdatedSensor == NUM_SENSORS - 1 ? 0 : lastUpdatedSensor + 1)) {
            if (ledDisplay.intervalTimePassed(currentMillis, true)) {
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
    Serial.begin(115200);
    Serial.println(F("Booting..."));

    Greenhouse = GreenhouseController();
    Greenhouse.setupSensors();

    Greenhouse.readSensors();
}

void loop()
{
    if (Serial.available()) {
        int inByte = Serial.read();
        Serial.print(inByte, DEC);
    }

    Greenhouse.currentMillis = millis();

    for (int i = 0; i < NUM_SENSORS; i++) {
        Greenhouse.handleSensor(i);
    }
}