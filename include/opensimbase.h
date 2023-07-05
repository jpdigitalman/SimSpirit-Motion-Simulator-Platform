TwoWire I2Csipo = TwoWire(0);
PCF8574 SIPO1(&I2Csipo, 0x20);
PCF8574 SIPO2(&I2Csipo, 0x21);

SDL_Arduino_TCA9545 TCA9545(&I2Csipo);

MT6701I2C SensorI2C_0(&I2Csipo);
MT6701I2C SensorI2C_1(&I2Csipo);
MT6701I2C SensorI2C_2(&I2Csipo);
MT6701I2C SensorI2C_3(&I2Csipo);

uint32_t chipId = 0;

void getChipID() {
  for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }

  PRINTF("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
  PRINTF("This chip has %d cores\n", ESP.getChipCores());
  PRINT("Chip ID: "); 
  PRINTLINE(chipId);
}


bool SIPO1_Pressed = false;
bool SIPO2_Pressed = false;

void IRAM_ATTR keyPressedOnPinExpander1() {
  SIPO1_Pressed = true; 
}
void IRAM_ATTR keyPressedOnPinExpander2() {
  SIPO2_Pressed = true; 
}
void enableLedA(bool en){
  if(en){
    SIPO1.digitalWrite(P0, LOW);
  }
  else{
    SIPO1.digitalWrite(P0, HIGH);
  }
}
void enableLedB(bool en){
  if(en){
    SIPO1.digitalWrite(P1, LOW);
  }
  else{
    SIPO1.digitalWrite(P1, HIGH);
  }
}
/*Button 1 is tied to SIPO1 Interrupt*/
void initSIPO1_Interrupt(){
  pinMode(SIPO1_INTERRUPT_PIN, INPUT_PULLUP); //mcu set interrupt pin as input
  attachInterrupt(digitalPinToInterrupt(SIPO1_INTERRUPT_PIN), keyPressedOnPinExpander1, CHANGE);
}
/*All Safety Switches are tied to SIPO2 Interrupt*/
void initSIPO2_Interrupt(){
  pinMode(SIPO2_INTERRUPT_PIN, INPUT_PULLUP); //mcu set pin as input
  attachInterrupt(digitalPinToInterrupt(SIPO2_INTERRUPT_PIN), keyPressedOnPinExpander2, CHANGE);
}
void enableEncoderSwitchesAll(bool en){
  if(en){
    SIPO2.digitalWrite(P0, HIGH); //ENABLE SENSOR1
    SIPO2.digitalWrite(P1, HIGH); //ENABLE SENSOR2
    SIPO2.digitalWrite(P2, HIGH); //ENABLE SENSOR3
    SIPO2.digitalWrite(P3, HIGH); //ENABLE SENSOR4
  }
  else{
    SIPO2.digitalWrite(P0, LOW); //ENABLE SENSOR1
    SIPO2.digitalWrite(P1, LOW); //ENABLE SENSOR2
    SIPO2.digitalWrite(P2, LOW); //ENABLE SENSOR3
    SIPO2.digitalWrite(P3, LOW); //ENABLE SENSOR4
  }  
}

//SIPO2 (PCF8574) controls the ENCODER SWITCHES AND ALL SAFTEY SWITCHES
void enableSIPO2(bool en){
  if(en){
    SIPO1.digitalWrite(P4, HIGH); //reset/disable encoder sensor reader chip
  }
  else{
    SIPO1.digitalWrite(P4, LOW);
  }
}

void enableEncoderReaderI2CBus_PCA9545APW(bool en){
  if(en){
    SIPO2.digitalWrite(P4, HIGH); //enable i2c bus PCA9545APW (which i2c reads all encoders)
  }
  else{
    SIPO2.digitalWrite(P4, LOW); //reset i2c bus PCA9545APW (which i2c reads all encoders)
  }
}
/// @brief buzzer init
void initPinMode(){
  pinMode(25, OUTPUT);
  digitalWrite(25, LOW);
}

