//#include <Preferences.h>
#include <webpage.h>

bool ledState = 0;
const int ledPin = 2;

String message = "";

void notifyClients() {
  ws.textAll(message);
}
void updateClient(JSONVar configObj){  
  if(configObj.keys().length() > 0){
    String jsonString = JSON.stringify(configObj);
    PRINTLINE("Keys");
    PRINTLINE("sending: " + jsonString);      
    message = jsonString;
    notifyClients();    
  }
}

/*
*Intelligent Json builder to WebApplication.
*Displays only updated values to the WebApp
*/
void displayUpdatedSensors(){
  JSONVar configObj;

  JSONVar ObjVal;
  getYawDegrees(ObjVal);
  String stringVal = JSON.stringify(ObjVal);
  if(stringVal.compareTo(old_stringVal) != 0){
    old_stringVal = stringVal;
    getYawDegrees(configObj);
  }
  else{
    configObj["YawDegrees"] = undefined;
  }

  JSONVar ObjVal1;
  getPitchYaw_PhaseA(ObjVal1);
  stringVal = JSON.stringify(ObjVal1);
  if(stringVal.compareTo(old_stringValA) != 0){
    old_stringValA = stringVal;
    getPitchYaw_PhaseA(configObj);
  }
  else{
    configObj["PitchYaw_PhaseA"] = undefined;
  }
  
  JSONVar ObjVal2;
  getPitchYaw_PhaseB(ObjVal2);
  stringVal = JSON.stringify(ObjVal2);
  if(stringVal.compareTo(old_stringValB) != 0){
    old_stringValB = stringVal;
    getPitchYaw_PhaseB(configObj);
  }
  else{
    configObj["PitchYaw_PhaseB"] = undefined;
  }
  
  JSONVar ObjVal3;
  getPitchYaw_PhaseC(ObjVal3);
  stringVal = JSON.stringify(ObjVal3);
  if(stringVal.compareTo(old_stringValC) != 0){
    old_stringValC = stringVal;
    getPitchYaw_PhaseC(configObj);
  }
  else{
    configObj["PitchYaw_PhaseC"] = undefined;
  }
  //
  JSONVar ObjVal4;
  getHT_Roll_Degrees(ObjVal4);
  stringVal = JSON.stringify(ObjVal4);
  if(stringVal.compareTo(old_stringValRoll) != 0){
    old_stringValRoll = stringVal;
    getHT_Roll_Degrees(configObj);
  }
  else{
    configObj["HT_Roll_Degrees"] = undefined;
  }

  JSONVar ObjVal5;
  getHT_Pitch_Degrees(ObjVal5);
  stringVal = JSON.stringify(ObjVal5);
  if(stringVal.compareTo(old_stringValPitch) != 0){
    old_stringValPitch = stringVal;
    getHT_Pitch_Degrees(configObj);
  }
  else{
    configObj["HT_Pitch_Degrees"] = undefined;
  }

  JSONVar ObjVal6;
  getHT_Yaw_Degrees(ObjVal6);
  stringVal = JSON.stringify(ObjVal6);
  if(stringVal.compareTo(old_stringValYaw) != 0){
    old_stringValYaw = stringVal;
    getHT_Yaw_Degrees(configObj);
  }
  else{
    configObj["HT_Yaw_Degrees"] = undefined;
  }

  // 
  if (millis() - lastSendTime > interval) { 

    if(yaw360 != oldyaw360){
      PRINTLINE("Base360: " + String(yaw360));
      oldyaw360 = yaw360;
    }

    if(calib360 != oldcalib360){
      PRINTLINE("Calib360: " + String(calib360));
      oldcalib360 = calib360;
    }

    if(phase_a_ct != oldphase_a_ct){
      PRINTLINE("Phase A Position: " + String(phase_a_ct));
      oldphase_a_ct = phase_a_ct;
    }
    if(phase_b_ct != oldphase_b_ct){
      PRINTLINE("Phase B Position: " + String(phase_b_ct));
      oldphase_b_ct = phase_b_ct;
    }
    if(phase_c_ct != oldphase_c_ct){
      PRINTLINE("Phase C Position: " + String(phase_c_ct));
      oldphase_c_ct = phase_c_ct;
    }

    if (ledVal==HIGH) {
      enableLedA(1);
      enableLedB(1);
      ledVal = LOW;
    }else{
      enableLedA(0);
      enableLedB(0);
      ledVal = HIGH;
    }
    //LED_FLASH_A();    
    //updateClient(configObj);
    //lastSendTime = millis();
    
    lastSendTime = millis();

    if(ccw = true){
      testangle--;
    }
    else{
      testangle++;
    }
    
    if(testangle == 360 || testangle < 0){
      testangle = 0;
      ccw = true;
    }
    else{
      ccw = false;
    }

    //PRINTLINE("waiting: " + String(waiting));
    if(waiting == 25){
      //global_targetangle = 55;
      //global_steptoangle_yaw_flag = true;
      waiting = 0;
    }
    
    
    
  }
}

