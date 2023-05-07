//
//   SDL_Arduino_TCA9545 Library
//   SDL_Arduino_TCA9545.cpp Arduino code
//   Version 1.1
//   SwitchDoc Labs   April 10, 2015
//
//



#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>



/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
    #define TCA9545_ADDRESS                         0x70

/*=========================================================================*/
/*=========================================================================
 I2C BUS ADDRESSES
 -----------------------------------------------------------------------*/


    #define TCA9545_CONFIG_BUS0                  0x01  // 1 = enable, 0 = disable
    #define TCA9545_CONFIG_BUS1                  0x02  // 1 = enable, 0 = disable
    #define TCA9545_CONFIG_BUS2                  0x04  // 1 = enable, 0 = disable
    #define TCA9545_CONFIG_BUS3                  0x08  // 1 = enable, 0 = disable

/*=========================================================================
    CONFIG REGISTER (R/W)
    -----------------------------------------------------------------------*/
    #define TCA9545_REG_CONFIG                      0x00
    /*---------------------------------------------------------------------*/


/*=========================================================================*/

class SDL_Arduino_TCA9545{
 public:
  SDL_Arduino_TCA9545();
  SDL_Arduino_TCA9545(TwoWire *pWire);
  void begin();
  void read_control_register(uint8_t *value);
  void write_control_register(uint8_t value);
  void TCA9545SetConfig(void);
  void SelectTCA9548A(uint8_t bus);

 private:

  uint8_t TCA9545_i2caddr;
    
  void wireWriteRegister(uint8_t reg, uint8_t value);
  void wireReadRegister(uint8_t reg, uint8_t *value);

  TwoWire *_wire;

};
