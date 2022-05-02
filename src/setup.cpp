#include <SerialUI.h>
#include "AutoWaterer.h"

SUI::SerialUI MySUI(3);

MyTrackedViewsContainerSt MyViews;

void initData() {
	humidityCheckInterval = SerialUI::Menu::Item::Request::UnsignedLong(CFG_HumidityInterval,SUI_STR("Humidity interval"),SUI_STR("In seconds"),updateCFG);
	
	SensorsConfig[0].enable = SerialUI::Menu::Item::Request::Toggle(CFG_EnableSensor1,SUI_STR("S1 Enable"),SUI_STR("Sensor 1"),updateCFG);
	SensorsConfig[1].enable = SerialUI::Menu::Item::Request::Toggle(CFG_EnableSensor2,SUI_STR("S2 Enable"),SUI_STR("Sensor 2"),updateCFG);
	SensorsConfig[2].enable = SerialUI::Menu::Item::Request::Toggle(CFG_EnableSensor3,SUI_STR("S3 Enable"),SUI_STR("Sensor 3"),updateCFG);

	SensorsConfig[0].limit = SerialUI::Menu::Item::Request::UnsignedLong(CFG_Sensor1Limit,SUI_STR("S1 Limit"),SUI_STR("Humidity limit"),updateCFG);
	SensorsConfig[1].limit = SerialUI::Menu::Item::Request::UnsignedLong(CFG_Sensor2Limit,SUI_STR("S2 Limit"),SUI_STR("Humidity limit"),updateCFG);
	SensorsConfig[2].limit = SerialUI::Menu::Item::Request::UnsignedLong(CFG_Sensor3Limit,SUI_STR("S3 Limit"),SUI_STR("Humidity limit"),updateCFG);

	SensorsConfig[0].wateringTime = SerialUI::Menu::Item::Request::UnsignedLong(CFG_wateringTimeSens1,SUI_STR("S1 Pump time"),SUI_STR("Seconds to pump"),updateCFG);
	SensorsConfig[1].wateringTime = SerialUI::Menu::Item::Request::UnsignedLong(CFG_wateringTimeSens2,SUI_STR("S2 Pump time"),SUI_STR("Seconds to pump"),updateCFG);
	SensorsConfig[2].wateringTime = SerialUI::Menu::Item::Request::UnsignedLong(CFG_wateringTimeSens3,SUI_STR("S3 Pump time"),SUI_STR("Seconds to pump"),updateCFG);

	SensorsConfig[0].maxTimeInterval = SerialUI::Menu::Item::Request::UnsignedLong(CFG_MaxTimeInterval1,SUI_STR("S1 Max interval"),SUI_STR("Longest time (Hours)"),updateCFG);
	SensorsConfig[1].maxTimeInterval = SerialUI::Menu::Item::Request::UnsignedLong(CFG_MaxTimeInterval2,SUI_STR("S2 Max interval"),SUI_STR("Longest time (Hours)"),updateCFG);
	SensorsConfig[2].maxTimeInterval = SerialUI::Menu::Item::Request::UnsignedLong(CFG_MaxTimeInterval3,SUI_STR("S3 Max interval"),SUI_STR("Longest time (Hours)"),updateCFG);

	SensorsConfig[0].minTimeInterval = SerialUI::Menu::Item::Request::UnsignedLong(CFG_MinTimeInterval1,SUI_STR("S1 Min interval"),SUI_STR("Shortest time (Hours)"),updateCFG);
	SensorsConfig[1].minTimeInterval = SerialUI::Menu::Item::Request::UnsignedLong(CFG_MinTimeInterval2,SUI_STR("S2 Min interval"),SUI_STR("Shortest time (Hours)"),updateCFG);
	SensorsConfig[2].minTimeInterval = SerialUI::Menu::Item::Request::UnsignedLong(CFG_MinTimeInterval3,SUI_STR("S3 Min interval"),SUI_STR("Shortest time (Hours)"),updateCFG);

	SensorsConfig[0].calDry = SerialUI::Menu::Item::Request::UnsignedLong(CFG_Sensor1Dry,SUI_STR("S1 Dry"),SUI_STR("Value in air"),updateCFG);
	SensorsConfig[1].calDry = SerialUI::Menu::Item::Request::UnsignedLong(CFG_Sensor2Dry,SUI_STR("S2 Dry"),SUI_STR("Value in air"),updateCFG);
	SensorsConfig[2].calDry = SerialUI::Menu::Item::Request::UnsignedLong(CFG_Sensor3Dry,SUI_STR("S3 Dry"),SUI_STR("Value in air"),updateCFG);

	SensorsConfig[0].calWet = SerialUI::Menu::Item::Request::UnsignedLong(CFG_Sensor1Wet,SUI_STR("S1 Wet"),SUI_STR("Value in water"),updateCFG);
	SensorsConfig[1].calWet = SerialUI::Menu::Item::Request::UnsignedLong(CFG_Sensor2Wet,SUI_STR("S2 Wet"),SUI_STR("Value in water"),updateCFG);
	SensorsConfig[2].calWet = SerialUI::Menu::Item::Request::UnsignedLong(CFG_Sensor3Wet,SUI_STR("S3 Wet"),SUI_STR("Value in water"),updateCFG);

	Sensors[0].rawHumidity = SerialUI::Tracked::Integer(SUI_STR("Sensor 1"),0);
	Sensors[1].rawHumidity = SerialUI::Tracked::Integer(SUI_STR("Sensor 2"),0);
	Sensors[2].rawHumidity = SerialUI::Tracked::Integer(SUI_STR("Sensor 3"),0);
}


