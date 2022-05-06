#include "AutoWaterer.h"
#include <EEPROMex.h>
#include "GreenhouseControllerConfiguration.h"
#include <avr/wdt.h>    
#include <EEPROMStore.h>

/*
	config.cpp -- part of the AutoWaterer project.
	Implementation of EEPROM config functions
*/
const uint8_t cfgVersion = 2;

void forceSystemReset(void);

uint8_t SetupConfig() {
  uint8_t cfgEEPROM = EEPROM.read(0);
  if (cfgVersion != cfgEEPROM) {
    //Init eeprom
    EEPROM.update(0, cfgVersion);
    //MyInputs contains default config on boot
    updateCFG();
  } else readCFG();

  return cfgEEPROM;
}

void readCFG() {
  int adr = sizeof(cfgVersion);
  EEPROM.readBlock(adr, humidityCheckInterval);
  EEPROM.readBlock(adr+sizeof(humidityCheckInterval), SensorsConfig, NUM_SENSORS);
}
void updateCFG() {
  int adr = sizeof(cfgVersion);
  EEPROM.updateBlock(adr, humidityCheckInterval);
  EEPROM.updateBlock(adr+sizeof(humidityCheckInterval), SensorsConfig, NUM_SENSORS);
}
void resetCFG() {
  MySUI.returnMessage(SUI_STR("Clearing eeprom and rebooting with defaults"));
  EEPROM.write(0,0); // reset cfg version
  delay(200);
  // No workie
  //forceSystemReset();
  MySUI.returnMessage(SUI_STR("Cleared eeprom. Reboot now."));
  MySUI.exit();
  delay(2000);
  while (1) {} // default config will load after reset
}

void PrintVersion() {
  MySUI.print(F("Config version: "));
  MySUI.println(cfgVersion);
}

/*void forceSystemReset() {
  //see http://www.embedds.com/using-watchdog-timer-in-your-projects/
  cli();
  wdt_reset();
  MCUSR = 0;                           // allow changes, disable reset
  WDTCSR = (1 << WDCE) | (1 << WDE);    //set up WDT interrupt
  WDTCSR = (1 << WDE) | (1 << WDP2);   //Start watchdog timer with 0.25s prescaler
  sei();
  delay( 2000 ) ;  // force WDT to reset system
}*/