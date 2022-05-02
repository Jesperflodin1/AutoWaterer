#ifndef _AutoWaterer_AutoWaterer_h
#define _AutoWaterer_AutoWaterer_h

#include <Arduino.h>
#include <SerialUI.h>
#include "config.h"
//#define DEBUG
//#include "DebugUtils.h"
/* MySUI
 * Our SerialUI Instance, through which we can send/receive
 * data from users.
 */ 
extern SUI::SerialUI MySUI;

typedef struct Sensor {
  SerialUI::Tracked::Integer rawHumidity = NULL;
  unsigned int humidity = 0;
  unsigned long prevMillisWater = 0;
  unsigned long prevMillisHumCheck = 0;    // time of previous humidity check
} Sensor;
extern Sensor Sensors[NUM_SENSORS];

// Values will be replaced by defaults in config.h on init
typedef struct SensorConfig {
  SerialUI::Menu::Item::Request::Toggle enable = 0;
  SerialUI::Menu::Item::Request::UnsignedLong limit = 100UL;
  SerialUI::Menu::Item::Request::UnsignedLong wateringTime = 0UL;
  SerialUI::Menu::Item::Request::UnsignedLong maxTimeInterval = 1000UL;
  SerialUI::Menu::Item::Request::UnsignedLong minTimeInterval = 1000UL;
  SerialUI::Menu::Item::Request::UnsignedLong calDry = 0UL;
  SerialUI::Menu::Item::Request::UnsignedLong calWet = 0UL;
  unsigned int npump = 0;
} SensorConfig;
extern SensorConfig SensorsConfig[NUM_SENSORS];

extern SerialUI::Menu::Item::Request::UnsignedLong humidityCheckInterval; // Same interval for all sensors

/*
 * This container holds all the tracked variable views.
 */
typedef struct MyTrackedViewsContainerStruct {
	
	SerialUI::Menu::Item::View::CurrentValue Sensor1;
	SerialUI::Menu::Item::View::CurrentValue Sensor2;
	SerialUI::Menu::Item::View::CurrentValue Sensor3;
	// constructor to set sane startup vals
	MyTrackedViewsContainerStruct() : 
		Sensor1(SUI_STR("Sensor1"),SUI_STR("Current (raw) humidity reading")),
		Sensor2(SUI_STR("Sensor2"),SUI_STR("Current (raw) humidity reading")),
		Sensor3(SUI_STR("Sensor3"),SUI_STR("Current (raw) humidity reading"))
	{}
} MyTrackedViewsContainerSt;
extern MyTrackedViewsContainerSt MyViews;


void updateLed(uint8_t, uint8_t);
void readHumidity(uint8_t);

/* ***** SetupSerialUI: where we'll be setting up menus and such **** */
bool SetupSerialUI();
void initData();

// "heartbeat" callback function, called periodically while connected
void CustomHeartbeatCode(); 

void doExit();


#define DIE_HORRIBLY(msg)	for(;;){ MySUI.println(msg); delay(1000); }


#endif
