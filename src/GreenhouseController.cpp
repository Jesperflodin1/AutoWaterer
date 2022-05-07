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


/* --- Global variables --- */

unsigned long currentMillis = 0;       // stores the value of millis() in each iteration of loop()
unsigned long prevMillisLedUpdate = 0; // time of previous led 7 segment display update


void GreenhouseController::setupPins() {
  for (int i=0; i<NUM_SENSORS; i++) {
    pinMode(HUMIDITYPOWER[i], OUTPUT);
    pinMode(HUMIDITYSENS[i], INPUT);
    pinMode(RELAY[i], OUTPUT);
  }
}



void initSensors() {
  for (int i=0; i<NUM_SENSORS; i++) {
    if ((bool)SensorsConfig[i].enable == true) { //If current sensor is enabled
      readHumidity(i);
        
      if (Sensors[i].humidity == 0) {
          ledDisplay.error(i);
      } else {
        prevMillisLedUpdate += 2000UL;
        ledDisplay.updateDisplay(i, Sensors[i].humidity);          
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
void setup() {
  setupPins();
  ledDisplay.begin();

  ledDisplay.showVersion(SetupConfig());
  delay(500);

  initSensors();
}


void loop() {
  currentMillis = millis();

  for (int i=0; i<NUM_SENSORS; i++) {
    if ((bool)SensorsConfig[i].enable == true) { //If current sensor is enabled

      if (currentMillis - Sensors[i].prevMillisHumCheck >= (unsigned long)humidityCheckInterval * 1000UL) { 
        Sensors[i].prevMillisHumCheck += (unsigned long)humidityCheckInterval * 1000UL;
        readHumidity(i);
        
        if (Sensors[i].humidity == 0) {
            ledDisplay.error(i);
        } else {
          prevMillisLedUpdate = millis();
          ledDisplay.updateDisplay(i, Sensors[i].humidity);          
        }        
        
        if (currentMillis - Sensors[i].prevMillisWater >= (unsigned long)SensorsConfig[i].minTimeInterval*60UL*60UL*1000UL) {
          SensorsConfig[i].npump = 0;        
        } 

        //Maxtime elapsed or humidity low
        if ( (currentMillis - Sensors[i].prevMillisWater >= (unsigned long)SensorsConfig[i].maxTimeInterval*60UL*60UL*1000UL && SensorsConfig[i].npump < 2) || (Sensors[i].humidity <= SensorsConfig[i].limit && SensorsConfig[i].npump < 2) ) {
          Sensors[i].prevMillisWater = currentMillis;
          pump(i);
        }         
      }
      static uint8_t lastUpdatedSensor = NUM_SENSORS-1;     
      if (currentMillis - prevMillisLedUpdate >= 2000UL && i == (lastUpdatedSensor == NUM_SENSORS-1 ? 0 : lastUpdatedSensor+1)) {
        lastUpdatedSensor = lastUpdatedSensor == NUM_SENSORS-1 ? 0 : lastUpdatedSensor+1;
        prevMillisLedUpdate += 2000UL;
        ledDisplay.updateDisplay(i, Sensors[i].humidity);                 
      }
    }    
  }
}