void reportModeToClient(String keystring){
  JSONVar configObj;
  if(keystring.compareTo("buttonFreeRide") == 0){
    MODE = FREE;
    setMode_Info(keystring); 
    getMode_Info(configObj);
    updateClient(configObj);
    beepTimes(1, 200);
  }
  if(keystring.compareTo("buttonHeadTracking") == 0){
    MODE = HEADTRACKING;
    setMode_Info(keystring); 
    getMode_Info(configObj);
    updateClient(configObj);
    beepTimes(1, 200);
  }
  if(keystring.compareTo("buttonHeadsUp") == 0){
    MODE = COCKPIT;
    setMode_Info(keystring); 
    getMode_Info(configObj);
    updateClient(configObj);
    beepTimes(1, 200);
  }
}

void togglePower_StandBy(){
  JSONVar configObj;
  String btnpower = getPower_Info(configObj);  
  if(btnpower.compareTo("StandBy") == 0){
    setPower_Mode("PowerOn");
    //activate PowerOn
    POWER = PowerOn;
  }
  else if(btnpower.compareTo("PowerOn") == 0){
    setPower_Mode("StandBy");
    //activate StandBy
    POWER = StandBy;
  }
}
void sendShutDown(String keystring){
  if(keystring.compareTo("buttonShutDown") == 0){
    //shutDown();
  }
}
void processPower_Mode(String keystring){  
  if(keystring.compareTo("btnPower") == 0 || keystring.compareTo("svgPower") == 0){    
    togglePower_StandBy();
    JSONVar configObj;
    getPower_Info(configObj);   
    //updateClient(configObj);
  }
}

String getString(JSONVar value){
  String valuestring = JSON.stringify(value);
  if(valuestring.indexOf('"') != -1){
      valuestring.remove(0, 1);
      valuestring.remove(valuestring.length() - 1);
  }  
  return valuestring;
}

/*Yaw, Pitch, Roll Command from User Interface */
void sendBtnRight(String keystring){
  if(keystring.compareTo("btnRight") == 0){
    rollTurn(15); //15 = pitchRight full
  }
}
void sendBtnUp(String keystring){
  if(keystring.compareTo("btnUp") == 0){
    pitchTurn(15);
  }
}
void sendBtnLeft(String keystring){
  if(keystring.compareTo("btnLeft") == 0){
    rollTurn(-15);
  }
}
void sendBtnDown(String keystring){
  if(keystring.compareTo("btnDown") == 0){
    pitchTurn(-15);
  }
}
void sendBtnCentre(String keystring){
  if(keystring.compareTo("btnCentre") == 0){
    pitchRoll_Centre();
  }
}

/***/
void sendAnalogAngle(String keystring, String valuestring){  
  if(keystring.compareTo("AnalogAngle") == 0){
    writeAnalogAngle(valuestring);
  }
}
void sendAnalogXAxis(String keystring, String valuestring){  
  if(keystring.compareTo("AnalogXAxis") == 0){
    writeAnalogXAxis(valuestring);
  }
}
void sendAnalogYAxis(String keystring, String valuestring){
  if(keystring.compareTo("AnalogYAxis") == 0){
    writeAnalogYAxis(valuestring);
  }
}
void sendBtnHTCalibrate(String keystring){
  if(keystring.compareTo("btnHTCalibrate") == 0){
    writeBtnHTCalibrate();
  }
}
/***/
void toggleEnableAudio(){
  JSONVar configObj;
  bool audiostate = getAudioEnable_Info(configObj);
  if(audiostate){
    PRINTLINE("disabling audio");
    setAudio_Enable(false);
  }
  else{
    PRINTLINE("enabling audio");
    setAudio_Enable(true);
  }
}
void processAudioEnable(String keystring){
  if(keystring.compareTo("btnAudioEnable") == 0){
    toggleEnableAudio();
    JSONVar configObj;
    getAudioEnable_Info(configObj);   
    updateClient(configObj);
  }
}
/**/
void toggleEnableVibr(){
  JSONVar configObj;
  bool vibrstring = getVibrEnable_Info(configObj);
  if(vibrstring){
    PRINTLINE("disabling Vibr");
    setVibr_Enable(false);
  }
  else {
    PRINTLINE("enabling Vibr");
    setVibr_Enable(true);
  }
}
void processHapticEnable(String keystring){
  if(keystring.compareTo("btnVibrEnable") == 0){
    toggleEnableVibr();
    JSONVar configObj;
    getVibrEnable_Info(configObj);   
    updateClient(configObj);
  }
}
/***/
void toggleHTEnable(){
  JSONVar configObj;
  int htstring = getHTEnable_Info(configObj);
  if(htstring){
    PRINTLINE("disabling HT");
    setHT_Enable(false);
    beepTimes(1, 250);
  }
  else {
    PRINTLINE("enabling HT");
    setHT_Enable(true);
    beepTimes(1, 250);
  }
}
void processHTEnable(String keystring){
  if(keystring.compareTo("btnHTEnable") == 0){
    toggleHTEnable();
    JSONVar configObj;
    getHTEnable_Info(configObj);   
    updateClient(configObj);
  }
}
/**/
void togglePitchYawEnable(){
  JSONVar configObj;
  int pitchyawstring = getPitchYaw_Info(configObj);
  if(pitchyawstring){
    PRINTLINE("disabling PitchYaw");
    setPitchYaw_Enable(false);
    pitchrollenabled = false;
    beepTimes(1, 250);
  }
  else{
    PRINTLINE("enabling PitchYaw");
    setPitchYaw_Enable(true);
    pitchrollenabled = true;
    beepTimes(1, 250);
  }
}
void processPitchYaw(String keystring){
  if(keystring.compareTo("btnPitchYaw") == 0){
    togglePitchYawEnable();
    JSONVar configObj;
    getPitchYaw_Info(configObj);   
    updateClient(configObj);
  }
}
/**/
void switchWifi(String valuestring){
  PRINTLINE("Wifi_Valx: " + valuestring);
  if(valuestring.compareTo("true") == 0){
    PRINTLINE("enabling Wifi");
    //enable wifi here
    setWifi_Enable(true);
  }
  else if(valuestring.compareTo("false") == 0){
    PRINTLINE("disabling Wifi");
    //disable wifi here
    setWifi_Enable(false);
  }
  else{
    PRINTLINE("Error Wifi operation");
  }
}
void processWifiSwitch(String keystring, String valuestring){
  if(keystring.compareTo("wifiSwitch") == 0){
    switchWifi(valuestring);
    JSONVar configObj;
    getWifiSwitch_Info(configObj);   
    updateClient(configObj);
  }
}
void switchBle(String valuestring){
  PRINTLINE("Ble_Valx: " + valuestring);      
  //PRINTLINE("Wifi_Keyx: " + keystring);
  if(valuestring.compareTo("true") == 0){
    PRINTLINE("enabling Ble");
    //enable Ble here
    setBle_Enable(true);
  }
  else if(valuestring.compareTo("false") == 0){
    PRINTLINE("disabling Ble");
    //disable Ble here
    setBle_Enable(false);
  }
  else{
    PRINTLINE("Error Ble operation");
  }
}
void processBleSwitch(String keystring, String valuestring){
  if(keystring.compareTo("bleSwitch") == 0){
    switchBle(valuestring);
    JSONVar configObj;
    getBleSwitch_Info(configObj);   
    updateClient(configObj);
  }
}