/// @brief /
/// @param en 
void buzzer(bool en){
  if(en){
    digitalWrite(25, HIGH);
  }
  else{
    digitalWrite(25, LOW);
  }
}

void beepTimes(int t, int tm){
  for(int i = 0; i < t; i++){
    buzzer(true);
    delay(tm);
    buzzer(false);
    delay(tm);
  }  
}

void audioModeEnable(bool en){
  if(en){
    SIPO1.digitalWrite(P5, HIGH);
  }
  else{
    SIPO1.digitalWrite(P5, LOW);
  }
}

/*
//shutdown ACTIVE high. Be careful not to put the ATX machine in pepertual shutdown
//if by any crazy experiment this pin is set in perpetual shutdown mode, the only recovery way is to physically 
cut wires on the PCB by removing PIN11 of U2 or removing PIN3 of U4 from the PCBA
*/
void kill(){
  Serial.println("kill");
  SIPO1.digitalWrite(P6, HIGH);
}
  
///
void SIPO1_Config(){
  // Set pinMode to OUTPUT
  SIPO1.pinMode(P0, OUTPUT); //p0 = ledA
  SIPO1.digitalWrite(P0, LOW);
  
  SIPO1.pinMode(P1, OUTPUT);//p1 ledB
  SIPO1.digitalWrite(P1, LOW);
  
  SIPO1.pinMode(P2, OUTPUT);
  SIPO1.digitalWrite(P2, LOW); //not connected

  SIPO1.pinMode(P3, INPUT_PULLUP); //button 1 input
  //PIN 13 INTERRRUPT ACTIVE LOW CONNECTED TO PIN IO4 (PIN26) OF MCU
  
  /*
  Pulling the RESET pin P4
  LOW resets the I2C-bus state machine and causes all the channels to be deselected as
  does the internal power-on reset function.
  */
  SIPO1.pinMode(P4, OUTPUT);
  SIPO1.digitalWrite(P4, LOW); //reset/disable encoder sensor reader chip
  
  SIPO1.pinMode(P5, OUTPUT);
  SIPO1.digitalWrite(5, LOW); //AUDIO MODE ENABLE HIGH

  //SIPO1.pinMode(P6, OUTPUT);
  SIPO1.digitalWrite(P6, LOW); //shutdown ACTIVE high. careful not to put the machine in pepertual shutdown
  
  SIPO1.pinMode(P7, OUTPUT); //NOT CONNECTED
  SIPO1.digitalWrite(P7, LOW);

    
  SIPO1.begin();

  
}
void SIPO2_Config(){
  // Set pinMode to OUTPUT
  SIPO2.pinMode(P0, OUTPUT);
  SIPO2.digitalWrite(P0, LOW); //yaw encoder switch on
  
  SIPO2.pinMode(P1, OUTPUT);
  SIPO2.digitalWrite(P1, LOW); //phase A encoder switch enable/disable
  
  SIPO2.pinMode(P2, OUTPUT);
  SIPO2.digitalWrite(P2, LOW); //phase B encoder switch enable/disable

  SIPO2.pinMode(P3, OUTPUT);
  SIPO2.digitalWrite(3, LOW); //phase C encoder switch enable/disable
  
  SIPO2.pinMode(P4, OUTPUT);
  SIPO2.digitalWrite(4, HIGH); //reset/enable i2c bus PCA9545APW (which i2c reads all encoders)
  
  SIPO2.pinMode(P5, INPUT_PULLUP); //safety switch 1

  SIPO2.pinMode(P6, INPUT_PULLUP); //safety switch 2

  SIPO2.pinMode(P7, INPUT_PULLUP); //safety switch 3


  SIPO2.begin();
    
}

