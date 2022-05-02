#include <SerialUI.h>
#include "AutoWaterer.h"

// "heartbeat" function, called periodically while connected
void CustomHeartbeatCode () {
// Do while connected?
  static uint8_t curSensor = 0;
  readHumidity(curSensor);
  updateLed(curSensor, Sensors[curSensor].humidity);
  if (curSensor == NUM_SENSORS-1) 
    curSensor = 0;
  else
    curSensor++;
} 

/* ********* callbacks and validation functions ********* */

void doExit() {

    /* Exit triggered */
    MySUI.println(F("Exit triggered!"));
    MySUI.exit();
}


