//------------------------------------------------------------------------------
// Модуль содержит объявления переменных
//------------------------------------------------------------------------------
#ifndef VARIABLES_h
#define VARIABLES_h

#include "dict.h"
/*
//------------------------------------------------------------------------------
// var_type
//------------------------------------------------------------------------------
#define INT   0
#define FLOAT 1

//------------------------------------------------------------------------------
// io_type
//------------------------------------------------------------------------------
#define IN  0
#define OUT 1
#define INTERNAL 2

typedef union 
{
  signed long ival;
  float fval;
} T_VAR;

typedef struct 
{
  int tag; //числовой идентификатор переменной
  char var_type;
  char io_type;
  int fram_addr;
  int modbus_addr;
  char[8] var_name; 
  char[8] var_unit; //название единицы измерения
  T_VAR def_val;
  T_VAR min_val;
  T_VAR max_val;
  char after_point; //знаков после запятой
  char access_level; //права доступа
} T_DICT_RECORD;
*/
//-----------------------------------------------
//  IDs for GetStringByTag
#define ID_VAR_NAME 0
#define ID_VAR_UNIT 1
#define ID_CURR_VAL 2
#define ID_MIN      3 
#define ID_MAX      4

//---------------------
// Access rights
#define ACCESS_0   0 //edit not allowed
#define ACCESS_1   1 //pass 1 and pass 2, setting default values disabled
#define ACCESS_2   2 //pass 2 only, setting default values enabled
#define MODBUS_ACCESS 255  //access by modbus

signed char GetStringByTag(int tag, char id, char* buff, char buf_size);
//-----------------------------------------------
#define EMPTY_CELL 0

//Переменные настройки канала термостатирования
#define BASE_T_L 1
#define BASE_T_R 37

#define SHIFT_T  0
#define K_CD_T   1
#define T_F_T    2
#define ADJ_S_T  3
#define K_P_T    4
#define K_D_T    5
#define T_DF_T   6
#define KI_T     7
#define DISP_T   8
#define SM_T     9
#define K_CLC_T  10
#define LIM_LO_T 11
#define LIM_HI_T 12

#define CEL_F_T  13
#define CLC_LI_T 14
#define MISM_T   15
#define CEL_T    16
#define T_T      17
#define U_T      18
#define E_FF_D   19
#define E_E      20
#define MI_DC_T  21
#define SK_INT_T 22
#define L_COMP_T 23
#define MI_P_T   24
#define MI_KD_T  25

#define DELTA_T_PLUS  26
#define DELTA_T_MINUS 27

#define RESERVED_T1  28
#define RESERVED_T2  29
#define RESERVED_T3  30
#define RESERVED_T4  31
#define RESERVED_T5  32
#define RESERVED_T6  33
#define RESERVED_T7  34
#define RESERVED_T8  35

#define SHIFT_T_L  (BASE_T_L + SHIFT_T)
#define K_CD_T_L   (BASE_T_L + K_CD_T)
#define T_F_T_L    (BASE_T_L + T_F_T)
#define ADJ_S_T_L  (BASE_T_L + ADJ_S_T)
#define K_P_T_L    (BASE_T_L + K_P_T)
#define K_D_T_L    (BASE_T_L + K_D_T)
#define T_DF_T_L   (BASE_T_L + T_DF_T)
#define KI_T_L     (BASE_T_L + KI_T)
#define DISP_T_L   (BASE_T_L + DISP_T)
#define SM_T_L     (BASE_T_L + SM_T)
#define K_CLC_T_L  (BASE_T_L + K_CLC_T)
#define LIM_LO_T_L (BASE_T_L + LIM_LO_T)
#define LIM_HI_T_L (BASE_T_L + LIM_HI_T)

#define CEL_F_T_L  (BASE_T_L + CEL_F_T)
#define CLC_LI_T_L (BASE_T_L + CLC_LI_T)
#define MISM_T_L   (BASE_T_R + MISM_T)

#define CEL_T_L   (BASE_T_L + CEL_T)
#define U_T_L      (BASE_T_L + U_T)
#define T_T_L      (BASE_T_L + T_T)
#define E_FF_D_L   (BASE_T_L + E_FF_D)
#define E_E_L      (BASE_T_L + E_E)
#define MI_DC_T_L  (BASE_T_L + MI_DC_T)
#define SK_INT_T_L (BASE_T_L + SK_INT_T)
#define L_COMP_T_L (BASE_T_L + L_COMP_T)
#define MI_P_T_L   (BASE_T_L + MI_P_T)
#define MI_KD_T_L  (BASE_T_L + MI_KD_T)

