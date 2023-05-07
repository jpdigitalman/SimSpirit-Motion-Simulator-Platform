
//      ******************************************************************
//      *                                                                *
//      *                    Marksim stepper Version 2            *
//      *                                                                *
//      *                                                                *
//      *                                                                *
//      *                                                                *
//      ******************************************************************

#ifndef ESP_FlexyStepper_h
#define ESP_FlexyStepper_h

#ifdef ESP32

#else
#error Platform not supported, only ESP32 modules are currently supported
#endif


#include <Arduino.h>
#include <stdlib.h>

typedef void (*callbackFunction)(void);
typedef void (*positionCallbackFunction)(long);

class ESP_FlexyStepper
{
public:
  ESP_FlexyStepper();
  ~ESP_FlexyStepper();
  //service functions
  bool startAsService(int coreNumber = 1);
  void stopService(void);
  bool isStartedAsService(void);

  //IO setup and helper / debugging functions
  void connectToPins(byte stepPinNumber, byte directionPinNumber=255);
  void setBrakePin(byte brakePin, byte activeState = ESP_FlexyStepper::ACTIVE_HIGH);
  long getTaskStackHighWaterMark(void);
  void clearLimitSwitchActive(void);
  bool motionComplete();
  int getDirectionOfMotion(void);
  bool isMovingTowardsHome(void);
  void emergencyStop(bool holdUntilReleased = false);
  void releaseEmergencyStop(void);
  void activateBrake(void);
  void deactivateBrake(void);
  bool isBakeActive(void);
  //the central function to calculate the next movment step signal
  bool processMovement(void);

  //register function for callbacks
  void registerHomeReachedCallback(callbackFunction homeReachedCallbackFunction);
  void registerLimitReachedCallback(callbackFunction limitSwitchTriggerdCallbackFunction);
  void registerTargetPositionReachedCallback(positionCallbackFunction targetPositionReachedCallbackFunction);
  void registerEmergencyStopTriggeredCallback(callbackFunction emergencyStopTriggerdCallbackFunction);
  void registerEmergencyStopReleasedCallback(callbackFunction emergencyStopReleasedCallbackFunction);

  //configuration functions
  void setStepsPerMillimeter(float motorStepPerMillimeter);
  void setStepsPerRevolution(float motorStepPerRevolution);
  void setSpeedInStepsPerSecond(float speedInStepsPerSecond);
  void setSpeedInMillimetersPerSecond(float speedInMillimetersPerSecond);
  void setSpeedInRevolutionsPerSecond(float speedInRevolutionsPerSecond);
  void setAccelerationInMillimetersPerSecondPerSecond(float accelerationInMillimetersPerSecondPerSecond);
  void setAccelerationInRevolutionsPerSecondPerSecond(float accelerationInRevolutionsPerSecondPerSecond);
  void setDecelerationInMillimetersPerSecondPerSecond(float decelerationInMillimetersPerSecondPerSecond);
  void setDecelerationInRevolutionsPerSecondPerSecond(float decelerationInRevolutionsPerSecondPerSecond);
  void setAccelerationInStepsPerSecondPerSecond(float accelerationInStepsPerSecondPerSecond);
  void setDecelerationInStepsPerSecondPerSecond(float decelerationInStepsPerSecondPerSecond);
  void setDirectionToHome(signed char directionTowardHome);
  void setLimitSwitchActive(byte limitSwitchType);

  void setBrakeEngageDelayMs(unsigned long);
  void setBrakeReleaseDelayMs(signed long);

  float getCurrentVelocityInStepsPerSecond();
  float getCurrentVelocityInRevolutionsPerSecond();
  float getCurrentVelocityInMillimetersPerSecond(void);

  //positioning functions
  void setCurrentPositionInSteps(long currentPositionInSteps);
  void setCurrentPositionInMillimeters(float currentPositionInMillimeters);
  void setCurrentPositionInRevolutions(float currentPositionInRevolutions);

  long getCurrentPositionInSteps();
  float getCurrentPositionInRevolutions();
  float getCurrentPositionInMillimeters();

  void startJogging(signed char direction);
  void stopJogging();
  void goToLimitAndSetAsHome(callbackFunction callbackFunctionForHome = NULL, long maxDistanceToMoveInSteps = 2000000000L);
  void goToLimit(signed char direction, callbackFunction callbackFunctionForLimit = NULL);
  

  void setCurrentPositionAsHomeAndStop(void);
  void setTargetPositionToStop();
  long getDistanceToTargetSigned(void);

