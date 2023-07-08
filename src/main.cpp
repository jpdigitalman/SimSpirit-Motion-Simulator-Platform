#include <Arduino.h>

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include <AsyncElegantOTA.h>

#include <Wire.h>
#include "PCF8574.h" 
#include <MT6701_I2C.h>
#include "SDL_Arduino_TCA9545.h"
#include <Arduino_JSON.h>

#include <defaultSettings.h>
#include <pindefines.h>
#include <Preferences.h>
#include <debug.h>
#include <network.h>

#include <WebSerial.h>

#include <simspiritbase.h>
#include <FixedConfig.h>
#include <SaveConfig.h>

#include <pulsefast.h>
#include <stepPulse.h>

#include <simMagic6.h>
#include <simulator__Yaw.h>
#include <simulator_phaseA.h>
#include <simulator_phaseB.h>
#include <simulator_phaseC.h>
#include <simulator_Run.h>

#include <powerDefaults.h>
#include <web.h>
#include <udpstart.h>
#include <udp_assetocorsa.h>
#include <game_asseto_corsa.h>
#include <game_projectcars.h>
#include <udp_epic_rollercoaster.h>
#include <game_f122_2.h>
#include <simspiritnow.h>
#include <BTN.h>
#include <telemetry.h>

void setup() {
  Serial.begin(115200);
  delay(800);
  
  getChipID();
  initSPIFFS();

  setupRxNow();

  pulse_setup();
  loadSine();
  initHD();

  setDirectionAntiClockwise(encoder_yaw_channel);//setDirectionClockwise(encoder_yaw_channel);
  defaultPRzero = readDefaultZero();//?
  //setSensorZeroDegrees(encoder_yaw_channel, defaultPRzero);
  
  PRINTLINE("Sim Magic Ready");   
  setupBTN();
}

int8_t cxn, cxn_old = 0;

//(udp port 20777)
int8_t game = epic_rollercoasterDirectUDP;//lfs; //f122; //assettocorsa //projectcars //epic_rollercoasterDashboardUDP //epic_rollercoasterDirectUDP //allgames //

void loop() {

    doYaw();
    pr1_do();
    pr2_do();
    pr3_do();
    
    cxn = Read_AnyController(game);
    Serial.println("Connection State Code: " +String(cxn));
    if(cxn!=cxn_old){
      
      cxn_old = cxn;
    }
    
    if(cxn==HT_Data){      
      doMarkSim_HT();       
    }
    else if(cxn==GameTelemetry){
      doMarkSim_UDP();
    }

    //esp32 motion sim.

    doBTN();

    displayUpdatedSensors();
    ws.cleanupClients(); 
}

//g813pcq9