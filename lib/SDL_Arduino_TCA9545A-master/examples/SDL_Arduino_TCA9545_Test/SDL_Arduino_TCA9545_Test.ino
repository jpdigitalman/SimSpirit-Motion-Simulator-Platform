//
//   SDL_Arduino_TCA9545 Library Test Code
//   SDL_Arduino_TCA9545.cpp Arduino code - runs in continuous mode
//   Version 1.1
//   SwitchDoc Labs   April 10, 2015
//
//
// This was designed for the SwitchDoc Labs I2C Mux Breakout Board containing the TCA9545
//



#include <Wire.h>
#include <SDL_Arduino_TCA9545.h>

SDL_Arduino_TCA9545 TCA9545;


// I2C Scanner
// --------------------------------------
// i2c_scanner
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//

void  scan_i2c_devices()
{
  byte error, address;
  int nDevices;

  Wire.begin();
  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

 
}

void setup(void) 
{
    
  Serial.begin(9600);
  Wire.begin();
  
  TCA9545.TCA9545SetConfig();
  Serial.println("------------------------------");
  Serial.println("------------------------------");
  Serial.println("SDA_Arduino_TCA9545_Test");
  
  Serial.println("Reading all four I2C Buses");
  Serial.println("------------------------------");
  Serial.println("------------------------------");
  Serial.println();

}

void loop(void) 
{
  
  Serial.println("------------------------------");
    
  uint8_t config;
  Serial.println("------------------------------");
  // Bus 0
  TCA9545.write_control_register(TCA9545_CONFIG_BUS0);

  TCA9545.read_control_register(&config);
  Serial.print("Bus 0 Control Register:");
  Serial.println(config & 0x0F, HEX);
  
  scan_i2c_devices();
  
  
  delay(2000);
  
    Serial.println("------------------------------");
  // Bus 1
  TCA9545.write_control_register(TCA9545_CONFIG_BUS1);

  TCA9545.read_control_register(&config);
  Serial.print("Bus 1 Control Register:");
  Serial.println(config & 0x0F , HEX);
  
  scan_i2c_devices();
  
  
  delay(2000);
  
    Serial.println("------------------------------");
  // Bus 2
  TCA9545.write_control_register(TCA9545_CONFIG_BUS2);
 
  TCA9545.read_control_register(&config);
  Serial.print("Bus 2 Control Register:");
  Serial.println(config & 0x0F, HEX);
  
  scan_i2c_devices();
  
  
  delay(2000);
  
    Serial.println("------------------------------");
  // Bus 3
  TCA9545.write_control_register(TCA9545_CONFIG_BUS3);

  TCA9545.read_control_register(&config);
  Serial.print("Bus 3 Control Register:");
  Serial.println(config & 0x0F, HEX);
  
  scan_i2c_devices();
  
  
  delay(2000);
}
