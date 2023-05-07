

// All the structs must be packed.
// The hpp file is from https://www.projectcarsgame.com/two/project-cars-2-api/
// Patch 5 API.
#pragma pack(push)
#pragma pack(1)
#include "udp_projectcars.h"
#pragma pack(pop)


const char * const GEAR_NAMES[16] = {
  "N",  // Neutral
  "1",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  "10",
  "11",
  "12",
  "13",
  "14",
  "R",  // Reverse
};

void read_projectcars(int packet_length) {
  // if there's data available, read a packet
  //int packetSize = udp.parsePacket();
  if (true) {
    // read the packet into packetBufffer
    //int n = udp.read(packetBuffer, sizeof(packetBuffer));
    if (packet_length >= sizeof(PacketBase)) {
      struct PacketBase *header = (struct PacketBase *)&packetBuffer;
      switch (header->mPacketType) {
        case eCarPhysics:
          {
            struct sTelemetryData *carPhysics = (struct sTelemetryData *)&packetBuffer;
#if 0
            Serial.printf("sFuelCapacity %u liters\n", carPhysics->sFuelCapacity);
            Serial.printf("sFuelLevel %f\n", carPhysics->sFuelLevel);
            float fuel_liters = carPhysics->sFuelLevel * (float)carPhysics->sFuelCapacity;
            Serial.printf("Fuel %f liters\n", fuel_liters);
            float fuel_gallons = fuel_liters * 0.2641729f;
            Serial.printf("Fuel %f gallons\n", fuel_gallons);

            Serial.printf("sSpeed %f meters/s\n", carPhysics->sSpeed);
            float speed_kph = carPhysics->sSpeed * (3600.0f/1000.0f);
            Serial.printf("sSpeed %f KPH\n", speed_kph);
            float speed_mph = speed_kph * 0.62137f;
            Serial.printf("sSpeed %f MPH\n", speed_mph);

            uint8_t currentGear = carPhysics->sGearNumGears & 0x0F;
            Serial.printf("sGear %u\n", currentGear);
            Serial.printf("Gear %s\n", GEAR_NAMES[currentGear]);
            Serial.printf("sNumGears %u\n", carPhysics->sGearNumGears >> 4);
#endif
            //Serial.printf("sRpm %u sMaxRpm %u\n", carPhysics->sRpm, carPhysics->sMaxRpm);
            Serial.printf("Heading = %f, Pitch = %f, Roll = %f\n", \
              carPhysics->sOrientation[0], carPhysics->sOrientation[1], carPhysics->sOrientation[2]);

            float newyaw, newpitch, newroll;
            if(eqlz){
                newyaw = 360-((carPhysics->sOrientation[0]) * RAD_TO_DEG + 180.0f); 
                newpitch = ((carPhysics->sOrientation[1]) * RAD_TO_DEG); 
                newroll = ((carPhysics->sOrientation[2]) * RAD_TO_DEG);
            }
            else{
                newyaw = carPhysics->sOrientation[0]; 
                newpitch = carPhysics->sOrientation[1]; 
                newroll = carPhysics->sOrientation[2];
            }
            Serial.printf("Roll = %f, Pitch = %f, Yaw = %f\n", \
            newroll, newpitch, newyaw);

            htyawdegree = newyaw; //yaw
            //boost pr
            float boostpitch = newpitch*amp_sim_pr; 
            htpitchdegree = boostpitch > pitchMax ? pitchMax : boostpitch;
            float boostroll = newroll*amp_sim_pr;      
            htrolldegree = boostroll > rollMax ? rollMax : boostroll;
            
          }
          break;
        case eRaceDefinition:
          {
            struct sRaceData *raceData = (struct sRaceData *)&packetBuffer;
#if 0
            Serial.printf("sWorldFastestLapTime %f secs\n", raceData->sWorldFastestLapTime);
            Serial.printf("sTrackLength %f meters\n", raceData->sTrackLength);
#endif
          }
          break;
        case eParticipants:
          {
            struct sParticipantsData *participants = (struct sParticipantsData *)&packetBuffer;
          }
          break;
        case eTimings:
          {
            struct sTimingsData *timings = (struct sTimingsData *)&packetBuffer;
          }
          break;
        case eGameState:
          {
            struct sGameStateData *gameState = (struct sGameStateData *)&packetBuffer;
          }
          break;
        case eWeatherState: // not sent at the moment, information can be found in the game state packet
          break;
        case eVehicleNames: //not sent at the moment
          break;
        case eTimeStats:
          {
            struct sTimeStatsData *timeStats = (struct sTimeStatsData *)&packetBuffer;
          }
          break;
        case eParticipantVehicleNames:
          {
            struct sParticipantVehicleNamesData *participantVehicleNames = (struct sParticipantVehicleNamesData *)&packetBuffer;
          }
          break;
        default:
          break;
      }
    }
  }
}