/*
*Xbox Controller data
*/
void gamePadRead(String keystring, String valuestring){
  PRINTLINE("Xbox: keystring: " + keystring + " valuestring: " + valuestring);
  //control yaw
  if(keystring.compareTo("LEFT_ANALOG_STICK_x") == 0 || keystring.compareTo("RIGHT_ANALOG_STICK_x") == 0){
    float  vax = valuestring.toFloat();
    int power = abs((vax*100));
    if(vax > 0){
      rightTurn(power);
      PRINTLINE("ANALOGRIGHT:" + String(power));
    }
    else if(vax < 0){
      leftTurn(power);
      PRINTLINE("ANALOGLEFT:" + String(power));
    }
    else{
      rightTurn(power);
      leftTurn(power);
      PRINTLINE("ANALOG STOP:" + String(power));
    }     
  }
  if(keystring.compareTo("turnleft") == 0){
    leftTurn(valuestring.toInt()*100);
  }
  if(keystring.compareTo("turnright") == 0){
    rightTurn(valuestring.toInt()*100);
  }
  //control pitch 
  if(keystring.compareTo("forwardlook") == 0){
    int val =  map(valuestring.toInt(), 0, 100, 0, 15);
    pitchTurn(val);
  }
  if(keystring.compareTo("backlook") == 0){
    int val =  map(valuestring.toInt(), 0, 100, 0, 15);
    pitchTurn(-val);
  }
  //control roll
  if(keystring.compareTo("rightlook") == 0){
    int val =  map(valuestring.toInt(), 0, 100, 0, 15);
    rollTurn(val);
  }  
  if(keystring.compareTo("leftlook") == 0){
    int val =  map(valuestring.toInt(), 0, 100, 0, 15);
    rollTurn(-val);
  }
  ///  
}

/***/
void decodeCommand(String msg){
  //JSONVar myObj = JSON.parse("{\"result\":true,\"count\":42,\"foo\":\"bar\"}");
  JSONVar myObj = JSON.parse(msg);    
  JSONVar keys = myObj.keys();
  for (int i = 0; i < keys.length(); i++) {
    JSONVar value = myObj[keys[i]];
    JSONVar key = keys[i];
    
    PRINT("JSON.typeof(myObj[");
    PRINT(key);
    PRINT("]) = ");
    PRINTLINE(JSON.typeof(value));
    
    PRINT("myObj[");
    PRINT(key);
    PRINT("] = ");
    PRINTLINE(value);    
    PRINTLINE();
    
    String  valuestring = getString(value);
    String  keystring = getString(key);
    
    processPower_Mode(keystring);      
    
    reportModeToClient(keystring);
    sendShutDown(keystring);
    sendBtnRight(keystring);
    sendBtnUp(keystring);
    sendBtnLeft(keystring);
    sendBtnDown(keystring);
    sendBtnCentre(keystring);
    sendAnalogAngle(keystring, valuestring);
    
    sendAnalogXAxis(keystring, valuestring);
    sendBtnHTCalibrate(keystring);
    
    processAudioEnable(keystring);
    processHapticEnable(keystring);
    processHTEnable(keystring);
    processPitchYaw(keystring);
    processWifiSwitch(keystring, valuestring);
    processBleSwitch(keystring, valuestring);
    powerYawSettings(keystring, valuestring);
    powerHtSettings(keystring, valuestring);
    powerHudSettings(keystring, valuestring);
    
    gamePadRead(keystring, valuestring);
    
    
  }
}