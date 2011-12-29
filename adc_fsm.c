#include "board.h"
#include "adc_fsm.h"
//#include "messages.h"
#include "timers.h"
#include "variables.h"
#include "LPC_Uart.h"
#include <stdio.h>

#define MIDCODE 32768
#define THR_UP (MIDCODE / 2 - 2048)
#define THR_DOWN (MIDCODE - 512)

const char gains[5] = {16UL, 8UL, 4UL, 2UL, 1UL};

const char aux_gains[4] = {G_1, G_1, G_1, G_1};
const int main_modes[4] = {0x200F, 0x200A, 0x200F, 0x200A};
const char adc_bits[4] = {16, 24, 16, 24};
  
const int tag_0[4] = {ADC_1, ADC_2, ADC_3, ADC_4};
const int tag_1[4] = {ADC_1_, ADC_2_, ADC_3_, ADC_4_};
const char autoRangeAllowed[4] = {FALSE, FALSE, FALSE, TRUE};

char main_gains[4] = {G_1, G_1, G_1, G_1};  
char adc_state[4] = {0, 0, 0, 0};

unsigned int upThrs[4] = {0, THR_UP, 0, THR_UP};
unsigned int downThrs[4] = {0, THR_DOWN, 0, THR_DOWN};

char ignore_cnt[4];

//char adc_iteration_count = 0;
unsigned int adc_values[3][4] =  //values of the measured input voltage in adc discretes
{{0, 0, 0, 0},
{0, 0, 0, 0},
{0, 0, 0, 0}};
/*
  adc_values_[4], //temp var
  adc_curr_values[4],// temp var - instant input voltage in adc discrete
  adc_prev_values[4],// temp var - instant input voltage in adc discrete
  */
unsigned int  adc_values2[4];//adc value in the impedance measuring phase
//char adc_gain[4] = {16, 16, 16, 16};
char adc_break[4];
//static float adc_zero_shift[4] = {1.08, 1.08, 1.08, 0.61};
//static float adc_zero_shift2[4] = {0.0, 0.0, 0.0, 0.0};
float adc_u1[4], adc_u2[4], adc_r[4];
float debug_float;

//char debug_str[16]*/

//#define MAIN_GAIN G_1
//#define AUX_GAIN  G_1
/*
//---------------------------------------------------------------------
// DEBUG function
//---------------------------------------------------------------------
float GetAdcVoltage(char ch)
{
  float val;
  // Vref = 2500.0 mV 
  // gain - коэфф. усиления АЦП
  float gain;
  switch(MAIN_GAIN)
  {
  case G_1: gain = 1; break;
  case G_2: gain = 2; break;
  case G_4: gain = 4; break;
  case G_8: gain = 8; break;
  case G_16: gain = 16; break;
  case G_32: gain = 32; break;
  case G_64: gain = 64; break;
  case G_128: gain = 128; break;
  };
  float K = 2500.0 / (gain * 0x00800000);
  signed int signed_code;
  signed_code = adc_values[ch] - 0x00800000;
  val = signed_code * K + adc_zero_shift[ch]; // for bipolar
  //return adc_code * K; // for uniipolar
  return -val;
}
*/

/* float GetRin(char ch)
{
  //aux gain = 2.0
  const float K = 2500.0 / (2.0 * 0x00800000);
  float r_in, u2;
  signed int signed_code;
  signed_code = adc_values2[ch] - 0x00800000;
  u2 = signed_code * K + adc_zero_shift2[ch];
  r_in = (u2 - adc_u1[ch]) / 210.0e-3;
  return r_in;
}  */

