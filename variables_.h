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
  char edit_allowed; //разрешено редактирование пользователем
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
#define ACCESS_1   1 //pass 1 and pass 2
#define ACCESS_2    2 //pass 2 only

signed char GetStringByTag(int tag, char id, char* buff, char buf_size);
//-----------------------------------------------
#define EMPTY_CELL 0

//Переменные настройки канала термостатирования
#define BASE_T_L 1
#define BASE_T_R 27

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
#define DEBUG0   16
#define DEBUG1   17
#define DEBUG2   18
#define E_FF_D   19
#define E_E      20
#define MI_DC_T  21
#define SK_INT_T 22
#define L_COMP_T 23
#define MI_P_T   24
#define MI_KD_T  25

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

#define DEBUG0_L   (BASE_T_L + DEBUG0)
#define DEBUG1_L   (BASE_T_L + DEBUG1)
#define DEBUG2_L   (BASE_T_L + DEBUG2)
#define E_FF_D_L   (BASE_T_L + E_FF_D)
#define E_E_L      (BASE_T_L + E_E)
#define MI_DC_T_L  (BASE_T_L + MI_DC_T)
#define SK_INT_T_L (BASE_T_L + SK_INT_T)
#define L_COMP_T_L (BASE_T_L + L_COMP_T)
#define MI_P_T_L   (BASE_T_L + MI_P_T)
#define MI_KD_T_L  (BASE_T_L + MI_KD_T)

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

#define DEBUG0_R   (BASE_T_R + DEBUG0)
#define DEBUG1_R   (BASE_T_R + DEBUG1)
#define DEBUG2_R   (BASE_T_R + DEBUG2)
#define E_FF_D_R   (BASE_T_R + E_FF_D)
#define E_E_R      (BASE_T_R + E_E)
#define MI_DC_T_R  (BASE_T_R + MI_DC_T)
#define SK_INT_T_R (BASE_T_R + SK_INT_T)
#define L_COMP_T_R (BASE_T_R + L_COMP_T)
#define MI_P_T_R   (BASE_T_R + MI_P_T)
#define MI_KD_T_R  (BASE_T_R + MI_KD_T)

//Переменные настройки канала кислорода
#define BASE_O2_L 53
#define BASE_O2_R 73

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
#define SH_4_O   17

#define C_KL_O   18
#define CI_O_O   19

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
#define SH_4_O_L   (BASE_O2_L + SH_4_O)

#define C_KL_O_L   (BASE_O2_L + C_KL_O)
#define CI_O_O_L   (BASE_O2_L + CI_O_O)

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
#define SH_4_O_R   (BASE_O2_R + SH_4_O)

#define C_KL_O_R   (BASE_O2_R + C_KL_O)
#define CI_O_O_R   (BASE_O2_R + CI_O_O)

//Переменные настройки канала химнедожога
#define BASE_HN_L 93
#define BASE_HN_R 115

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
#define SH_4_H   19
#define C_KL_HN  20  
#define CI_O_H   21

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
#define SH_4_H_L   (BASE_HN_L + SH_4_H)
#define C_KL_HN_L  (BASE_HN_L + C_KL_HN)
#define CI_O_H_L   (BASE_HN_L + CI_O_H)

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
#define SH_4_H_R   (BASE_HN_R + SH_4_H)
#define C_KL_HN_R  (BASE_HN_R + C_KL_HN)
#define CI_O_H_R   (BASE_HN_R + CI_O_H)

//----------------------------------------------
#define T_CL_E     137  //cold junction temp
// output dac and pwm codes
//#define CI_O_O_L 190  //dac code for the o2 left channel
//#define CI_O_O_R 192  //dac code for the o2 right channel

//----------------------------------------------
//adc_codes  (main channel)
#define ADC_1      138
#define ADC_2      139
#define ADC_3      140
#define ADC_4      141

