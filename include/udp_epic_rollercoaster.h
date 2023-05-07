
float GetYaw(){
    String yaw_s = packetBuffer;
    yaw_s = yaw_s.substring(yaw_s.indexOf('Y') + 2);
    yaw_s = yaw_s.substring(0, yaw_s.indexOf(']'));
    float yaw_f = atof(yaw_s.c_str());
    Serial.println("Yaw Decoded: " + String(yaw_f));
    return yaw_f;
}

float GetPitch(){
    String pitch_s = packetBuffer;
    pitch_s = pitch_s.substring(pitch_s.indexOf('P') + 2);
    pitch_s = pitch_s.substring(0, pitch_s.indexOf(']'));
    float pitch_f = atof(pitch_s.c_str());
    Serial.println("Pitch Decoded: " + String(pitch_f));
    return pitch_f;
}

float GetRoll(){
    String roll_s = packetBuffer;
    roll_s = roll_s.substring(roll_s.indexOf('R') + 2);
    roll_s = roll_s.substring(0, roll_s.indexOf(']'));
    float roll_f = atof(roll_s.c_str());
    Serial.println("Roll Decoded: " + String(roll_f));
    return roll_f;
}

void read_epicrollercoaster(int packet_length){   
  if (packet_length >= 120){
      float _header = GetYaw();
      float _pitch = GetPitch();
      float _roll = GetRoll();

      float newyaw, newpitch, newroll;
      if(eqlz){
        newyaw = 360-((_header) * RAD_TO_DEG + 180.0f); 
        newpitch = ((_pitch) * RAD_TO_DEG); 
        newroll = ((_roll) * RAD_TO_DEG);
      }
      else{
        newyaw = _header; 
        newpitch = _pitch; 
        newroll = _roll;
      }      
      //      
      Serial.printf("Roll = %f, Pitch = %f, Yaw = %f\n", newroll, newpitch, newyaw);

      htyawdegree = newyaw; //yaw
      //boost pr
      float boostpitch = newpitch*amp_sim_pr; 
      htpitchdegree = boostpitch > pitchMax ? pitchMax : boostpitch;
      float boostroll = newroll*amp_sim_pr;      
      htrolldegree = boostroll > rollMax ? rollMax : boostroll;
  }
}