/*
void startAdcConvertion(char channel, char gain[4], long int polarity)
{
//writing operation to  the configuration register - 0x10
  WriteByteToAllAdc(0x10);

//------------------Configuration register--------------------------------------
// bit 2 -0 /input/
// 000  Ain1+ - Ain1-
// 001  Ain2+ - Ain2-
// 010  Ain3+ - Ain3-
// 011  Ain1- - Ain1- (for zero calibration)
// 100 reserved
// 101 reserved
// 110 Temp sensor
// 111 AVdd monitor
  
// bit3 = 0
// bit 4 - buffer
// bit 5, 6 = 0
// bit 7 - reference; 1 - internal. 0 - external
  
//  bit10 - 8 /gain/
//     gain  range (Vref = 2500 mV)
// 000 - 1   2500 mV (in amp not used)
// 001 - 2   1250 mV (in amp not used)
// 010 - 4   625 mV
// 011 - 8   312,5 mV
// 100 - 16  156,25 mV
// 101 - 32  78,125 mV
// 110 - 64  39,06 mV
// 111 - 128 19,53 mV
  
//  bit 11 - Boost
//  bit 12 - 1 - unipolar; 0 - bipolar
//  bit 13 - Burnout
//  bit 15, 14 - Bias
//    00 - Bias disabled
//    01 - Bias connected to Ain1-
//    10 - Bias connected to Ain2-
//    11 - Reserved
//------------------------------------------------------------------------------
//configuration register - 0x0300
// channel, Ref = ext, G = gain, Boost = 0, polarity, Burnout = 0, No bias;
*/
void startAdcConvertion(char adc_chan, char channel, char gain, long int polarity)
{
  char conf_m_byte, conf_l_byte;
  //writing operation to  the configuration register - 0x10
  WriteByteToAdc(adc_chan, 0x10);

  conf_m_byte = gain | polarity;  //changed 0x48
  
  // bit_7 - internal reference
  // bit_4 - buffer
  conf_l_byte = (0x00 << 7) | /*(0x01 << 4)|*/ channel;                                  ////buffer off now
  
  WriteByteToAdc(adc_chan, conf_m_byte);
  WriteByteToAdc(adc_chan, conf_l_byte);

  WriteByteToAdc(adc_chan, 0x58); //Start convertion
}
//------------------------------------------------------------------------------
// Mode register
//
// MR15 - MR13 Mode select bit
// 000 - Continue convertion  mode
// 001 - Single convertion mode
// 010 - Idle mode
// 011 - Power down mode
// 100 - Internal zero-scale calibration 
// 101 - Full-scale calibration
// 110 - Sysyem zero-scale calibration
// 111 - Sysyem full-scale calibration
//
// MR12 - MR8 = 0
//
// MR7, MR6
// 00 - CLK mode; not used here, must be 0
//
// MR5, MR4 = 0
//------------------------------------------------------------------------------
// MR3 - MR0 Fadc t_settle, ms Rejection
//------------------------------------------------------------------------------
// 0000 -      x      x            x
// 0001 -     470     4            x
// 0010 -     242     8            x
// 0011 -     123    16            x
// 0100 -      62    32            x
// 0101 -      50    40            x
// 0110 -      39    48            x
// 0111 -      33.2  60            x
// 1000 -      19.6 101            60Hz
// 1001 -      16.7 120            50Hz
// 1010 -      16.7 120            50 & 60Hz
// 1011 -      12.5 160            50 & 60Hz
// 1100 -      10   200            50 & 60Hz
// 1101 -      8.33 240            50 & 60Hz
// 1110 -      6.25 320            50 & 60Hz
// 1111 -      4.17 480            50 & 60Hz
void setAdcMode(char adc_num, int mode)
{
  //writing operation to  the mode register - 0x08
  WriteByteToAdc(adc_num, 0x08);
  
  WriteByteToAdc(adc_num, (mode & 0xFF00) >> 8);
  WriteByteToAdc(adc_num, mode & 0x00FF);
}
/*
void setAdcMode(int mode)
{
  //writing operation to  the mode register - 0x08
  WriteByteToAllAdc(0x08);
  
  WriteByteToAllAdc((mode & 0xFF00) >> 8);
  WriteByteToAllAdc(mode & 0x00FF);
}*/

void setAdcModes(int mode[4])
{
  //writing operation to  the mode register - 0x08
 /* WriteByteToAdc(0x08);
  
  WriteByteToAllAdc((mode & 0xFF00) >> 8);
  WriteByteToAllAdc(mode & 0x00FF);
  */
  
//  void WriteByteToAdc(char bytes[4])
}
/*
void InitAdc(void)
{
  //Reset ADC
  for(char i = 0; i < 4; i++)
  {
    WriteByteToAdc(i, 0xFF);
    setAdcMode(i, 0x2002);//(0x0001);
    startAdcConvertion(i, 0, MAIN_GAIN, BIPOLAR);
  };
}
*/

void initAdc(char num)
{
  for (char i = 0; i < 4; i++)
  {
    WriteByteToAdc(num, 0xFF);
  };
  
  setAdcMode(num, 0x2002);                                                        // 
  startAdcConvertion(num, 1, aux_gains[num], UNIPOLAR);                           // newly added lines
  ResetTimer(ADC_TIME_OUT);                                                       //
  
  adc_state[num] = 0;                                                             //  changed from  adc_state[num] = 3;
}

void initAdcFsm(void)
{
  ResetTimer(TIMER_ADC_RESET);
  for(char i = 0; i < 4; i++)
    initAdc(i);
}

#define CURR_MODE1 (0 << 2)
#define CURR_MODE2 (1 << 2)
#define CURR_OUT1  (2 << 2)
#define CURR_OUT2  (3 << 2)

#define CURR_DIS  0
#define _10uA     1
#define _210uA    2
#define _1mA      3

