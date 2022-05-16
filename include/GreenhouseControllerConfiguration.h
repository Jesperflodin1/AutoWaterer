#ifndef _GreenhouseControllerConfiguration_h
#define _GreenhouseControllerConfiguration_h
#include <Arduino.h>
#include "Configuration.h"


namespace GreenhouseController::GreenhouseControllerConfiguration {

// SensorConfiguration& getSensorConfiguration(uint8_t sensor) { return StoredConfiguration.Data.Sensor[sensor]; }
// Configuration& getConfiguration() { return StoredConfiguration.Data; };

uint8_t getNextSensorId();

void Reset();
bool Save();

byte* serializedConfig(byte* emptyStr, char delimiter);

uint8_t getHumidityCheckInterval();
bool getEnabled(uint8_t sensor);
uint8_t getHumidityLimit(uint8_t sensor);
uint8_t getPumpTime(uint8_t sensor);
uint8_t getMaxPumpings(uint8_t sensor);
uint8_t getPumpTimeout(uint8_t sensor);
uint8_t getPumpDelay(uint8_t sensor);
uint16_t getCalDry(uint8_t sensor);
uint16_t getCalWet(uint8_t sensor);

void setHumidityCheckInterval(uint8_t value);
void setEnabled(uint8_t sensor, bool enabled);
void setHumidityLimit(uint8_t sensor, uint8_t humidity);
void setPumpTime(uint8_t sensor, uint8_t pumpTime);
void setMaxPumpings(uint8_t sensor, uint8_t maxPumpings);
void setPumpTimeout(uint8_t sensor, uint8_t pumpTimeout);
void setPumpDelay(uint8_t sensor, uint8_t pumpDelay);
void setCalDry(uint8_t sensor, uint16_t calDry);
void setCalWet(uint8_t sensor, uint16_t calWet);
}

#endif
