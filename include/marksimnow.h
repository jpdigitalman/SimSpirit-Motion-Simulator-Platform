#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

//int cmdBle, cmdBle_old = 0;
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char info[32];
    float yaw;
    float pitch;
    float roll;
    int cmd;
} struct_message;

// Create a struct_message
struct_message rxData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&rxData, incomingData, sizeof(rxData));

  /*
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(rxData.info);
  Serial.print("Yaw: ");
  Serial.println(rxData.yaw);
  Serial.print("Pitch: ");
  Serial.println(rxData.pitch);
  Serial.print("Roll: ");
  Serial.println(rxData.roll);
  Serial.print("Cmd: ");
  Serial.println(rxData.cmd);
  Serial.println();
  */

  rxConnected = true;
  
}

float equalise360_old(float diff){
  int left_part, right_part;
  char buffer[6];
  sprintf(buffer, "%lf", diff);
  sscanf(buffer, "%d.%d", &left_part, &right_part);
  float subt = left_part - diff;
  int target = ((int)(diff + 360) % 360);
  float movement = target + subt;
  return movement;
}

float equalise360(float diff){  
  float movement = (float)(((int)(diff*100)+36000) % 36000)/100.00f;  
  printf("eq360: %f\n", movement);
  return movement;
}

void calibrateYaw(){
    beepTimes(2, 100);  
    doYaw();    
    PRINTLINE("We are now connected to a network.");        
    htyawdegree_init = equalise360(calib360 - rxData.yaw);    
    PRINTLINE("Yaw Calibrated. HT Yaw Degree init Difference btw ht and enc: " + String(htyawdegree_init));    
}

void setInitZero(float val){
  if(setupMode){    
    defaultPRzero = val; //calib360; //0?
    //save defaultPRzero            
    setYawPr_Zero(defaultPRzero);
    setupMode = false;
  }
}

float readDefaultZero(){
  JSONVar configObj;
  float zero_default = getDefaultZero_Yaw_Pr(configObj); 
  Serial.println("Reading from memory Yaw_Pr_Zero: " + String(zero_default));

  if(isnan(zero_default)){
    Serial.println("Failed reading default 0 from NVS. Using Calib360 as Initial Position....");
    doYaw(); 
    zero_default = defaultPRzero;  //calib360     
    Serial.println("Calib360: " + String(calib360));
    setInitZero(zero_default);
  }

  return zero_default;
}

void calibratePR(){
    startReturnToZero = false;
    
    while (!startReturnToZero)
    {
      Serial.println("moving to zero");
      htyawdegree = defaultPRzero;
      htyawdegree_init = equalise360(defaultPRzero-rxData.yaw);
      doYaw(); 
      trackToYaw();

      //doBTN(); 
    }    
    pr_init = equalise360(0.00-defaultPRzero); //new
    beepTimes(2, 100);  
    PRINTLINE("Zero Position OK");
}

/// @brief //always re-calibrate at HT off. this stops unnecessary movement 
// also re-initialise initial position for Game Telemetry or Game-Controller inputs
void doCalibrate(){    
    calibrateYaw();        
    calibratePR();
    calib_yaw = 2;
    pr_enable = true;
    cmdBle_old = cmdBle;   
}


void readHTData(){

    //yaw
    htyawdegree = equalise360(htyawdegree_init + rxData.yaw);
    if(htyawdegree != htyawdegree_old){
        htyawdegree_old = htyawdegree;
        PRINTLINE("HT Yaw Degree: " + String(htyawdegree));
    }  
      
    //pitch    
    htpitchdegree = rxData.pitch;
    if(htpitchdegree != htpitchgree_old){
        htpitchgree_old = htpitchdegree;
        PRINTLINE("HT Pitch Degree: " + String(htpitchdegree));
    }

    //roll
    htrolldegree = rxData.roll;
    if(htrolldegree != htrolldegree_old){
        htrolldegree_old = htrolldegree;
        PRINTLINE("HT Roll Degree: " + String(htrolldegree));
    } 
    //cmd if cmdBle == 0 then allow HT
    cmdBle = rxData.cmd;
    if(cmdBle != cmdBle_old){
        cmdBle_old = cmdBle;
        Serial.println("HT Cmd: " + String(cmdBle));
    }
}

