

void getWifi_Info(JSONVar &configObj){
  // Set the values in the document
  configObj["ssid"] = wifiCredentials.ssid;
  configObj["password"] = wifiCredentials.password;    
}
void getHTCalibrate_Info(JSONVar &configObj){
  configObj["btnHTCalibrate"] = false;
}

////
void getYawDegrees(JSONVar &configObj){
  configObj["YawDegrees"] = readYawDegrees();
}
void getPitchYaw_PhaseA(JSONVar &configObj){
  configObj["PitchYaw_PhaseA"] = readPitchYaw_PhaseA();
}
void getPitchYaw_PhaseB(JSONVar &configObj){
  configObj["PitchYaw_PhaseB"] = readPitchYaw_PhaseB();
}
void getPitchYaw_PhaseC(JSONVar &configObj){
  configObj["PitchYaw_PhaseC"] = readPitchYaw_PhaseC();
}
void getHT_Yaw_Degrees(JSONVar &configObj){
  configObj["HT_Yaw_Degrees"] = calib360; // readHT_Yaw_Degrees(); display calibrated heading instead of raw
}
void getHT_Pitch_Degrees(JSONVar &configObj){
  configObj["HT_Pitch_Degrees"] = readHT_Pitch_Degrees(); //display calibrated when done
}
void getHT_Roll_Degrees(JSONVar &configObj){
  configObj["HT_Roll_Degrees"] = readHT_Roll_Degrees(); //''
}
