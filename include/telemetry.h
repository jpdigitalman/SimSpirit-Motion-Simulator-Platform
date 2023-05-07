int8_t Read_AnyController(int8_t game){
    if(checkHTConnection() == false){
      connectionState = connectionState != GameTelemetry ? -1: connectionState; 
      if(wifiConnected == false){
        if(wifiSetup_Started == false){
          enableWifi(stationMode);  
          wifiSetup_Started = true;
          calib_yaw = 2;
          connectionState = 1;
        }        
      }
      else{
        if(udp_Telemetry == false){
          UDP_Start_Telmetry();
          connectionState = 2;
          doCalibrate(); //this will perform PR calibration when UDP is enabled.
        }
        else{
          readGame_Telemetry(game);
          connectionState = GameTelemetry;
        }        
      }
    }
    else{
      readHTData();
      connectionState = HT_Data;  
    }
    return connectionState;
}