//------------------------------------------------------------------------------
// ADC inputs disconnect monitoring
//------------------------------------------------------------------------------
#include "disconnect.h"
#include "timers.h"
#include "messages.h"
#include "variables.h"

char disconn_state[4], disconn_i[4];
long int disconn_lth[4], disconn_hth[4], disconn_adc_code[4];

//------------------------------------------------------------------------------
// Init è Process
//------------------------------------------------------------------------------
void InitDisconn(void)
{
  for(char i = 0; i < 4; i++)
    disconn_state[i] = 0;
}

void ProcessDisconn(char ch)
{
  switch(ch)
  {
  case 0:
    disconn_adc_code[0] = GetIntValueByTag(ADC_1_) / 16;
    break;
  case 1:
    disconn_adc_code[1] = GetIntValueByTag(ADC_2_) / 16;
    break;
  case 2:
    disconn_adc_code[2] = GetIntValueByTag(ADC_3_) / 16;
    break;
  case 3:
    disconn_adc_code[3] = GetIntValueByTag(ADC_4_) / 16;
    break;
  };
  
  switch(disconn_state[ch])
  {
  case 0:  //connected
    switch(ch)
    {
    case 0:
      disconn_hth[0] = GetIntValueByTag(INPUT0_RESISTANCE_DETECTOR_HI_THRESHOLD);
      break;
    case 1:
      disconn_hth[1] = GetIntValueByTag(INPUT1_RESISTANCE_DETECTOR_HI_THRESHOLD);
      break;
    case 2:
      disconn_hth[2] = GetIntValueByTag(INPUT2_RESISTANCE_DETECTOR_HI_THRESHOLD);
      break;
    case 3:
      disconn_hth[3] = GetIntValueByTag(INPUT3_RESISTANCE_DETECTOR_HI_THRESHOLD);
      break;
    };
    
    if(disconn_adc_code[ch] > disconn_hth[ch])
    {
      disconn_i[ch] = 0;
      disconn_state[ch] = 1;
    };
    break;
    //-----------------------
  case 1:  //may be disconnected
    disconn_i[ch]++;
    if(disconn_i[ch] > 5)
      disconn_state[ch] = 2;
    
    if(disconn_adc_code[ch] < disconn_hth[ch])
      disconn_state[ch] = 0;
    break;
    //-------------------------
  case 2:  //disconnected
    switch(ch)
    {
    case 0:
      disconn_lth[0] = GetIntValueByTag(INPUT0_RESISTANCE_DETECTOR_LOW_THRESHOLD);
      break;
    case 1:
      disconn_lth[1] = GetIntValueByTag(INPUT1_RESISTANCE_DETECTOR_LOW_THRESHOLD);
      break;
    case 2:
      disconn_lth[2] = GetIntValueByTag(INPUT2_RESISTANCE_DETECTOR_LOW_THRESHOLD);
      break;
    case 3:
      disconn_lth[3] = GetIntValueByTag(INPUT3_RESISTANCE_DETECTOR_LOW_THRESHOLD);
      break;
    };
    
    if(disconn_adc_code[ch] < disconn_lth[ch])
    {
      disconn_i[ch] = 0;
      disconn_state[ch] = 3;
    };
    break;
    
  case 3:  //may be connected
    disconn_i[ch]++;
    if(disconn_i[ch] > 5)
      disconn_state[ch] = 0;
    
    if(disconn_adc_code[ch] > disconn_lth[ch])
      disconn_state[ch] = 2;
    break;
  };
  
  switch(ch)
  {
  case 0:
    SetIntValueByTag(FLT_TP_L, (disconn_state[0] >=2)); //left thermocouple failure
    break;
  case 1:
    SetIntValueByTag(FLT_CH_L, (disconn_state[1] >= 2)); //left sensor fail
    break;
  case 2:
    SetIntValueByTag(FLT_TP_R, (disconn_state[2] >=2)); //right thermocouple failure
    break;
  case 3:
    SetIntValueByTag(FLT_CH_R, (disconn_state[3] >= 2)); //right sensor fail
    break;  
  };
}