#define CURR_AUX_MODE (CURR_MODE1)// | _10uA)
#define CURR_MAIN_MODE (CURR_MODE1 | CURR_DIS)
//------------------------------------------------------------------------------
// IO1, IO0
//---------------------
//       00 - current disabled
//       01 - 10 uA
//       10 - 210 uA
//       11 - 1 mA
//
//------------------------
// IO3, IO2
//------------------------
//       00 - source 1  -> out 1; source 2  -> out 2
//       01 - source 1  -> out 2; source 2  -> out 1
//       10 - both sources are connected to the out 1 (only for 10 & 210 uA)
//       11 - both sources are connected to the out 2 (only for 10 & 210 uA)
//
// IO7 - IO4 must be zeros
/*
void AdcCurrOut(char curr_mode)
{
//writing operation to  the IO register - 0x28
  WriteByteToAllAdc(0x28);
  WriteByteToAllAdc(curr_mode);
}
*/
//char debug, tgl_flag = 0;
unsigned long int Mid(unsigned long int val1, 
                      unsigned long int val2,
                      unsigned long int val3)
{
  if(((val1 >= val2) && (val1 <= val3)) ||
     ((val1 >= val3) && (val1 <= val2))) return val1;

  if(((val2 >= val1) && (val2 <= val3)) ||
     ((val2 >= val3) && (val2 <= val1))) return val2;
  
  return val3;
}

/*
#define SYS_ADC0_CLK  2
#define SYS_ADC1_CLK  3
#define SYS_ADC2_CLK  4
#define SYS_ADC3_CLK  5
#define SYS_ADC_MOSI  6
#define SYS_RES0      7
*/
void ProcessAdc(void)
{
  unsigned long int code;
  //----------------------------------------------------------------------------
  long adcResetTime;
  adcResetTime = 1; // temp; change from: GetIntValueByTag(ADC_RESET_TIME);
  if(adcResetTime != -1)
  {
    if(GetTimer(TIMER_ADC_RESET) > adcResetTime * minute)
    {
      ResetTimer(TIMER_ADC_RESET);
      for(char i = 0; i < 4; i++)
      {
        initAdc(i);
        ignore_cnt[i] = 1;  //ignore cycles counter
      };
    };
  };
  //----------------------------------------------------------------------------
  for(char i= 0; i < 4; i++)
  {
    switch(adc_state[i])
    {
    case 0:
      if(!GetAdcMiso(i))
      { 
        if(!ignore_cnt[i])
        {
          adc_values[0][i] = MIDCODE - GetAdcValue(i, adc_bits[i]);
        }
        else
        {
          GetAdcValue(i, adc_bits[i]);
          --ignore_cnt[i];
        };
        code = Mid(adc_values[0][i], adc_values[1][i], adc_values[2][i]);// | (gains[main_gains[i]] << 24);
         
        SetIntValueByTag(tag_0[i], code);
        // preparing to next convertion cycle  
        setAdcMode(i, 0x2002);
        startAdcConvertion(i, 1, aux_gains[i], UNIPOLAR);                        // changed from: startAdcConvertion(i, 1, aux_gains[i], BIPOLAR); 
        ResetTimer(ADC_TIME_OUT);
        adc_state[i] = 1;
        
        //-------------------------------------------------------
        for(int j = 0; j < 4; j++)
        {
          adc_values[2][j] = adc_values[1][j];
          adc_values[1][j] = adc_values[0][j];
        };
        //-------------------------------------------------------  
        // unsigned int upThrs[4] = {15800, 15800, 15800, 15800};
        // unsigned int downThrs[4] = {1024, 1024, 1024, 1024};
        /*
        if(autoRangeAllowed[i] && (code < upThrs[i]) && (main_gains[i] < G_16))
        {
          ++main_gains[i];
       //   adc_state[i] = 3;
        };
        if(autoRangeAllowed[i] && (code > downThrs[i]) && (main_gains[i] > G_1))
        {
          --main_gains[i];
        //  adc_state[i] = 3;
        };*/
      }
      else
      {
        if(GetTimer(ADC_TIME_OUT) > 50)
        {
          adc_state[i] = 2;  //reset
        };
      };
      break;
    case 1: //check if input wires are disconnected 
      if(!GetAdcMiso(i))
      {   
        //-------------------------------------------------------
        code = GetAdcValue(i, adc_bits[i]);                                             
        SetIntValueByTag(tag_1[i], code);//adc_values[i]);
        //-------------------------------------------------------
        // preparing to next convertion cycle  
        setAdcMode(i, main_modes[i]);
        // startAdcConvertion(i, 0x06, main_gains[i], UNIPOLAR);  //temperature snsor
        startAdcConvertion(i, 0, main_gains[i], BIPOLAR);
        ResetTimer(ADC_TIME_OUT);
        adc_state[i] = 0;
      }
      else
      {
        if(GetTimer(ADC_TIME_OUT) > 2)
        {
          adc_state[i] = 2;  //reset
        };
      };
      break;      
    case 2: // epic fail! reset ADCs!
      ResetTimer(ADC_TIME_OUT);
      initAdc(i);          //   adc_state[i] = 3;
      break;
    case 3:  //full-scale calibration  ???
      if(!GetAdcMiso(i))
      {
        ResetTimer(ADC_TIME_OUT);
        setAdcMode(i, 0xa00f);
     //   startAdcConvertion(i, 0, main_gains[i], UNIPOLAR); 
        //-------------------------
        // char conf_m_byte, conf_l_byte;
         //writing operation to  the configuration register - 0x10
            WriteByteToAdc(i, 0x10);
            /*
            conf_m_byte = main_gains[i] | UNIPOLAR;  //changed 0x48
  
            // bit_7 - internal reference
            // bit_4 - buffer
            conf_l_byte = (0x01 << 7) | i;
            */
            WriteByteToAdc(i, main_gains[i] | BIPOLAR);  //conf_m_byte
            WriteByteToAdc(i, (0x00 << 7));  //ref_sel = external         //conf_l_byte

            WriteByteToAdc(i, 0x70); //Start convertion
        //-------------------------
        
        adc_state[i] = 4;
      }
      else
      {
        if(GetTimer(ADC_TIME_OUT) > 100)
        {
          adc_state[i] = 2;  //reset
        };
      }
      break;
    case 4:  //zero-scale calibration
      if(!GetAdcMiso(i))
      {
        GetAdcValue(i, adc_bits[i]);
        ResetTimer(ADC_TIME_OUT);
        // preparing to next convertion cycle  
        setAdcMode(i, main_modes[i]);
        startAdcConvertion(i, 0, main_gains[i], UNIPOLAR);
        adc_state[i] = 0;
      }
      else
      {
        if(GetTimer(ADC_TIME_OUT) > 100)
        {
          adc_state[i] = 2;  //reset
        };
      }
      break;    
    };
  };
}

























