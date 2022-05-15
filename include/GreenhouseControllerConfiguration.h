#ifndef _GreenhouseControllerConfiguration_h
#define _GreenhouseControllerConfiguration_h
#include "EEPROMStore.h"
#include "PinConfiguration.h"
#include <Arduino.h>

/* --- Default configuration --- */
#define CFG_VERSION 0xA1

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
private:
    // 10 byte sensor configuration struct
    struct __attribute__((packed)) SensorConfiguration {
        bool m_enabled;
        uint8_t m_humidityLimit;
        uint8_t m_pumpTime; // Seconds
        uint8_t m_maxPumpings;
        uint8_t m_pumpTimeout; // Hours
        uint8_t m_pumpDelay; // Hours
        uint16_t m_calibrationDry;
        uint16_t m_calibrationWet;

        SensorConfiguration()
            : m_enabled(CFG_SENSOR_ENABLE)
            , m_humidityLimit(CFG_SENSOR_LIMIT)
            , m_pumpTime(CFG_SENSOR_PUMPTIME)
            , m_maxPumpings(CFG_SENSOR_MAXPUMPINGS)
            , m_pumpTimeout(CFG_SENSOR_PUMPTIMEOUT)
            , m_pumpDelay(CFG_SENSOR_PUMPDELAY)
            , m_calibrationDry(CFG_SENSOR_CALIBRATIONDRY)
            , m_calibrationWet(CFG_SENSOR_CALIBRATIONWET)
        {
        }
        void Reset()
        {
            m_enabled = CFG_SENSOR_ENABLE;
            m_humidityLimit = CFG_SENSOR_LIMIT;
            m_pumpTime = CFG_SENSOR_PUMPTIME;
            m_maxPumpings = CFG_SENSOR_MAXPUMPINGS;
            m_pumpTimeout = CFG_SENSOR_PUMPTIMEOUT;
            m_pumpDelay = CFG_SENSOR_PUMPDELAY;
            m_calibrationDry = CFG_SENSOR_CALIBRATIONDRY;
            m_calibrationWet = CFG_SENSOR_CALIBRATIONWET;
        }
    };

    // 10*NUM_SENSORS + 1 byte configuration struct (Default 10*3+1 = 31 byte)
    struct __attribute__((packed)) Configuration {
        uint8_t humidityCheckInterval = CFG_HUMIDITYCHECKINTERVAL;
        struct SensorConfiguration Sensor[NUM_SENSORS];

        void Reset()
        {
            humidityCheckInterval = CFG_HUMIDITYCHECKINTERVAL;
            for (int i = 0; i < NUM_SENSORS; i++) {
                Sensor[i].Reset();
            }
        }
    };

    // SensorConfiguration& getSensorConfiguration(uint8_t sensor) { return StoredConfiguration.Data.Sensor[sensor]; }
    // Configuration& getConfiguration() { return StoredConfiguration.Data; };

public:
    EEPROMStore<GreenhouseControllerConfiguration::Configuration> StoredConfiguration {};
    void Reset();
    bool Save();

    byte* serializedConfig(byte* emptyStr, char delimiter);

    uint8_t getHumidityCheckInterval() { return StoredConfiguration.Data.humidityCheckInterval; }
    bool getEnabled(uint8_t sensor) { return StoredConfiguration.Data.Sensor[sensor].m_enabled; }
    uint8_t getHumidityLimit(uint8_t sensor) { return StoredConfiguration.Data.Sensor[sensor].m_humidityLimit; }
    uint8_t getPumpTime(uint8_t sensor) { return StoredConfiguration.Data.Sensor[sensor].m_pumpTime; }
    uint8_t getMaxPumpings(uint8_t sensor) { return StoredConfiguration.Data.Sensor[sensor].m_maxPumpings; }
    uint8_t getPumpTimeout(uint8_t sensor) { return StoredConfiguration.Data.Sensor[sensor].m_pumpTimeout; }
    uint8_t getPumpDelay(uint8_t sensor) { return StoredConfiguration.Data.Sensor[sensor].m_pumpDelay; }
    uint16_t getCalDry(uint8_t sensor) { return StoredConfiguration.Data.Sensor[sensor].m_calibrationDry; }
    uint16_t getCalWet(uint8_t sensor) { return StoredConfiguration.Data.Sensor[sensor].m_calibrationWet; }

    void setHumidityCheckInterval(uint8_t value) { StoredConfiguration.Data.humidityCheckInterval = value; }
    void setEnabled(uint8_t sensor, bool enabled) { StoredConfiguration.Data.Sensor[sensor].m_enabled = enabled; }
    void setHumidityLimit(uint8_t sensor, uint8_t humidity) { StoredConfiguration.Data.Sensor[sensor].m_humidityLimit = humidity; }
    void setPumpTime(uint8_t sensor, uint8_t pumpTime) { StoredConfiguration.Data.Sensor[sensor].m_pumpTime = pumpTime; }
    void setMaxPumpings(uint8_t sensor, uint8_t maxPumpings) { StoredConfiguration.Data.Sensor[sensor].m_maxPumpings = maxPumpings; }
    void setPumpTimeout(uint8_t sensor, uint8_t pumpTimeout) { StoredConfiguration.Data.Sensor[sensor].m_pumpTimeout = pumpTimeout; }
    void setPumpDelay(uint8_t sensor, uint8_t pumpDelay) { StoredConfiguration.Data.Sensor[sensor].m_pumpDelay = pumpDelay; }
    void setCalDry(uint8_t sensor, uint16_t calDry) { StoredConfiguration.Data.Sensor[sensor].m_calibrationDry = calDry; }
    void setCalWet(uint8_t sensor, uint16_t calWet) { StoredConfiguration.Data.Sensor[sensor].m_calibrationWet = calWet; }
};

void readCFG(void);
void updateCFG(void);
void resetCFG(void);
void printVersion(void);

#endif
