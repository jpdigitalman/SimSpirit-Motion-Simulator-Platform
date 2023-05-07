void setPowerYaw(String valuestring){
  PRINTLINE("Power Yaw: " + valuestring);
  int valint = valuestring.toInt();
  setPowerYaw(valint);
}

void powerYawSettings(String keystring, String valuestring){
  if(keystring.compareTo("btnPowerYaw") == 0){
    setPowerYaw(valuestring);
    JSONVar configObj;
    getBtnPowerYaw_Info(configObj);   
    updateClient(configObj);
  }
}

void setPowerHt(String valuestring){
  PRINTLINE("Power Ht: " + valuestring);
  int valint = valuestring.toInt();
  setPowerHt(valint);
}

void powerHtSettings(String keystring, String valuestring){
  if(keystring.compareTo("btnPowerHt") == 0){
    setPowerHt(valuestring);
    JSONVar configObj;
    getBtnPowerHt_Info(configObj);   
    updateClient(configObj);
  }
}

void setPowerHUD(String valuestring){
  PRINTLINE("Power HUD: " + valuestring);
  int valint = valuestring.toInt();
  setPowerHud(valint);
}

void powerHudSettings(String keystring, String valuestring){
  if(keystring.compareTo("btnPowerHud") == 0){
    setPowerHUD(valuestring);
    JSONVar configObj;
    getBtnPowerHud_Info(configObj);   
    updateClient(configObj);
  }
}