#define DELTA_T_PLUS_L  (BASE_T_L + DELTA_T_PLUS)                                             ///
#define DELTA_T_MINUS_L  (BASE_T_L + DELTA_T_MINUS)
#define RESERVED_T1_L  (BASE_T_L + RESERVED_T1)
#define RESERVED_T2_L  (BASE_T_L + RESERVED_T2)
#define RESERVED_T3_L  (BASE_T_L + RESERVED_T3)
#define RESERVED_T4_L  (BASE_T_L + RESERVED_T4)
#define RESERVED_T5_L  (BASE_T_L + RESERVED_T5)
#define RESERVED_T6_L  (BASE_T_L + RESERVED_T6)
#define RESERVED_T7_L  (BASE_T_L + RESERVED_T7)
#define RESERVED_T8_L  (BASE_T_L + RESERVED_T8)

#define SHIFT_T_R  (BASE_T_R + SHIFT_T)
#define K_CD_T_R   (BASE_T_R + K_CD_T)
#define T_F_T_R    (BASE_T_R + T_F_T)
#define ADJ_S_T_R  (BASE_T_R + ADJ_S_T)
#define K_P_T_R    (BASE_T_R + K_P_T)
#define K_D_T_R    (BASE_T_R + K_D_T)
#define T_DF_T_R   (BASE_T_R + T_DF_T)
#define KI_T_R     (BASE_T_R + KI_T)
#define DISP_T_R   (BASE_T_R + DISP_T)
#define SM_T_R     (BASE_T_R + SM_T)
#define K_CLC_T_R  (BASE_T_R + K_CLC_T)
#define LIM_LO_T_R (BASE_T_R + LIM_LO_T)
#define LIM_HI_T_R (BASE_T_R + LIM_HI_T)

#define CEL_F_T_R  (BASE_T_R + CEL_F_T)
#define CLC_LI_T_R (BASE_T_R + CLC_LI_T)
#define MISM_T_R   (BASE_T_R + MISM_T)

#define CEL_T_R   (BASE_T_R + CEL_T)
#define U_T_R      (BASE_T_R + U_T)
#define T_T_R      (BASE_T_R + T_T)
#define E_FF_D_R   (BASE_T_R + E_FF_D)
#define E_E_R      (BASE_T_R + E_E)
#define MI_DC_T_R  (BASE_T_R + MI_DC_T)
#define SK_INT_T_R (BASE_T_R + SK_INT_T)
#define L_COMP_T_R (BASE_T_R + L_COMP_T)
#define MI_P_T_R   (BASE_T_R + MI_P_T)
#define MI_KD_T_R  (BASE_T_R + MI_KD_T)

#define DELTA_T_PLUS_R  (BASE_T_R + DELTA_T_PLUS)                                             ///
#define DELTA_T_MINUS_R  (BASE_T_R + DELTA_T_MINUS)
#define RESERVED_T1_R  (BASE_T_R + RESERVED_T1)
#define RESERVED_T2_R  (BASE_T_R + RESERVED_T2)
#define RESERVED_T3_R  (BASE_T_R + RESERVED_T3)
#define RESERVED_T4_R  (BASE_T_R + RESERVED_T4)
#define RESERVED_T5_R  (BASE_T_R + RESERVED_T5)
#define RESERVED_T6_R  (BASE_T_R + RESERVED_T6)
#define RESERVED_T7_R  (BASE_T_R + RESERVED_T7)
#define RESERVED_T8_R  (BASE_T_R + RESERVED_T8)

//Переменные настройки канала кислорода
#define BASE_O2_L 73
#define BASE_O2_R 94

#define SHIFT_E  0
#define K_CD_E   1
#define T_F_E    2
#define T_FF_T   3
#define T_F_O    4
#define N        5
#define X1       6
#define Y1       7
#define X2       8
#define Y2       9
#define X3       10
#define Y3       11
#define X4       12
#define Y4       13
#define X5       14
#define Y5       15
#define K_I_O    16
#define SH_O   17

#define E_F_E    18
#define C_KL_O   19
#define DEBUG    20

