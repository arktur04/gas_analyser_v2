//------------------------------------------------------------------------------
// ADC inputs disconnect monitoring
//------------------------------------------------------------------------------
#include "board.h"
#include "variables.h"

unsigned int dacCodes[4];
float currentValues[4];

const float minCurrent = 4.0;
const float maxCurrent = 20.0;
const int maxDacCode = 4095;

int getDacCode(float value, float max, float k, int shift)
{
  float current;
  int dacCode;
  current = value * (maxCurrent - minCurrent) / max  + minCurrent;
  current = (current < minCurrent)? minCurrent: current; 
  current = (current > maxCurrent)? maxCurrent: current; 
  dacCode = (int)(current * k + shift);
  return (dacCode < 0)? 0: (dacCode > maxDacCode)? maxDacCode: dacCode; 
}

void processCurrOuts(void)
{
  //---------------------------------------
  // DAC test mode
  if(GetIntValueByTag(DAC_TEST_FLAG))
  {
    dacCodes[0] = GetIntValueByTag(DAC_1);
    dacCodes[1] = GetIntValueByTag(DAC_2);
    dacCodes[2] = GetIntValueByTag(DAC_3);
    dacCodes[3] = GetIntValueByTag(DAC_4);
  }
  else
  {
    //---------------------------------------
    // Output calibr mode
    
    if(GetIntValueByTag(OUT_CALIBR_FLAG))
    {
      currentValues[0] = GetFloatValueByTag(REPR_O2_L);
      currentValues[1] = GetFloatValueByTag(REPR_H_L);
      currentValues[2] = GetFloatValueByTag(REPR_O2_R);
      currentValues[3] = GetFloatValueByTag(REPR_H_R);
    }
    else
    {
      currentValues[0] = GetFloatValueByTag(C_KL_O_L);
      currentValues[1] = GetFloatValueByTag(C_KL_HN_L);
      currentValues[2] = GetFloatValueByTag(C_KL_O_R);
      currentValues[3] = GetFloatValueByTag(C_KL_HN_R);
    };
    
    dacCodes[0] = getDacCode(currentValues[0], 
                             GetFloatValueByTag(MAX_O2_L), 
                             GetFloatValueByTag(K_I_O_L),
                             GetIntValueByTag(SH_O_L));
    
    dacCodes[1] = getDacCode(currentValues[1], 
                             GetFloatValueByTag(MAX_XH_L), 
                             GetFloatValueByTag(K_I_H_L),
                             GetIntValueByTag(SH_H_L));
    
    dacCodes[2] = getDacCode(currentValues[2], 
                             GetFloatValueByTag(MAX_O2_R), 
                             GetFloatValueByTag(K_I_O_R),
                             GetIntValueByTag(SH_O_R));
    
    dacCodes[3] = getDacCode(currentValues[3], 
                             GetFloatValueByTag(MAX_XH_R), 
                             GetFloatValueByTag(K_I_H_R),
                             GetIntValueByTag(SH_H_R));
  };
  WriteToDac(dacCodes);
}
