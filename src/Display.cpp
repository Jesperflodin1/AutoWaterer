#include "Display.h"

Display::Display() {
    
}
void Display::begin() {
    m_tmiInterface.begin();
    m_ledModule.begin();
    m_ledModule.setBrightness(2);
}

void Display::updateDisplay(uint8_t sensor, uint8_t humidity) {
  if (humidity == 100) humidity = 99;
  m_numberWriter.writeHexCharAt(0, sensor+1);
  m_charWriter.writeCharAt(1, '-');
  m_numberWriter.writeDec2At(2, humidity);
  m_ledModule.flush();
}
void Display::error(uint8_t errCode) {
  m_charWriter.writeCharAt(0, 'E');
  m_charWriter.writeCharAt(1, 'R');
  m_charWriter.writeCharAt(2, 'R');
  m_numberWriter.writeHexCharAt(3, errCode+1);
  m_ledModule.flush();
  //delay(3000);
}

void Display::showBoot() {
    m_charWriter.writeCharAt(0, 'B');
    m_charWriter.writeCharAt(1, 'O');
    m_charWriter.writeCharAt(2, 'O');
    m_charWriter.writeCharAt(3, 'T');
    m_ledModule.flush();
}

void Display::showVersion(uint8_t version) {
    m_charWriter.writeCharAt(0, 'V');
    m_charWriter.writeCharAt(1, '-');
    m_numberWriter.writeDec2At(2, version);
    m_ledModule.flush();
}
void Display::showVersion(uint8_t majorVersion, uint8_t minorVersion) {
    m_charWriter.writeCharAt(0, 'V');
    m_charWriter.writeCharAt(1, majorVersion);
    m_numberWriter.writeDec2At(2, minorVersion);
    m_ledModule.flush();
}