void  scan_i2c_devices()
{
  byte error, address;
  int nDevices;
  Wire.begin(I2C_SDA, I2C_SCL);
  PRINTLINE("Scanning I2C ...");
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
      PRINT("I2C device found; at address 0x");
      if (address<16) 
        PRINT("0");
      PRINT(address,HEX);
      PRINTLINE("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      PRINT("Unknow error at address 0x");
      if (address<16) 
        PRINT("0");
      PRINTLINE(address,HEX);
    }    
  }
  if (nDevices == 0)
    PRINTLINE("No I2C devices found\n");
  else
    PRINTLINE("done\n"); 
}

void initI2C_PinExpander_PCF8574_ALL(){
  I2Csipo.begin(I2C_SDA, I2C_SCL, 3400000ul); //3.4mhz?

  //scan_i2c_devices();
  //I2Csipo.begin(I2C_SDA, I2C_SCL); //super speed
}

void configPinExpander_PCF8574_SIPO1(){  
  SIPO1_Config();  
  PRINTLINE("Done configuring PCF8574 1");
}
void configPinExpander_PCF8574_SIPO2(){  
  SIPO2_Config();
  PRINTLINE("Done configuring PCF8574 2");    
}


/// @brief /
void initPins(){
  pinMode(CON_PUL_1, OUTPUT); 
  digitalWrite(CON_PUL_1, LOW);

  pinMode(CON_PUL_2, OUTPUT); 
  digitalWrite(CON_PUL_2, LOW);

  pinMode(CON_PUL_3, OUTPUT); 
  digitalWrite(CON_PUL_3, LOW);

  pinMode(CON_PUL_4, OUTPUT); 
  digitalWrite(CON_PUL_4, LOW);

  /// 
  pinMode(CON_DIR_1, OUTPUT); 
  digitalWrite(CON_DIR_1, LOW);

  pinMode(CON_DIR_2, OUTPUT); 
  digitalWrite(CON_DIR_2, LOW);

  pinMode(CON_DIR_3, OUTPUT); 
  digitalWrite(CON_DIR_3, LOW);

  pinMode(CON_DIR_4, OUTPUT); 
  digitalWrite(CON_DIR_4, LOW);
}

/***/
void initPinOut(){
  pinMode(0, OUTPUT); //set alarm pin as output. This pin also controls one of the LEDs
  digitalWrite(0, LOW); //alarm low

  initPins();
}

/**/
void LED_GREEN_ON_BLUE_OFF(){
  SIPO1.digitalWrite(P0, HIGH);
  SIPO1.digitalWrite(P1, LOW);
}
void LED_BLUE_ON_GREEN_OFF(){
  SIPO1.digitalWrite(P0, LOW);
  SIPO1.digitalWrite(P1, HIGH);
}
void LED_BLUE_OFF_GREEN_OFF(){
  SIPO1.digitalWrite(P0, LOW);
  SIPO1.digitalWrite(P1, HIGH);
}

/**/
void LED_FLASH_A(){
  LED_GREEN_ON_BLUE_OFF();
  delay(500);
  LED_BLUE_ON_GREEN_OFF();
  delay(500);
  LED_BLUE_OFF_GREEN_OFF();
}

void GREEN_BLUE_ON(int t){
  delay(500);
  for(int i = 0; i < t; i++){
    LED_GREEN_ON_BLUE_OFF();
    LED_BLUE_ON_GREEN_OFF();
  }
  LED_BLUE_OFF_GREEN_OFF();
}

void LED_B_ON(){
  SIPO1.digitalWrite(P2, LOW); 
}
void LED_B_OFF(){
  SIPO1.digitalWrite(P2, HIGH); 
}

