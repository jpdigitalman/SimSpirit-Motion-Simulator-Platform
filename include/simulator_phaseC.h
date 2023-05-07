/**
 * @brief auto track phase goto angle. 
 * 
 * @param prC_level absolute level from simMagic
 * @param direction computed
 * @param target computed
 * @param speed from auto computed speed
 */
void trackPhaseC(int prC_level){
    rotateMotorbyStep(3, prC_level);
}