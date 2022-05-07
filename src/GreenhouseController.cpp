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

unsigned long currentMillis = 0;       // stores the value of millis() in each iteration of loop()

GreenhouseController Greenhouse;

Display ledDisplay;

// Setup eeprom, load config values, setup pins, init sensors, init display
GreenhouseController::GreenhouseController() {
    GreenhouseConfiguration = GreenhouseControllerConfiguration();

    for (int i=0; i<NUM_SENSORS; i++) {
        pinMode(HUMIDITYPOWER[i], OUTPUT);
        pinMode(HUMIDITYSENS[i], INPUT);
        pinMode(RELAY[i], OUTPUT);
    }

    ledDisplay.begin();
}

void GreenhouseController::setupSensors() {
  for (int i=0; i<NUM_SENSORS; i++) {
    Sensors[i] = Sensor(i, GreenhouseConfiguration);
  }
}

void GreenhouseController::readSensors() {
  for (int i=0; i<NUM_SENSORS; i++) {
    if (Sensors[i].enabled() == true) { //If current sensor is enabled
      
    }
  }   
}

void GreenhouseController::readSensor(uint8_t sensor) {
    Sensors[sensor].readHumidity();
      
    if (Sensors[sensor].getHumidity() == 0) {
        ledDisplay.error(sensor);
    } else {
      ledDisplay.resetTimer();
      ledDisplay.updateDisplay(sensor, Sensors[sensor].getHumidity());          
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
void setup() {
  Greenhouse = GreenhouseController();

  Greenhouse.readSensors();
}


void loop() {
  currentMillis = millis();

  for (int i=0; i<NUM_SENSORS; i++) {
    if (Greenhouse.Sensors[i].enabled() == true) { //If current sensor is enabled

      if (Greenhouse.Sensors[i].intervalTimePassed(currentMillis, true)) { 

        Greenhouse.readSensor(i);     
        
        if (Greenhouse.Sensors[i].pumpDelayPassed(currentMillis)) {
          Greenhouse.Sensors[i].resetPumpings();       
        } 

        //Maxtime elapsed or humidity low
        if ( (Greenhouse.Sensors[i].pumpTimeoutPassed(currentMillis, true) && Greenhouse.Sensors[i].getPumpings() < 2) || (Greenhouse.Sensors[i].lowHumidity() && Greenhouse.Sensors[i].getPumpings() < 2) ) {
          Greenhouse.Sensors[i].pump();
        }         
      }
      static uint8_t lastUpdatedSensor = NUM_SENSORS-1;     
      if (ledDisplay.intervalTimePassed(currentMillis, true) && i == (lastUpdatedSensor == NUM_SENSORS-1 ? 0 : lastUpdatedSensor+1)) {
        lastUpdatedSensor = lastUpdatedSensor == NUM_SENSORS-1 ? 0 : lastUpdatedSensor+1;

        ledDisplay.updateDisplay(i, Greenhouse.Sensors[i].getHumidity());                 
      }
    }    
  }
}