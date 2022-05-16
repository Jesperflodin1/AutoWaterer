#ifndef _PIN_CONFIGURATION_H
#define _PIN_CONFIGURATION_H
#include <Arduino.h>

// Many TM1637 LED modules contain 10 nF capacitors on their DIO and CLK lines
// which are unreasonably high. This forces a 100 microsecond delay between
// bit transitions. If you remove those capacitors, you can set this as low as
// 1-5 micros.
#define DELAY_MICROS 100
// static const uint8_t DELAY_MICROS = 100;

#define NUM_SENSORS 3 // 3 humidity sensors with one relay each

#define HUMIDITYPOWER_PINS \
    {                      \
        2, 3, 4            \
    }
#define HUMIDITYSENS_PINS \
    {                     \
        A1, A2, A3        \
    }
#define RELAY_PINS \
    {              \
        8, 9, 10   \
    }

// 7 segment display
#define CLK_PIN A0
#define DIO_PIN 7
#define NUM_DIGITS 4

const uint8_t HUMIDITYPOWER[NUM_SENSORS] = HUMIDITYPOWER_PINS;
const uint8_t HUMIDITYSENS[NUM_SENSORS] = HUMIDITYSENS_PINS; // Sensor data pin for analog read
const uint8_t RELAY[NUM_SENSORS] = RELAY_PINS;

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

#endif