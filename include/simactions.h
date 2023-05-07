void leftTurn(int power){
  leftPower = power;
  //Serial.println("LEFT HOOK: " + String(power));
}
void rightTurn(int power){
  leftPower = power;
  //Serial.println("RIGHT HOOK: " + String(power));
}

/*From Yaw, Pitch, Roll Command from User Interface GamePad (Or From SimTool GameEngine Synchronisation )
To Yaw, Pitch, Roll commander*/
void pitchTurn(int val){
  pitchVal = val;
}
void rollTurn(int val){
  rollVal = val;
}
void pitchRoll_Centre(){
  rollVal = 0;
  pitchVal = 0;
}
void yawTurn(int val){
  yawVal = val;
}

/**/
void writeBtnHTCalibrate(){
  WebSerial.println("Calibrate");
}
/*Yaw, Pitch, Roll Command from User Interface GamePad (Or From SimTool GameEngine Synchronisation )*/
void writeAnalogAngle(String valuestring){
  WebSerial.println("analogAngle: " + valuestring); //yaw
  yawTurn(valuestring.toInt());
}
void writeAnalogXAxis(String valuestring){
  WebSerial.println("analog X Angle: " + valuestring); //roll
  int val = map(valuestring.toInt(), 0, analogGamePadX_Y_Axis_Maximum_Input, 0, 15);
  rollTurn(val);
}
void writeAnalogYAxis(String valuestring){
  WebSerial.println("Analog Y: " + valuestring); //pitch
  int val = map(valuestring.toInt(), 0, analogGamePadX_Y_Axis_Maximum_Input, 0, 15);
  pitchTurn(val);
}

/*
Yaw, Pitch, Roll From Head Tracker sensor data
*/
int readHT_Yaw_Degrees(){
  return htyawdegree;
}
int readHT_Pitch_Degrees(){
  return htpitchdegree;
}
int readHT_Roll_Degrees(){
  return htrolldegree;
}

/***/
/*
Encoder Data from base sensor data for Yaw, PistonA, PistonB, PistonC
*/
int readYawDegrees(){  
  return 25; // yawdegree;
}
int readPitchYaw_PhaseA(){
  return 50; //phaseA;// pitchyawphase_a;
}
int readPitchYaw_PhaseB(){
  return 50; //phaseB; // pitchyawphase_b;
}
int readPitchYaw_PhaseC(){
  return 50; //phaseC; // pitchyawphase_c;
}
