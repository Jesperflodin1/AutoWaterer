#ifndef _GreenhouseControllerConfiguration_h
#define _GreenhouseControllerConfiguration_h
#include "EEPROMStore.h"
#include "PinConfiguration.h"
#include <Arduino.h>

/* --- Default configuration --- */
#define CFG_SENSOR_ENABLE 1
#define CFG_SENSOR_LIMIT 90
#define CFG_SENSOR_PUMPTIME 14 // Sec
#define CFG_SENSOR_MAXPUMPINGS 2
#define CFG_SENSOR_PUMPTIMEOUT 48 // Hour
#define CFG_SENSOR_PUMPDELAY 8 // Hour
#define CFG_SENSOR_CALIBRATIONWET 660
#define CFG_SENSOR_CALIBRATIONDRY 85

#define CFG_HUMIDITYCHECKINTERVAL 30 // min

class GreenhouseControllerConfiguration {
public:
    // 10 byte sensor configuration struct
    struct SensorConfiguration {
        bool enable;
        uint8_t humidityLimit;
        uint8_t pumpTime; // Seconds
        uint8_t maxPumpings;
        uint8_t pumpTimeout; // Hours
        uint8_t pumpDelay; // Hours
        uint16_t calibrationDry;
        uint16_t calibrationWet;

        SensorConfiguration()
            : enable(CFG_SENSOR_ENABLE)
            , humidityLimit(CFG_SENSOR_LIMIT)
            , pumpTime(CFG_SENSOR_PUMPTIME)
            , maxPumpings(CFG_SENSOR_MAXPUMPINGS)
            , pumpTimeout(CFG_SENSOR_PUMPTIMEOUT)
            , pumpDelay(CFG_SENSOR_PUMPDELAY)
            , calibrationDry(CFG_SENSOR_CALIBRATIONDRY)
            , calibrationWet(CFG_SENSOR_CALIBRATIONWET)
        {
        }
    };

    // 10*NUM_SENSORS + 1 byte configuration struct (Default 10*3+1 = 31 byte)
    struct Configuration {
        uint8_t humidityCheckInterval;
        struct SensorConfiguration Sensor[NUM_SENSORS];

        Configuration()
        {
            humidityCheckInterval = CFG_HUMIDITYCHECKINTERVAL;
            for (int i = 0; i < NUM_SENSORS; i++) {
                Sensor[i] = SensorConfiguration();
            }
        }

        void Reset()
        {
            for (int i = 0; i < NUM_SENSORS; i++) {
                Sensor[i] = SensorConfiguration();
            }
        }
    };

    GreenhouseControllerConfiguration();

    SensorConfiguration getSensorConfig(uint8_t sensor) { return StoredConfiguration.Data.Sensor[sensor]; }
    Configuration getGlobalConfig() { return StoredConfiguration.Data; };

    void Reset();
    void Save();

    char* serializedConfig(char* emptyStr, char delimiter);

private:
    EEPROMStore<GreenhouseControllerConfiguration::Configuration> StoredConfiguration;
};

uint8_t SetupConfig(void);

void readCFG(void);
void updateCFG(void);
void resetCFG(void);
void printVersion(void);

#endif
