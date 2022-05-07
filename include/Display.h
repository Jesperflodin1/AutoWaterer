#ifndef _DISPLAY_H
#define _DISPLAY_H

//#include <AceTMI.h>
#include <digitalWriteFast.h>
#include <ace_tmi/SimpleTmi1637FastInterface.h>
#include <AceSegment.h> // Tm1637Module
#include <AceSegmentWriter.h> 

#include "PinConfiguration.h"

using ace_tmi::SimpleTmi1637FastInterface;
using ace_segment::LedModule;
using ace_segment::Tm1637Module;
//using ace_segment::StringWriter;
using ace_segment::CharWriter;
using ace_segment::NumberWriter;

class Display {
    private:
        SimpleTmi1637FastInterface<DIO_PIN, CLK_PIN, DELAY_MICROS> m_tmiInterface;
        Tm1637Module<SimpleTmi1637FastInterface<DIO_PIN, CLK_PIN, DELAY_MICROS>, NUM_DIGITS> m_ledModule { m_tmiInterface };
        CharWriter<LedModule> m_charWriter { m_ledModule };
        NumberWriter<LedModule> m_numberWriter { m_ledModule };

        uint32_t m_prevMillisLedUpdate = 0;

        // Display update interval in milliseconds
        const uint16_t m_ledUpdateInterval = 2000;
    public:
        void begin();

        // Check if interval in seconds has passed for this sensor
        bool intervalTimePassed(const uint32_t& currentMillis = millis(), bool autoReset = true);
        void resetTimer();

        void updateDisplay(uint8_t, uint8_t);
        void error(uint8_t);

        void showBoot();
        void showVersion(uint8_t);
        void showVersion(uint8_t, uint8_t);
};

#endif