#define SHIFT_E_L  (BASE_O2_L + SHIFT_E)
#define K_CD_E_L   (BASE_O2_L + K_CD_E)
#define T_F_E_L    (BASE_O2_L + T_F_E)
#define T_FF_T_L   (BASE_O2_L + T_FF_T)
#define T_F_O_L    (BASE_O2_L + T_F_O)
#define N_L        (BASE_O2_L + N)
#define X1_L       (BASE_O2_L + X1)
#define Y1_L       (BASE_O2_L + Y1)
#define X2_L       (BASE_O2_L + X2)
#define Y2_L       (BASE_O2_L + Y2)
#define X3_L       (BASE_O2_L + X3)
#define Y3_L       (BASE_O2_L + Y3)
#define X4_L       (BASE_O2_L + X4)
#define Y4_L       (BASE_O2_L + Y4)
#define X5_L       (BASE_O2_L + X5)
#define Y5_L       (BASE_O2_L + Y5)
#define K_I_O_L    (BASE_O2_L + K_I_O)
#define SH_O_L   (BASE_O2_L + SH_O)

#define E_F_E_L    (BASE_O2_L + E_F_E)
#define C_KL_O_L   (BASE_O2_L + C_KL_O)
#define DEBUG_L    (BASE_O2_L + DEBUG)

#define SHIFT_E_R  (BASE_O2_R + SHIFT_E)
#define K_CD_E_R   (BASE_O2_R + K_CD_E)
#define T_F_E_R    (BASE_O2_R + T_F_E)
#define T_FF_T_R   (BASE_O2_R + T_FF_T)
#define T_F_O_R    (BASE_O2_R + T_F_O)
#define N_R        (BASE_O2_R + N)
#define X1_R       (BASE_O2_R + X1)
#define Y1_R       (BASE_O2_R + Y1)
#define X2_R       (BASE_O2_R + X2)
#define Y2_R       (BASE_O2_R + Y2)
#define X3_R       (BASE_O2_R + X3)
#define Y3_R       (BASE_O2_R + Y3)
#define X4_R       (BASE_O2_R + X4)
#define Y4_R       (BASE_O2_R + Y4)
#define X5_R       (BASE_O2_R + X5)
#define Y5_R       (BASE_O2_R + Y5)
#define K_I_O_R    (BASE_O2_R + K_I_O)
#define SH_O_R   (BASE_O2_R + SH_O)

#define E_F_E_R    (BASE_O2_R + E_F_E)
#define C_KL_O_R   (BASE_O2_R + C_KL_O)
#define DEBUG_R    (BASE_O2_R + DEBUG)

//Переменные настройки канала химнедожога
#define BASE_HN_L 115
#define BASE_HN_R 138

#define T_F_H    0
#define T_FF_H   1
#define T_D_H    2
#define K_R_H    3
#define K_L_H    4
#define LIM_H    5
#define KLIM_H   6
#define T_FD_H   7
#define HN_X0    8 
#define HN_Y0    9
#define HN_X1    10
#define HN_Y1    11
#define HN_X2    12
#define HN_Y2    13
#define HN_X3    14
#define HN_Y3    15
#define HN_X4    16
#define HN_Y4    17
#define K_I_H    18
#define SH_H   19
#define C_KL_HN  20  
#define CHUV_HN 21
#define DEBUG_HN  22

#define T_F_H_L    (BASE_HN_L + T_F_H)
#define T_FF_H_L   (BASE_HN_L + T_FF_H)
#define T_D_H_L    (BASE_HN_L + T_D_H)
#define K_R_H_L    (BASE_HN_L + K_R_H)
#define K_L_H_L    (BASE_HN_L + K_L_H)
#define LIM_H_L    (BASE_HN_L + LIM_H)
#define KLIM_H_L   (BASE_HN_L + KLIM_H)
#define T_FD_H_L   (BASE_HN_L + T_FD_H)
#define HN_X0_L    (BASE_HN_L + HN_X0)
#define HN_Y0_L    (BASE_HN_L + HN_Y0)
#define HN_X1_L    (BASE_HN_L + HN_X1)
#define HN_Y1_L    (BASE_HN_L + HN_Y1)
#define HN_X2_L    (BASE_HN_L + HN_X2)
#define HN_Y2_L    (BASE_HN_L + HN_Y2)
#define HN_X3_L    (BASE_HN_L + HN_X3)
#define HN_Y3_L    (BASE_HN_L + HN_Y3)
#define HN_X4_L    (BASE_HN_L + HN_X4)
#define HN_Y4_L    (BASE_HN_L + HN_Y4)
#define K_I_H_L    (BASE_HN_L + K_I_H)
#define SH_H_L     (BASE_HN_L + SH_H)
#define C_KL_HN_L     (BASE_HN_L + C_KL_HN)
#define CHUV_HN_L  (BASE_HN_L + CHUV_HN)
#define DEBUG_H_L    (BASE_HN_L + DEBUG_HN)

