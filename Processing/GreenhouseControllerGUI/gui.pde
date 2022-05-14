/* =========================================================
 * ====                   WARNING                        ===
 * =========================================================
 * The code in this tab has been generated from the GUI form
 * designer and care should be taken when editing this file.
 * Only add/edit code inside the event handlers i.e. only
 * use lines between the matching comment tags. e.g.

 void myBtnEvents(GButton button) { //_CODE_:button1:12356:
     // It is safe to enter your event code here  
 } //_CODE_:button1:12356:
 
 * Do not rename this tab!
 * =========================================================
 */

public void humidityInterval_changed(GSlider source, GEvent event) { //_CODE_:humidityInterval:766451:
  //println("humidityInterval - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "H," + source.getValueS();
    arduinoPort.write(cmd + "\n");
  }
} //_CODE_:humidityInterval:766451:

public void sensor1Enable_clicked(GCheckbox source, GEvent event) { //_CODE_:sensor1Enable:999645:
  //println("sensor1enable - GCheckbox >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.SELECTED) {
    String cmd = "E,1,1";
    arduinoPort.write(cmd + '\n');
  } else if (arduinoPort != null && arduinoPort.active() && event == GEvent.DESELECTED) {
    String cmd = "E,1,0";
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor1Enable:999645:

public void sensor2Enable_clicked(GCheckbox source, GEvent event) { //_CODE_:sensor2Enable:320699:
  //println("sensor2Enable - GCheckbox >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.SELECTED) {
    String cmd = "E,2,1";
    arduinoPort.write(cmd + '\n');
  } else if (arduinoPort != null && arduinoPort.active() && event == GEvent.DESELECTED) {
    String cmd = "E,2,0";
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor2Enable:320699:

public void sensor3Enable_clicked(GCheckbox source, GEvent event) { //_CODE_:sensor3Enable:839573:
  //println("sensor3Enable - GCheckbox >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.SELECTED) {
    String cmd = "E,3,1";
    arduinoPort.write(cmd + '\n');
  } else if (arduinoPort != null && arduinoPort.active() && event == GEvent.DESELECTED) {
    String cmd = "E,3,0";
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor3Enable:839573:

public void sensor1Limit_changed(GSlider source, GEvent event) { //_CODE_:sensor1Limit:916357:
  //println("sensor1Limit - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "L,1," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor1Limit:916357:

public void sensor2Limit_changed(GSlider source, GEvent event) { //_CODE_:sensor2Limit:640917:
  //println("sensor2Limit - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "L,2," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor2Limit:640917:

public void sensor3Limit_change1(GSlider source, GEvent event) { //_CODE_:sensor3Limit:307781:
  //println("sensor3Limit - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "L,3," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor3Limit:307781:

public void sensor1Pumptime_changed(GSlider source, GEvent event) { //_CODE_:sensor1Pumptime:699780:
  //println("sensor1Pumptime - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "P,1," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor1Pumptime:699780:

public void sensor2Pumptime_changed(GSlider source, GEvent event) { //_CODE_:sensor2Pumptime:339239:
  //println("sensor2Pumptime - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "P,2," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor2Pumptime:339239:

public void sensor3Pumptime_changed(GSlider source, GEvent event) { //_CODE_:sensor3Pumptime:412668:
  //println("sensor3Pumptime - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "P,3," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor3Pumptime:412668:

public void sensor1Maxpumpings_changed(GSlider source, GEvent event) { //_CODE_:sensor1Maxpumpings:705855:
  //println("sensor1Maxpumpings - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "M,1," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor1Maxpumpings:705855:

public void sensor2Maxpumpings_changed(GSlider source, GEvent event) { //_CODE_:sensor2Maxpumpings:404000:
  //println("sensor2Maxpumpings - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "M,2," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor2Maxpumpings:404000:

public void sensor3Maxpumpings_changed(GSlider source, GEvent event) { //_CODE_:sensor3Maxpumpings:887263:
  //println("sensor3Maxpumpings - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "M,3," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor3Maxpumpings:887263:

public void sensor1Pumptimeout_changed(GSlider source, GEvent event) { //_CODE_:sensor1Pumptimeout:793933:
  //println("sensor1Pumptimeout - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "T,1," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor1Pumptimeout:793933:

public void sensor2Pumptimeout_changed(GSlider source, GEvent event) { //_CODE_:sensor2Pumptimeout:419186:
  //println("slider5 - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "T,2," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor2Pumptimeout:419186:

public void sensor3Pumptimeout_changed(GSlider source, GEvent event) { //_CODE_:sensor3Pumptimeout:597904:
  //println("slider6 - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "T,3," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor3Pumptimeout:597904:

public void sensor1Pumpdelay_changed(GSlider source, GEvent event) { //_CODE_:sensor1Pumpdelay:898301:
  //println("sensor1Pumpdelay - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "D,1," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor1Pumpdelay:898301:

public void sensor2Pumpdelay_changed(GSlider source, GEvent event) { //_CODE_:sensor2Pumpdelay:807098:
  //println("sensor2Pumpdelay - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "D,2," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor2Pumpdelay:807098:

public void sensor3Pumpdelay_changed(GSlider source, GEvent event) { //_CODE_:sensor3Pumpdelay:824482:
  //println("sensor3Pumpdelay - GSlider >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.RELEASED) {
    String cmd = "D,3," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor3Pumpdelay:824482:


public void sensor1CalDry_changed(GTextField source, GEvent event) { //_CODE_:sensor1CalDry:353032:
  //println("sensor1CalDry - GTextField >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && (event == GEvent.LOST_FOCUS || event == GEvent.ENTERED)) {
    String cmd = "K,1," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor1CalDry:353032:

public void sensor2CalDry_changed(GTextField source, GEvent event) { //_CODE_:sensor2CalDry:525195:
  //println("textfield2 - GTextField >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && (event == GEvent.LOST_FOCUS || event == GEvent.ENTERED)) {
    String cmd = "K,2," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor2CalDry:525195:

public void sensor3CalDry_changed(GTextField source, GEvent event) { //_CODE_:sensor3CalDry:333581:
  //println("textfield4 - GTextField >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && (event == GEvent.LOST_FOCUS || event == GEvent.ENTERED)) {
    String cmd = "K,3," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor3CalDry:333581:


public void sensor1CalWet_changed(GTextField source, GEvent event) { //_CODE_:sensor1CalWet:735550:
  //println("textfield1 - GTextField >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && (event == GEvent.LOST_FOCUS || event == GEvent.ENTERED)) {
    String cmd = "W,1," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor1CalWet:735550:

public void sensor2CalWet_changed(GTextField source, GEvent event) { //_CODE_:sensor2CalWet:893584:
  //println("textfield1 - GTextField >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && (event == GEvent.LOST_FOCUS || event == GEvent.ENTERED)) {
    String cmd = "W,2," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor2CalWet:893584:

public void sensor3CalWet_changed(GTextField source, GEvent event) { //_CODE_:sensor3CalWet:649370:
  //println("textfield3 - GTextField >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && (event == GEvent.LOST_FOCUS || event == GEvent.ENTERED)) {
    String cmd = "W,3," + source.getValueI();
    arduinoPort.write(cmd + '\n');
  }
} //_CODE_:sensor3CalWet:649370:



public void resetButton_clicked(GButton source, GEvent event) { //_CODE_:resetButton:668454:
  //println("resetButton - GButton >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.CLICKED) {
    String cmd = "R,";
    arduinoPort.write(cmd + '\n');
    saving = true;
    showSavingPrompt();
  }
} //_CODE_:resetButton:668454:
public void saveButton_clicked(GButton source, GEvent event) { //_CODE_:resetButton:668454:
  //println("resetButton - GButton >> GEvent." + event + " @ " + millis());
  if (arduinoPort != null && arduinoPort.active() && event == GEvent.CLICKED) {
    String cmd = "M,1," + sensor1Maxpumpings.getValueI();
    arduinoPort.write(cmd + '\n');
    cmd = "M,2," + sensor2Maxpumpings.getValueI();
    arduinoPort.write(cmd + '\n');
    cmd = "M,3," + sensor3Maxpumpings.getValueI();
    arduinoPort.write(cmd + '\n');
    
    cmd = "D,1," + sensor1Pumpdelay.getValueI();
    arduinoPort.write(cmd + '\n');
    cmd = "D,2," + sensor2Pumpdelay.getValueI();
    arduinoPort.write(cmd + '\n');
    cmd = "D,3," + sensor3Pumpdelay.getValueI();
    arduinoPort.write(cmd + '\n');
    
    cmd = "H," + humidityInterval.getValueS();
    arduinoPort.write(cmd + "\n");
    
    cmd = "S,";
    arduinoPort.write(cmd + '\n');
    saving = true;
    showSavingPrompt();
  }
} //_CODE_:resetButton:668454:

public void connectButton_clicked(GButton source, GEvent event) { 
  if (event == GEvent.CLICKED) {
    showConnecting();
    connectSerial(serialList.getSelectedText());
  }
} 



// Create all the GUI controls. 
// autogenerated do not edit
public void createGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setMouseOverEnabled(false);
  G4P.setDisplayFont("Arial", G4P.PLAIN, 13);
  G4P.setInputFont("Arial", G4P.PLAIN, 13);
  G4P.setSliderFont("Arial", G4P.PLAIN, 13);
  surface.setTitle("Greenhouse Controller");
  humidityIntervalLabel = new GLabel(this, 20, 20, 150, 40);
  humidityIntervalLabel.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  humidityIntervalLabel.setText("Intervall för fuktmätning");
  humidityIntervalLabel.setOpaque(false);
  humidityInterval = new GSlider(this, 180, 10, 310, 60, 10.0);
  humidityInterval.setShowValue(true);
  humidityInterval.setShowLimits(true);
  humidityInterval.setLimits(30, 15, 120);
  humidityInterval.setNbrTicks(8);
  humidityInterval.setStickToTicks(true);
  humidityInterval.setShowTicks(true);
  humidityInterval.setNumberFormat(G4P.INTEGER, 0);
  humidityInterval.setOpaque(false);
  humidityInterval.addEventHandler(this, "humidityInterval_changed");
  sensor1Enable = new GCheckbox(this, 140, 80, 200, 20);
  sensor1Enable.setIconAlign(GAlign.LEFT, GAlign.MIDDLE);
  sensor1Enable.setText("Sensor 1");
  sensor1Enable.setOpaque(false);
  sensor1Enable.addEventHandler(this, "sensor1Enable_clicked");
  sensor1Limit_Label = new GLabel(this, 20, 110, 110, 40);
  sensor1Limit_Label.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  sensor1Limit_Label.setText("Fuktgräns för vattning (0-100)");
  sensor1Limit_Label.setOpaque(false);
  sensor1Pumptime_label = new GLabel(this, 20, 170, 110, 40);
  sensor1Pumptime_label.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  sensor1Pumptime_label.setText("Pumptid (1-60 sek)");
  sensor1Pumptime_label.setOpaque(false);
  sensor1Pumpings_label = new GLabel(this, 20, 230, 110, 40);
  sensor1Pumpings_label.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  sensor1Pumpings_label.setText("Max antal pumpningar inom fördröjningstiden");
  sensor1Pumpings_label.setOpaque(false);
  sensor1Maxpumpings = new GSlider(this, 140, 220, 200, 60, 10.0);
  sensor1Maxpumpings.setShowValue(true);
  sensor1Maxpumpings.setShowLimits(true);
  sensor1Maxpumpings.setLimits(2, 1, 6);
  sensor1Maxpumpings.setNbrTicks(6);
  sensor1Maxpumpings.setStickToTicks(true);
  sensor1Maxpumpings.setShowTicks(true);
  sensor1Maxpumpings.setNumberFormat(G4P.INTEGER, 0);
  sensor1Maxpumpings.setOpaque(false);
  sensor1Maxpumpings.addEventHandler(this, "sensor1Maxpumpings_changed");
  sensor1Pumpdelay_label = new GLabel(this, 20, 290, 110, 40);
  sensor1Pumpdelay_label.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  sensor1Pumpdelay_label.setText("Fördröjningstid (timmar)");
  sensor1Pumpdelay_label.setOpaque(false);
  sensor1Pumpdelay = new GSlider(this, 140, 280, 200, 60, 10.0);
  sensor1Pumpdelay.setShowValue(true);
  sensor1Pumpdelay.setShowLimits(true);
  sensor1Pumpdelay.setLimits(8, 1, 12);
  sensor1Pumpdelay.setNbrTicks(12);
  sensor1Pumpdelay.setStickToTicks(true);
  sensor1Pumpdelay.setShowTicks(true);
  sensor1Pumpdelay.setNumberFormat(G4P.INTEGER, 0);
  sensor1Pumpdelay.setOpaque(false);
  sensor1Pumpdelay.addEventHandler(this, "sensor1Pumpdelay_changed");
  sensor1Pumptimeout_label = new GLabel(this, 20, 350, 110, 40);
  sensor1Pumptimeout_label.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  sensor1Pumptimeout_label.setText("Tvinga vattning efter (timmar)");
  sensor1Pumptimeout_label.setOpaque(false);
  sensor1Pumptimeout = new GSlider(this, 140, 340, 200, 60, 10.0);
  sensor1Pumptimeout.setShowValue(true);
  sensor1Pumptimeout.setShowLimits(true);
  sensor1Pumptimeout.setLimits(48, 12, 72);
  sensor1Pumptimeout.setNbrTicks(6);
  sensor1Pumptimeout.setShowTicks(true);
  sensor1Pumptimeout.setNumberFormat(G4P.INTEGER, 0);
  sensor1Pumptimeout.setOpaque(false);
  sensor1Pumptimeout.addEventHandler(this, "sensor1Pumptimeout_changed");
  sensor1CalWet_label = new GLabel(this, 20, 410, 110, 40);
  sensor1CalWet_label.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  sensor1CalWet_label.setText("Kalibreringsvärde våt jord");
  sensor1CalWet_label.setOpaque(false);
  sensor1CalWet = new GTextField(this, 140, 420, 200, 20, G4P.SCROLLBARS_NONE);
  sensor1CalWet.setPromptText("1-1024");
  sensor1CalWet.setOpaque(true);
  sensor1CalWet.addEventHandler(this, "sensor1CalWet_changed");
  sensor1CalDry_label = new GLabel(this, 20, 470, 110, 40);
  sensor1CalDry_label.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  sensor1CalDry_label.setText("Kalibreringsvärde torr jord");
  sensor1CalDry_label.setOpaque(false);
  sensor1CalDry = new GTextField(this, 140, 480, 200, 20, G4P.SCROLLBARS_NONE);
  sensor1CalDry.setPromptText("1-1024");
  sensor1CalDry.setOpaque(true);
  sensor1CalDry.addEventHandler(this, "sensor1CalDry_changed");
  sensor1Pumptime = new GSlider(this, 140, 160, 200, 60, 10.0);
  sensor1Pumptime.setShowValue(true);
  sensor1Pumptime.setShowLimits(true);
  sensor1Pumptime.setLimits(15, 5, 60);
  sensor1Pumptime.setNbrTicks(12);
  sensor1Pumptime.setShowTicks(true);
  sensor1Pumptime.setNumberFormat(G4P.INTEGER, 0);
  sensor1Pumptime.setOpaque(false);
  sensor1Pumptime.addEventHandler(this, "sensor1Pumptime_changed");
  sensor1Limit = new GSlider(this, 140, 100, 200, 60, 10.0);
  sensor1Limit.setShowValue(true);
  sensor1Limit.setShowLimits(true);
  sensor1Limit.setLimits(70, 0, 100);
  sensor1Limit.setNbrTicks(10);
  sensor1Limit.setShowTicks(true);
  sensor1Limit.setNumberFormat(G4P.INTEGER, 0);
  sensor1Limit.setOpaque(false);
  sensor1Limit.addEventHandler(this, "sensor1Limit_changed");
  sensor2Limit = new GSlider(this, 360, 100, 200, 60, 10.0);
  sensor2Limit.setShowValue(true);
  sensor2Limit.setShowLimits(true);
  sensor2Limit.setLimits(70, 0, 100);
  sensor2Limit.setNbrTicks(10);
  sensor2Limit.setShowTicks(true);
  sensor2Limit.setNumberFormat(G4P.INTEGER, 0);
  sensor2Limit.setOpaque(false);
  sensor2Limit.addEventHandler(this, "sensor2Limit_changed");
  sensor2Pumptime = new GSlider(this, 360, 160, 200, 60, 10.0);
  sensor2Pumptime.setShowValue(true);
  sensor2Pumptime.setShowLimits(true);
  sensor2Pumptime.setLimits(15, 5, 60);
  sensor2Pumptime.setNbrTicks(12);
  sensor2Pumptime.setShowTicks(true);
  sensor2Pumptime.setNumberFormat(G4P.INTEGER, 0);
  sensor2Pumptime.setOpaque(false);
  sensor2Pumptime.addEventHandler(this, "sensor2Pumptime_changed");
  sensor2Maxpumpings = new GSlider(this, 360, 220, 200, 60, 10.0);
  sensor2Maxpumpings.setShowValue(true);
  sensor2Maxpumpings.setShowLimits(true);
  sensor2Maxpumpings.setLimits(2, 1, 6);
  sensor2Maxpumpings.setNbrTicks(6);
  sensor2Maxpumpings.setStickToTicks(true);
  sensor2Maxpumpings.setShowTicks(true);
  sensor2Maxpumpings.setNumberFormat(G4P.INTEGER, 0);
  sensor2Maxpumpings.setOpaque(false);
  sensor2Maxpumpings.addEventHandler(this, "sensor2Maxpumpings_changed");
  sensor2Pumpdelay = new GSlider(this, 360, 280, 200, 60, 10.0);
  sensor2Pumpdelay.setShowValue(true);
  sensor2Pumpdelay.setShowLimits(true);
  sensor2Pumpdelay.setLimits(8, 1, 12);
  sensor2Pumpdelay.setNbrTicks(12);
  sensor2Pumpdelay.setStickToTicks(true);
  sensor2Pumpdelay.setShowTicks(true);
  sensor2Pumpdelay.setNumberFormat(G4P.INTEGER, 0);
  sensor2Pumpdelay.setOpaque(false);
  sensor2Pumpdelay.addEventHandler(this, "sensor2Pumpdelay_changed");
  sensor2Pumptimeout = new GSlider(this, 360, 340, 200, 60, 10.0);
  sensor2Pumptimeout.setShowValue(true);
  sensor2Pumptimeout.setShowLimits(true);
  sensor2Pumptimeout.setLimits(48, 12, 72);
  sensor2Pumptimeout.setNbrTicks(6);
  sensor2Pumptimeout.setShowTicks(true);
  sensor2Pumptimeout.setNumberFormat(G4P.INTEGER, 0);
  sensor2Pumptimeout.setOpaque(false);
  sensor2Pumptimeout.addEventHandler(this, "sensor2Pumptimeout_changed");
  sensor2CalWet = new GTextField(this, 360, 420, 200, 20, G4P.SCROLLBARS_NONE);
  sensor2CalWet.setPromptText("1-1024");
  sensor2CalWet.setOpaque(true);
  sensor2CalWet.addEventHandler(this, "sensor2CalWet_changed");
  sensor2CalDry = new GTextField(this, 360, 480, 200, 20, G4P.SCROLLBARS_NONE);
  sensor2CalDry.setPromptText("1-1024");
  sensor2CalDry.setOpaque(true);
  sensor2CalDry.addEventHandler(this, "sensor2CalDry_changed");
  sensor3Limit = new GSlider(this, 580, 100, 200, 60, 10.0);
  sensor3Limit.setShowValue(true);
  sensor3Limit.setShowLimits(true);
  sensor3Limit.setLimits(70, 0, 100);
  sensor3Limit.setNbrTicks(10);
  sensor3Limit.setShowTicks(true);
  sensor3Limit.setNumberFormat(G4P.INTEGER, 0);
  sensor3Limit.setOpaque(false);
  sensor3Limit.addEventHandler(this, "sensor3Limit_change1");
  sensor3Pumptime = new GSlider(this, 580, 160, 200, 60, 10.0);
  sensor3Pumptime.setShowValue(true);
  sensor3Pumptime.setShowLimits(true);
  sensor3Pumptime.setLimits(15, 5, 60);
  sensor3Pumptime.setNbrTicks(12);
  sensor3Pumptime.setShowTicks(true);
  sensor3Pumptime.setNumberFormat(G4P.INTEGER, 0);
  sensor3Pumptime.setOpaque(false);
  sensor3Pumptime.addEventHandler(this, "sensor3Pumptime_changed");
  sensor3Maxpumpings = new GSlider(this, 580, 220, 200, 60, 10.0);
  sensor3Maxpumpings.setShowValue(true);
  sensor3Maxpumpings.setShowLimits(true);
  sensor3Maxpumpings.setLimits(2, 1, 6);
  sensor3Maxpumpings.setNbrTicks(6);
  sensor3Maxpumpings.setStickToTicks(true);
  sensor3Maxpumpings.setShowTicks(true);
  sensor3Maxpumpings.setNumberFormat(G4P.INTEGER, 0);
  sensor3Maxpumpings.setOpaque(false);
  sensor3Maxpumpings.addEventHandler(this, "sensor3Maxpumpings_changed");
  sensor2Enable = new GCheckbox(this, 360, 80, 200, 20);
  sensor2Enable.setIconAlign(GAlign.LEFT, GAlign.MIDDLE);
  sensor2Enable.setText("Sensor 2");
  sensor2Enable.setOpaque(false);
  sensor2Enable.addEventHandler(this, "sensor2Enable_clicked");
  sensor3Enable = new GCheckbox(this, 580, 80, 200, 20);
  sensor3Enable.setIconAlign(GAlign.LEFT, GAlign.MIDDLE);
  sensor3Enable.setText("Sensor 3");
  sensor3Enable.setOpaque(false);
  sensor3Enable.addEventHandler(this, "sensor3Enable_clicked");
  sensor3Pumpdelay = new GSlider(this, 580, 280, 200, 60, 10.0);
  sensor3Pumpdelay.setShowValue(true);
  sensor3Pumpdelay.setShowLimits(true);
  sensor3Pumpdelay.setLimits(8, 1, 12);
  sensor3Pumpdelay.setNbrTicks(12);
  sensor3Pumpdelay.setStickToTicks(true);
  sensor3Pumpdelay.setShowTicks(true);
  sensor3Pumpdelay.setNumberFormat(G4P.INTEGER, 0);
  sensor3Pumpdelay.setOpaque(false);
  sensor3Pumpdelay.addEventHandler(this, "sensor3Pumpdelay_changed");
  sensor3Pumptimeout = new GSlider(this, 580, 340, 200, 60, 10.0);
  sensor3Pumptimeout.setShowValue(true);
  sensor3Pumptimeout.setShowLimits(true);
  sensor3Pumptimeout.setLimits(48, 12, 72);
  sensor3Pumptimeout.setNbrTicks(6);
  sensor3Pumptimeout.setShowTicks(true);
  sensor3Pumptimeout.setNumberFormat(G4P.INTEGER, 0);
  sensor3Pumptimeout.setOpaque(false);
  sensor3Pumptimeout.addEventHandler(this, "sensor3Pumptimeout_changed");
  sensor3CalWet = new GTextField(this, 580, 420, 200, 20, G4P.SCROLLBARS_NONE);
  sensor3CalWet.setPromptText("1-1024");
  sensor3CalWet.setOpaque(true);
  sensor3CalWet.addEventHandler(this, "sensor3CalWet_changed");
  sensor3CalDry = new GTextField(this, 580, 480, 200, 20, G4P.SCROLLBARS_NONE);
  sensor3CalDry.setPromptText("1-1024");
  sensor3CalDry.setOpaque(true);
  sensor3CalDry.addEventHandler(this, "sensor3CalDry_changed");
  
  sensor1Raw_label = new GLabel(this, 830, 200, 150, 30);
  sensor1Raw_label.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  sensor1Raw_label.setText("Aktuellt värde sensor 1");
  sensor1Raw_label.setOpaque(false);
  sensor1RawValue = new GLabel(this, 830, 230, 150, 50);
  sensor1RawValue.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  sensor1RawValue.setText("1024");
  sensor1RawValue.setOpaque(true);
  sensor2Raw_label = new GLabel(this, 830, 310, 150, 30);
  sensor2Raw_label.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  sensor2Raw_label.setText("Aktuellt värde sensor 2");
  sensor2Raw_label.setOpaque(false);
  sensor2RawValue = new GLabel(this, 830, 340, 150, 50);
  sensor2RawValue.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  sensor2RawValue.setText("1024");
  sensor2RawValue.setOpaque(true);
  sensor3RawValue = new GLabel(this, 830, 450, 150, 50);
  sensor3RawValue.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  sensor3RawValue.setText("1024");
  sensor3RawValue.setOpaque(true);
  sensor3Raw_label = new GLabel(this, 830, 420, 150, 30);
  sensor3Raw_label.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  sensor3Raw_label.setText("Aktuellt värde sensor 3");
  sensor3Raw_label.setOpaque(false);
  
  resetButton = new GButton(this, 550, 20, 160, 30);
  resetButton.setText("Nollställ inställningar");
  resetButton.addEventHandler(this, "resetButton_clicked");
  saveButton = new GButton(this, 750, 20, 140, 30);
  saveButton.setText("Spara inställningar");
  saveButton.addEventHandler(this, "saveButton_clicked");
  
  panelLoading = new GPanel(this, 225, 175, 500, 200, "Ansluter till arduino");
  panelLoading.setCollapsible(false);
  panelLoading.setDraggable(false);
  panelLoading.setText("Ansluter till arduino");
  panelLoading.setOpaque(true);
  loadingLabel = new GLabel(this, 150, 75, 200, 50);
  loadingLabel.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  loadingLabel.setText("Letar efter Arduino Uno...");
  loadingLabel.setOpaque(false);
  StyledString loadingString = new StyledString("Letar efter Arduino Uno...");
  loadingString.addAttribute(TextAttribute.SIZE, 18);
  loadingLabel.setStyledText(loadingString);
  loadingLabel.setVisible(false);
  panelLoading.addControl(loadingLabel);
  serialList = new GDropList(this, 120, 80, 250, 80);
  serialList.setOpaque(false);
  panelLoading.addControl(serialList);
  connectButton = new GButton(this, 380, 80, 50, 25);
  connectButton.setText("Anslut");
  connectButton.addEventHandler(this, "connectButton_clicked");
  panelLoading.addControl(connectButton);
  
  savingLabel = new GLabel(this, 150, 75, 200, 50);
  savingLabel.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  savingLabel.setText("Sparar inställningar till arduino...");
  savingLabel.setOpaque(false);
  StyledString savingString = new StyledString("Sparar inställningar till arduino...");
  savingString.addAttribute(TextAttribute.SIZE, 18);
  savingLabel.setStyledText(savingString);
  savingLabel.setVisible(false);
  panelLoading.addControl(savingLabel);
  
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

// Variable declarations 
// autogenerated do not edit
GLabel humidityIntervalLabel; 
GSlider humidityInterval; 
GCheckbox sensor1Enable; 
GLabel sensor1Limit_Label; 
GLabel sensor1Pumptime_label; 
GLabel sensor1Pumpings_label; 
GSlider sensor1Maxpumpings; 
GLabel sensor1Pumpdelay_label; 
GSlider sensor1Pumpdelay; 
GLabel sensor1Pumptimeout_label; 
GSlider sensor1Pumptimeout; 
GLabel sensor1CalWet_label; 
GTextField sensor1CalWet; 
GLabel sensor1CalDry_label; 
GTextField sensor1CalDry; 
GSlider sensor1Pumptime; 
GSlider sensor1Limit; 
GSlider sensor2Limit; 
GSlider sensor2Pumptime; 
GSlider sensor2Maxpumpings; 
GSlider sensor2Pumpdelay; 
GSlider sensor2Pumptimeout; 
GTextField sensor2CalWet; 
GTextField sensor2CalDry; 
GSlider sensor3Limit; 
GSlider sensor3Pumptime; 
GSlider sensor3Maxpumpings; 
GCheckbox sensor2Enable; 
GCheckbox sensor3Enable; 
GSlider sensor3Pumpdelay; 
GSlider sensor3Pumptimeout; 
GTextField sensor3CalWet; 
GTextField sensor3CalDry; 
GButton resetButton; 
GLabel sensor1Raw_label; 
GLabel sensor1RawValue; 
GLabel sensor2Raw_label; 
GLabel sensor2RawValue; 
GLabel sensor3RawValue; 
GLabel sensor3Raw_label; 
GPanel panelLoading; 
GLabel loadingLabel; 
GLabel savingLabel;
GDropList serialList;
GButton connectButton;
GButton saveButton;
