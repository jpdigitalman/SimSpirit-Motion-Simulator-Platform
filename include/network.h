#include <WiFi.h>
#include <ESPmDNS.h>

#include <WiFiUdp.h>

// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
const char* PARAM_INPUT_3 = "ip";
const char* PARAM_INPUT_4 = "gateway";

//Variables to save values from HTML form
String ssid;
String pass; //98j2hin6mr3ioujpm
String ip;
String gateway;

// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
const char* ipPath = "/ip.txt";
const char* gatewayPath = "/gateway.txt";

void initSPIFFS(){
    if(!SPIFFS.begin(true)){
      PRINTLINE("An Error has occurred while mounting SPIFFS");
      return;      
    }
}

// Read File from SPIFFS
String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);
    
  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
    return String();
  }
  
  String fileContent;
  while(file.available()){
    fileContent = file.readStringUntil('\n');
    break;     
  }
  return fileContent;
}

// Write file to SPIFFS
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- frite failed");
  }
}

void loadCustomCredentials(){
  ssid = readFile(SPIFFS, ssidPath);
  pass = readFile(SPIFFS, passPath);
}
void loadDefaultCredentials(int vv){
  if(vv == 1){
    ssid = "";//"";
    pass = "";//""; 
  }
  else{
    ssid = "";//"SmartRouter-EA04";//"";
    pass = "";//"";//"; 
  }
}
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Set your Static IP address
IPAddress local_IP(172, 20, 10, 8);
// Set your Gateway IP address
IPAddress local_Gateway(172, 20, 1, 1);
IPAddress subnet(255, 255, 255, 240);
//IPAddress primaryDNS(8, 8, 8, 8);   //optional
//IPAddress secondaryDNS(8, 8, 4, 4); //optional
const char* host = "SimSpirit"; //http://esp32.local

unsigned long previousMillis = 0;
const long intervalWifi = 4000;  // interval to wait for Wi-Fi connection (milliseconds)

/*
*ARDUINO_EVENT_WIFI_READY = 0,
	ARDUINO_EVENT_WIFI_SCAN_DONE,
	ARDUINO_EVENT_WIFI_STA_START,
	ARDUINO_EVENT_WIFI_STA_STOP,
	ARDUINO_EVENT_WIFI_STA_CONNECTED,
	ARDUINO_EVENT_WIFI_STA_DISCONNECTED,
	ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE,
	ARDUINO_EVENT_WIFI_STA_GOT_IP,
	ARDUINO_EVENT_WIFI_STA_GOT_IP6,
	ARDUINO_EVENT_WIFI_STA_LOST_IP,
	ARDUINO_EVENT_WIFI_AP_START,
*https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFiGeneric.h#L36-L78
*/
void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("Connected to AP successfully!");
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  wifiConnected = true;
}

void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info){
  wifiConnected = false;
  udp_Telemetry = false;
  Serial.println("Disconnected from WiFi access point");
  Serial.print("WiFi lost connection. Reason: ");
  Serial.println(info.wifi_sta_disconnected.reason);
  Serial.println("Trying to Reconnect");
  //WiFi.setHostname(hostname.c_str()); //define hostname
  WiFi.begin(ssid.c_str(), pass.c_str());
}

void disconnectWifi(){
  WiFi.disconnect(true);
  wifiSetup_Started = false;
  Serial.println("Wifi Stopped");
}