#define T_F_H_R    (BASE_HN_R + T_F_H)
#define T_FF_H_R   (BASE_HN_R + T_FF_H)
#define T_D_H_R    (BASE_HN_R + T_D_H)
#define K_R_H_R    (BASE_HN_R + K_R_H)
#define K_L_H_R    (BASE_HN_R + K_L_H)
#define LIM_H_R    (BASE_HN_R + LIM_H)
#define KLIM_H_R   (BASE_HN_R + KLIM_H)
#define T_FD_H_R   (BASE_HN_R + T_FD_H)
#define HN_X0_R    (BASE_HN_R + HN_X0)
#define HN_Y0_R    (BASE_HN_R + HN_Y0)
#define HN_X1_R    (BASE_HN_R + HN_X1)
#define HN_Y1_R    (BASE_HN_R + HN_Y1)
#define HN_X2_R    (BASE_HN_R + HN_X2)
#define HN_Y2_R    (BASE_HN_R + HN_Y2)
#define HN_X3_R    (BASE_HN_R + HN_X3)
#define HN_Y3_R    (BASE_HN_R + HN_Y3)
#define HN_X4_R    (BASE_HN_R + HN_X4)
#define HN_Y4_R    (BASE_HN_R + HN_Y4)
#define K_I_H_R    (BASE_HN_R + K_I_H)
#define SH_H_R     (BASE_HN_R + SH_H)
#define C_KL_HN_R  (BASE_HN_R + C_KL_HN)
#define CHUV_HN_R  (BASE_HN_R + CHUV_HN)
#define DEBUG_H_R    (BASE_HN_R + DEBUG_HN)

//----------------------------------------------
#define T_CL_E     161  //cold junction temp
// output dac and pwm codes
//#define CI_O_O_L 190  //dac code for the o2 left channel
//#define CI_O_O_R 192  //dac code for the o2 right channel

//----------------------------------------------
//adc_codes  (main channel)
#define ADC_1      162
#define ADC_2      163
#define ADC_3      164
#define ADC_4      165

//adc_codes  (second channel)
#define ADC_1_     166
#define ADC_2_     167
#define ADC_3_     168
#define ADC_4_     169
/*
//аналоговые входы, mV
#define AN_IN_1    250
#define AN_IN_2    251
#define AN_IN_3    252
#define AN_IN_4    253

//импедансы аналоговых входов, Ом
#define AN_R_1    254
#define AN_R_2    255
#define AN_R_3    256
#define AN_R_4    257
*/
#define CHANNEL_STATE_L 170  //1 - on, 0- off, 2 - fail
#define CHANNEL_STATE_R 171  //1 - on, 0- off, 2 - fail
//-------------------------
#define AN_OUT_1  172
#define AN_OUT_2  173
#define AN_OUT_3  174
#define AN_OUT_4  175

#define DAC_1     176
#define DAC_2     177
#define DAC_3     178
#define DAC_4     179

#define PWM_1     180
#define PWM_2     181

#define HEATER_STATE_L     182
#define HEATER_STATE_R     183
#define HEATER_OVERLOAD_L  184
#define HEATER_OVERLOAD_R  185

//failure signals
#define FLT_CH_L  186 //left sensor failure
#define FLT_CH_R  187 //right sensor failure
#define FLT_TP_L  188 //left thermocouple failure
#define FLT_TP_R  189 //right thermocouple failure
#define FLT_NE_L  190 //left heater failure
#define FLT_NE_R  191 //right heater failure
#define FLT_GA_L  192 //left general failure
#define FLT_GA_R  193 //right general failure

//tresholds (NVRAM vars)
#define THR_H_L   194  //left hn threshold 
#define THR_H_R   195  //right hn threshold 
#define THR_O_L   196  //left o2 threshold 
#define THR_O_R   197  //right o2 threshold 
#define G_TH_H_L  198  //left hn hysteresis 
#define G_TH_H_R  199  //right hn hysteresis
#define G_TH_O_L  200  //left o2 hysteresis
#define G_TH_O_R  201  //right o2 hysteresis

//treshold outputs
#define FTH_H_L   202  //left hn treshold output
#define FTH_H_R   203  //right hn treshold output
#define FTH_O2_L  204  //left o2 treshold output
#define FTH_O2_R  205  //right o2 treshold output

//------------------------------------------------------------------------------
#define RS_232_SPEED  206  //rs-232 speed
#define RS_232_EVEN   207  //rs-232 even
#define RS_232_ODD    208  //rs-232 odd
#define RS_232_STOP   209  //rs-232 stop bits