//adc_codes  (second channel)
#define ADC_1_     142
#define ADC_2_     143
#define ADC_3_     144
#define ADC_4_     145
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
#define CHANNEL_STATE_L 146  //1 - on, 0- off, 2 - fail
#define CHANNEL_STATE_R 147  //1 - on, 0- off, 2 - fail
//-------------------------
#define AN_OUT_1  148
#define AN_OUT_2  149
#define AN_OUT_3  150
#define AN_OUT_4  151

#define DAC_1     152
#define DAC_2     153
#define DAC_3     154
#define DAC_4     155

#define PWM_1     156
#define PWM_2     157

#define HEATER_STATE_L     158
#define HEATER_STATE_R     159
#define HEATER_OVERLOAD_L  160
#define HEATER_OVERLOAD_R  161

//failure signals
#define FLT_CH_L  162 //left sensor failure
#define FLT_CH_R  163 //right sensor failure
#define FLT_TP_L  164 //left thermocouple failure
#define FLT_TP_R  165 //right thermocouple failure
#define FLT_NE_L  166 //left heater failure
#define FLT_NE_R  167 //right heater failure
#define FLT_GA_L  168 //left general failure
#define FLT_GA_R  169 //right general failure

//tresholds (NVRAM vars)
#define THR_H_L   170  //left hn threshold 
#define THR_H_R   171  //right hn threshold 
#define THR_O_L   172  //left o2 threshold 
#define THR_O_R   173  //right o2 threshold 
#define G_TH_H_L  174  //left hn hysteresis 
#define G_TH_H_R  175  //right hn hysteresis
#define G_TH_O_L  176  //left o2 hysteresis
#define G_TH_O_R  177  //right o2 hysteresis

//treshold outputs
#define FTH_H_L   178  //left hn treshold output
#define FTH_H_R   179  //right hn treshold output
#define FTH_O2_L  180  //left o2 treshold output
#define FTH_O2_R  181  //right o2 treshold output

//------------------------------------------------------------------------------
#define RS_232_SPEED  182  //rs-232 speed
#define RS_232_EVEN   183  //rs-232 even
#define RS_232_ODD    184  //rs-232 odd
#define RS_232_STOP   185  //rs-232 stop bits

#define RS_485_SPEED  186  //rs-485 speed
#define RS_485_EVEN   187  //rs-485 even
#define RS_485_ODD    188  //rs-485 odd
#define RS_485_STOP   189  //rs-485 stop
#define RS_485_ADDR   190  //rs-485 addr

#define ETHERNET_IP_ADDR_0      191
#define ETHERNET_IP_ADDR_1      192
#define ETHERNET_IP_ADDR_2      193
#define ETHERNET_IP_ADDR_3      194

#define ETHERNET_IP_MASK_0      195
#define ETHERNET_IP_MASK_1      196
#define ETHERNET_IP_MASK_2      197
#define ETHERNET_IP_MASK_3      198

#define ETHERNET_IP_GATE_0      199
#define ETHERNET_IP_GATE_1      200
#define ETHERNET_IP_GATE_2      201
#define ETHERNET_IP_GATE_3      202

#define RELAY_OUT_0             203
#define RELAY_OUT_1             204
#define RELAY_OUT_2             205
#define RELAY_OUT_3             206
#define RELAY_OUT_4             207
#define RELAY_OUT_5             208
//--------------------------------------------
#define INPUT0_RESISTANCE_DETECTOR_LOW_THRESHOLD 209
#define INPUT0_RESISTANCE_DETECTOR_HI_THRESHOLD  210
#define INPUT1_RESISTANCE_DETECTOR_LOW_THRESHOLD 211
#define INPUT1_RESISTANCE_DETECTOR_HI_THRESHOLD  212
#define INPUT2_RESISTANCE_DETECTOR_LOW_THRESHOLD 213
#define INPUT2_RESISTANCE_DETECTOR_HI_THRESHOLD  214
#define INPUT3_RESISTANCE_DETECTOR_LOW_THRESHOLD 215
#define INPUT3_RESISTANCE_DETECTOR_HI_THRESHOLD  216

#define SCR_BACKLIGHT_TIME   217
#define PROTECT_RESET_TIME   218

#define PASS_RESET_TIME      219

