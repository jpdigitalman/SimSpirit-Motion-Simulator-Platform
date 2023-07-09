//#include <Preferences.h>
#include <webpage.h>

bool ledState = 0;
const int ledPin = 2;

/*
*Intelligent Json builder to WebApplication.
*Displays only updated values to the WebApp
*/
void displayUpdatedSensors(){
  
}

void reportValues( bool serialCMD){
  
  
  //sensor data
  /*
  getYawDegrees(configObj);
  getPitchYaw_PhaseA(configObj);
  getPitchYaw_PhaseB(configObj);
  getPitchYaw_PhaseC(configObj);
  getHT_Yaw_Degrees(configObj);
  getHT_Pitch_Degrees(configObj);
  getHT_Roll_Degrees(configObj);
  */

}

//char input[] = "";
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  
}

void initWebSocket() {
  
}


void initWebPage(){
    // Route for root / main page
    

}

void initOTA(){
    // Start ElegantOTA
    //AsyncElegantOTA.begin(&server);
    //AsyncElegantOTA.begin(&server, "user", "pass");
}

void exeCommand(const char *motor, bool direction){
    
}

/* Message callback of WebSerial */
void recvMsg(uint8_t *data, size_t len){
  
}

/**/
void initSerialWeb(){
  //WebSerial is accessible at "<IP Address>/webserial" in browser
  WebSerial.begin(&server);
  /* Attach Message Callback */
  WebSerial.msgCallback(recvMsg);
}

void startServer(){
    // Start server
    server.begin();
}

bool enableWifi(bool mode){
  // Load values saved in SPIFFS
  //loadCustomCredentials();
  loadDefaultCredentials(1);
  
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println();
  
  bool stamodex = mode; 
  if(initWifi(1)){
    //initWebSocket();
    //initWebPage();  
    //initOTA();
    //initSerialWeb();
    //startServer();
    
    return true;
  }
  else{
    if(stamodex == false){
      initWifiManager(false);
      initWebSocket();
      initWebPage();  
      //initOTA();
      //initSerialWeb();
    }
    else{
      initWifiManager(true);
    }
    
    startServer();
    if(stamodex == true){
      return false;
    }
    else{
      return true;
    }
    
  }  
}
