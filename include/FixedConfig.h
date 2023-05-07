Preferences preferences;


void getPHASE_A_Up_Direction_Info(JSONVar &configObj){
  preferences.begin("pr1_up", false);
  bool phase_a_up_state = preferences.getBool("pr1_up", true);
  if(phase_a_up_state){
    configObj["PHASE_A_UP"] = true;
  }
  else{
    configObj["PHASE_A_UP"] = false;
  }
  preferences.end();   
}

void getPHASE_B_Up_Direction_Info(JSONVar &configObj){
  preferences.begin("pr2_up", false);
  bool phase_b_up_state = preferences.getBool("pr2_up", true);
  if(phase_b_up_state){
    configObj["PHASE_B_UP"] = true;
  }
  else{
    configObj["PHASE_B_UP"] = false;
  }  
  preferences.end(); 
}
void getPHASE_C_Up_Direction_Info(JSONVar &configObj){
  preferences.begin("pr3_up", false);
  bool phase_c_up_state = preferences.getBool("pr3_up", true);
  if(phase_c_up_state){
    configObj["PHASE_C_UP"] = true;
  }
  else{
    configObj["PHASE_C_UP"] = false;
  }  
  preferences.end(); 
}

void getPHASE_Yaw_Foward_Direction_Info(JSONVar &configObj){
  preferences.begin("phase_yaw", false);
  bool phase_c_up_state = preferences.getBool("phase_yaw", true);
  if(phase_c_up_state){
    configObj["PHASE_Yaw_Foward"] = true;
  }
  else{
    configObj["PHASE_Yaw_Foward"] = false;
  }  
  preferences.end(); 
}

/**SENSOR*/

void getSENSE_A_Up_Direction_Info(JSONVar &configObj){
  preferences.begin("sense1_up", false);
  bool sense_a_up_state = preferences.getBool("sense1_up", true);
  if(sense_a_up_state){
    configObj["SENSE_A_UP"] = true;
  }
  else{
    configObj["SENSE_A_UP"] = false;
  }
  preferences.end();   
}
void getSENSE_B_Up_Direction_Info(JSONVar &configObj){
  preferences.begin("sense2_up", false);
  bool sense_b_up_state = preferences.getBool("sense2_up", true);
  if(sense_b_up_state){
    configObj["SENSE_B_UP"] = true;
  }
  else{
    configObj["SENSE_B_UP"] = false;
  }  
  preferences.end(); 
}
void getSENSE_C_Up_Direction_Info(JSONVar &configObj){
  preferences.begin("sense3_up", false);
  bool sense_c_up_state = preferences.getBool("sense3_up", true);
  if(sense_c_up_state){
    configObj["SENSE_C_UP"] = true;
  }
  else{
    configObj["SENSE_C_UP"] = false;
  }  
  preferences.end(); 
}
void getSENSE_Yaw_Foward_Direction_Info(JSONVar &configObj){
  preferences.begin("sense_yaw", false);
  bool sense_c_up_state = preferences.getBool("sense_yaw", true);
  if(sense_c_up_state){
    configObj["SENSE_Yaw_Foward"] = true;
  }
  else{
    configObj["SENSE_Yaw_Foward"] = false;
  }  
  preferences.end(); 
}

///
//

/*return calibration status*/
void getPhaseCalibrate_Info(JSONVar &configObj){
  if(MODE == PHASE_CALIBRATION){
    configObj["btnphaseCalibrate"] = true;
  }
  else{
    configObj["btnphaseCalibrate"] = false;
  }  
}

String getPower_Info(JSONVar &configObj){
  preferences.begin("power_ops", false);
  String modeString = String(preferences.getString("power_ops", "StandBy"));
  if(modeString.equals("StandBy")){
    configObj["btnPower"] = "StandBy";
  }
  else if(modeString.equals("PowerOn")){
    configObj["btnPower"] = "PowerOn";
  }
  else {
    configObj["btnPower"] = "StandBy";
  }
  preferences.end();

  return modeString;  
}

//
void getMode_Info(JSONVar &configObj){
  preferences.begin("mode_ops", false);
  String modeString = String(preferences.getString("mode_ops", "buttonFreeRide"));
  PRINTLINE("modeops: " + modeString);
  if(modeString.equals("buttonFreeRide")){
    configObj["buttonFreeRide"] = true;
    configObj["buttonHeadTracking"] = false;
    configObj["buttonHeadsUp"] = false;
  }
  else if(modeString.equals("buttonHeadTracking")){
    configObj["buttonFreeRide"] = false;
    configObj["buttonHeadTracking"] = true;
    configObj["buttonHeadsUp"] = false;
  }
  else if(modeString.equals("buttonHeadsUp")){
    configObj["buttonFreeRide"] = false;
    configObj["buttonHeadTracking"] = false;
    configObj["buttonHeadsUp"] = true;
  }
  else{
    configObj["buttonFreeRide"] = true;
    configObj["buttonHeadTracking"] = false;
    configObj["buttonHeadsUp"] = false;
  }
  preferences.end();  
}

