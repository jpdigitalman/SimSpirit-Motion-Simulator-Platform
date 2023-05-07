
// buffer for receiving data
char packetBuffer[20000]; //buffer to hold incoming packet,

void UDP_Start_Telmetry() {
  // Configure UDP settings
  udp.begin(F1_UDP_PORT);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), F1_UDP_PORT);
  udp_Telemetry = true;  
}

void UDP_Stop(){
  udp.stop();
  udp_Telemetry = false;
  Serial.println("UDP Stopped");
}