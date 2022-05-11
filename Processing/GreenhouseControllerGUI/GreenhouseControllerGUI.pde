// Need G4P library
import g4p_controls.*;
import java.awt.font.TextAttribute;
import processing.serial.*;

Serial arduinoPort;  // Create object from Serial class
String inString;
boolean firstContact = false;  // Whether we've heard from the microcontroller

boolean serialInput = false;
boolean connecting = false;

boolean configDone = false;
static boolean configRequested = true;
byte[] configBytes = new byte[0]; //Incoming config string

byte[] sensorBytes = new byte[0];

int pingInterval = 2000;
long prevMillisPing = 0;


public void setup(){
  size(1050, 550, JAVA2D);
  createGUI();
  customGUI();
  // Place your setup code here
  showConnectPrompt();
  
}

public void draw(){
  background(230);
  
  if (connecting) {
    showConnecting();
    connecting = false;
  }

  if (firstContact) {
    hideConnectPrompt();
    
    if (serialInput) {
      if (!configDone && configBytes.length == 56) {
        println("Got config data with correct length");
        //String[] splitStr = configStr.split(",",0);
        
        humidityInterval.setValue(configBytes[1]);
        
        sensor1Enable.setSelected(configBytes[3] == 1);
        sensor2Enable.setSelected(configBytes[3+17] == 1);
        sensor3Enable.setSelected(configBytes[3+17*2] == 1);
        
        sensor1Limit.setValue(configBytes[5]);
        sensor2Limit.setValue(configBytes[5+17]);
        sensor3Limit.setValue(configBytes[5+17*2]);
        
        sensor1Pumptime.setValue(configBytes[7]);
        sensor2Pumptime.setValue(configBytes[7+17]);
        sensor3Pumptime.setValue(configBytes[7+17*2]);
        
        sensor1Maxpumpings.setValue(configBytes[9]);
        sensor2Maxpumpings.setValue(configBytes[9+17]);
        sensor3Maxpumpings.setValue(configBytes[9+17*2]);
        
        sensor1Pumptimeout.setValue(configBytes[11]);
        sensor2Pumptimeout.setValue(configBytes[11+17]);
        sensor3Pumptimeout.setValue(configBytes[11+17*2]);
        
        sensor1Pumpdelay.setValue(configBytes[13]);
        sensor2Pumpdelay.setValue(configBytes[13+17]);
        sensor3Pumpdelay.setValue(configBytes[13+17*2]);
        
        String calDry1 = Integer.toString(((char) (configBytes[16] & 0xFF) << 8) | (configBytes[15] & 0xFF));
        String calDry2 = Integer.toString(((char) (configBytes[16+17] & 0xFF) << 8) | (configBytes[15+17] & 0xFF));
        String calDry3 = Integer.toString(((char) (configBytes[16+17*2] & 0xFF) << 8) | (configBytes[15+17*2] & 0xFF));
        sensor1CalDry.setText(calDry1);
        sensor2CalDry.setText(calDry2);
        sensor3CalDry.setText(calDry3);
        
        String calWet1 = Integer.toString(((char) (configBytes[19] & 0xFF) << 8) | (configBytes[18] & 0xFF));
        String calWet2 = Integer.toString(((char) (configBytes[19+17] & 0xFF) << 8) | (configBytes[18+17] & 0xFF));
        String calWet3 = Integer.toString(((char) (configBytes[19+17*2] & 0xFF) << 8) | (configBytes[18+17*2] & 0xFF));
        sensor1CalWet.setText(calWet1);
        sensor2CalWet.setText(calWet2);
        sensor3CalWet.setText(calWet3);

        serialInput = false;
        configDone = true;
      } else if (sensorBytes != null) {
        String sensor1 = Integer.toString(((char) (sensorBytes[1] & 0xFF) << 8) | (sensorBytes[0] & 0xFF));
        String sensor2 = Integer.toString(((char) (sensorBytes[4] & 0xFF) << 8) | (sensorBytes[3] & 0xFF));
        String sensor3 = Integer.toString(((char) (sensorBytes[7] & 0xFF) << 8) | (sensorBytes[6] & 0xFF));
        
        sensor1RawValue.setText(sensor1);
        sensor2RawValue.setText(sensor2);
        sensor3RawValue.setText(sensor3);
        sensor1RawValue.getStyledText().addAttribute(TextAttribute.SIZE, 16);
        sensor2RawValue.getStyledText().addAttribute(TextAttribute.SIZE, 16);
        sensor3RawValue.getStyledText().addAttribute(TextAttribute.SIZE, 16);
  
        serialInput = false;
        sensorBytes = null;
      }
    } 
    long currentMillis = millis();
    if (currentMillis - prevMillisPing >= pingInterval*10) {
      //ping();
      println("SERIAL TIMEOUT");
      firstContact = false;
      arduinoPort.stop();
      showConnectPrompt();
    }
  }
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){
  //panelLoading.setVisible(false);
  
  
  StyledString loadingString = new StyledString("Letar efter arduino...");
  loadingString.addAttribute(TextAttribute.SIZE, 18);
  loadingLabel.setStyledText(loadingString);
  
  sensor1Enable.getStyledText().addAttribute(TextAttribute.SIZE, 16);
  sensor2Enable.getStyledText().addAttribute(TextAttribute.SIZE, 16);
  sensor3Enable.getStyledText().addAttribute(TextAttribute.SIZE, 16);
  
  sensor1RawValue.getStyledText().addAttribute(TextAttribute.SIZE, 16);
  sensor2RawValue.getStyledText().addAttribute(TextAttribute.SIZE, 16);
  sensor3RawValue.getStyledText().addAttribute(TextAttribute.SIZE, 16);
  
  sensor1CalDry.setNumeric(0,1024,500);
  sensor2CalDry.setNumeric(0,1024,500);
  sensor3CalDry.setNumeric(0,1024,500);
  sensor1CalWet.setNumeric(0,1024,500);
  sensor2CalWet.setNumeric(0,1024,500);
  sensor3CalWet.setNumeric(0,1024,500);

}
void showConnecting() {
  panelLoading.setVisible(true);
  serialList.setVisible(false);
  connectButton.setVisible(false);
  loadingLabel.setVisible(true);
}
void showConnectPrompt() {
  serialList.setItems(Serial.list(),0);
  panelLoading.setVisible(true);
  serialList.setVisible(true);
  connectButton.setVisible(true);
  loadingLabel.setVisible(false);
}
void hideConnectPrompt() {
  panelLoading.setVisible(false);
  serialList.setVisible(false);
  connectButton.setVisible(false);
  loadingLabel.setVisible(false);
}