/***
 * 
 * 
*/
bool InitSensor_Bus(){
  byte address = 0x70;
  Wire.begin();
  Wire.beginTransmission(0x70);
  byte error = Wire.endTransmission();
  if (error == 0)
  {
    PRINTLINE("I2C Bus PCA9545A Initialised at address 0x");
    if (address<16) 
      PRINT("0");
    PRINT(address,HEX);
    PRINTLINE("  !");
    Wire.write(1 << 0);          // send byte to select bus
    Wire.endTransmission();
    return 1;
  }
  else if (error==4) 
  {
    PRINT("Unknow error at address 0x");
    PRINTLINE(address,HEX);
    return 0;
  }
  else{
    return 0;  
  }
}
bool SelectSensorChannel_Bus(int channel){
  byte address = 0x70;
  Wire.begin();
  Wire.beginTransmission(address);
  byte error = Wire.endTransmission();
  if (error == 0)
  {
    Wire.write(1 << channel);          // send byte to select bus
    Wire.endTransmission();
    return 1;
  }
  else if (error==4) 
  {
    return 0;
  }
  else{
    return 0;
  }
}
/**
 * @brief 
 * 
 */
void configSensors_PCA9545A(){
  InitSensor_Bus(); 
  
  SelectSensorChannel_Bus(0);
  SensorI2C_0.begin();
  SensorI2C_0.setClock(MT6701_I2C_CLOCK_1MHZ);
  if(!SensorI2C_0.isConnected()) {
    PRINTLINE("Датчик не обнаружен Yaw");
    delay(500);
  }
  PRINTLINE("MT6701 CONFIGURED IN TWI CHANNEL 0");
}

void initHD(){
  initPinMode();

  initI2C_PinExpander_PCF8574_ALL(); //initialise i2c communication for pcf8574 hardware

  configPinExpander_PCF8574_SIPO1(); //Safety switch interrupts and buttons
  //initSIPO1_Interrupt();
  enableSIPO2(1);
  
  configPinExpander_PCF8574_SIPO2();
  //initSIPO2_Interrupt(); //disallow interrupt on safety switch
  enableEncoderSwitchesAll(1); //all  encoder switches enableAllSensors(); 

  enableEncoderReaderI2CBus_PCA9545APW(1);
  configSensors_PCA9545A();//pin i2c bus multiplexer for READING encoders
  
  /*
  if(setAudioMode()){
    introSound();
  }
  */
  enableLedA(0);//switch ledA
  enableLedB(0); //switch off ledB

  delay(500);

  beepTimes(2, 500);

  delay(500);
  
  PRINTLINE("beep");
}

/**
 * @brief 
 * 
 */
void readSensorsDegrees(int bus, float &degreesAngle) {
  if(bus == 0){
    SelectSensorChannel_Bus(bus); 
    float yawdeg = SensorI2C_0.getDegreesAngle();
    degreesAngle = yawdeg >= 360.00 ? degreesAngle : yawdeg;
  }
  else if(bus == 1){
    SelectSensorChannel_Bus(bus); 
    float pr1deg = SensorI2C_0.getDegreesAngle();
    degreesAngle = pr1deg >= 360.00 ? degreesAngle : pr1deg;
  }
  else if(bus == 2){
    SelectSensorChannel_Bus(bus); 
    float pr2deg = SensorI2C_0.getDegreesAngle();
    degreesAngle = pr2deg >= 360.00 ? degreesAngle : pr2deg;
  }
  else if(bus == 3){
    SelectSensorChannel_Bus(bus); 
    float pr3deg = SensorI2C_0.getDegreesAngle();
    degreesAngle = pr3deg >= 360.00 ? degreesAngle : pr3deg;
  }  
}

/// @brief /
/// @param bus 
/// @param newAngle 
void getSensorZeroDegrees(int bus){
  if(bus == 0){
    SelectSensorChannel_Bus(bus);
    Serial.println("Yaw Reading Current Value...");
    word zdp;
    zdp = SensorI2C_0.getZeroDegreePositionData();
    Serial.print("Yaw Zero Degree Position (): ");
    Serial.println(zdp);
    Serial.println();
  }
  else if(bus == 1){
    SelectSensorChannel_Bus(bus);
    Serial.println("PR1 Reading Current Value...");
    word zdp;
    zdp = SensorI2C_1.getZeroDegreePositionData();
    Serial.print("PR1 Zero Degree Position (): ");
    Serial.println(zdp);
    Serial.println();
  }
  else if(bus == 2){
    SelectSensorChannel_Bus(bus); 
    Serial.println("PR2 Reading Current Value...");
    word zdp;
    zdp = SensorI2C_2.getZeroDegreePositionData();
    Serial.print("PR2 Zero Degree Position (HEX): ");
    Serial.println(zdp, HEX);
    Serial.println();
  }
  else if(bus == 3){
    SelectSensorChannel_Bus(bus);
    Serial.println("PR3 Reading Current Value...");
    word zdp;
    zdp = SensorI2C_3.getZeroDegreePositionData();
    Serial.print("PR3 Zero Degree Position (HEX): ");
    Serial.println(zdp);
    Serial.println();
  }
}

