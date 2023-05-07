





void moveYaw(int steps){
    //getCurrentPositionInRevolutions(); //get the current, absolute position in revs
    //setCurrentPositionInRevolutions //assign value in rv

    //setTargetPositionInRevolutions //set the target position to an absolute value in revolutions from the current position
    //setTargetPositionInSteps //set a new absolute target position in steps to move to
    //getCurrentPositionInSteps //
    //getCurrentPositionInRevolutions

    float angle = map_Generic((float)steps, 0.000f, 360.000f, 0.000f, 1.000f);
    PRINTLINE("angle: " + String(angle));
    //yaw.setTargetPositionInRevolutions(angle);

    //yaw.setTargetPositionInSteps(steps);
}

