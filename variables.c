#include <stdio.h>
#include <string.h>
#include "irq.h"
#include "dict.h"
#include "board.h"
#include "variables.h"
#include "messages.h"

#define DISABLE_INT NVIC_RIT

const T_DICT_VAR_DESCR dict_var_descrs[MAX_RECORD] = {
  //---------------------------------------------------------------------------------------------------------------
  // tag var_type io_type fram_addr      var_name    var_unit     def_val  min_val       after_point 
  //                               modbus_addr                                  max_val     edit_allowed
  //---------------------------------------------------------------------------------------------------------------
  //                                                                                           
  //Переменные настройки канала термостатирования                                         
  {EMPTY_CELL,          INT,   INTERNAL,  -1,  -1,  "",         "",             0.0,  0.0, 10000.0, 3, ACCESS_0},  //empty cell in table
  {BASE_T_L + SHIFT_T,  INT, INTERNAL,   0,  0,   "Shift_T",  "б/р",         55.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + K_CD_T,   FLOAT, INTERNAL,   1,  2,   "K_cd_T",   "E-6\x86\x43", 12.8,  0.0, 10000.0, 3, ACCESS_1}, //changed from "\x86\x43\x88\x65\x80"
  {BASE_T_L + T_F_T,    FLOAT, INTERNAL,   2,  4,   "T_f_T",    "-",            1.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + ADJ_S_T,  FLOAT, INTERNAL,   3,  6,   "t\x86зад.",  "\x86\x43",   600.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + K_P_T,    FLOAT, INTERNAL,   4,  8,   "K_p_T",    "-",            1.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + K_D_T,    FLOAT, INTERNAL,   5,  10,  "K_d_T",    "-",            1.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + T_DF_T,   FLOAT, INTERNAL,   6,  12,  "T_df_T",   "с",            1.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + KI_T,     FLOAT, INTERNAL,   7,  14,  "Ki_t",     "-",        26624.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + DISP_T,   FLOAT, INTERNAL,   8,  16,  "Disp_t",   "-",        26624.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + SM_T,     FLOAT, INTERNAL,   9,  18,  "Sm_t",     "-",        26624.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + K_CLC_T,  FLOAT, INTERNAL,  10,  20,  "K_clc_t",   "-",        26624.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + LIM_LO_T, INT,   INTERNAL,  11,  22,  "Lim_lo_t", "-",        26624.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + LIM_HI_T, INT,   INTERNAL,  12,  24,  "Lim_hi_t", "-",        26624.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + CEL_F_T,  FLOAT, INTERNAL,  -1,  26 , "Cel_f_t",         "-",         1.0,     0.0, 10000.0, 3, ACCESS_0},  //result 
  {CLC_LI_T_L,          INT,   INTERNAL,  -1,  -1, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},  //pwm code for the left channel
  {MISM_T_L,            FLOAT, INTERNAL,  -1,  28, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},   
  
  {CEL_T_L,             FLOAT, INTERNAL,  -1,  30, "Cel_t",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {T_T_L,               FLOAT, INTERNAL,  -1,  32, "tтп",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {U_T_L,               FLOAT, INTERNAL,  -1,  34, "Uвх",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {E_FF_D_L,            FLOAT, INTERNAL,  -1,  36, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {E_E_L,               FLOAT, INTERNAL,  -1,  38, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {MI_DC_T_L,           FLOAT, INTERNAL,  -1,  40, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {SK_INT_T_L,          FLOAT, INTERNAL,  -1,  42, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {L_COMP_T_L,          FLOAT, INTERNAL,  -1,  44, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {MI_P_T_L,            FLOAT, INTERNAL,  -1,  46, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {MI_KD_T_L,           FLOAT, INTERNAL,  -1,  48, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  
  {BASE_T_R + SHIFT_T,  INT, INTERNAL,  20,  50,  "Shift_T",  "-",            0.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + K_CD_T,   FLOAT, INTERNAL,  21,  52,  "K_cd_T",   "E-6\x86\x43", 12.8,  0.0, 10000.0, 3, ACCESS_1},  //changed from "\x86\x43\x88\x65\x80"
  {BASE_T_R + T_F_T,    FLOAT, INTERNAL,  22,  54,  "T_f_T",    "-",            1.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + ADJ_S_T,  FLOAT, INTERNAL,  23,  56,  "t\x86зад.",  "\x86\x43",   600.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + K_P_T,    FLOAT, INTERNAL,  24,  58,  "K_p_T",    "-",            1.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + K_D_T,    FLOAT, INTERNAL,  25,  60,  "K_d_T",    "-",             1.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + T_DF_T,   FLOAT, INTERNAL,  26,  62,  "T_df_T",   "с",             1.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + KI_T,     FLOAT, INTERNAL,  27,  64,  "Ki_t",     "-",         26624.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + DISP_T,   FLOAT, INTERNAL,  28,  66,  "Disp_t",   "-",         26624.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + SM_T,     FLOAT, INTERNAL,  29,  68,  "Sm_t",     "-",         26624.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + K_CLC_T,  FLOAT, INTERNAL,  30,  70,  "K_clc_t",   "-",         26624.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + LIM_LO_T, INT,   INTERNAL,  31,  72,  "Lim_lo_t", "-",         26624.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + LIM_HI_T, INT,   INTERNAL,  32,  74,  "Lim_hi_t", "-",         26624.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + CEL_F_T,  FLOAT, INTERNAL, - 1,  78, "Cel_f_t",         "-",         1.0,     0.0, 10000.0, 3, ACCESS_0},  //result
  {CLC_LI_T_R,          INT,   INTERNAL,  -1,  -1, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},  //pwm code for the right channel
  {MISM_T_R,            FLOAT, INTERNAL,  -1,  80, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  
  {CEL_T_R,             FLOAT,   INTERNAL,  -1,  82, "Cel_t",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {T_T_R,               FLOAT,   INTERNAL,  -1,  84, "tтп",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {U_T_R,               FLOAT,   INTERNAL,  -1,  86, "Uвх",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {E_FF_D_R,            FLOAT,   INTERNAL,  -1,  88, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {E_E_R,               FLOAT,   INTERNAL,  -1,  90, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {MI_DC_T_R,           FLOAT,   INTERNAL,  -1,  92, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {SK_INT_T_R,          FLOAT,   INTERNAL,  -1,  94, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {L_COMP_T_R,          FLOAT,   INTERNAL,  -1,  96, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {MI_P_T_R,            FLOAT,   INTERNAL,  -1,  98, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {MI_KD_T_R,           FLOAT,   INTERNAL,  -1,  100, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},
 
  {BASE_O2_L + SHIFT_E, INT, INTERNAL,  40,  200,  "Shift_K",  "-",         0.0,     0.0, 10000.0, 3, ACCESS_1},  //Переменные настройки канала кислорода
  {BASE_O2_L + K_CD_E,  FLOAT, INTERNAL,  41,  202,  "K_cd_E",   "мкВ",       3.46,    0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_L + T_F_E,   FLOAT, INTERNAL,  42,  204,  "Tфчэ",    "c",         1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_L + T_FF_T,  FLOAT, INTERNAL,  43,  206,  "T_ff_T",   "c",         1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_L + T_F_O,   FLOAT, INTERNAL,  44,  208,  "TфО",    "c",         1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_L + N,       INT,   INTERNAL,  45,  210,  "N",        "-",         0.0,     0.0, 5.0,     0, ACCESS_1},
  {BASE_O2_L + X1,      FLOAT, INTERNAL,  46,  212,  "X1",       "об.%",      6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_L + Y1,      FLOAT, INTERNAL,  47,  214,  "Y1",       "об.%",      6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_L + X2,      FLOAT, INTERNAL,  48,  216,  "X2",       "об.%",      10.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_L + Y2,      FLOAT, INTERNAL,  49,  218,  "Y2",       "об.%",      8.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_L + X3,      FLOAT, INTERNAL,  50,  220, "X3",       "об.%",      14.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_L + Y3,      FLOAT, INTERNAL,  51,  222, "Y3",       "об.%",      6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_L + X4,      FLOAT, INTERNAL,  52,  224, "X4",       "об.%",      17.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_L + Y4,      FLOAT, INTERNAL,  53,  226, "Y4",       "об.%",      6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_L + X5,      FLOAT, INTERNAL,  54,  228, "X5",       "об.%",      20.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_L + Y5,      FLOAT, INTERNAL,  55,  230, "Y5",       "об.%",      12.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_L + K_I_O,   FLOAT, INTERNAL,  56,  232, "K_i_0",    "1/мА",     200.0,   0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_L + SH_O,  INT,   INTERNAL,  57,  234, "Sh_0",   "-",         0.0,     0.0, 10000.0, 0, ACCESS_1},
  
  {BASE_O2_L + E_F_E,   FLOAT, INTERNAL,  -1,  236, "Uчэ",      "мв",       200.0,   0.0, 10000.0, 3, ACCESS_0},
  {BASE_O2_L + C_KL_O,  FLOAT, INTERNAL,  -1,  238, "O2,%",         "-",         1.0,     0.0, 10000.0, 2, ACCESS_0},  //o2 result
  {DEBUG_L,            INT,   INTERNAL,  -1,  -1, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  
  {BASE_O2_R + SHIFT_E, INT, INTERNAL,  70,  300,  "Shift_K",  "-",        0.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_R + K_CD_E,  FLOAT, INTERNAL,  71,  302,  "K_cd_E",   "мкВ",      3.46,    0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_R + T_F_E,   FLOAT, INTERNAL,  72,  304,  "Tфчэ",    "c",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_R + T_FF_T,  FLOAT, INTERNAL,  73,  306,  "T_ff_T",   "c",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_R + T_F_O,   FLOAT, INTERNAL,  74,  308,  "TфО",    "c",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_R + N,       INT,   INTERNAL,  75,  310,  "N",        "-",        0.0,     0.0, 5.0,     0, ACCESS_1},
  {BASE_O2_R + X1,      FLOAT, INTERNAL,  76,  312,  "X1",       "об.%",     6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + Y1,      FLOAT, INTERNAL,  77,  314,  "Y1",       "об.%",     6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + X2,      FLOAT, INTERNAL,  78,  316,  "X2",       "об.%",     10.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + Y2,      FLOAT, INTERNAL,  79,  318,  "Y2",       "об.%",     8.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + X3,      FLOAT, INTERNAL,  80,  320,  "X3",       "об.%",     14.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + Y3,      FLOAT, INTERNAL,  81,  322,  "Y3",       "об.%",     6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + X4,      FLOAT, INTERNAL,  82,  324,  "X4",       "об.%",     17.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + Y4,      FLOAT, INTERNAL,  83,  326,  "Y4",       "об.%",     6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + X5,      FLOAT, INTERNAL,  84,  328,  "X5",       "об.%",     20.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + Y5,      FLOAT, INTERNAL,  85,  330,  "Y5",       "об.%",     12.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + K_I_O,   FLOAT, INTERNAL,  86,  332,  "K_i_0",    "1/мА",   200.0,    0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_R + SH_O,  INT,   INTERNAL,  87,  334,  "Sh_0",   "-",         0.0,    0.0, 10000.0, 0, ACCESS_1},
  
  {BASE_O2_R + E_F_E,   FLOAT, INTERNAL,  -1,  336,  "Uчэ",      "мв",       200.0,   0.0, 10000.0, 3, ACCESS_0},
  {BASE_O2_R + C_KL_O,  FLOAT, INTERNAL,  -1,  338,  "O2,%",     "-",         1.0,    0.0, 10000.0, 3, ACCESS_0},  //o2 result  
  {DEBUG_R,            INT,   INTERNAL,  -1,  -1, "",    "-",        1.0,     0.0, 10000.0, 2, ACCESS_0},  
  
  {BASE_HN_L + T_F_H,   FLOAT, INTERNAL, 110,  400, "T_f_h",    "с",        1.0,     0.0, 10000.0, 3, ACCESS_1},  //Переменные настройки канала химнедожога
  {BASE_HN_L + T_FF_H,  FLOAT, INTERNAL, 111,  402, "T_ff_h",   "с",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_L + T_D_H,   FLOAT, INTERNAL, 112,  404, "T_d_h",    "c",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_L + K_R_H,   FLOAT, INTERNAL, 113,  406, "K_r_h",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_L + K_L_H,   FLOAT, INTERNAL, 114,  408, "K_l_h",    "-",        -1.0,    -10.0, 10.0,  3, ACCESS_1},
  {BASE_HN_L + LIM_H,   FLOAT, INTERNAL, 115,  410, "Огр.Х",    "мВ",       50.0,    0.0, 5.0,     3, ACCESS_1},
  {BASE_HN_L + KLIM_H,  FLOAT, INTERNAL, 116,  412, "KогрХ_h",   "%",       1.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + T_FD_H,  FLOAT, INTERNAL, 117,  414, "T_fd_h",   "с",        30.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_X0,   FLOAT, INTERNAL, 118,  416, "X0",      "-",        0.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_Y0,   FLOAT, INTERNAL, 119,  418, "Y0",      "-",        0.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_X1,   FLOAT, INTERNAL, 120,  420, "X1",      "-",        6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_Y1,   FLOAT, INTERNAL, 121,  422, "Y1",      "-",        6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_X2,   FLOAT, INTERNAL, 122,  424, "X2",      "-",        10.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_Y2,   FLOAT, INTERNAL, 123,  426, "Y2",      "-",        8.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_X3,   FLOAT, INTERNAL, 124,  428, "X3",      "-",        14.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_Y3,   FLOAT, INTERNAL, 125,  430, "Y3",      "-",        6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_X4,   FLOAT, INTERNAL, 126,  432, "X4",      "-",        17.0,    0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_L + HN_Y4,   FLOAT, INTERNAL, 127,  434, "Y4",      "-",        6.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_L + K_I_H,   FLOAT, INTERNAL, 128,  440, "K_i_h",   "1/мА",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_L + SH_H,    INT,   INTERNAL, 129,  442, "Sh_h",    "-",        0.0,     0.0, 10000.0, 0, ACCESS_1},
  {BASE_HN_L + C_KL_HN, FLOAT, INTERNAL,  -1,  444, "",        "-",        1.0,     0.0, 10000.0, 0, ACCESS_0},  //hn right
  {BASE_HN_L + CHUV_HN, FLOAT, INTERNAL, 130,  446, "",        "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},
  {DEBUG_H_R,           INT,   INTERNAL,  -1,   -1, "",        "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, //dac code for the HN left channel
  
  {BASE_HN_R + T_F_H,   FLOAT, INTERNAL, 150,  500, "T_f_h",    "с",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_R + T_FF_H,  FLOAT, INTERNAL, 151,  502, "T_ff_h",   "с",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_R + T_D_H,   FLOAT, INTERNAL, 152,  504, "T_d_h",    "c",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_R + K_R_H,   FLOAT, INTERNAL, 153,  506, "K_r_h",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_R + K_L_H,   FLOAT, INTERNAL, 154,  508, "K_l_h",    "-",        -1.0,    -10.0, 10.0,  3, ACCESS_1},
  {BASE_HN_R + LIM_H,   FLOAT, INTERNAL, 155,  510, "Огр.Х",    "мВ",       50.0,    0.0, 5.0,     3, ACCESS_1},
  {BASE_HN_R + KLIM_H,  FLOAT, INTERNAL, 156,  512, "KогрХ",    "%",        1.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + T_FD_H,  FLOAT, INTERNAL, 157,  514, "T_fd_h",   "с",        30.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_X0,   FLOAT, INTERNAL, 158,  516, "X0",       "-",        0.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_Y0,   FLOAT, INTERNAL, 159,  518, "Y0",       "-",        0.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_X1,   FLOAT, INTERNAL, 160,  520, "X1",       "-",        6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_Y1,   FLOAT, INTERNAL, 161,  522, "Y1",       "-",        6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_X2,   FLOAT, INTERNAL, 162,  524, "X2",       "-",        10.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_Y2,   FLOAT, INTERNAL, 163,  526, "Y2",       "-",        8.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_X3,   FLOAT, INTERNAL, 164,  528, "X3",       "-",        14.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_Y3,   FLOAT, INTERNAL, 165,  530, "Y3",       "-",        6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_X4,   FLOAT, INTERNAL, 166,  532, "X4",       "-",        17.0,    0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_R + HN_Y4,   FLOAT, INTERNAL, 167,  534, "Y4",       "-",        6.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_R + K_I_H,   FLOAT, INTERNAL, 168,  540, "K_i_h",    "1/мА",     1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_R + SH_H,    INT,   INTERNAL, 169,  542, "Sh_h",     "-",        0.0,     0.0, 10000.0, 0, ACCESS_1},
  {BASE_HN_R + C_KL_HN, FLOAT, INTERNAL,  -1,  544, "",         "-",        1.0,     0.0, 10000.0, 0, ACCESS_1},  //hn right 
  {BASE_HN_R + CHUV_HN, FLOAT, INTERNAL, 170,  546, "",         "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},
  {DEBUG_H_R,           INT,   INTERNAL,  -1,   -1, "",         "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, //dac code for the HN left channel
  
  {T_CL_E,              FLOAT, INTERNAL,  -1,  800, "Тхк",      "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},  //cold junction temp  
  {ADC_1,               INT,   IN,        -1,  900, "АЦП1",      "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {ADC_2,               INT,   IN,        -1,  902, "АЦП2",      "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {ADC_3,               INT,   IN,        -1,  904, "АЦП3",         "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {ADC_4,               INT,   IN,        -1,  906,  "АЦП4",         "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {ADC_1_,              INT,   IN,        -1,  908,  "",         "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {ADC_2_,              INT,   IN,        -1,  910,  "",         "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {ADC_3_,              INT,   IN,        -1,  912,  "",         "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {ADC_4_,              INT,   IN,        -1,  914,  "",         "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {CHANNEL_STATE_L,     INT,   INTERNAL,  -1,  916, "L status", "",        0.0,     0.0, 2.0,     0, ACCESS_0},
  {CHANNEL_STATE_R,     INT,   INTERNAL,  -1,  918, "R status", "",        0.0,     0.0, 2.0,     0, ACCESS_0},
  {AN_OUT_1,            FLOAT, OUT,       -1,   -1, "Dac1",    "мА",       0.0,     0.0, 10000.0, 2, ACCESS_0},
  {AN_OUT_2,            FLOAT, OUT,       -1,   -1, "Dac2",    "мА",       0.0,     0.0, 10000.0, 2, ACCESS_0},
  {AN_OUT_3,            FLOAT, OUT,       -1,   -1, "Dac3",    "мА",       0.0,     0.0, 10000.0, 2, ACCESS_0},
  {AN_OUT_4,            FLOAT, OUT,       -1,   -1, "Dac4",    "мА",       0.0,     0.0, 10000.0, 2, ACCESS_0},
  {DAC_1,               INT,   OUT,       -1,   -1, "код DAC1",    "",       0.0,     0.0, 10000.0, 2, ACCESS_0},
  {DAC_2,               INT,   OUT,       -1,   -1, "код DAC2",    "",       0.0,     0.0, 10000.0, 2, ACCESS_0},
  {DAC_3,               INT,   OUT,       -1,   -1, "код DAC3",    "",       0.0,     0.0, 10000.0, 2, ACCESS_0},
  {DAC_4,               INT,   OUT,       -1,   -1, "код DAC4",    "",       0.0,     0.0, 10000.0, 2, ACCESS_0},   
  {PWM_1,               INT,   OUT,       -1,   -1, "PWM_1",    "",       0.0,     0.0, 10000.0, 2, ACCESS_0},
  {PWM_2,               INT,   OUT,       -1,   -1, "PWM_2",    "",       0.0,     0.0, 10000.0, 2, ACCESS_0},
  {HEATER_STATE_L,      BOOLEAN, IN,      -1,  1000, "Обрыв Л.",  "",        0.0,     0.0, 1.0, 0, ACCESS_0},  //обрыв цепи нагревателей
  {HEATER_STATE_R,      BOOLEAN, IN,      -1,  1002, "Обрыв П.",  "",        0.0,     0.0, 1.0, 0, ACCESS_0},
  {HEATER_OVERLOAD_L,   BOOLEAN, IN,      -1,  1004, "Перегр.Л.",  "",        0.0,     0.0, 1.0, 0, ACCESS_0},
  {HEATER_OVERLOAD_R,   BOOLEAN, IN,      -1,  1006, "Перегр.П.",  "",        0.0,     0.0, 1.0, 0, ACCESS_0},
  {FLT_CH_L,            BOOLEAN, INTERNAL,  -1, 1480, "", "", 0.0, 0.0, 0.0, 0, ACCESS_0}, 
  {FLT_CH_R,            BOOLEAN, INTERNAL,  -1, 1482, "", "", 0.0, 0.0, 0.0, 0, ACCESS_0},
  {FLT_TP_L,            BOOLEAN, INTERNAL,  -1, 1484, "", "", 0.0, 0.0, 0.0, 0, ACCESS_0},
  {FLT_TP_R,            BOOLEAN, INTERNAL,  -1, 1486, "", "", 0.0, 0.0, 0.0, 0, ACCESS_0},
  {FLT_NE_L,            BOOLEAN, INTERNAL,  -1, 1488, "", "", 0.0, 0.0, 0.0, 0, ACCESS_0},
  {FLT_NE_R,            BOOLEAN, INTERNAL,  -1, 1490, "", "", 0.0, 0.0, 0.0, 0, ACCESS_0},
  {FLT_GA_L,            BOOLEAN, INTERNAL,  -1, 1492, "", "", 0.0, 0.0, 0.0, 0, ACCESS_0},
  {FLT_GA_R,            BOOLEAN, INTERNAL,  -1, 1494, "", "", 0.0, 0.0, 0.0, 0, ACCESS_0},
  {THR_H_L,             FLOAT,   INTERNAL, 180, 1496, "Пор.Х",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},     //left hn treshold 
  {THR_H_R,             FLOAT,   INTERNAL, 181, 1498, "Пор.Х",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},     //right hn treshold 
  {THR_O_L,             FLOAT,   INTERNAL, 182, 1500, "Пор.О",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},     //left o2 treshold 
  {THR_O_R,             FLOAT,   INTERNAL, 183, 1502, "Пор.О",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},     //right o2 treshold 
  {G_TH_H_L,            FLOAT,   INTERNAL, 184, 1504, "Гист.Х",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},    //left hn hysteresis 
  {G_TH_H_R,            FLOAT,   INTERNAL, 185, 1506, "Гист.Х",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},    //right hn hysteresis
  {G_TH_O_L,            FLOAT,   INTERNAL, 186, 1508, "Гист.О",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},    //left o2 hysteresis
  {G_TH_O_R,            FLOAT,   INTERNAL, 187, 1510, "Гист.О",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},    //right o2 hysteresis
  {FTH_H_L,             BOOLEAN, OUT,       -1, 1512, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},  //left hn treshold output
  {FTH_H_R,             BOOLEAN, OUT,       -1, 1514, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1}, //right hn treshold output
  {FTH_O2_L,            BOOLEAN, OUT,       -1, 1516, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1}, //left o2 treshold output
  {FTH_O2_R,            BOOLEAN, OUT,       -1, 1518, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1}, //right o2 treshold output
  {RS_232_SPEED,        INT,     INTERNAL, 190,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {RS_232_EVEN,         BOOLEAN, INTERNAL, 191,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {RS_232_ODD,          BOOLEAN, INTERNAL, 192,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {RS_232_STOP,         INT,     INTERNAL, 193,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {RS_485_SPEED,        INT,     INTERNAL, 200,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {RS_485_EVEN,         BOOLEAN, INTERNAL, 201,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {RS_485_ODD,          BOOLEAN, INTERNAL, 202,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {RS_485_STOP,         INT,     INTERNAL, 203,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {RS_485_ADDR,         INT,     INTERNAL, 204,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {ETHERNET_IP_ADDR_0,  INT,     INTERNAL, 210,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {ETHERNET_IP_ADDR_1,  INT,     INTERNAL, 211,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {ETHERNET_IP_ADDR_2,  INT,     INTERNAL, 212,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {ETHERNET_IP_ADDR_3,  INT,     INTERNAL, 213,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {ETHERNET_IP_MASK_0,  INT,     INTERNAL, 214,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {ETHERNET_IP_MASK_1,  INT,     INTERNAL, 215,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {ETHERNET_IP_MASK_2,  INT,     INTERNAL, 216,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {ETHERNET_IP_MASK_3,  INT,     INTERNAL, 217,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {ETHERNET_IP_GATE_0,  INT,     INTERNAL, 218,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {ETHERNET_IP_GATE_1,  INT,     INTERNAL, 219,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {ETHERNET_IP_GATE_2,  INT,     INTERNAL, 220,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {ETHERNET_IP_GATE_3,  INT,     INTERNAL, 221,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {RELAY_OUT_0,         BOOLEAN, INTERNAL,  -1, 1520, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {RELAY_OUT_1,         BOOLEAN, INTERNAL,  -1, 1522, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {RELAY_OUT_2,         BOOLEAN, INTERNAL,  -1, 1524, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {RELAY_OUT_3,         BOOLEAN, INTERNAL,  -1, 1526, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {RELAY_OUT_4,         BOOLEAN, INTERNAL,  -1, 1528, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {RELAY_OUT_5,         BOOLEAN, INTERNAL,  -1, 1530, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {INPUT0_RESISTANCE_DETECTOR_LOW_THRESHOLD, INT, INTERNAL, 223, 1532, "In0_LoThr", "", 0.0, 0.0, 0.0, 0, ACCESS_1}, 
  {INPUT0_RESISTANCE_DETECTOR_HI_THRESHOLD,  INT, INTERNAL, 224, 1534, "In0_HiThr", "", 0.0, 0.0, 0.0, 0, ACCESS_1},
  {INPUT1_RESISTANCE_DETECTOR_LOW_THRESHOLD, INT, INTERNAL, 225, 1536, "In1_LoThr", "", 0.0, 0.0, 0.0, 0, ACCESS_1},
  {INPUT1_RESISTANCE_DETECTOR_HI_THRESHOLD,  INT, INTERNAL, 226, 1538, "In1_HiThr", "", 0.0, 0.0, 0.0, 0, ACCESS_1},
  {INPUT2_RESISTANCE_DETECTOR_LOW_THRESHOLD, INT, INTERNAL, 227, 1540, "In2_LoThr", "", 0.0, 0.0, 0.0, 0, ACCESS_1},
  {INPUT2_RESISTANCE_DETECTOR_HI_THRESHOLD,  INT, INTERNAL, 228, 1542, "In2_HiThr", "", 0.0, 0.0, 0.0, 0, ACCESS_1},
  {INPUT3_RESISTANCE_DETECTOR_LOW_THRESHOLD, INT, INTERNAL, 229, 1544, "In3_LoThr", "", 0.0, 0.0, 0.0, 0, ACCESS_1},
  {INPUT3_RESISTANCE_DETECTOR_HI_THRESHOLD,  INT, INTERNAL, 230, 1546, "In3_HiThr", "", 0.0, 0.0, 0.0, 0, ACCESS_1},
  {SCR_BACKLIGHT_TIME,  INT,     INTERNAL, 231,  -1, "откл.подсв", "мин",      0.0,     0.0, 0.0,     0, ACCESS_1},
  {PROTECT_RESET_TIME,  INT,     INTERNAL, 232,  -1, "сбр.защит",  "с",        0.0,     0.0, 0.0,     0, ACCESS_1},
  {PASS_RESET_TIME,     INT,     INTERNAL, 233,  -1, "сбр.пароля", "мин",      0.0,     0.0, 0.0,     0, ACCESS_1},
  {PWM0_ON,             BOOLEAN, INTERNAL, 234,  1600, "",         "",         0.0,     0.0, 0.0,     0, ACCESS_1},
  {PWM1_ON,             BOOLEAN, INTERNAL, 235,  1602, "",         "",         0.0,     0.0, 0.0,     0, ACCESS_1},
  {DEBUG_1,             FLOAT,   INTERNAL,  -1,  -1, "Debug 1",    "",         0.0,     0.0, 0.0,     0, ACCESS_0},
  {DEBUG_2,             FLOAT,   INTERNAL,  -1,  -1, "Debug 2",    "",         0.0,     0.0, 0.0,     0, ACCESS_0},
  {RELAY_OUT_TEST_FLAG, BOOLEAN, INTERNAL,  -1,  1800, "",           "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},
  {DAC_TEST_FLAG,       BOOLEAN, INTERNAL,  -1,  1802, "",           "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},
  {PWM_OUT_TEST_FLAG,   BOOLEAN, INTERNAL,  -1,  1804, "",           "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},
  {OUT_CALIBR_FLAG,     BOOLEAN, INTERNAL,  -1,  1806, "",           "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},
   
  {MAX_O2_L,            FLOAT,   INTERNAL,  236, 2000, "Max",       "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},     
  {MAX_O2_R,            FLOAT,   INTERNAL,  237, 2002, "Max",       "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {MAX_XH_L,            FLOAT,   INTERNAL,  238, 2004, "Max",       "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {MAX_XH_R,            FLOAT,   INTERNAL,  239, 2006, "Max",       "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
    
  {REPR_O2_L,           FLOAT,   INTERNAL,  240, 2044, "О2л",       "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {REPR_O2_R,           FLOAT,   INTERNAL,  241, 2046, "О2п",       "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {REPR_H_L,            FLOAT,   INTERNAL,  242, 2048, "ХНл",       "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {REPR_H_R,            FLOAT,   INTERNAL,  243, 2050, "ХНп",       "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
 // {EMPTY_CELL,          INT,     INTERNAL,  -1,  -1,  "",         "",             0.0,  0.0, 10000.0, 3, ACCESS_0}
};
/*
typedef struct T_DICT_ENTRY{
  T_VAR curr_val;
  T_VAR prev_val;
} T_DICT_ENTRY;
*/
T_VAR dict_vars[(sizeof dict_var_descrs) / (sizeof dict_var_descrs[0])];

volatile char dictLocked = 0;

char accessLevel = 0;
//------------------------------------------------------------------------------
//  Fram functions
//------------------------------------------------------------------------------

/*
void WriteIntToFram(unsigned int fram_add, unsigned int data);
void ReadIntFromFram(unsigned int fram_add, unsigned int *data);
*/
char* NotFound(void)
{
  return "nf";
};

void SetDefaultValues(void)
{
  lockDict();
 // NVIC_IntDisable(DISABLE_INT);
  
  if(accessLevel == ACCESS_2)
  {
    for(int i = 0; dict_var_descrs[i].tag != MAX_RECORD - 1; ++i)
      if(dict_var_descrs[i].fram_addr != -1)
      {
        switch(dict_var_descrs[i].var_type)
        {
        case INT:
          dict_vars[i].ival = (long)dict_var_descrs[i].def_val;                            //  check this!
          break;
        case FLOAT:
          dict_vars[i].fval = dict_var_descrs[i].def_val;
          break;
        };
      };
    SendMessage(MSG_VAR_CHANGED);
    SaveValuesToFram();
  };
  
 // NVIC_IntEnable(DISABLE_INT);
  unlockDict();
};

void LoadValuesFromFram(void)
{
 // NVIC_IntDisable(DISABLE_INT);
  lockDict();
  
  for(int i = 0; dict_var_descrs[i].tag != MAX_RECORD - 1; ++i)
    if(dict_var_descrs[i].fram_addr != -1)
    {
      ReadIntFromFram(dict_var_descrs[i].fram_addr,
                      &dict_vars[i].ival);
    };
  SendMessage(MSG_VAR_CHANGED);
  
 // NVIC_IntEnable(DISABLE_INT);
  unlockDict();
};

void SaveValuesToFram(void)
{
 // NVIC_IntDisable(DISABLE_INT);
  lockDict();
  
  for(int i = 0; dict_var_descrs[i].tag != MAX_RECORD - 1; ++i)
    if(dict_var_descrs[i].fram_addr != -1)
    {
      WriteIntToFram(dict_var_descrs[i].fram_addr, dict_vars[i].ival);
    };
  SendMessage(MSG_VAR_CHANGED);
  
 // NVIC_IntEnable(DISABLE_INT);
  unlockDict();
};

int GetIntValueByTag(int tag)
{
  return dict_vars[tag].ival;
};

float GetFloatValueByTag(int tag)
{
  return dict_vars[tag].fval;
};

char* GetNameByTag(int tag)
{
  return (char*) dict_var_descrs[tag].var_name;
};

char* GetUnitByTag(int tag)
{
  return (char*) dict_var_descrs[tag].var_unit;
};

T_VAR GetValueByTag(int tag)
{
  T_VAR value;
  
  NVIC_IntDisable(DISABLE_INT);
  
  value = dict_vars[tag];
  
  NVIC_IntEnable(DISABLE_INT);

  return value;
}; 

char GetTypeByTag(int tag)
{
  return dict_var_descrs[tag].var_type;
};

signed char GetStringByTag(int tag, char id, char* buff, char buf_size)
{
  char buffer[50];
  char j; //количество символов в строке
  
 // NVIC_IntDisable(DISABLE_INT);
  
  switch(id)
  {
  case ID_CURR_VAL:
    j = (dict_var_descrs[tag].var_type == INT?
         sprintf(buffer, "%d", dict_vars[tag].ival):
           sprintf(buffer, "%1.*f",                                      
                   dict_var_descrs[tag].after_point, 
                   dict_vars[tag].fval));
    break;
  case ID_MIN:
    j = (dict_var_descrs[tag].var_type == INT?
         sprintf(buffer, "%d", (int)dict_var_descrs[tag].min_val):
           sprintf(buffer, 
                   "%1.*f", 
                   dict_var_descrs[tag].after_point, 
                   dict_var_descrs[tag].min_val));                                 //check it, it may be wrong!
    break;
  case ID_MAX:
    j = (dict_var_descrs[tag].var_type == INT?
         sprintf(buffer, "%d", (int)dict_var_descrs[tag].max_val):
           sprintf(buffer, 
                   "%1.*f", 
                   dict_var_descrs[tag].after_point, 
                   dict_var_descrs[tag].max_val));                                 //check it, it may be wrong!
    break;    
  };
  if(j > buf_size)  //fail!
  {
    buff[0] = 0;
    return (signed char)-1;
  };
  strcpy(buff, buffer);
  
 // NVIC_IntEnable(DISABLE_INT);
  return 0; //normal
};

// this function assigns the value to the dictionary entry
//  if it is enabled by access level
void setTagValue_(int tag, T_VAR value, char accsessLevel)                       
{
//  NVIC_IntDisable(DISABLE_INT);
  lockDict();
  
  if (EditingEnabled(tag));//(accsessLevel && (accsessLevel >= dict_var_descrs[tag].access_level))
  {
    dict_vars[tag] = value;
    if(dict_var_descrs[tag].fram_addr != -1)
      WriteIntToFram(dict_var_descrs[tag].fram_addr, dict_vars[tag].ival); 
    SendMessage(MSG_VAR_CHANGED);  
  };
  
 // NVIC_IntEnable(DISABLE_INT);
  unlockDict();
}

void setTagValue(int tag, T_VAR value)
{
  setTagValue_(tag, value, accessLevel);
}

void SetIntValueByTag(const int tag, const int i_value)
{
  setTagValue(tag, ((T_VAR){.ival = i_value}));
};

void SetFloatValueByTag(const int tag, const float f_value)
{
  setTagValue(tag, ((T_VAR){.fval = f_value}));
};

void SetDefaulValueByTag(const int tag)
{
  SetFloatValueByTag(tag, dict_var_descrs[tag].def_val);
}
//------------------------------------------------------------------------------
signed int FindRecordByModbusAddr(int addr)
{
  int high = MAX_RECORD;
  int low = 0;
  int probe;
  char found;
  
  //NVIC_IntDisable(DISABLE_INT);
  lockDict();
  
  while(high - low > 1)
  {
    probe = (low + high) / 2;
    if(dict_var_descrs[probe].modbus_addr == -1)
    {
      found = false;
      for(probe = low + 1; probe < high; probe++)
      {
        if(dict_var_descrs[probe].modbus_addr > -1)
        {
          found = true;
          break;
        };
      };
    };
    if(!found) break;
    if(dict_var_descrs[probe].modbus_addr > addr)
      high = probe;
    else
      low = probe;
  };
  unlockDict();
  
  if(dict_var_descrs[low].modbus_addr == addr)
  {
  //  NVIC_IntEnable(DISABLE_INT);
    return low;
  };
  
//  NVIC_IntEnable(DISABLE_INT);
  return -1;
}

char GetDataByModbusAddr(int addr, unsigned short* data)
{
  int tag;
  
 // NVIC_IntDisable(DISABLE_INT);
  lockDict();
    
  if(!(addr%2))
  {
    tag = FindRecordByModbusAddr(addr);
    if(tag > -1)
    {
      *data = dict_vars[tag].ival;
      NVIC_IntEnable(DISABLE_INT);
      return 1; 
    };
  }
  else
  {
    tag = FindRecordByModbusAddr(addr - 1);
    if(tag > -1)
    {
      *data = dict_vars[tag].ival >> 16;
      NVIC_IntEnable(DISABLE_INT);
      return 2; 
    };
  };
  *data = 0;
  
 // NVIC_IntEnable(DISABLE_INT);
  unlockDict();
  return 0;
};

char SetDataByModbusAddr(int addr, unsigned short value)
{
  int tag;
  
 // NVIC_IntDisable(DISABLE_INT);
  lockDict();
    
  if(!(addr%2))
  {
    tag = FindRecordByModbusAddr(addr);
    if(tag > -1)
    {
      dict_vars[tag].ival = value;
      unlockDict();
    //  NVIC_IntEnable(DISABLE_INT);
      return 1;    
    };
  }
  else
  {
    tag = FindRecordByModbusAddr(addr - 1);
    if(tag > -1)
    {
      dict_vars[tag].ival = value;
      WriteIntToFram(dict_var_descrs[tag].fram_addr, dict_vars[tag].ival);
      SendMessage(MSG_VAR_CHANGED);
      unlockDict();
     // NVIC_IntEnable(DISABLE_INT);
      return 2;  
    };
  };
  
 // NVIC_IntEnable(DISABLE_INT);
  unlockDict();
  return 0;  
};
//------------------------------------------------------------------------------

void setAccessLevel(char level)
{
  accessLevel = level;
}

char EditingEnabled(int tag)
{
  return accessLevel && (accessLevel >= dict_var_descrs[tag].access_level);
}

char getAccessLevel(int tag)
{
  return dict_var_descrs[tag].access_level;
}

char getDictLocked(void)
{
  return dictLocked;
}

void lockDict(void)
{
  dictLocked = true;
 // __disable_interrupt();
};

void unlockDict(void)
{
  dictLocked = false;
 // __enable_interrupt();
};
