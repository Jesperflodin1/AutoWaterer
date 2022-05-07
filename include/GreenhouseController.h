#ifndef _GreenhouseController_h
#define _GreenhouseController_h

#include "GreenhouseControllerConfiguration.h"
#include "PinConfiguration.h"
#include "Display.h"

class GreenhouseController {

    private:
        Display ledDisplay;
        GreenhouseControllerConfiguration GreenhouseConfiguration;

    public:
        void setupPins();

};


#endif