bool initWifi(bool ops){
    if(ops == false){
      return false;
    }
    if(ssid==""){
        Serial.println("Undefined SSID.");
        return false;
    }

    // delete old config
    WiFi.disconnect(true);
    delay(500);
    WiFi.onEvent(WiFiStationConnected, ARDUINO_EVENT_WIFI_STA_CONNECTED);
    WiFi.onEvent(WiFiGotIP, ARDUINO_EVENT_WIFI_STA_GOT_IP);
    WiFi.onEvent(WiFiStationDisconnected, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

    WiFi.setHostname(hostname.c_str()); //define hostname

    WiFi.mode(WIFI_STA);
    //local_IP.fromString(ip.c_str());
    //local_Gateway.fromString(gateway.c_str());

    // Configures static IP address  
    /*
    if (!WiFi.config(local_IP, local_Gateway, subnet)) {
        PRINTLINE("STA Failed to configure");
        return false;
    }
    */
    //PRINTLINE("")
    // Connect to Wi-Fi
    PRINT("Connecting to ");
    PRINTLINE(ssid);

    WiFi.begin(ssid.c_str(), pass.c_str());
    PRINTLINE("Connecting to WiFi..");
    unsigned long currentMillis = millis();
    previousMillis = currentMillis;
    while (WiFi.status() != WL_CONNECTED) {
        delay(200);        
        Serial.print(".");
        currentMillis = millis();
        if (currentMillis - previousMillis >= intervalWifi) {
          Serial.println("Failed to connect.");
          //return false;
          break;
        }
    }    
    PRINTLINE("Waiting for WiFi..");
    // Print ESP Local IP Address
    PRINTLINE(WiFi.localIP());
    // Print ESP MAC Address
    PRINTLINE("MAC address: ");
    PRINTLINE(WiFi.macAddress());

    /*use mdns for host name resolution*/

    if (!MDNS.begin(host)) { 
        PRINTLINE("Error setting up MDNS responder!");
        while (1) {
            delay(1000);
            break;
        }
    }
    else{      
      PRINTLINE("mDNS responder started");
      PRINT("http://");
      PRINT(host);
      PRINTLINE(".local");
    }
    return true;   
}

void WifiSetup_Submit(){
  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
      vTaskDelay(10);
      int params = request->params();
      for(int i=0;i<params;i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->isPost()){
          // HTTP POST ssid value
          if (p->name() == PARAM_INPUT_1) {
            ssid = p->value().c_str();
            Serial.print("SSID set to: ");
            Serial.println(ssid);
            // Write file to save value
            writeFile(SPIFFS, ssidPath, ssid.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_INPUT_2) {
            pass = p->value().c_str();
            Serial.print("Password set to: ");
            Serial.println(pass);
            // Write file to save value
            writeFile(SPIFFS, passPath, pass.c_str());
          }
          // HTTP POST ip value
          if (p->name() == PARAM_INPUT_3) {
            ip = p->value().c_str();
            Serial.print("IP Address set to: ");
            Serial.println(ip);
            // Write file to save value
            writeFile(SPIFFS, ipPath, ip.c_str());
          }
          // HTTP POST gateway value
          if (p->name() == PARAM_INPUT_4) {
            gateway = p->value().c_str();
            Serial.print("Gateway set to: ");
            Serial.println(gateway);
            // Write file to save value
            writeFile(SPIFFS, gatewayPath, gateway.c_str());
          }
          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      request->send(200, "text/html", "Done. Restart SimSpirit, connect to your router and go to IP address: " + ip + "<div id=\"countdown\"></div><br><progress value=\"0\" max=\"10\" id=\"progressBar\"></progress><script>var timeleft=10,downloadTimer=setInterval((function(){timeleft<=0?(clearInterval(downloadTimer),document.getElementById(\"countdown\").innerHTML=\"Finished\"):(document.getElementById(\"countdown\").innerHTML=timeleft+\" seconds to shutdown\",document.getElementById(\"progressBar\").value=10-timeleft),timeleft-=1}),1e3);</script>");
      yield();
      delay(3000);
      yield();
      ESP.restart();
    });
}

void initWifiManager(bool stamode){
    // Connect to Wi-Fi network with SSID and password
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
    WiFi.softAP("SimSpirit-WIFI-MANAGER", NULL);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP); 

    if(stamode == true){
      // Web Server Root URL
      server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/wifimanager.html", "text/html");
      });      
      server.serveStatic("/", SPIFFS, "/");
    }

    WifiSetup_Submit();
}