  void setTargetPositionInSteps(long absolutePositionToMoveToInSteps);
  void setTargetPositionInMillimeters(float absolutePositionToMoveToInMillimeters);
  void setTargetPositionInRevolutions(float absolutePositionToMoveToInRevolutions);
  void setTargetPositionRelativeInSteps(long distanceToMoveInSteps);
  void setTargetPositionRelativeInMillimeters(float distanceToMoveInMillimeters);
  void setTargetPositionRelativeInRevolutions(float distanceToMoveInRevolutions);

  long getTargetPositionInSteps();
  float getTargetPositionInMillimeters();
  float getTargetPositionInRevolutions();

  //blocking function calls
  void moveToPositionInSteps(long absolutePositionToMoveToInSteps);
  void moveToPositionInMillimeters(float absolutePositionToMoveToInMillimeters);
  void moveToPositionInRevolutions(float absolutePositionToMoveToInRevolutions);
  void moveRelativeInSteps(long distanceToMoveInSteps);
  void moveRelativeInMillimeters(float distanceToMoveInMillimeters);
  void moveRelativeInRevolutions(float distanceToMoveInRevolutions);

  bool moveToHomeInSteps(signed char directionTowardHome, float speedInStepsPerSecond, long maxDistanceToMoveInSteps, int homeSwitchPin);
  bool moveToHomeInMillimeters(signed char directionTowardHome, float speedInMillimetersPerSecond, long maxDistanceToMoveInMillimeters, int homeLimitSwitchPin);
  bool moveToHomeInRevolutions(signed char directionTowardHome, float speedInRevolutionsPerSecond, long maxDistanceToMoveInRevolutions, int homeLimitSwitchPin);

  static const byte LIMIT_SWITCH_BEGIN = -1;
  static const byte LIMIT_SWITCH_END = 1;
  static const byte LIMIT_SWITCH_COMBINED_BEGIN_AND_END = 2;
  static const byte ACTIVE_HIGH = 1;
  static const byte ACTIVE_LOW = 2;

private:
  callbackFunction _homeReachedCallback = NULL;
  callbackFunction _limitTriggeredCallback = NULL;
  callbackFunction _emergencyStopTriggeredCallback = NULL;
  callbackFunction _emergencyStopReleasedCallback = NULL;
  positionCallbackFunction _targetPositionReachedCallback = NULL;
  callbackFunction _callbackFunctionForGoToLimit = NULL;

  static void taskRunner(void *parameter);

  void DeterminePeriodOfNextStep();
  void triggerBrakeIfNeededOrSetTimeout(void);

  byte stepPin;
  byte brakePin = -1;
  byte brakePinActiveState = ACTIVE_HIGH;
  unsigned long _brakeEngageDelayMs = 0;
  signed long _brakeReleaseDelayMs = -1;
  unsigned long _timeToEngangeBrake = LONG_MAX;
  unsigned long _timeToReleaseBrake = LONG_MAX;
  bool _isBrakeConfigured = false;
  bool _hasMovementOccuredSinceLastBrakeRelease = true;

  byte directionPin;
  bool _isBrakeActive = false;
  float stepsPerMillimeter;
  float stepsPerRevolution;
  int directionOfMotion;
  long currentPosition_InSteps;
  long targetPosition_InSteps;
  float desiredSpeed_InStepsPerSecond;
  float desiredPeriod_InUSPerStep;
  float acceleration_InStepsPerSecondPerSecond;
  float acceleration_InStepsPerUSPerUS;
  float deceleration_InStepsPerSecondPerSecond;
  float deceleration_InStepsPerUSPerUS;
  float periodOfSlowestStep_InUS;
  float minimumPeriodForAStoppedMotion;
  float nextStepPeriod_InUS;
  unsigned long lastStepTime_InUS;
  float currentStepPeriod_InUS;
  bool emergencyStopActive;
  bool holdEmergencyStopUntilExplicitRelease;
  signed char directionTowardsHome;
  signed char lastStepDirectionBeforeLimitSwitchTrigger;
  //true if the current stepper positon equals the homing position
  bool isCurrentlyHomed;
  bool isOnWayToHome = false;
  bool isOnWayToLimit = false;
  bool firstProcessingAfterTargetReached = true;
  //The type ID of the limit switch type that is active. possible values are LIMIT_SWITCH_BEGIN (-1) or LIMIT_SWITCH_END (1) or LIMIT_SWITCH_COMBINED_BEGIN_AND_END (2) or 0 if no limit switch is active
  signed char activeLimitSwitch;
  bool limitSwitchCheckPeformed;
  // 0 if the the stepper is allowed to move in both directions (e.g. no limit or homing switch triggered), otherwise indicated which direction is currently not allowed for further movement
  signed char disallowedDirection;

  TaskHandle_t xHandle = NULL;
};

// ------------------------------------ End ---------------------------------
#endif


template <class X, class M, class N, class O, class Q>
X map_Generic(X x, M in_min, N in_max, O out_min, Q out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}