

/**
 * @brief auto track phase goto angle. 
 * 
 * @param prA_level absolute level from simMagic -90 to 0 to +90
 * @param direction computed
 * @param target computed
 * @param speed from auto computed speed
 */
void trackPhaseA(int prA_level){ 
    rotateMotorbyStep(1, prA_level);
}