bool SetupSerialUI() {
  	MySUI.setGreeting(F(serial_ui_greeting_str));
	// SerialUI acts just like (is actually a facade for)
	// Serial.  Use _it_, rather than Serial, throughout the
	// program.
	// basic setup of SerialUI:
	MySUI.begin(serial_baud_rate); // serial line open/setup
	// MySUI.setTimeout(serial_readtimeout_ms);   // timeout for reads (in ms), same as for Serial.
	MySUI.setMaxIdleMs(serial_maxidle_ms);    // timeout for user (in ms)
	// how we are marking the "end-of-line" (\n, by default):
	MySUI.setReadTerminator(serial_input_terminator);
	// project UID -- will be used to remember state in Druid...
	MySUI.setUID(SUI_STR("ea6579bd13f7487a9a683140077ffaa5oexB3WpKKC"));

	MySUI.setEchoCommands(true);

	// have a "heartbeat" function to hook-up
	MySUI.setUserPresenceHeartbeat(CustomHeartbeatCode); 
	// heartbeat_function_period_ms set in main settings header
	MySUI.setUserPresenceHeartbeatPeriod(heartbeat_function_period_ms);
	
	
	
	// Add variable state tracking 
	
	MySUI.trackState(Sensors[0].rawHumidity);
	MySUI.trackState(Sensors[1].rawHumidity);
	MySUI.trackState(Sensors[2].rawHumidity);
	
	// Associate tracked vars with views
	MyViews.Sensor1.associate(Sensors[0].rawHumidity);
	MyViews.Sensor2.associate(Sensors[1].rawHumidity);
	MyViews.Sensor3.associate(Sensors[2].rawHumidity);
	
	
	
	// a few error messages we hopefully won't need
	
	SUI_FLASHSTRING CouldntCreateMenuErr = F("Could not create menu?");
	SUI_FLASHSTRING CouldntAddItemErr = F("Could not add item?");
	
	// get top level menu, to start adding items
	SerialUI::Menu::Menu * topMenu = MySUI.topLevelMenu();
	if (! topMenu ) {
		// well, that can't be good...
		MySUI.returnError(F("Very badness in sEriALui!1"));
		return false;
	}
	
	
	
	/* *** Main Menu *** */

	SerialUI::Menu::Menu * submenuSettings = topMenu->subMenu(
		SUI_STR("Settings"),
		NULL);
	if (! submenuSettings ) { 
		DIE_HORRIBLY(CouldntCreateMenuErr);
	}

	SerialUI::Menu::Menu * submenuCal = topMenu->subMenu(
		SUI_STR("Calibration"),
		SUI_STR("Calibrate sensors"));
	if (! submenuCal ) { 
		DIE_HORRIBLY(CouldntCreateMenuErr);
	}
	

	if( ! topMenu->addCommand(
		SUI_STR("Exit"),
		doExit)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	/* *** Main Menu -> Settings *** */
  	if( ! submenuSettings->addRequest(
		humidityCheckInterval)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! submenuSettings->addCommand(
		SUI_STR("Reset settings"),
		resetCFG,
		SUI_STR("Reset all to defaults") )) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	/* *** Main Menu -> Settings -> Sensor 1 *** */
	if( ! submenuSettings->addText(
		SUI_STR("Sensor 1"),
		SUI_STR("Sensor 1 settings"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! submenuSettings->addRequest(
		SensorsConfig[0].enable)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuSettings->addRequest(
		SensorsConfig[0].limit)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuSettings->addRequest(
		SensorsConfig[0].wateringTime)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuSettings->addRequest(
		SensorsConfig[0].maxTimeInterval)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuSettings->addRequest(
		SensorsConfig[0].minTimeInterval)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}


	/* *** Main Menu -> Settings -> Sensor 2 *** */

	if( ! submenuSettings->addText(
		SUI_STR("Sensor 2"),
		SUI_STR("Sensor 2 settings"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	
	if( ! submenuSettings->addRequest(
		SensorsConfig[1].enable)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuSettings->addRequest(
		SensorsConfig[1].limit)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuSettings->addRequest(
		SensorsConfig[1].wateringTime)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuSettings->addRequest(
		SensorsConfig[1].maxTimeInterval)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuSettings->addRequest(
		SensorsConfig[1].minTimeInterval)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	/* *** Main Menu -> Settings -> Sensor 3 *** */

	if( ! submenuSettings->addText(
		SUI_STR("Sensor 3"),
		SUI_STR("Sensor 3 settings"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	
	if( ! submenuSettings->addRequest(
		SensorsConfig[2].enable)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuSettings->addRequest(
		SensorsConfig[2].limit)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuSettings->addRequest(
		SensorsConfig[2].wateringTime)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuSettings->addRequest(
		SensorsConfig[2].maxTimeInterval)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuSettings->addRequest(
		SensorsConfig[2].minTimeInterval)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}


	/* *** Main Menu -> Calibration *** */

	/* *** Main Menu -> Calibration -> Calibrate sensor 1 *** */
  
	if( ! submenuCal->addText(
		SUI_STR("Sensor 1 calibration"),
		SUI_STR("Raw values in air and water"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuCal->addView(
		MyViews.Sensor1)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuCal->addRequest(
		SensorsConfig[0].calDry)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuCal->addRequest(
		SensorsConfig[0].calWet)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	/* *** Main Menu -> Calibration -> Calibrate sensor 2 *** */

	
	if( ! submenuCal->addText(
		SUI_STR("Sensor 2 calibration"),
		SUI_STR("Raw values in air and water"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuCal->addView(
		MyViews.Sensor2)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuCal->addRequest(
		SensorsConfig[1].calDry)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuCal->addRequest(
		SensorsConfig[1].calWet)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}


	/* *** Main Menu -> Calibration -> Calibrate sensor 3 *** */

	
	if( ! submenuCal->addText(
		SUI_STR("Sensor 3 calibration"),
		SUI_STR("Raw values in air and water"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuCal->addView(
		MyViews.Sensor3)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submenuCal->addRequest(
		SensorsConfig[2].calDry)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! submenuCal->addRequest(
		SensorsConfig[2].calWet)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	return true;
	
}