void setSensorZeroDegrees(int bus, float newAngle){  
  newAngle = 360.00-(newAngle+zero_offset);
  bool result = false;  
  if(bus == 0){
    SelectSensorChannel_Bus(bus);
    Serial.println("Yaw Reading Current Value...");
    word zdp;
    zdp = SensorI2C_0.getZeroDegreePositionData();
    Serial.print("Yaw Zero Degree Position (HEX): ");
    Serial.println(zdp, HEX);
    Serial.println();
    delay(300); // The delay is not important. so it's easier to see in the SM
    Serial.print("Yaw Changing Value... ");     
    //result = SensorI2C_0.setZeroDegreePositionDataVerify((word)((newAngle * 4096) / 360));
    word ax = map((newAngle*100), 0, 36000, 0, 4096);
    result = SensorI2C_0.setZeroDegreePositionDataVerify(ax);
    if(result){
      SensorI2C_0.saveNewValues();
      delay(700); // >600ms
      Serial.println("Yaw Reading New Value...");
      word zdp_after;
      zdp_after = SensorI2C_0.getZeroDegreePositionData();
      Serial.print("Yaw Zero Degree Position After Saving (HEX): ");
      Serial.println(zdp_after, HEX);
      Serial.println();
    }
  }
  else if(bus == 1){
    SelectSensorChannel_Bus(bus);
    Serial.println("PR1 Reading Current Value...");
    word zdp;
    zdp = SensorI2C_1.getZeroDegreePositionData();
    Serial.print("PR1 Zero Degree Position (HEX): ");
    Serial.println(zdp, HEX);
    Serial.println();
    delay(300); // The delay is not important. so it's easier to see in the SM
    Serial.print("PR1 Changing Value... ");     
    //result = SensorI2C_1.setZeroDegreePositionDataVerify((word)((newAngle * 4096) / 360));
    word ax = map((newAngle*100), 0, 36000, 0, 4096);
    result = SensorI2C_1.setZeroDegreePositionDataVerify(ax);
    if(result){
      SensorI2C_1.saveNewValues();
      delay(700); // >600ms
      Serial.println("PR1 Reading New Value...");
      word zdp_after;
      zdp_after = SensorI2C_1.getZeroDegreePositionData();
      Serial.print("PR1 Zero Degree Position After Saving (HEX): ");
      Serial.println(zdp_after, HEX);
      Serial.println();
    }
  }
  else if(bus == 2){
    SelectSensorChannel_Bus(bus); 
    Serial.println("PR2 Reading Current Value...");
    word zdp;
    zdp = SensorI2C_2.getZeroDegreePositionData();
    Serial.print("PR2 Zero Degree Position (HEX): ");
    Serial.println(zdp, HEX);
    Serial.println();
    delay(300); // The delay is not important. so it's easier to see in the SM
    Serial.print("PR2 Changing Value... ");    
    //result = SensorI2C_2.setZeroDegreePositionDataVerify((word)((newAngle * 4096) / 360));
    word ax = map((newAngle*100), 0, 36000, 0, 4096);
    result = SensorI2C_2.setZeroDegreePositionDataVerify(ax);
    if(result){
      SensorI2C_2.saveNewValues();
      delay(700); // >600ms
      Serial.println("PR2 Reading New Value...");
      word zdp_after;
      zdp_after = SensorI2C_2.getZeroDegreePositionData();
      Serial.print("PR2 Zero Degree Position After Saving (HEX): ");
      Serial.println(zdp_after, DEC);
      Serial.println();
    }
  }
  else if(bus == 3){
    SelectSensorChannel_Bus(bus);
    Serial.println("PR3 Reading Current Value...");
    word zdp;
    zdp = SensorI2C_3.getZeroDegreePositionData();
    Serial.print("PR3 Zero Degree Position (HEX): ");
    Serial.println(zdp, HEX);
    Serial.println();
    delay(300); // The delay is not important. so it's easier to see in the SM
    Serial.print("PR3 Changing Value... ");     
    //result = SensorI2C_3.setZeroDegreePositionDataVerify((word)((newAngle * 4096) / 360));
    word ax = map((newAngle*100), 0, 36000, 0, 4096);
    result = SensorI2C_3.setZeroDegreePositionDataVerify(ax);
    if(result){
      SensorI2C_3.saveNewValues();
      delay(700); // >600ms
      Serial.println("PR3 Reading New Value...");
      word zdp_after;
      zdp_after = SensorI2C_3.getZeroDegreePositionData();
      Serial.print("PR3 Zero Degree Position After Saving (HEX): ");
      Serial.println(zdp_after, HEX);
      Serial.println();
    }
  }
  Serial.println("Set Zero Result: " + String(result));
}


