//#define DEBUG_PRINT (1)
/* f1_22 UDP API ****************************************************/

#define ESP_DRD_USE_SPIFFS true

// All the F1 2022 structs must be packed.
#pragma pack(push)
#pragma pack(1)
struct PacketHeader
{
  uint16_t  m_packetFormat;            // 2022
  uint8_t   m_gameMajorVersion;        // Game major version - "X.00"
  uint8_t   m_gameMinorVersion;        // Game minor version - "1.XX"
  uint8_t   m_packetVersion;           // Version of this packet type, all start from 1
  uint8_t   m_packetId;                // Identifier for the packet type, see below
  uint64_t  m_sessionUID;              // Unique identifier for the session
  float     m_sessionTime;             // Session timestamp
  uint32_t  m_frameIdentifier;         // Identifier for the frame the data was retrieved on
  uint8_t   m_playerCarIndex;          // Index of player's car in the array
  uint8_t   m_secondaryPlayerCarIndex; // Index of secondary player's car in the array (splitscreen)
  // 255 if no second player
};

struct CarTelemetryData
{
    uint16_t      m_speed;                    // Speed of car in kilometres per hour
    float         m_throttle;                 // Amount of throttle applied (0.0 to 1.0)
    float         m_steer;                    // Steering (-1.0 (full lock left) to 1.0 (full lock right))
    float         m_brake;                    // Amount of brake applied (0.0 to 1.0)
    uint8_t       m_clutch;                   // Amount of clutch applied (0 to 100)
    uint8_t       m_gear;                     // Gear selected (1-8, N=0, R=-1)
    uint16_t      m_engineRPM;                // Engine RPM
    uint8_t       m_drs;                      // 0 = off, 1 = on
    uint8_t       m_revLightsPercent;         // Rev lights indicator (percentage)
    uint16_t      m_revLightsBitValue;        // Rev lights (bit 0 = leftmost LED, bit 14 = rightmost LED)
    uint16_t      m_brakesTemperature[4];     // Brakes temperature (celsius)
    uint8_t       m_tyresSurfaceTemperature[4]; // Tyres surface temperature (celsius)
    uint8_t       m_tyresInnerTemperature[4]; // Tyres inner temperature (celsius)
    uint16_t      m_engineTemperature;        // Engine temperature (celsius)
    float         m_tyresPressure[4];         // Tyres pressure (PSI)
    uint8_t       m_surfaceType[4];           // Driving surface, see appendices
};

struct PacketCarTelemetryData
{
  PacketHeader     m_header;              // Header

  CarTelemetryData m_carTelemetryData[22];
  
  uint8_t          m_mfdPanelIndex;       // Index of MFD panel open - 255 = MFD closed
                                          // Single player, race – 0 = Car setup, 1 = Pits
                                          // 2 = Damage, 3 =  Engine, 4 = Temperatures
                                          // May vary depending on game mode
  uint8_t          m_mfdPanelIndexSecondaryPlayer;   // See above
  int8_t           m_suggestedGear;       // Suggested gear for the player (1-8)
                                          // 0 if no gear suggested
};

struct CarStatusData
{
  uint8_t     m_tractionControl;          // 0 (off) - 2 (high)
  uint8_t     m_antiLockBrakes;           // 0 (off) - 1 (on)
  uint8_t     m_fuelMix;                  // Fuel mix - 0 = lean, 1 = standard, 2 = rich, 3 = max
  uint8_t     m_frontBrakeBias;           // Front brake bias (percentage)
  uint8_t     m_pitLimiterStatus;         // Pit limiter status - 0 = off, 1 = on
  float       m_fuelInTank;               // Current fuel mass
  float       m_fuelCapacity;             // Fuel capacity
  float       m_fuelRemainingLaps;        // Fuel remaining in terms of laps (value on MFD)
  uint16_t    m_maxRPM;                   // Cars max RPM, point of rev limiter
  uint16_t    m_idleRPM;                  // Cars idle RPM
  uint8_t     m_maxGears;                 // Maximum number of gears
  uint8_t     m_drsAllowed;               // 0 = not allowed, 1 = allowed, -1 = unknown
  uint16_t    m_drsActivationDistance;    // 0 = DRS not available, non-zero - DRS will be available
                                          // in [X] metres
  uint8_t     m_actualTyreCompound;       // F1 Modern - 16 = C5, 17 = C4, 18 = C3, 19 = C2, 20 = C1
                                          // 7 = inter, 8 = wet
                                          // F1 Classic - 9 = dry, 10 = wet
                                          // F2 – 11 = super soft, 12 = soft, 13 = medium, 14 = hard
                                          // 15 = wet
  uint8_t     m_tyreVisualCompound;       // F1 visual (can be different from actual compound)
                                          // 16 = soft, 17 = medium, 18 = hard, 7 = inter, 8 = wet
                                          // F1 Classic – same as above
                                          // F2 – 19 = super soft, 20 = soft, 21 = medium, 22 = hard
                                          // 15 = wet
  uint8_t     m_tyresAgeLaps;             // Age in laps of the current set of tyres  
  int8_t      m_vehicleFiaFlags;          // -1 = invalid/unknown, 0 = none, 1 = green
                                          // 2 = blue, 3 = yellow, 4 = red
  float       m_ersStoreEnergy;           // ERS energy store in Joules
  uint8_t     m_ersDeployMode;            // ERS deployment mode, 0 = none, 1 = medium
                                          // 2 = overtake, 3 = hotlap
  float       m_ersHarvestedThisLapMGUK;  // ERS energy harvested this lap by MGU-K
  float       m_ersHarvestedThisLapMGUH;  // ERS energy harvested this lap by MGU-H
  float       m_ersDeployedThisLap;       // ERS energy deployed this lap
  uint8_t     m_networkPaused; // Whether the car is paused in a network game
};

