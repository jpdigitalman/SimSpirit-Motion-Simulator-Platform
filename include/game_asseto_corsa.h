
struct Asseto_corsa_pack 
{     
  float     _header;      
  float     _pitch;    
  float     _roll;
};



void read_Assetto_corsa(int packet_length){    
    if (packet_length >= sizeof(Asseto_corsa_pack)){
      Serial.println("Reading Game Telemetry Data..." + String(packet_length));
      struct Asseto_corsa_pack *ac_sim_pack = (struct Asseto_corsa_pack *)&packetBuffer;
      
      bool eqlz = false;
      float newyaw, newpitch, newroll;
      if(eqlz){
        newyaw = 360-((ac_sim_pack->_header) * RAD_TO_DEG + 180.0f); 
        newpitch = ((ac_sim_pack->_pitch) * RAD_TO_DEG); 
        newroll = ((ac_sim_pack->_roll) * RAD_TO_DEG);
      }
      else{
        newyaw = ac_sim_pack->_header; 
        newpitch = ac_sim_pack->_pitch; 
        newroll = ac_sim_pack->_roll;
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