void setPHASE_A_Up_Direction_Info(bool state){
    preferences.begin("pr1_up", false);
    preferences.putBool("pr1_up", state); 
    preferences.end();
}
void setPHASE_B_Up_Direction_Info(bool state){
    preferences.begin("pr2_up", false);
    preferences.putBool("pr2_up", state); 
    preferences.end();
}
void setPHASE_C_Up_Direction_Info(bool state){
    preferences.begin("pr3_up", false);
    preferences.putBool("pr3_up", state); 
    preferences.end();
}
void setPHASE_Yaw_Direction_Info(bool state){
    preferences.begin("phase_yaw", false);
    preferences.putBool("phase_yaw", state); 
    preferences.end();
}
/***/
void setSENSE_A_Up_Direction_Info(bool state){
    preferences.begin("sense1_up", false);
    preferences.putBool("sense1_up", state); 
    preferences.end();
}
void setSENSE_B_Up_Direction_Info(bool state){
    preferences.begin("sense2_up", false);
    preferences.putBool("sense2_up", state); 
    preferences.end();
}
void setSENSE_C_Up_Direction_Info(bool state){
    preferences.begin("sense3_up", false);
    preferences.putBool("sense3_up", state); 
    preferences.end();
}
void setSENSE_Yaw_Direction_Info(bool state){
    preferences.begin("sense_yaw", false);
    preferences.putBool("sense_yaw", state); 
    preferences.end();
}

///
void setPower_Mode(String mode){
    preferences.begin("power_ops", false);
    preferences.putString("power_ops", mode); 
    preferences.end();
}

void setMode_Info(String mode){
    preferences.begin("mode_ops", false);
    preferences.putString("mode_ops", mode); 
    preferences.end();
}

void setAudio_Enable(bool en){
    preferences.begin("audio_en", false);
    preferences.putBool("audio_en", en); 
    preferences.end();
}

void setVibr_Enable(bool en){
    preferences.begin("vibr_en", false);
    preferences.putBool("vibr_en", en); 
    preferences.end();
}

void setHT_Enable(bool en){
    preferences.begin("HT_en", false);
    preferences.putBool("HT_en", en); 
    preferences.end();
}

void setPitchYaw_Enable(bool en){
    preferences.begin("pitchyaw_en", false);
    preferences.putBool("pitchyaw_en", en); 
    preferences.end();
}

void setWifi_Enable(bool en){
    preferences.begin("wifiswitch_en", false);
    preferences.putBool("wifiswitch_en", en); 
    preferences.end();
}

void setBle_Enable(bool en){
    preferences.begin("bleswitch_en", false);
    preferences.putBool("bleswitch_en", en); 
    preferences.end();
}

void setPowerYaw(int val){    
    preferences.begin("btnpoweryaw_en", false);
    preferences.putInt("btnpoweryaw_en", val); 
    preferences.end();
}

void setPowerHt(int val){    
    preferences.begin("btnpowerht_en", false);
    preferences.putInt("btnpowerht_en", val); 
    preferences.end();
}

void setPowerHud(int val){    
    preferences.begin("btnpowerhud_en", false);
    preferences.putInt("btnpowerhud_en", val); 
    preferences.end();
}

void saveVoltage(int volts){
    preferences.begin("voltage", false);
    preferences.putInt("voltage", volts); 
    preferences.end();
}

//
void setA_Buffer_Max_Index(int val){
    preferences.begin("indexAmax", false);
    preferences.putInt("indexAmax", val); 
    preferences.end();
}
void setB_Buffer_Max_Index(int val){
    preferences.begin("indexBmax", false);
    preferences.putInt("indexBmax", val); 
    preferences.end();
}
void setC_Buffer_Max_Index(int val){
    preferences.begin("indexCmax", false);
    preferences.putInt("indexCmax", val); 
    preferences.end();
}

//
void setYawPr_Zero(float val){    
    preferences.begin("def_0_pr", false);
    preferences.putFloat("def_0_pr", val); 
    preferences.end();
}