bool getAudioEnable_Info(JSONVar &configObj){
  preferences.begin("audio_en", false);
  bool audiostring = preferences.getBool("audio_en", true);
  if(audiostring){
    configObj["btnAudioEnable"] = true;
  }
  else{
    configObj["btnAudioEnable"] = false;
  }  
  preferences.end(); 

  return audiostring;
}

bool getVibrEnable_Info(JSONVar &configObj){
  preferences.begin("vibr_en", false);
  bool vibrstring = preferences.getBool("vibr_en", true);
  if(vibrstring){
    configObj["btnVibrEnable"] = true;
  }
  else{
    configObj["btnVibrEnable"] = false;
  }  
  preferences.end(); 

  return vibrstring;
}
bool getHTEnable_Info(JSONVar &configObj){
  preferences.begin("HT_en", false);
  bool htstring = preferences.getBool("HT_en", true);
  if(htstring){
    configObj["btnHTEnable"] = true;
  }
  else{
    configObj["btnHTEnable"] = false;
  }  
  preferences.end(); 

  return htstring;
}
bool getPitchYaw_Info(JSONVar &configObj){
  preferences.begin("pitchyaw_en", false);
  bool pitchyawstring = preferences.getBool("pitchyaw_en", false);
  if(pitchyawstring){
    configObj["btnPitchYaw"] = true;
  }
  else{
    configObj["btnPitchYaw"] = false;
  }  
  preferences.end(); 

  return pitchyawstring;
}
void getWifiSwitch_Info(JSONVar &configObj){
  preferences.begin("wifiswitch_en", false);
  bool pitchyawstring = preferences.getBool("wifiswitch_en", true);
  if(pitchyawstring){
    configObj["wifiSwitch"] = true;
  }
  else{
    configObj["wifiSwitch"] = false;
  }  
  preferences.end(); 
}
void getBleSwitch_Info(JSONVar &configObj){
  preferences.begin("bleswitch_en", false);
  bool pitchyawstring = preferences.getBool("bleswitch_en", false);
  if(pitchyawstring){
    configObj["bleSwitch"] = true;
  }
  else{
    configObj["bleSwitch"] = false;
  }  
  preferences.end(); 
}
void getBtnPowerYaw_Info(JSONVar &configObj){
  preferences.begin("btnpoweryaw_en", false);
  int pitchyawpower = preferences.getInt("btnpoweryaw_en", 50);
  configObj["btnPowerYaw"] = pitchyawpower;
  preferences.end(); 
}
void getBtnPowerHt_Info(JSONVar &configObj){
  preferences.begin("btnpowerht_en", false);
  int btnpowerht = preferences.getInt("btnpowerht_en", 70);
  configObj["btnPowerHt"] = btnpowerht;
  preferences.end(); 
}
void getBtnPowerHud_Info(JSONVar &configObj){
  preferences.begin("btnpowerhud_en", false);
  int btnpowerhud = preferences.getInt("btnpowerhud_en", 70);
  configObj["btnPowerHud"] = btnpowerhud;
  preferences.end(); 
}

int getLastVoltage(){
  preferences.begin("voltage", false);
  int initVoltage = preferences.getInt("voltage", 4095);  
  preferences.end(); 
  return initVoltage;
}

//maxPhse buffers
void getA_Buffer_Max_Index(JSONVar &configObj){
  preferences.begin("indexAmax", false);
  int bufferMax = preferences.getInt("indexAmax", 0);//0 will force the init cylinders at bottom
  configObj["indexAmax"] = bufferMax;
  preferences.end(); 
}
void getB_Buffer_Max_Index(JSONVar &configObj){
  preferences.begin("indexBmax", false);
  int bufferMax = preferences.getInt("indexBmax", 0);//0 will force the init cylinders at bottom
  configObj["indexBmax"] = bufferMax;
  preferences.end(); 
}
void getC_Buffer_Max_Index(JSONVar &configObj){
  preferences.begin("indexCmax", false);
  int bufferMax = preferences.getInt("indexCmax", 0);//0 will force the init cylinders at bottom
  configObj["indexCmax"] = bufferMax;
  preferences.end(); 
}

///
float getDefaultZero_Yaw_Pr(JSONVar &configObj){
  preferences.begin("def_0_pr", false);
  float defaultzeroyawpr = preferences.getFloat("def_0_pr");
  configObj["def_0_pr"] = defaultzeroyawpr;
  preferences.end(); 
  return defaultzeroyawpr;
}