public void connectSerial(String port) {
  arduinoPort = new Serial(this, port, 9600);
  redraw();
  delay(2000);
  arduinoPort.write("   ");
  delay(2000);
  prevMillisPing = millis();
  
  arduinoPort.bufferUntil('\n');
  configRequested = false;
  
}

void ping() {
  if (firstContact) {
    arduinoPort.write('X');
  } else {
    arduinoPort.write('Z');
  }
}

void serialEvent(Serial arduinoPort) {
  // read a byte from the serial port:
  int inByte = arduinoPort.read();
  // if this is the first byte received, and it's an A,
  // clear the serial buffer and note that you've
  // had first contact from the microcontroller.
  // Otherwise, add the incoming byte to the array:
  
    if ((char)inByte == 'Z') {
      arduinoPort.clear();   // clear the serial port buffer
      firstContact = true;  // you've had first contact from the microcontroller
      arduinoPort.write('X');
    } 
    if ((char)inByte == 'X') {
      prevMillisPing = millis(); //reset timeout timer
      arduinoPort.clear();   // clear the serial port buffer
      if (!firstContact) {
        firstContact = true;  // you've had first contact from the microcontroller
        configRequested = false;
      }
    }
  if (firstContact) {
    
    if (!configRequested && configBytes.length == 0) {
      println("Requesting complete config");
      arduinoPort.write('C'); //Request complete config
      configRequested = true;
    }
    //Handle command
    if ((char)inByte == 'C') {
      println("Got config cmd");
      //configStr = arduinoPort.readStringUntil('\n');
      configBytes = arduinoPort.readBytes(57);
      serialInput = true;
      println(configBytes);
    } else if ((char)inByte == 'S') {
      sensorBytes = arduinoPort.readBytes(12);
      serialInput = true;
    }
    //inString = arduinoPort.readStringUntil('\n');
  }

  
  
}

//StyledString test;
