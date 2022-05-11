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