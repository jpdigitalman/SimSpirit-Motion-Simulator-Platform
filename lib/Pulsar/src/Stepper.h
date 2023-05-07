/*
 * Stepper.h - Stepper library for Wiring/Arduino - Version 1.1.0
 
 */

// ensure this library description is only included once
#ifndef Stepper_h
#define Stepper_h

// library interface description
class Stepper {
  public:
    // constructors:
    Stepper(int number_of_steps, int motor_pulse_pin, int motor_dir_pin);
    
    // speed setter method:
    void setSpeed(long whatSpeed);

    // mover method:
    void step(int number_of_steps);

    int version(void);

    long pulser(int &pulsedone);

  private:
    //void stepMotor(int this_step);

    int direction;            // Direction of rotation
    unsigned long step_delay; // delay between steps, in ms, based on speed
    int number_of_steps;      // total number of steps this motor can take
    int pin_count;            // how many pins are in use.
    int step_number;          // which step the motor is on
    //
    int pulseState;
    int pulse;
    int pulsedone;
    unsigned long previousMillis_PulsePin;  // will store last time pulsePin was updated
    // constants won't change:
    long interval_PulsePin;  // interval at which to pulse the pin (milliseconds)
    int pulseDirection[500];
    long universalPosition_Counter;

    // motor pin numbers:
    int motor_pulse_pin;
    int motor_dir_pin;

    unsigned long last_step_time; // time stamp in us of when the last step was taken
};

#endif

