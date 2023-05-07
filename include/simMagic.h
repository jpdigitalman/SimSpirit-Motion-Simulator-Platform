/******************************************************************************

                            MarkSim
                MarkSim 3 piston Rotation Matrix
John-Paul Madueke 2023

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define nne(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

#define nna(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

const int sine_wave_size_Cpt_i = 360;
const int sine_wave_Cpt_i[] = {
  100,102,103,105,107,109,110,112,114,116,117,119,121,122,124,126,128,129,131,133,134,136,137,139,141,142,144,145,147,148,150,152,153,154,156,157,159,160,162,163,164,166,167,168,169,171,172,173,174,175,177,178,179,180,181,182,183,184,185,186,187,187,188,189,190,191,191,192,193,193,194,195,195,196,196,197,197,197,198,198,198,199,199,199,199,200,200,200,200,200,
  200,200,200,200,200,200,199,199,199,199,198,198,198,197,197,197,196,196,195,195,194,193,193,192,191,191,190,189,188,187,187,186,185,184,183,182,181,180,179,178,177,175,174,173,172,171,169,168,167,166,164,163,162,160,159,157,156,154,153,152,150,148,147,145,144,142,141,139,137,136,134,133,131,129,128,126,124,122,121,119,117,116,114,112,110,109,107,105,103,102,
  100,98,97,95,93,91,90,88,86,84,83,81,79,78,76,74,72,71,69,67,66,64,63,61,59,58,56,55,53,52,50,48,47,46,44,43,41,40,38,37,36,34,33,32,31,29,28,27,26,25,23,22,21,20,19,18,17,16,15,14,13,13,12,11,10,9,9,8,7,7,6,5,5,4,4,3,3,3,2,2,2,1,1,1,1,0,0,0,0,0,
  0,0,0,0,0,0,1,1,1,1,2,2,2,3,3,3,4,4,5,5,6,7,7,8,9,9,10,11,12,13,13,14,15,16,17,18,19,20,21,22,23,25,26,27,28,29,31,32,33,34,36,37,38,40,41,43,44,46,47,48,50,52,53,55,56,58,59,61,63,64,66,67,69,71,72,74,76,78,79,81,83,84,86,88,90,91,93,95,97,98,
};
int phaseA_Sine[360];
int phaseB_Sine[360];
int phaseC_Sine[360];

void loadSine(){
  for(int i = 0; i < 360; i++){
    phaseA_Sine[i] = (sine_wave_Cpt_i[i]-100);
    phaseB_Sine[(((i-240) + 360) % 360)] = (sine_wave_Cpt_i[i]-100);
    phaseC_Sine[(((i-120) + 360) % 360)] = (sine_wave_Cpt_i[i]-100);
  }
}

void simMagic(int &phaseA_Level, int &phaseB_Level, int &phaseC_Level){
  ////
  int yawangle = ((((int)pr_init + (int)htyawdegree) + 360) % 360);
  int i_yawPoint = (((yawangle+90) + 360) % 360); //add 90 degrees to yaw
  int i_pitchPoint = htpitchdegree*100;
  int i_rollPoint = htrolldegree*100;

  //rollPoint = -rollPoint; //invert roll? 1.00 0.00 001
  
  int normA = phaseA_Sine[i_yawPoint];
  int normB = phaseB_Sine[i_yawPoint];
  int normC = phaseC_Sine[i_yawPoint];
  
  /***/
  int pitchA, pitchB, pitchC = 0;
  //do positive pitch  and negative pitch
  pitchA = normA >= 0 ? normA*i_pitchPoint : -(abs(normA))*i_pitchPoint;
  pitchB = normB >= 0 ? normB*i_pitchPoint : -(abs(normB))*i_pitchPoint;
  pitchC = normC >= 0 ? normC*i_pitchPoint : -(abs(normC))*i_pitchPoint;
  /***/
  
   /* Shift angle to right angle to get yaw*/  
   /**to be reviewed*/
  int shiftA = phaseA_Sine[(((i_yawPoint+90) + 360) % 360)];  
  int shiftB = phaseB_Sine[(((i_yawPoint+90) + 360) % 360)];  
  int shiftC = phaseC_Sine[(((i_yawPoint+90) + 360) % 360)];  
  
  int rollA, rollB, rollC = 0;
  
  rollA = shiftA >= 0 ? shiftA*i_rollPoint : -(abs(shiftA))*i_rollPoint;
  rollB = shiftB >= 0 ? shiftB*i_rollPoint : -(abs(shiftB))*i_rollPoint;
  rollC = shiftC >= 0 ? shiftC*i_rollPoint : -(abs(shiftC))*i_rollPoint;
    
  /*compute final piston level using Maximum Priority*/  
  phaseA_Level = (pitchA <= 0 && rollA <= 0 ? -(nna(pitchA, rollA)) : -(nne(pitchA, rollA)))/100;
  phaseB_Level = (pitchB <= 0 && rollB <= 0 ? -(nna(pitchB, rollB)) : -(nne(pitchB, rollB)))/100;
  phaseC_Level = (pitchC <= 0 && rollC <= 0 ? -(nna(pitchC, rollC)) : -(nne(pitchC, rollC)))/100;
  

  PRINTLINE("________________________");
  PRINTLINE("Yaw Position Degree" + String(yawangle));
  PRINTLINE("Pitch Angle: " + String(htpitchdegree));
  PRINTLINE("Roll Angle: " + String(htrolldegree));
  PRINTLINE("________________________");
  PRINTLINE("________________________");
  PRINTLINE("Piston A Final Position:" + String(phaseA_Level));
  PRINTLINE("Piston B Final Position:" + String(phaseB_Level));
  PRINTLINE("Piston C Final Position:" + String(phaseC_Level));
  PRINTLINE("________________________");
}
