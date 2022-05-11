#include "GreenhouseControllerConfiguration.h"

GreenhouseControllerConfiguration::GreenhouseControllerConfiguration()
{
    StoredConfiguration = EEPROMStore<GreenhouseControllerConfiguration::Configuration> {};
}

void GreenhouseControllerConfiguration::Reset()
{
    StoredConfiguration.Reset();
}

void GreenhouseControllerConfiguration::Save()
{
    StoredConfiguration.Save();
}

// needs a string of 53 chars
char* GreenhouseControllerConfiguration::serializedConfig(char* emptyStr, char delimiter)
{
    // C,1,2,3,4,5,6,77,88

    char configStr[53];

    configStr[0] = 'C';
    configStr[1] = delimiter;

    for (int i = 0; i < NUM_SENSORS; i++) {
        configStr[2 + 17 * i] = getSensorConfig(i).enable;
        configStr[3 + 17 * i] = delimiter;
        configStr[4 + 17 * i] = getSensorConfig(i).humidityLimit;
        configStr[5 + 17 * i] = delimiter;
        configStr[6 + 17 * i] = getSensorConfig(i).pumpTime;
        configStr[7 + 17 * i] = delimiter;
        configStr[8 + 17 * i] = getSensorConfig(i).maxPumpings;
        configStr[9 + 17 * i] = delimiter;
        configStr[10 + 17 * i] = getSensorConfig(i).pumpTimeout;
        configStr[11 + 17 * i] = delimiter;
        configStr[12 + 17 * i] = getSensorConfig(i).pumpDelay;
        configStr[13 + 17 * i] = delimiter;
        configStr[14 + 17 * i] = getSensorConfig(i).calibrationDry & 0xFF;
        configStr[15 + 17 * i] = getSensorConfig(i).calibrationDry >> 8;
        configStr[16 + 17 * i] = delimiter;
        configStr[17 + 17 * i] = getSensorConfig(i).calibrationWet & 0xFF;
        configStr[18 + 17 * i] = getSensorConfig(i).calibrationWet >> 8;
    }

    strcpy(emptyStr, configStr);
    return emptyStr;
}