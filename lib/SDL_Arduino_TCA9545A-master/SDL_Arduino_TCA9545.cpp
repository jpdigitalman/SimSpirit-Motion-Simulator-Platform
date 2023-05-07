//
//   SDL_Arduino_TCA9545 Library
//   SDL_Arduino_TCA9545.cpp Arduino code - runs in continuous mode
//   Version 1.1
//   SwitchDoc Labs   April 10, 2015
//
//



//#include "Arduino.h"


#include <Wire.h>

#include "SDL_Arduino_TCA9545.h"



SDL_Arduino_TCA9545::SDL_Arduino_TCA9545() {
	
	_wire = &Wire;
    
    TCA9545_i2caddr = 0x70;

}
/**************************************************************************/
/*! 
    @brief  Instantiates a new SDL_Arduino_TCA9545 class
*/
/**************************************************************************/
SDL_Arduino_TCA9545::SDL_Arduino_TCA9545(TwoWire *pWire) {
	
	_wire = pWire;
    
    TCA9545_i2caddr = 0x70;

}

void SDL_Arduino_TCA9545::begin(){
	_wire->begin();
}

/**************************************************************************/
/*! 
    @brief  Sends a single command byte over I2C
*/
/**************************************************************************/
void SDL_Arduino_TCA9545::wireWriteRegister (uint8_t reg, uint8_t value)
{
	_wire->beginTransmission(TCA9545_i2caddr);


    //8-bits

    _wire->write(value);             // Lower 8-bits
    _wire->endTransmission();
}

/**************************************************************************/
/*! 
    @brief  Reads an 8 bit values over I2C
*/
/**************************************************************************/
void SDL_Arduino_TCA9545::wireReadRegister(uint8_t reg, uint8_t *value)
{


    _wire->requestFrom(TCA9545_i2caddr, (uint8_t)1);
    // Shift values to create properly formed integer
    *value =_wire->read();
}

//

void SDL_Arduino_TCA9545::SelectTCA9548A(uint8_t bus){
	_wire->beginTransmission(0x70);  // TCA9548A address
	_wire->write(1 << bus);          // send byte to select bus
	_wire->endTransmission();
	_wire->print(bus);
}

void SDL_Arduino_TCA9545::TCA9545SetConfig(void)
{
    uint8_t config;
    
    config = 0;   // no buses turned on
    
    // Set Config register to take into account the settings above
    wireWriteRegister(TCA9545_REG_CONFIG, config);
}

void SDL_Arduino_TCA9545::read_control_register(uint8_t *value)
{
   
    wireReadRegister(TCA9545_REG_CONFIG, value);

}

void SDL_Arduino_TCA9545::write_control_register(uint8_t value)
{
    
    wireWriteRegister(TCA9545_REG_CONFIG, value);

}




