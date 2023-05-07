
void steps(float step, int motorspeed, int motor){  
  if(step > 0){
    PRINTLINE("motor: " + String(motor) + ", number of steps: " + String(step) + ", speed: " + String(motorspeed));
    //rotateMotorbyStep(motor, right, (int)abs(step), motorspeed);   
  }
  else{
    PRINTLINE("motor: " + String(motor) + ", number of steps: " + String(step) + ", speed: " + String(motorspeed));
    //rotateMotorbyStep(motor, left, (int)abs(step), motorspeed);   
  }
}

/**
 * @brief Pulse Yaw sends Step Pulse to Yaw Motor and also the Direction to turn the motor 
 * 
 * @param step This is the number of steps to turn the motor
 * @param motorSpeed the speed of the tuning.
 * @return int returns the position of the motor
 */
void pulseYaw(float step, int motorspeed) {
  if (motorspeed > 0) {
    steps(step, motorspeed, 0);
  }
}

void pulseRightYaw(int speed){
  disableAutoStop = true; //ignore auto stop
  pulseYaw(1, speed);   
}
void pulseLeftYaw(int speed){
  disableAutoStop = true;
  pulseYaw(-1, speed);
}

/**
 * @brief Pulse PhaseA sends Step Pulse to Piston B Motor and also the Direction to turn the motor 
 * 
 * @param step This is the number of steps to turn the motor
 * @param motorSpeed the speed of the tuning.
 * @return int returns the position of the motor
 */

int pulsePhaseA(int step, int motorspeed) {
  if (motorspeed > 0) {
    steps(step, motorspeed, 1);
  }
  return 0;
}
void pulseRight_PhaseA(int speed){
  pulsePhaseA(1, speed);   
}
void pulseLeft_PhaseA(int speed){
  pulsePhaseA(-1, speed);
}

/**
 * @brief Pulse PhaseB sends Step Pulse to Piston B Motor and also the Direction to turn the motor 
 * 
 * @param step This is the number of steps to turn the motor
 * @param motorSpeed the speed of the tuning.
 * @return int returns the position of the motor
 */

int pulsePhaseB(int step, int motorspeed) {
  if (motorspeed > 0) {
    steps(step, motorspeed, 2);
  }
  return 0;
}
void pulseRight_PhaseB(int speed){
  pulsePhaseB(1, speed);   
}
void pulseLeft_PhaseB(int speed){
  pulsePhaseB(-1, speed);
}

/**
 * @brief Pulse PhaseC  sends Step Pulse to Piston C Motor and also the Direction to turn the motor 
 * 
 * @param step This is the number of steps to turn the motor
 * @param motorSpeed the speed of the tuning.
 * @return int returns the position of the motor
 */

int pulsePhaseC(int step, int motorspeed) {
  if (motorspeed > 0) {
    steps(step, motorspeed, 3);
  }
  return 0;
}
void pulseRight_PhaseC(int speed){
  pulsePhaseC(1, speed);   
}
void pulseLeft_PhaseC(int speed){
  pulsePhaseC(-1, speed);
}