struct PacketCarStatusData
{
  PacketHeader     m_header;              // Header

  CarStatusData    m_carStatusData[22];
};

struct CarSetupData
{
  uint8_t   m_frontWing;                // Front wing aero
  uint8_t   m_rearWing;                 // Rear wing aero
  uint8_t   m_onThrottle;               // Differential adjustment on throttle (percentage)
  uint8_t   m_offThrottle;              // Differential adjustment off throttle (percentage)
  float     m_frontCamber;              // Front camber angle (suspension geometry)
  float     m_rearCamber;               // Rear camber angle (suspension geometry)
  float     m_frontToe;                 // Front toe angle (suspension geometry)
  float     m_rearToe;                  // Rear toe angle (suspension geometry)
  uint8_t   m_frontSuspension;          // Front suspension
  uint8_t   m_rearSuspension;           // Rear suspension
  uint8_t   m_frontAntiRollBar;         // Front anti-roll bar
  uint8_t   m_rearAntiRollBar;          // Front anti-roll bar
  uint8_t   m_frontSuspensionHeight;    // Front ride height
  uint8_t   m_rearSuspensionHeight;     // Rear ride height
  uint8_t   m_brakePressure;            // Brake pressure (percentage)
  uint8_t   m_brakeBias;                // Brake bias (percentage)
  float     m_rearLeftTyrePressure;     // Rear left tyre pressure (PSI)
  float     m_rearRightTyrePressure;    // Rear right tyre pressure (PSI)
  float     m_frontLeftTyrePressure;    // Front left tyre pressure (PSI)
  float     m_frontRightTyrePressure;   // Front right tyre pressure (PSI)
  uint8_t   m_ballast;                  // Ballast
  float     m_fuelLoad;                 // Fuel load
};

struct PacketCarSetupData
{
  PacketHeader    m_header;            // Header

  CarSetupData    m_carSetups[22];
};

struct CarMotionData
{
    float         m_worldPositionX;           // World space X position
    float         m_worldPositionY;           // World space Y position
    float         m_worldPositionZ;           // World space Z position
    float         m_worldVelocityX;           // Velocity in world space X
    float         m_worldVelocityY;           // Velocity in world space Y
    float         m_worldVelocityZ;           // Velocity in world space Z
    int16_t       m_worldForwardDirX;         // World space forward X direction (normalised)
    int16_t       m_worldForwardDirY;         // World space forward Y direction (normalised)
    int16_t       m_worldForwardDirZ;         // World space forward Z direction (normalised)
    int16_t       m_worldRightDirX;           // World space right X direction (normalised)
    int16_t       m_worldRightDirY;           // World space right Y direction (normalised)
    int16_t       m_worldRightDirZ;           // World space right Z direction (normalised)
    float         m_gForceLateral;            // Lateral G-Force component
    float         m_gForceLongitudinal;       // Longitudinal G-Force component
    float         m_gForceVertical;           // Vertical G-Force component
    float         m_yaw;                      // Yaw angle in radians
    float         m_pitch;                    // Pitch angle in radians
    float         m_roll;                     // Roll angle in radians
};

struct PacketMotionData
{
    PacketHeader    m_header;               	// Header

    CarMotionData   m_carMotionData[22];    	// Data for all cars on track

    // Extra player car ONLY data
    float         m_suspensionPosition[4];      // Note: All wheel arrays have the following order:
    float         m_suspensionVelocity[4];      // RL, RR, FL, FR
    float         m_suspensionAcceleration[4];	// RL, RR, FL, FR
    float         m_wheelSpeed[4];           	// Speed of each wheel
    float         m_wheelSlip[4];               // Slip ratio for each wheel
    float         m_localVelocityX;         	// Velocity in local space
    float         m_localVelocityY;         	// Velocity in local space
    float         m_localVelocityZ;         	// Velocity in local space
    float         m_angularVelocityX;		    // Angular velocity x-component
    float         m_angularVelocityY;           // Angular velocity y-component
    float         m_angularVelocityZ;           // Angular velocity z-component
    float         m_angularAccelerationX;       // Angular velocity x-component
    float         m_angularAccelerationY;	    // Angular velocity y-component
    float         m_angularAccelerationZ;       // Angular velocity z-component
    float         m_frontWheelsAngle;           // Current front wheels angle in radians
};
#pragma pack(pop)

