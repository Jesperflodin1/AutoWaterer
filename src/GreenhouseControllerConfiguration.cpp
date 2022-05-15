#include "GreenhouseControllerConfiguration.h"

void GreenhouseControllerConfiguration::Reset()
{
    StoredConfiguration.Reset();
}

bool GreenhouseControllerConfiguration::Save()
{
    return StoredConfiguration.Save();
}

// needs a string of 55 chars
byte* GreenhouseControllerConfiguration::serializedConfig(byte* emptyBytes, char delimiter)
{
    // C,1,2,3,4,5,6,77,88

    // byte emptyBytes[54];

    emptyBytes[0] = 'C';
    emptyBytes[1] = delimiter;
    emptyBytes[2] = getHumidityCheckInterval();
    emptyBytes[3] = delimiter;

    for (int i = 0; i < NUM_SENSORS; i++) {
        emptyBytes[4 + 17 * i] = getEnabled(i);
        emptyBytes[5 + 17 * i] = delimiter;
        emptyBytes[6 + 17 * i] = getHumidityLimit(i);
        emptyBytes[7 + 17 * i] = delimiter;
        emptyBytes[8 + 17 * i] = getPumpTime(i);
        emptyBytes[9 + 17 * i] = delimiter;
        emptyBytes[10 + 17 * i] = getMaxPumpings(i);
        emptyBytes[11 + 17 * i] = delimiter;
        emptyBytes[12 + 17 * i] = getPumpTimeout(i);
        emptyBytes[13 + 17 * i] = delimiter;
        emptyBytes[14 + 17 * i] = getPumpDelay(i);
        emptyBytes[15 + 17 * i] = delimiter;
        emptyBytes[16 + 17 * i] = getCalDry(i) & 0xFF;
        emptyBytes[17 + 17 * i] = getCalDry(i) >> 8;
        emptyBytes[18 + 17 * i] = delimiter;
        emptyBytes[19 + 17 * i] = getCalWet(i) & 0xFF;
        emptyBytes[20 + 17 * i] = getCalWet(i) >> 8;
    }

    return emptyBytes;
}