void reportValues( bool serialCMD){
  JSONVar configObj;
  //feature actions
  getPower_Info(configObj);
  getWifi_Info(configObj);
  getMode_Info(configObj);
  getHTCalibrate_Info(configObj);
  getPhaseCalibrate_Info(configObj); //phase calibration info
  getAudioEnable_Info(configObj);
  getVibrEnable_Info(configObj);
  getHTEnable_Info(configObj);
  getPitchYaw_Info(configObj);
  getWifiSwitch_Info(configObj);
  getBleSwitch_Info(configObj);
  
  //sensor data
  getYawDegrees(configObj);
  getPitchYaw_PhaseA(configObj);
  getPitchYaw_PhaseB(configObj);
  getPitchYaw_PhaseC(configObj);
  getHT_Yaw_Degrees(configObj);
  getHT_Pitch_Degrees(configObj);
  getHT_Roll_Degrees(configObj);

  //power setting
  getBtnPowerYaw_Info(configObj);
  getBtnPowerHt_Info(configObj);
  getBtnPowerHud_Info(configObj);   

  if(serialCMD){
    String jsonString = JSON.stringify(configObj);
    PRINTLINE("sending: " + jsonString);     
  }
  else{
    //send to clients
    updateClient(configObj);
  }       
}

//char input[] = "";
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  PRINT("WebSocket running on core ");
  PRINTLINE(xPortGetCoreID());
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    message = (char*)data;
    if (strcmp((char*)data, "toggle") == 0) {
      //ledState = !ledState;
      //notifyClients();
    }
    else if (strcmp((char*)data, "getValues") == 0) {
      reportValues(false);
    }
    else{
      decodeCommand(message);
    }        
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      PRINTF("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      PRINTF("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var){
  //PRINTLINE("processor: " + var);
  if(var == "STATE"){
    if (ledState){      
      return "ON";
    }
    else{      
      return "OFF";
    }
  }
  return String();
}

void initWebPage(){
    // Route for root / main page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", WEBPAGE_HTML, WEBPAGE_HTML_SIZE);
        response->addHeader("Content-Encoding","gzip");
        request->send(response);        
        //request->send(SPIFFS, "/Index.html");
    });

    // Wifi Manager URL
    server.on("/wifimanager.html", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/wifimanager.html", "text/html");
    });

    server.serveStatic("/", SPIFFS, "/");

    WifiSetup_Submit();

}

void initOTA(){
    // Start ElegantOTA
    //AsyncElegantOTA.begin(&server);
    AsyncElegantOTA.begin(&server, "user", "pass");
}

void exeCommand(const char *motor, bool direction){
  String dir;
  if(direction == true){
    dir = "right";
  }
  else{
    dir = "left";
  }

  global_direction = direction;
  if(strcmp(motor, "yaw") == 0){
    global_motor = 0;
    global_steptoangle_yaw_flag = true;             
    WebSerial.println("Yaw turning " + dir + " by steps");
  }
  else if(strcmp(motor, "pr1") == 0){
    global_motor = 1;
    global_steptoangle_yaw_flag = true;             
    WebSerial.println("Pr1 turning " + dir + " by steps");
  }
  else if(strcmp(motor, "pr2") == 0){
    global_motor = 2;
    global_steptoangle_yaw_flag = true;             
    WebSerial.println("Pr2 turning " + dir + " by steps");
  }
  else if(strcmp(motor, "pr3") == 0){
    global_motor = 3;
    global_steptoangle_yaw_flag = true;             
    WebSerial.println("Pr3 turning " + dir + " by steps");
  }
  else{
    global_steptoangle_yaw_flag = false;             
    WebSerial.println("Selected Motor " + String(motor) + " Not found");
  }
  
}