void setDirectionClockwise(int bus){  
  if(bus == 0){
    SelectSensorChannel_Bus(bus); 
    SensorI2C_0.setOutputRotationDirectionClockwise();
  }
  else if(bus == 1){
    SelectSensorChannel_Bus(bus); 
    SensorI2C_0.setOutputRotationDirectionClockwise();
  }
  else if(bus == 2){
    SelectSensorChannel_Bus(bus); 
    SensorI2C_0.setOutputRotationDirectionClockwise();
  }
  else if(bus == 3){
    SelectSensorChannel_Bus(bus); 
    SensorI2C_0.setOutputRotationDirectionClockwise();
  } 
}
void setDirectionAntiClockwise(int bus){  
  if(bus == 0){
    SelectSensorChannel_Bus(bus); 
    SensorI2C_0.setOutputRotationDirectionCounterclockwise();
  }
  else if(bus == 1){
    SelectSensorChannel_Bus(bus); 
    SensorI2C_0.setOutputRotationDirectionCounterclockwise();
  }
  else if(bus == 2){
    SelectSensorChannel_Bus(bus); 
    SensorI2C_0.setOutputRotationDirectionCounterclockwise();
  }
  else if(bus == 3){
    SelectSensorChannel_Bus(bus); 
    SensorI2C_0.setOutputRotationDirectionCounterclockwise();
  } 
}

/**SENSOR DIRECTION**/
void yawSensorSetDirection()
{
   if(SENSE_Yaw_Foward){     
      setDirectionClockwise(0);
   }
   else{
      setDirectionAntiClockwise(0);
   }
}


void sense_A_SetDirection(){ 
   if(SENSE_A_UP){
      setDirectionClockwise(1);
   }
   else{
      setDirectionAntiClockwise(1);
   }   
}

void sense_B_SetDirection(){
   if(SENSE_B_UP){
      setDirectionClockwise(2);
   }
   else{
      setDirectionAntiClockwise(2);
   }
}

void holdMotor(int motor, uint8_t state){
  //pinMode(BREAK_YAW, OUTPUT);  
  if(motor == 0){        
      //digitalWrite(BREAK_YAW, state);//enable CON_HOLD_1 force stop
  }
  else if(motor == 1){
      //SIPO2.digitalWrite(BREAK_PR1, state);
  }
  else if(motor == 2){
      //SIPO2.digitalWrite(BREAK_PR2, state);
  }
  else if(motor == 3){
      //SIPO2.digitalWrite(BREAK_PR3, state);
  }
  
}