#if 0                                                                                            //old version
void ProcessAdc(void)
{
  char aux_gains[4] = {AUX_GAIN, AUX_GAIN, AUX_GAIN, AUX_GAIN};
  char main_gains[4] = {G_1, G_1, G_1, G_1};
  switch(adc_state)
  {
    case 0: 
      if(RdyIsLow())
      {   
     //   ResetTimer(ADC_CONV_TIMER);
     //   ResetTimer(ADC_TIME_OUT);
        GetAdcValue(adc_values);

        SetIntValueByTag(ADC_1, Mid(adc_values[0], adc_values_1[0], adc_values_2[0]));
        SetIntValueByTag(ADC_2, Mid(adc_values[1], adc_values_1[1], adc_values_2[1]));
        SetIntValueByTag(ADC_3, Mid(adc_values[2], adc_values_1[2], adc_values_2[2]));
        SetIntValueByTag(ADC_4, Mid(adc_values[3], adc_values_1[3], adc_values_2[3]));
           
        // preparing to next convertion cycle  
        setAdcMode(0x2002);
        startAdcConvertion(1, aux_gains, BIPOLAR); 
       // ResetTimer(ADC_CONV_TIMER);
          
        adc_state = 1;
          
       //   sprintf(debug_str, "%d \n\r", adc_values[3]);
         // UART_PutStringByPolling(UART0, debug_str);
        //-------------------------------------------------------
        for(int i = 0; i < 4; i++)
        {
          adc_values_2[i] = adc_values_1[i];
          adc_values_1[i] = adc_values[i];
        };
        //-------------------------------------------------------        
      }
      else
        initAdc();
      break;
    case 1: //check if input wires are broken 
      if(RdyIsLow())
      {   
      //  ResetTimer(ADC_CONV_TIMER);
      //  ResetTimer(ADC_TIME_OUT);
        GetAdcValue(adc_values);
        //-------------------------------------------------------
        
        //-------------------------------------------------------
        SetIntValueByTag(ADC_1_, adc_values[0]);
        SetIntValueByTag(ADC_2_, adc_values[1]);
        SetIntValueByTag(ADC_3_, adc_values[2]);
        SetIntValueByTag(ADC_4_, adc_values[3]);
           
        // preparing to next convertion cycle  
        setAdcMode(0x2002);
        startAdcConvertion(0, main_gains, UNIPOLAR);
      //  ResetTimer(ADC_CONV_TIMER);
          
        adc_state = 0;
          
       //   sprintf(debug_str, "%d \n\r", adc_values[3]);
       // UART_PutStringByPolling(UART0, debug_str);
      }
      else
        InitAdc();
      break;      
/*    case 2: // epic fail! reset ADCs!
      ResetTimer(ADC_CONV_TIMER); 
      ResetTimer(ADC_TIME_OUT);
      InitAdc();
      adc_state = 0;
      break;*/

  };

}
#endif