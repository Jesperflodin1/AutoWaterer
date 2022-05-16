
#include <digitalWriteFast.h>
#include <AceSegment.h> // Tm1637Module
#include <AceSegmentWriter.h>
#include <ace_tmi/SimpleTmi1637FastInterface.h>
#include "Display.h"
using ace_segment::LedModule;
using ace_segment::Tm1637Module;
using ace_tmi::SimpleTmi1637FastInterface;
// using ace_segment::StringWriter;
using ace_segment::CharWriter;
using ace_segment::NumberWriter;

namespace GreenhouseController::Display {
namespace {
    using TmiInterface = SimpleTmi1637FastInterface<DIO_PIN, CLK_PIN, DELAY_MICROS>;
    TmiInterface m_tmiInterface;
    Tm1637Module<TmiInterface, NUM_DIGITS> m_ledModule(m_tmiInterface);
    CharWriter<LedModule> m_charWriter(m_ledModule);
    NumberWriter<LedModule> m_numberWriter(m_ledModule);

    uint32_t m_prevMillisLedUpdate = 0;
    // Display update interval in milliseconds
    const uint16_t m_ledUpdateInterval = 2000;
}

void begin()
{
    m_tmiInterface.begin();
    m_ledModule.begin();
    m_ledModule.setBrightness(2);
}

bool intervalTimePassed(const uint32_t& currentMillis, bool autoReset)
{
    uint32_t delta = currentMillis - m_prevMillisLedUpdate;

    if (delta >= (uint32_t)m_ledUpdateInterval) {
        if (autoReset)
            m_prevMillisLedUpdate = currentMillis;
        return true;
    } else {
        return false;
    }
}

void updateDisplay(uint8_t sensor, uint8_t humidity)
{
    if (humidity == 100)
        humidity = 99;
    m_numberWriter.writeHexCharAt(0, sensor + 1);
    m_charWriter.writeCharAt(1, '-');
    m_numberWriter.writeDec2At(2, humidity);
    m_ledModule.flush();
}
void error(uint8_t errCode)
{
    m_charWriter.writeCharAt(0, 'E');
    m_charWriter.writeCharAt(1, 'R');
    m_charWriter.writeCharAt(2, 'R');
    m_numberWriter.writeHexCharAt(3, errCode + 1);
    m_ledModule.flush();
    // delay(3000);
}

void showBoot()
{
    m_charWriter.writeCharAt(0, 'B');
    m_charWriter.writeCharAt(1, 'O');
    m_charWriter.writeCharAt(2, 'O');
    m_charWriter.writeCharAt(3, 'T');
    m_ledModule.flush();
}

void showVersion(uint8_t version)
{
    m_charWriter.writeCharAt(0, 'V');
    m_charWriter.writeCharAt(1, '-');
    m_numberWriter.writeDec2At(2, version);
    m_ledModule.flush();
}
void showVersion(uint8_t majorVersion, uint8_t minorVersion)
{
    m_charWriter.writeCharAt(0, 'V');
    m_charWriter.writeCharAt(1, majorVersion);
    m_numberWriter.writeDec2At(2, minorVersion);
    m_ledModule.flush();
}

void showPump(uint8_t sensor)
{
    m_charWriter.writeCharAt(0, 'P');
    m_charWriter.writeCharAt(1, 'M');
    m_charWriter.writeCharAt(2, 'P');
    m_numberWriter.writeHexCharAt(3, sensor + 1);
    m_ledModule.flush();
    // delay(3000);
}

void showUSB()
{
    m_charWriter.clear();
    m_ledModule.flush();
    m_charWriter.writeCharAt(0, 'U');
    m_charWriter.writeCharAt(1, 'S');
    m_charWriter.writeCharAt(2, 'B');
    m_ledModule.flush();
}
}