bool checkHTConnection(){
    if(rxConnected){
      Serial.print("READING HEADTRACKER TOOK "); Serial.print(millis()-timestamp_ht); Serial.println(" ms");
      rxConnected = false;         
      timestamp_ht = millis(); 
      HTconnected = true; 
      disconnectTimer = 0;     

      if(millis() - lastFlashTime > intervalFlash){
        if (ledVal==HIGH) {
            enableLedA(1);
            enableLedB(1);
            ledVal = LOW;
        }else{
            enableLedA(0);
            enableLedB(0);
            ledVal = HIGH;
        }
        lastFlashTime = millis();
      }        
    }
    disconnectTimer++;
    if(millis() - timestamp_ht > intervalHTRead){
        Serial.println("HT disconnected");
        HTconnected = false;
        if(udp_Telemetry == false){
          calib_yaw = -1; 
        }
        

        if(wifiSetup_Started == false){
          
        }
        else{
          Serial.println("Interval missed: " +String(millis() - timestamp_ht));
        }    
    }
    if(HTconnected != HTconnected_old){
        if(HTconnected){
            //UDP_Stop_Stop();
            //disconnectWifi();
            //
            delay(20);
            calibrateYaw();
        }
        else{
            //doCalibrate(); //this could change PR calibration if HTSwitch off withoutwarning
            beepTimes(6, 40);  
            enableLedA(0);
            enableLedB(0);
            calib_yaw = 2;
            Serial.println("State of calib: " + String(calib_yaw));
        }
        HTconnected_old = HTconnected;
    }

  return HTconnected;
}
 
 void doMarkSim_UDP(){
      if(!setupMode){
          Simulate();
      }
 }

void doMarkSim_HT(){

      Serial.println("cmd: " + String(cmdBle));

      timestamp_runsim = millis();

      if(cmdBle == 1){
        //left yaw normal speed
        calib_yaw = 0;
        int speed = map(25, 0, 100, 0, yaw_max_frequency);
        turn_MotorLeft(0, speed);
        manualTurn = true;
      }
      else if(cmdBle == 2) {
        calib_yaw = 0;
        //right yaw normal speed
        int speed = map(25, 0, 100, 0, yaw_max_frequency);
        turn_MotorRight(0, speed);
        manualTurn = true;
      }
      else if(cmdBle == 3){
        if(cmdBle_old == 3){
            calib_yaw = 0;
        }
        if(calib_yaw == 0){
            calibrateYaw();
            calib_yaw = 2;
            pr_enable = false;
            cmdBle_old = cmdBle;
        } 
      }
      else if(cmdBle == 117){  //CALIBRATE YAW, CALIBRATE AND enable PR
          doYaw();
          setInitZero(calib360);
          doCalibrate();                 
      }
      else if(cmdBle == 66 || cmdBle == 77){ //pair btn singl click, double click
        calib_yaw = 0;
        
      }
      else if(cmdBle == 33){ //pair btn triple click

      }
      else if(cmdBle == 88){
        //mode switch cockpit / free mode
        //start angle**middle angle
        
      }
      else if(cmdBle == 44){ //power btn Tripple click

      }
      else if(cmdBle == 11){ //press and hold for high speed turn left yaw
        calib_yaw = 0;
        int speed = map(85, 0, 100, 0, yaw_max_frequency);
        turn_MotorLeft(0, speed);
        manualTurn = true;
      }
      else if(cmdBle == 22){ //press and hold for high speed turn right yaw
        calib_yaw = 0;
        int speed = map(85, 0, 100, 0, yaw_max_frequency);
        turn_MotorRight(0, speed);
        manualTurn = true;
      }
      else if(cmdBle == 0){
        if(manualTurn){
          stopMotor(0);
          manualTurn = false;
        }
        calib_pr = false; 
        if(!setupMode){
          if(HTconnected){
            Simulate();
          }
          else{
            stopMotor(0);
          }           
        }
      }
      else if (cmdBle == -1){
        calib_pr = false;
        stopMotor(0);
      }
      else{
        stopMotor(0);
      }

      if(cmdBle != cmdBle_old){
        if(cmdBle_old == -1){
          //autoCalibrate();          
        }
      }
      //cmdBle_old = cmdBle;

      PRINTLINE();
      PRINT("AUTO-TRACKING TOOK "); PRINT(millis()-timestamp_runsim); PRINTLINE(" ms");
      PRINTLINE();
}


void setupRxNow() {
  
  Serial.println();
  Serial.print("MarkSim MAC Address:  ");
  Serial.println(WiFi.macAddress());
  Serial.println();
  //
  //uint8_t defaultMACAddress[] = {0x4C, 0xA4, 0x79, 0xE0, 0x23, 0x77};//-----
  //esp_wifi_set_mac(WIFI_IF_STA, &defaultMACAddress[0]);
  
  Serial.print("[NEW] ESP32 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //delay(1500);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing MarkSim Rx-NOW");
    return;
  }
  
  Serial.println("MarkSim Rx-NOW InitSuccess");  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
  Serial.println("MarkSim ready to Receive HT data");
  Serial.println("______________________________________");
  Serial.println("______________________________________");
  Serial.println();
}