/* Message callback of WebSerial */
void recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  
  WebSerial.println(d);

  int yawCmd, pitchCmd, rollCmd = 0;
  char opcode[7];
  String cmd;
    
  char local_direction[7];
  char local_motor[7];

  if (sscanf(d.c_str(), "%d,%d,%d", &yawCmd, &pitchCmd, &rollCmd) == 3) {  //30, 15, 12 (yaw(360), pitch(-+90), roll(-+90))
      WebSerial.println("Executing PR position Simulation..");
      //simMagic(yawCmd, pitchCmd, rollCmd, phaseA_target, phaseB_target, phaseC_target);
  }
  else if (sscanf(d.c_str(), "%s %d, %d, %d", &opcode, &yawCmd, &pitchCmd, &rollCmd) == 4) {  //marksim 30, 15, 12 (yaw, pitch, roll)
      WebSerial.println("Executing MarkSim...");
      if(strcmp(opcode, "marksim") == 0){
        if(yawCmd < 360){
          if(pitchCmd <= 90){
            if(rollCmd <= 90){
              //Simulate(yawCmd, pitchCmd, rollCmd);
            }
            else{
              WebSerial.println("Roll must be less than 90 degrees");
            }
          }
          else{
            WebSerial.println("Pitch must be less than 90 degrees");
          }
        }
        else{
          WebSerial.println("Yaw must be less than 360 degrees");
        }        
      }
      else{
        WebSerial.println("Invalid command");
      }
  }
  else if(sscanf(d.c_str(), "%s %d %s %s", &opcode, &global_targetangle, &local_direction, &local_motor) == 4) {
      Serial.println(String(opcode));
      Serial.println(String(global_targetangle));
      if(strcmp(opcode, "stepby") == 0){            //stepby 7500 right yaw/pr1/pr2   stepby 3358 right         
        if(strcmp(local_direction, "left") == 0){   //stepby 300000 right yaw
          exeCommand(local_motor, left);
        }
        else{
          exeCommand(local_motor, right);
        }
      }
      else if(strcmp(opcode, "goto") == 0){             //goto 360 right        
        if(strcmp(local_direction, "left") == 0){
          global_direction = left;
          WebSerial.println("turning left by angle");
        }
        else{
          global_direction = right;
          WebSerial.println("turning right by angle");
        }
        global_jumptoangle_yaw_flag = true;
      }
  }
  else if(sscanf(d.c_str(), "%s %d %s", &opcode, &global_targetangle, &local_motor) == 3){ //trackto 30 yaw/pr1/pr2 (auto track to angle)  //limit PR to 90 degrees
      Serial.println(String(opcode));
      Serial.println(String(global_targetangle));
      Serial.println(String(local_motor));                                        //trackto 30 pr1
      if(strcmp(opcode, "trackto") == 0){
        if(strcmp(local_motor, "yaw") == 0){
          global_autotracker_flag =true;
          WebSerial.println("auto tracking yaw... ");
        }
        else if(strcmp(local_motor, "pr1") == 0){
          phaseA_target = global_targetangle;
          pr1_autotracker_flag = true;
          WebSerial.println("auto tracking pr1... ");
        }
        else if(strcmp(local_motor, "pr2") == 0){
          phaseB_target = global_targetangle;
          pr2_autotracker_flag = true;
          WebSerial.println("auto tracking pr2... ");
        }
        else if(strcmp(local_motor, "pr3") == 0){
          phaseC_target = global_targetangle;
          pr3_autotracker_flag = true;
          WebSerial.println("auto tracking pr3... ");
        }
        else{
          WebSerial.println("Invalid Selection");
        }        
      }
  }
  else{

  }
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
  
  ip = readFile(SPIFFS, ipPath);
  gateway = readFile (SPIFFS, gatewayPath);
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println();
  //Serial.println(ip);
  //Serial.println(gateway);

  //loadCredentials(wifiCredentials);
  //saveCredentials(wifiCredentials); 
  bool stamodex = mode; 
  if(initWifi(stamodex)){
    initWebSocket();
    initWebPage();  
    //initOTA();
    //initSerialWeb();
    startServer();
    
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