#define LEFT_CH_ON           220
#define RIGHT_CH_ON          221
  
#define DEBUG_1              222
#define DEBUG_2              223
//------------------------------------------------------------------------------
#define RELAY_OUT_TEST_FLAG  224
#define DAC_TEST_FLAG        225 // true if the dac test sreen is active
#define PWM_OUT_TEST_FLAG    226
//------------------------------------------------------------------------------
//  Калибровочные переменные каналов АЦП
//------------------------------------------------------------------------------
#define U_IN_1               227   //эдс 1-го канала (термопара)
//------------------------------------------------------------------------------
#define AUTO_RANGE_2         228   //автопереключене диапазонов 2-го канала
#define CURR_RANGE_2         229   //текущий диапазон 4-го канала
#define K_2_1                230   //коэфф. передачи 2-го канала, Ку = 1
#define K_2_2                231   //коэфф. передачи 2-го канала, Ку = 2
#define K_2_4                232   //коэфф. передачи 2-го канала, Ку = 4
#define K_2_8                233   //коэфф. передачи 2-го канала, Ку = 8
#define K_2_16               234   //коэфф. передачи 2-го канала, Ку = 16

#define SH_2_1               235   //смещение 2-го канала, Ку = 1
#define SH_2_2               236   //смещение 2-го канала, Ку = 2
#define SH_2_4               237   //смещение 2-го канала, Ку = 4
#define SH_2_8               238   //смещение 2-го канала, Ку = 8
#define SH_2_16              239   //смещение 2-го канала, Ку = 16

#define T_F_2                240   //постоянная времени фильтра 2-го канала

#define U_IN_2               241   //эдс 2-го канала
//------------------------------------------------------------------------------
#define U_IN_3               242   //эдс 3-го канала
//------------------------------------------------------------------------------
#define AUTO_RANGE_4         243   //автопереключене диапазонов 4-го канала
#define CURR_RANGE_4         244   //текущий диапазон 4-го канала
#define K_4_1                245   //коэфф. передачи 4-го канала, Ку = 1
#define K_4_2                246   //коэфф. передачи 4-го канала, Ку = 2
#define K_4_4                247   //коэфф. передачи 4-го канала, Ку = 4
#define K_4_8                248   //коэфф. передачи 4-го канала, Ку = 8
#define K_4_16               249   //коэфф. передачи 4-го канала, Ку = 16

#define SH_4_1               250   //смещение 4-го канала, Ку = 1
#define SH_4_2               251   //смещение 4-го канала, Ку = 2
#define SH_4_4               252   //смещение 4-го канала, Ку = 4
#define SH_4_8               253   //смещение 4-го канала, Ку = 8
#define SH_4_16              254   //смещение 4-го канала, Ку = 16

#define T_F_4                255   //постоянная времени фильтра 4-го канала

#define U_IN_4               256   //эдс 4-го канала
//------------------------------------------------------------------------------
#define RANGE_MAX_CODE       257   //код ADC, при котором происходит переход
                                   //на более высокий диапазон (меньший Ку)
#define RANGE_MIN_CODE       258   //код ADC, при котором происходит переход
                                   //на меньший диапазон (больший Ку)
//------------------------------------------------------------------------------
#define MAX_RECORD           259

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
 // void SaveAllChanges(void);
  //-----------------------------------
  int GetNumberByTag(int tag);
  int GetIntValueByTag(int tag);
  float GetFloatValueByTag(int tag);
  T_VAR GetValueByTag(int tag);
  char GetTypeByTag(int tag);
 // T_DICT_RECORD GetVarByTag(int tag);
  
//------------------------------------------------------------------------------
//  Common functions
//------------------------------------------------------------------------------  
  char* GetNameByTag(int tag);
  char* GetUnitByTag(int tag);
  
  void SetValueByTag(int tag, T_VAR value);
  void SetIntValueByTag(int tag, int value);
  void SetFloatValueByTag(int tag, float value);
  void SetDefaulValueByTag(int tag);
  //  #define MSG_VAR_CHANGED          10
//------------------------------------------------------------------------------
#endif
