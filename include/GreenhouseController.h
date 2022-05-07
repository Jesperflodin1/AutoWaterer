#ifndef _GreenhouseController_h
#define _GreenhouseController_h

#include "GreenhouseControllerConfiguration.h"
#include "PinConfiguration.h"
#include "Display.h"
#include "Sensor.h"

class GreenhouseController {

    private:
        GreenhouseControllerConfiguration GreenhouseConfiguration {};
        
    public:
        Sensor Sensors[NUM_SENSORS] = { {0, GreenhouseConfiguration}, {1, GreenhouseConfiguration}, {2, GreenhouseConfiguration} };

        GreenhouseController();
        void setupSensors();
        
        void readSensors();
        void readSensor(uint8_t);

};


#endif
