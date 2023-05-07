String hostname = "MarkSim";

bool autoMode = true; //overrides some hardware 
bool stationMode = true; //false enables Hotspot () Access Point Mode

int analogGamePadX_Y_Axis_Maximum_Input = 100;
const static float MAX_HT_DIFF = 90.00;     //maximum angle to turn the headtracker
const static int MAX_PR_DIFF = 120;

const int yaw_max_frequency = 20000; //30khz ==> max rpm for yaw
const int pr_max_frequency = 100000; //100khz ==> max rpm for PRs
const int accelMax = yaw_max_frequency; //accel /decel
const int accel_start = 5000;
const int accel_stop = 3000;
const int trimPr = 2000;

int pitchMax = 60;  //done
int rollMax = 35;  //done
float deadZonePr = 5.00;  //done
const int prBoost = 255; //=>22083 pulses
float amp_sim_pr = 8.00f;

const int prMax = 60;

const int stepsPerRevolution_Yaw = 100000;  // change this to fit the number of steps per revolution
const int stepsPerRevolution_PR = 24000;

const int yawAngleMax = 360; //degrees steps

const int phaseAngleMax = 8500; //points steps 90 max (angle)
const int maxSpeedConst = 10000;

bool forceread_alarm = false;
int waiting = 0;
bool moved = false;

const int Home_Return_Enable[] = { LOW, LOW, LOW, LOW }; //when enable signal is low, start homing
const int Home_Return_Disable[] = { HIGH, HIGH, HIGH, HIGH };
unsigned long interval_home = 2000; //intervale between checking home signal

const int deadzone_yaw = 10.0 * 100; //1.5 degrees ****
bool yawing = false;

long basestep = 0;

bool continuousTracking = true;

bool SENSE_A_UP = true; //FALSE?
bool SENSE_B_UP = true; //FALSE?
bool SENSE_C_UP = true; //FALSE?
bool SENSE_Yaw_Foward = true; //FALSE?

int calib_yaw = 0;
bool calib_pr = false;
bool HTconnected, HTconnected_old = false;
bool commandFlag = false;
int htyawstep = 0;


int intervalHTRead = 150;//150ms check maximum to reset HT 
long disconnectTimer = 0;


unsigned long lastSendTime, lastSendTime_home = 0;        // last send time
unsigned long interval = 200;           // interval between sends 
unsigned long lastFlashTime, lastFlashTime_home = 0;        // last send time
const int intervalFlash = 40;
unsigned long lastBeepTime, lastBeepTime_home = 0;        // last beep time
const int intervalBeep = 40;

const float zero_offset = 20.00f;
bool startReturnToZero = false;
float defaultPRzero = 270.00f;
bool pr_enable = false;

bool eqlz = false;
