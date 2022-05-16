#include "GreenhouseController.h"
using namespace GreenhouseController;

/* **** standard setup() function **** */
void setup()
{
    begin();

    readSensors();
}

void loop()
{
    currentMillis = millis();

    if (SerialComm::connected()) {

        SerialComm::serialLoop(currentMillis);
    } else {
        SerialComm::tryHandshake(currentMillis);
        if (SerialComm::connected())
            Display::showUSB();

        for (int i = 0; i < NUM_SENSORS; i++) {
            handleSensor(i);
        }
    }
}