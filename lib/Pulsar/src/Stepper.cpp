/*
 * Stepper.cpp - Stepper library for Wiring/Arduino - Version 1.1.0
 *
 * Original library        (0.1)   by John-Paul Madueke
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 *
 *
 * Drives MarkSim Motor
 *
 */

#include "Arduino.h"
#include "Stepper.h"

/*
 * two-wire constructor.
 * Sets which wires should control the motor.
 */
Stepper::Stepper(int number_of_steps, int motor_pulse_pin, int motor_dir_pin)
{
  this->step_number = 0;    // which step the motor is on *
  this->direction = 0;      // motor direction *
  this->last_step_time = 0; // time stamp in us of the last step taken *
  this->number_of_steps = number_of_steps; // total number of steps for this motor *

  //
  this->pulseState = LOW;
  this->pulse = 0;
  this->pulsedone = 0;
  this->previousMillis_PulsePin = 0;  // will store last time pulsePin was updated  
  this->interval_PulsePin = 0;  // interval at which to pulse the pin (milliseconds)
  this->pulseDirection[number_of_steps];
  this->universalPosition_Counter = 0;

  // Arduino pins for the motor control connection:
  this->motor_pulse_pin = motor_pulse_pin;
  this->motor_dir_pin = motor_dir_pin;

  // setup the pins on the microcontroller:
  pinMode(this->motor_pulse_pin, OUTPUT);
  pinMode(this->motor_dir_pin, OUTPUT);


  // pin_count is used by the stepMotor() method:
  this->pin_count = 2;
}


/*
 * Sets the speed in revs per minute
 */
void Stepper::setSpeed(long whatSpeed)
{
  this->step_delay = 60L * 1000L * 1000L / this->number_of_steps / whatSpeed;
}

/*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */
void Stepper::step(int steps_to_move)
{
  if(this->pulse <= 0){
    this->pulse = abs(steps_to_move);  // how many steps to take
    // determine direction based on whether steps_to_mode is + or -:
    if (steps_to_move > 0) { this->direction = 1; }
    if (steps_to_move < 0) { this->direction = 0; }
  }
}


/**
 * @brief this is Asynchrounous function called repeatedly as fast as possible
 * It Generates Both Pulses that turns the Marksim Driver Motors in CCW or CW direction
 * // the number of steps, moving one step each time:
 * 
 * @return It Returns the current Pulse Count position of the motor in +ve or -ve
 * 
 */
long Stepper:: pulser(int &pulsedone) {
  // check to see if it's time to pulse the Pin; that is, if the difference
  // between the current time and last time you pulsed the Pin is bigger than
  // the interval at which you want to pulse the pin.
  unsigned long currentMillis = micros();
  if(this->pulse > 0){
    if (currentMillis - this->previousMillis_PulsePin >= this->step_delay) {
      // save the last time you blinked the LED
      this->previousMillis_PulsePin = currentMillis;
      // if the pulse pin is off turn it on and vice-versa:
      // if the LED is off turn it on and vice-versa:
      if (this->pulseState == LOW) {
        this->pulseState = HIGH;     
        // set the pulsePin with the new pulsestate and direction
        digitalWrite(this->motor_dir_pin, this->direction); 
        digitalWrite(this->motor_pulse_pin, this->pulseState);   
        Serial.println(this->pulseState);
      } else {
        this->pulseState = LOW;
        // set the pulsePin with the new pulsestate and direction
        digitalWrite(this->motor_dir_pin, this->direction); 
        digitalWrite(this->motor_pulse_pin, this->pulseState);
        Serial.println(this->pulseState);
        //if current pass is high to low, then unqueue this pulse
        this->pulse--;
        pulsedone++; 
        //
        if(this->direction == 1){
          this->universalPosition_Counter++;
          if(this->universalPosition_Counter == this->number_of_steps){
            this->universalPosition_Counter = 0;
          }
        }
        else{
          if(this->universalPosition_Counter == 0){
            this->universalPosition_Counter = this->number_of_steps;
          }
          this->universalPosition_Counter--;
        }       
      }      
    }
  }
  return this->universalPosition_Counter;  
}

/*
  version() returns the version of the library:
*/
int Stepper::version(void)
{
  return 1;
}
