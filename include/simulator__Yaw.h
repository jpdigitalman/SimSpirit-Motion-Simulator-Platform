float getChairTargetMovement(float oldAngle, float newAngle){

  float diff = (oldAngle-newAngle);
  PRINTLINE("float diffx: " + String(diff));

  int left_part, right_part;
  char buffer[6];
  sprintf(buffer, "%lf", diff);
  sscanf(buffer, "%d.%d", &left_part, &right_part);

  PRINTLINE("partleft: " + String(left_part));
  PRINTLINE("partright: " + String(right_part));

  float subt = left_part - diff;
  //
  PRINTLINE("Subt: " + String(subt));

  int target = ((int)(oldAngle-newAngle + 360) % 360);

  PRINTLINE("Target: " + String(target));
  
  float movement = (target + subt) + 0.1;

  if(movement < 0){
    movement = 0.00f;
  }
  
  PRINTLINE("Movement: " + String(movement));

  return movement;
}

float getChairMovement(float oldAngle, float newAngle){
   float movement = (float)(((int)(oldAngle*100)-(int)(newAngle*100) + 36000) % 36000)/100.00f;
   PRINTLINE("NEW Movement: " + String(movement));
   return movement;
}

void trackToYaw(){
    //calib360 = get_base_position_degrees(yaw.GetAbsoluteStep());
    PRINTLINE("Incoming Auto-Track: HT_Target: " + String(htyawdegree) + ", Base360: " + String(calib360));
    float itarget = getChairMovement(htyawdegree, calib360); 
    int ispeed = 0;
    int target_angle = 0;
    bool idirection = false;
    //determine the right way to go
    if(itarget < 180.00){
      //right
      idirection = right;
      //limit autotracking to 90 degrees difference
      target_angle = itarget*100;
      int max_diff = MAX_HT_DIFF*100;
      if(target_angle > max_diff){
        target_angle = max_diff;
      }
      ispeed = map(target_angle, 0, max_diff, 0, yaw_max_frequency);
      PRINTLINE("Target: " + String(target_angle) + " speed right: " + String(ispeed));
    }
    else {
      //left
      idirection = left;
      itarget = 360.00 - itarget; //equalise to real angle

      //limit autotracking to 90 degrees difference
      target_angle = itarget*100;
      int max_diff = MAX_HT_DIFF*100;
      if(target_angle > max_diff){
        target_angle = max_diff;
      }
      ispeed = map(target_angle, 0, max_diff, 0, yaw_max_frequency);
      PRINTLINE("Target: " + String(target_angle) + " speed left: " + String(ispeed));
    }

    //add dead-zone: if new target exceed dead-zone, continue turning the yaw
    if(target_angle > deadzone_yaw){
      //if there is a new incoming angle to track to
      if(idirection == right){        
        turn_MotorRight(0, ispeed);  
      }
      else{
        turn_MotorLeft(0, ispeed); 
      }
      //
    }
    else{
      //stopMotor(0); //RESET MOTOR 
      forceStop(0);
      startReturnToZero = true;
      PRINTLINE("Dead Zone Limit. Auto tracking aborted.");
    }
}