#define RS_485_SPEED  210  //rs-485 speed
#define RS_485_EVEN   211  //rs-485 even
#define RS_485_ODD    212  //rs-485 odd
#define RS_485_STOP   213  //rs-485 stop
#define RS_485_ADDR   214  //rs-485 addr

#define ETHERNET_IP_ADDR_0      215
#define ETHERNET_IP_ADDR_1      216
#define ETHERNET_IP_ADDR_2      217
#define ETHERNET_IP_ADDR_3      218

#define ETHERNET_IP_MASK_0      219
#define ETHERNET_IP_MASK_1      220
#define ETHERNET_IP_MASK_2      221
#define ETHERNET_IP_MASK_3      222

#define ETHERNET_IP_GATE_0      223
#define ETHERNET_IP_GATE_1      224
#define ETHERNET_IP_GATE_2      225
#define ETHERNET_IP_GATE_3      226

#define RELAY_OUT_0             227
#define RELAY_OUT_1             228
#define RELAY_OUT_2             229
#define RELAY_OUT_3             230
#define RELAY_OUT_4             231
#define RELAY_OUT_5             232
//--------------------------------------------
#define INPUT0_RESISTANCE_DETECTOR_LOW_THRESHOLD 233
#define INPUT0_RESISTANCE_DETECTOR_HI_THRESHOLD  234
#define INPUT1_RESISTANCE_DETECTOR_LOW_THRESHOLD 235
#define INPUT1_RESISTANCE_DETECTOR_HI_THRESHOLD  236
#define INPUT2_RESISTANCE_DETECTOR_LOW_THRESHOLD 237
#define INPUT2_RESISTANCE_DETECTOR_HI_THRESHOLD  238
#define INPUT3_RESISTANCE_DETECTOR_LOW_THRESHOLD 239
#define INPUT3_RESISTANCE_DETECTOR_HI_THRESHOLD  240

#define SCR_BACKLIGHT_TIME      241
#define PROTECT_RESET_TIME      242

#define PASS_RESET_TIME         243

#define PWM0_ON                 244
#define PWM1_ON                 245
 
#define DEBUG_1                 246
#define DEBUG_2                 247
//------------------------------------------------------------------------------
#define RELAY_OUT_TEST_FLAG     248
#define DAC_TEST_FLAG           249 // true if the dac test sreen is active
#define PWM_OUT_TEST_FLAG       250
#define OUT_CALIBR_FLAG         251

#define MAX_O2_L                252  
#define MAX_O2_R                253
#define MAX_XH_L                254
#define MAX_XH_R                255  
  
#define REPR_O2_L               256
#define REPR_O2_R               257
#define REPR_H_L                258
#define REPR_H_R                259

//------------------------------------------------------------------------------
#define MAX_RECORD              260

//#define MAX_RECORDS 500

//------------------------------------------------------------------------------
//  Modbus functions
//------------------------------------------------------------------------------
/*
  T_DICT_RECORD GetByModbusAddr(int mbaddr);
  int GetTypeByModbusAddr(int mbaddr);
  int GetIntValueByModbusAddr(int mbaddr);
  float GetFloatValueByModbusAddr(int mbaddr);
*/
  char GetDataByModbusAddr(int addr, unsigned short* data);
  char SetDataByModbusAddr(int addr, unsigned short value);
//------------------------------------------------------------------------------
//  Fram functions
//------------------------------------------------------------------------------
  void SetDefaultValues(void);
  void LoadValuesFromFram(void);
  void SaveValuesToFram(void);
 
  //-----------------------------------
  int GetNumberByTag(int tag);
  int GetIntValueByTag(int tag);
  float GetFloatValueByTag(int tag);
  T_VAR GetValueByTag(int tag);
  char GetTypeByTag(int tag);
 // T_DICT_RECORD GetVarByTag(int tag);
  signed char GetStringByTag(int tag, char id, char* buff, char buf_size);
  
//------------------------------------------------------------------------------
//  Common functions
//------------------------------------------------------------------------------  
  char* GetNameByTag(int tag);
  char* GetUnitByTag(int tag);
  
  void setTagValue(int tag, T_VAR value);
  void SetIntValueByTag(int tag, int i_value);
  void SetFloatValueByTag(int tag, float f_value);
  void SetDefaulValueByTag(int tag);
  
  void setAccessLevel(char level);
  char EditingEnabled(int tag);
  char getAccessLevel(int tag);
  //  #define MSG_VAR_CHANGED          10
  
  //shared access control
  char getDictLocked(void);
  void lockDict(void);
  void unlockDict(void);
//------------------------------------------------------------------------------
#endif
