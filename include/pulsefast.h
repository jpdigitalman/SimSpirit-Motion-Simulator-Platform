#include "FastAccelStepper.h"

const int yaw_dirPin  =  DIR_Pins[0];
const int yaw_stepPin =  PWM_Pins[0];

const int pr1_dirPin  =  DIR_Pins[1];
const int pr1_stepPin =  PWM_Pins[1];

const int pr2_dirPin  =  DIR_Pins[2];
const int pr2_stepPin =  PWM_Pins[2];

const int pr3_dirPin  =  DIR_Pins[3];
const int pr3_stepPin =  PWM_Pins[3];

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *yaw = NULL;

FastAccelStepper *pr1 = NULL;

FastAccelStepper *pr2 = NULL;

FastAccelStepper *pr3 = NULL;

void pulse_setup() {
   engine.init(1);
   yaw = engine.stepperConnectToPin(yaw_stepPin);
   
   if (yaw) {
      yaw->setDirectionPin(yaw_dirPin);
      //yaw->setEnablePin(enablePinStepper);
      yaw->setAutoEnable(true);
      
    
      yaw->setSpeedInHz(yaw_max_frequency);       // 500 steps/s
      yaw->setAcceleration(accelMax);    // 100 steps/s²
   }
   
   pr1 = engine.stepperConnectToPin(pr1_stepPin);
   if (pr1) {
      pr1->setDirectionPin(pr1_dirPin);
      pr1->setAutoEnable(true);
    
      pr1->setSpeedInHz(pr_max_frequency);       
      pr1->setAcceleration(pr_max_frequency);    // 10000 steps/s²
   }

   pr2 = engine.stepperConnectToPin(pr2_stepPin);
   if (pr2) {
      pr2->setDirectionPin(pr2_dirPin);
      pr2->setAutoEnable(true);
    
      pr2->setSpeedInHz(pr_max_frequency);      
      pr2->setAcceleration(pr_max_frequency);    // 10000 steps/s²
   }

   pr3 = engine.stepperConnectToPin(pr3_stepPin);
   if (pr3) {
      pr3->setDirectionPin(pr3_dirPin);
      pr3->setAutoEnable(true);
    
      pr3->setSpeedInHz(pr_max_frequency);       
      pr3->setAcceleration(pr_max_frequency);    // 10000 steps/s²
   }
}


void doYaw(){    
    if(continuousTracking){
        //calibrateYaw(htyawdegree);
        readSensorsDegrees(encoder_yaw_channel, calib360); 
    }
    else{
        long angle = yaw->getCurrentPosition();
        if(angle != oldangle_yaw[0]){
            Serial.println("yaw step: " + String(angle));
            oldangle_yaw[0] = angle;
        }
        int compress = 0;
        if(angle >= 0){
            compress = map(angle, 0, stepsPerRevolution_Yaw, 0, 360);
        }
        else{
            compress = -(map(abs(angle), 0, stepsPerRevolution_Yaw, 0, 360));
        }
        calib360 = (compress + 360) % 360; //return absolue angle angle    
    }

    if((int)calib360 != (int)oldcalib360){
        Serial.println("Calib360: " + String(calib360));
        oldcalib360 = calib360;
        Serial.println("calib_yaw value: " + String(calib_yaw));
        Serial.println("pr_enable value: " + String(pr_enable));
        /*
        if(calib360 == 359){
            beepTimes(1, 50); 
        }
        */
    }
    
}

void pr1_do()
{    
    long angle = pr1->getCurrentPosition();
    if(angle != oldangle_yaw[1]){
        PRINTLINE("pr1 step: " + String(angle));
        oldangle_yaw[1] = angle;
    }
    phase_a_ct = angle; 
}

void pr2_do()
{    
    long angle = pr2->getCurrentPosition();
    if(angle != oldangle_yaw[2]){
        PRINTLINE("pr2 step: " + String(angle));
        oldangle_yaw[2] = angle;
    }
    phase_b_ct = angle;   
}

void pr3_do()
{    
    long angle = pr3->getCurrentPosition();
    if(angle != oldangle_yaw[3]){
        PRINTLINE("pr3 step: " + String(angle));
        oldangle_yaw[3] = angle;
    }
    phase_c_ct = angle;
}

void rotateMotorbyStep(int motor, int steps){    
    //int pulse_hz = map(speed, 0, 100, 0, yaw_max_frequency);
    if(motor == 0){
        yaw->move(steps);
    }
    else if(motor == 1){
        pr1->moveTo(steps);
    }
    else if(motor == 2){
        pr2->moveTo(steps);
    }
    else if(motor == 3){
        pr3->moveTo(steps);
    } 
    else{

    }     
}

////
/*
*/
void turn_MotorLeft(int motor, int speed){    
    if(motor == 0){
        yaw->setSpeedInHz(speed); 
        yaw->runForward();        
        yaw->applySpeedAcceleration();
    }
    else if(motor == 1){
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr1->setSpeedInHz(pulse_hz);
	    pr1->runForward();
    }
    else if(motor == 2){
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr2->setSpeedInHz(pulse_hz);
	    pr2->runForward();
    }
    else if(motor == 3){
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr3->setSpeedInHz(pulse_hz);
	    pr3->runForward();
    }
}

void turn_MotorRight(int motor, int speed){
    if(motor == 0){
        yaw->setSpeedInHz(speed);
        yaw->runBackward();
        yaw->applySpeedAcceleration();
    }
    else if(motor == 1){
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr1->setSpeedInHz(pulse_hz);
	    pr1->runBackward();
    }
    else if(motor == 2){
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr2->setSpeedInHz(pulse_hz);
	    pr2->runBackward();
    }
    else if(motor == 3){
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr3->setSpeedInHz(pulse_hz);
	    pr3->runBackward();
    }
}

void forceStop(int motor){
    if(motor == 0){
        if(yaw->isRunning()){
            
        }
        //yaw->setSpeedInHz(0);
        //yaw->applySpeedAcceleration();
        yaw->forceStop();
        //beepTimes(1, 50);        
    }
    else if(motor == 1){
        pr1->forceStop();
        //holdMotor(1, LOW);
    }
    else if(motor == 2){
        pr2->forceStop();
        //holdMotor(2, LOW);
    }
    else if(motor == 3){
        pr3->forceStop();
        //holdMotor(3, LOW);
    }
    else{

    }
}

void stopMotor(int motor){
    if(motor == 0){  
        yaw->setSpeedInHz(0);
        yaw->applySpeedAcceleration();
        yaw->stopMove();

        
        //beepTimes(1, 50);
    }
    else if(motor == 1){
        pr1->stopMove();
        //holdMotor(1, LOW);
    }
    else if(motor == 2){
        pr2->stopMove();
        //holdMotor(2, LOW);
    }
    else if(motor == 3){
        pr3->stopMove();
        //holdMotor(3, LOW);
    }
    else{

    }
}