void readF122(int packet_length){
  if (packet_length == sizeof(PacketHeader)) {
      struct PacketHeader *header = (struct PacketHeader *)&packetBuffer;
      //
      if (header->m_packetFormat == 2022) {
        Serial.println("Reading F1-22 Telemetry Data..." + String(packet_length));
        uint8_t myCar = header->m_playerCarIndex;
        switch (header->m_packetId) {
          case 0:
            {
              struct PacketMotionData *p;
              p = (struct PacketMotionData *)packetBuffer;
              struct CarMotionData *carmotion = &(p->m_carMotionData[myCar]);

              Serial.printf("Roll = %f, Pitch = %f, Yaw = %f\n", \
              carmotion->m_roll, carmotion->m_pitch, carmotion->m_yaw);

              htyawdegree = (carmotion->m_yaw) * 180.0 / PI; //yaw

              //boost pr
              float boostpitch = ((carmotion->m_pitch) * 180.0 / PI)*amp_sim_pr; 
              float boostroll = ((carmotion->m_roll) * 180.0 / PI)*amp_sim_pr; 

              htpitchdegree = boostpitch > pitchMax ? pitchMax : boostpitch;
              htrolldegree = boostroll > rollMax ? rollMax : boostroll;

            }
            break;
          case 5:
            {
              struct PacketCarSetupData *p;
              p = (struct PacketCarSetupData *)packetBuffer;
              struct CarSetupData *carsetup = &(p->m_carSetups[myCar]);
              
              Serial.printf("Diff on throttle = %u Diff off throttle %u\n", \
              carsetup->m_onThrottle, carsetup->m_offThrottle);
              //send_car_setup(carsetup);
            }
            break;
          case 6:
            {
              struct PacketCarTelemetryData *p;
              p = (struct PacketCarTelemetryData *)packetBuffer;
              struct CarTelemetryData *telemetry = &(p->m_carTelemetryData[myCar]);
              
              Serial.printf("Speed = %u RPM %u Gear %d Rev %% %u\n", \
              telemetry->m_speed, telemetry->m_engineRPM, \
              telemetry->m_gear, telemetry->m_revLightsPercent);
              
              //send_car_telemetry(telemetry);
            }
            break;
          case 7:
            {
              struct PacketCarStatusData *p;
              p = (struct PacketCarStatusData *)packetBuffer;
              struct CarStatusData *status = &(p->m_carStatusData[myCar]);
              
              Serial.printf("Fuel Mix = %u Front Brake Bias %u\n", \
              status->m_fuelMix, status->m_frontBrakeBias);

              //send_car_status(status);
            }
            break;
          default:
            break;
        }
      }
    }    
}

struct Outsim_pack 
{
  uint16_t  time;        
  float     angvel_x;      
  float     angvel_y;    
  float     angvel_z;
  float     header;          
  float     pitch;               
  float     roll;            
  float     accel_x;          
  float     accel_y;      
  float     accel_z;          
  float     vel_x; 
  float     vel_y;
  float     vel_z;
  int16_t   pos_x;
  int16_t   pos_y;
  int16_t   pos_z;
};

void readLfs(int packet_length){    
    if (packet_length >= sizeof(Outsim_pack)){
      Serial.println("Reading Live for Speed Telemetry Data..." + String(packet_length));
      struct Outsim_pack *outsim_pack = (struct Outsim_pack *)&packetBuffer;
      
      float newyaw, newpitch, newroll;
      newyaw = 360-((outsim_pack->header) * RAD_TO_DEG + 180.0f); 
      newpitch = ((outsim_pack->pitch) * RAD_TO_DEG); 
      newroll = ((outsim_pack->roll) * RAD_TO_DEG);
      //      
      Serial.printf("Roll = %f, Pitch = %f, Yaw = %f\n", \
      newroll, newpitch, newyaw);

      htyawdegree = newyaw; //yaw
      //boost pr
      float boostpitch = newpitch*amp_sim_pr; 
      htpitchdegree = boostpitch > pitchMax ? pitchMax : boostpitch;
      float boostroll = newroll*amp_sim_pr;      
      htrolldegree = boostroll > rollMax ? rollMax : boostroll;

    }
}


void readGame_Telemetry(int8_t game) {
  // if there's data available, read a packet
  int packetSize = udp.parsePacket();
  if (packetSize > 0) {
    // read the packet into packetBufffer
    int packet_length = udp.read(packetBuffer, sizeof(packetBuffer));
    if(game == f122){
      readF122(packet_length);
    }
    else if(game == lfs){
      readLfs(packet_length);
    }
    else if(game == assettocorsa || epic_rollercoasterDashboardUDP){
      read_Assetto_corsa(packet_length);
    }
    else if(game == projectcars){
      read_projectcars(packet_length);
    }
    else if(game == epic_rollercoasterDirectUDP){
      read_epicrollercoaster(packet_length);
    }
    else if(game == allgames){
      readF122(packet_length);
      readLfs(packet_length);
      read_Assetto_corsa(packet_length);
      read_projectcars(packet_length);
    }    
  }
}