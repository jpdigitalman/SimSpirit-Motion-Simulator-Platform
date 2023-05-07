
/**
 * @brief auto track phase goto angle. 
 * 
 * @param prB_level absolute level from simMagic
 * @param direction computed
 * @param target computed
 * @param speed from auto computed speed
 */
void trackPhaseB(int prB_level){
    rotateMotorbyStep(2, prB_level);
}