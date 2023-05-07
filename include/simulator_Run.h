
void Simulate(){    
    if(calib_yaw == 2){
        if(pr_enable){
            simMagic(phaseA_target, phaseB_target, phaseC_target);
            Serial.println("Simulate: phaseA_target:" + String(phaseA_target) + ", "+ String(phaseB_target) + ", "+ String(phaseC_target) );
            trackPhaseA(phaseA_target);
            trackPhaseB(phaseB_target);
            trackPhaseC(phaseC_target);
        }
        trackToYaw();             
    }
    else{
        //PRINTLINE("Waiting for Calibration");        
    }   
}
