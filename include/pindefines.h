#define I2C_SDA 23
#define I2C_SCL 22

#define SIPO1_INTERRUPT_PIN 4 //pin expander from i2c bus(PCF8574) 1 interrupt pin on microcontroller
#define SIPO2_INTERRUPT_PIN 5 //pin expander from i2c bus(PCF8574) 2 interrupt pin on microcontroller

#define right true
#define left false

#define ALM_1 P4
#define ALM_2 P5
#define ALM_3 P6
#define ALM_4 P7

#define ALM_1 P4
#define ALM_2 P5
#define ALM_3 P6
#define ALM_4 P7

#define GameTelemetry 7
#define HT_Data 3

#define allgames 0
#define f122  1
#define lfs 2
#define assettocorsa 3
#define projectcars 4
#define epic_rollercoasterDashboardUDP 5
#define epic_rollercoasterDirectUDP 6

#define CON_PUL_1 33 //14
#define CON_DIR_1 18 //19

#define CON_PUL_2 27
#define CON_DIR_2 15

#define CON_PUL_3 21
#define CON_DIR_3 16//33

#define CON_PUL_4 32
#define CON_DIR_4 17

const uint32_t PWM_Pins[]   = { CON_PUL_1, CON_PUL_2, CON_PUL_3, CON_PUL_4 };
const uint32_t DIR_Pins[]   = { CON_DIR_1, CON_DIR_2, CON_DIR_3, CON_DIR_4 };

bool pwm_on[4] = {false, false, false, false};
bool reported_done[] { false, false, false, false };
long oldangle_yaw[] =   { 0, 0, 0, 0 }; //oldangle = 0.0f

bool disableAutoStop = false;

/////

bool wifiConnected, wifiSetup_Started, udp_Telemetry = false;
int8_t connectionState = 0;

bool BleDoneDisconnect = false;
bool BleDisconnect = false;

///head tracker sensor data degrees
float htyawdegree, htyawdegree_init = 0.00f;
float htyawdegree_old = 0.00f;

float htpitchdegree = 0.00f;
float htpitchgree_old = 0.00f;

float htrolldegree = 0.00f;
float htrolldegree_old = 0.00f;

float pr_init = 0.00f;

int cmdBle, cmdBle_old = 0.00f;

int phaseA_target = 0; //computed final piston level -90 ---0---- +90
int phaseB_target = 0; //computed final piston
int phaseC_target = 0; //computed final piston

enum simMode{
   FREE,
   HEADTRACKING,
   COCKPIT,
   APP,
   VHT,
   PHASE_CALIBRATION
} MODE;

enum powerMode{
   PowerOn,
   StandBy
} POWER;


int leftPower, rightPower = 0;

int yawVal, pitchVal, rollVal = 0;

void updateClient(JSONVar configObj);
float equalise360(float diff);
void doBTN();


bool pitchrollenabled = false;

String old_stringVal = "";
String old_stringValA = "";
String old_stringValB = "";
String old_stringValC ="";

String old_stringValYaw ="";
String old_stringValPitch ="";
String old_stringValRoll ="";

String old_proceedNextPhase = "";

struct Credentials {
  char ssid[32];
  char password[32];
};
Credentials wifiCredentials;  // <- global configuration objects

//Preferences preferences;

float yaw360, oldyaw360 = 0.00f; //
float heading, initHeading, init360, calibA, calibB, calibC = 0.00f;
bool ht_calibrating, calibrated = false;
float calib360, roto360, calib_diff, oldcalib360, phase_a_ct, oldphase_a_ct, phase_b_ct, oldphase_b_ct, phase_c_ct, oldphase_c_ct = 0.00f;
long yaw_current_step = 0.00f;


bool directionTurning[4] = {false, false, false, false};

int absoluteAngle[4] = { 0, 0, 0, 0 };

bool ccw = false;

int testangle = 0;

float global_targetangle, global_difference = 0.00f;
int global_speed, global_motor = 0;
bool global_direction, global_jumptoangle_yaw_flag, global_steptoangle_yaw_flag = 0;
bool global_autotracker_flag, pr1_autotracker_flag, pr2_autotracker_flag, pr3_autotracker_flag = false;
int global_max_steps_yaw = 0;

int pr1_home, pr2_home, pr3_home = 0;
int oldpr1, oldpr2, oldpr3 = 0;

bool dir_yaw, dir_pr1, dir_pr2, dir_pr3;
float diff_yaw, diff_pr1, diff_pr2, diff_pr3;
int speed_yaw, speed_pr1, speed_pr2, speed_pr3;

int old_ht_position = 0;
int old_prA_level, old_prB_level, old_prC_level = 0;
bool ledVal = HIGH;
bool buzVal = HIGH;

bool rxConnected = false;
uint32_t timestamp_ht, timestamp_runsim;

bool setupMode = false;

bool manualTurn = false;
const int8_t encoder_yaw_channel = 2; //select encoder bus channel in i2c multiplexer 0

const uint16_t F1_UDP_PORT = 20777; //UDP PORT
WiFiUDP udp;

