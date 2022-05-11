// Need G4P library
import g4p_controls.*;
import java.awt.font.TextAttribute;
import processing.serial.*;

Serial arduinoPort;  // Create object from Serial class
String inString;
boolean firstContact = false;  // Whether we've heard from the microcontroller


public void setup(){
  size(1050, 550, JAVA2D);
  createGUI();
  customGUI();
  // Place your setup code here
  
}

public void draw(){
  background(230);
  
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){
  //panelLoading.setVisible(false);
  serialList.setItems(Serial.list(),0);
  
  StyledString loadingString = new StyledString("Letar efter arduino...");
  loadingString.addAttribute(TextAttribute.SIZE, 18);
  loadingLabel.setStyledText(loadingString);
  
  sensor1Enable.getStyledText().addAttribute(TextAttribute.SIZE, 16);
  sensor2Enable.getStyledText().addAttribute(TextAttribute.SIZE, 16);
  sensor3Enable.getStyledText().addAttribute(TextAttribute.SIZE, 16);
  
  sensor1RawValue.getStyledText().addAttribute(TextAttribute.SIZE, 16);
  sensor2RawValue.getStyledText().addAttribute(TextAttribute.SIZE, 16);
  sensor3RawValue.getStyledText().addAttribute(TextAttribute.SIZE, 16);
  
  sensor1RawValue.setText("1021");
  sensor1RawValue.getStyledText().addAttribute(TextAttribute.SIZE, 16);

}

public void connectSerial(String port) {
  serialList.setVisible(false);
  connectButton.setVisible(false);
  loadingLabel.setVisible(true);
  
  arduinoPort = new Serial(this, port, 9600);
  arduinoPort.bufferUntil('\n');
  
}

void serialEvent(Serial arduinoPort) {
  // read a byte from the serial port:
  int inByte = arduinoPort.read();
  // if this is the first byte received, and it's an A,
  // clear the serial buffer and note that you've
  // had first contact from the microcontroller.
  // Otherwise, add the incoming byte to the array:
  if (firstContact == false) {
    if (inByte == 'Z') {
      arduinoPort.clear();   // clear the serial port buffer
      firstContact = true;  // you've had first contact from the microcontroller
      arduinoPort.write('X');  // ask for more
    }
  } else {
    //inString = arduinoPort.readStringUntil('\n');
  }
}

//StyledString test;
