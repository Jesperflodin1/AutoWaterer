#include "Display.h"

Display::Display() {
    
}
void Display::begin() {
    tmiInterface.begin();
    ledModule.begin();
    ledModule.setBrightness(2);
}

void Display::updateDisplay(uint8_t sensor, uint8_t humidity) {
  if (humidity == 100) humidity = 99;
  numberWriter.writeHexCharAt(0, sensor+1);
  charWriter.writeCharAt(1, '-');
  numberWriter.writeDec2At(2, humidity);
  ledModule.flush();
}
void Display::error(uint8_t errCode) {
  charWriter.writeCharAt(0, 'E');
  charWriter.writeCharAt(1, 'R');
  charWriter.writeCharAt(2, 'R');
  numberWriter.writeHexCharAt(3, errCode+1);
  ledModule.flush();
  //delay(3000);
}

void Display::showBoot() {
    charWriter.writeCharAt(0, 'B');
    charWriter.writeCharAt(1, 'O');
    charWriter.writeCharAt(2, 'O');
    charWriter.writeCharAt(3, 'T');
    ledModule.flush();
}

void Display::showVersion(uint8_t version) {
    charWriter.writeCharAt(0, 'V');
    charWriter.writeCharAt(1, '-');
    numberWriter.writeDec2At(2, version);
    ledModule.flush();
}
void Display::showVersion(uint8_t majorVersion, uint8_t minorVersion) {
    charWriter.writeCharAt(0, 'V');
    charWriter.writeCharAt(1, majorVersion);
    numberWriter.writeDec2At(2, minorVersion);
    ledModule.flush();
}