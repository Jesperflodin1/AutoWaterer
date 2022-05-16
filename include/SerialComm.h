#ifndef _SERIALCOMM_H
#define _SERIALCOMM_H

namespace GreenhouseController::SerialComm {

bool prevMillisPingDelayPassed(uint32_t currentMillis = millis());
bool prevMillisPingTimeoutPassed(uint32_t currentMillis = millis());

void tryHandshake(uint32_t currentMillis);
void serialLoop(uint32_t currentMillis);
void begin();

bool connected();
}
#endif