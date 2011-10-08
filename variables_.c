#include <stdio.h>
#include <string.h>
#include "dict.h"
#include "board.h"
#include "variables.h"
#include "messages.h"

const T_DICT_VAR_DESCR dict_var_descrs[MAX_RECORD] = {
  //---------------------------------------------------------------------------------------------------------------
  // tag var_type io_type fram_addr      var_name    var_unit     def_val  min_val       after_point 
  //                               modbus_addr                                  max_val     edit_allowed
  //---------------------------------------------------------------------------------------------------------------
  //                                                                                           
  //Переменные настройки канала термостатирования                                         
  {EMPTY_CELL,          INT,   INTERNAL,  -1,  -1,  "",         "",             0.0,  0.0, 10000.0, 3, ACCESS_0},  //empty cell in table
  {BASE_T_L + SHIFT_T,  INT,   INTERNAL,   0,  0,   "Shift_T",  "б/р",         55.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + K_CD_T,   FLOAT, INTERNAL,   1,  2,   "K_cd_T",   "E-6\x86\x43", 12.8,  0.0, 10000.0, 3, ACCESS_1}, //changed from "\x86\x43\x88\x65\x80"
  {BASE_T_L + T_F_T,    FLOAT, INTERNAL,   2,  4,   "T_f_T",    "-",            1.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + ADJ_S_T,  FLOAT, INTERNAL,   3,  6,   "Adj_s_T",  "\x86\x43",   600.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + K_P_T,    FLOAT, INTERNAL,   4,  8,   "K_p_T",    "-",            1.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + K_D_T,    FLOAT, INTERNAL,   5,  10,  "K_d_T",    "-",            1.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + T_DF_T,   FLOAT, INTERNAL,   6,  12,  "T_df_T",   "с",            1.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + KI_T,     FLOAT, INTERNAL,   7,  14,  "Ki_t",     "-",        26624.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + DISP_T,   FLOAT, INTERNAL,   8,  16,  "Disp_t",   "-",        26624.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + SM_T,     FLOAT, INTERNAL,   9,  18,  "Sm_t",     "-",        26624.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + K_CLC_T,  FLOAT,   INTERNAL,  10,  20,  "K_clc_t",   "-",        26624.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + LIM_LO_T, INT,   INTERNAL,  11,  22,  "Lim_lo_t", "-",        26624.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + LIM_HI_T, INT,   INTERNAL,  12,  24,  "Lim_hi_t", "-",        26624.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_L + CEL_F_T,  FLOAT, INTERNAL,  -1,  26 , "",         "-",         1.0,     0.0, 10000.0, 3, ACCESS_1},  //result 
  {CLC_LI_T_L,          INT,   INTERNAL,  -1,  -1, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},  //pwm code for the left channel
  {MISM_T_L,            FLOAT,   INTERNAL,  -1,  28, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},   
  
  {DEBUG0_L,            FLOAT,   INTERNAL,  -1,  30, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {DEBUG1_L,            FLOAT,   INTERNAL,  -1,  32, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {DEBUG2_L,            FLOAT,   INTERNAL,  -1,  34, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {E_FF_D_L,            FLOAT,   INTERNAL,  -1,  36, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {E_E_L,               FLOAT,   INTERNAL,  -1,  38, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {MI_DC_T_L,           FLOAT,   INTERNAL,  -1,  40, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {SK_INT_T_L,          FLOAT,   INTERNAL,  -1,  42, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {L_COMP_T_L,          FLOAT,   INTERNAL,  -1,  44, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {MI_P_T_L,            FLOAT,   INTERNAL,  -1,  46, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {MI_KD_T_L,           FLOAT,   INTERNAL,  -1,  48, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  
  {BASE_T_R + SHIFT_T,  INT,   INTERNAL,  20,  50,  "Shift_T",  "-",            0.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + K_CD_T,   FLOAT, INTERNAL,  21,  52,  "K_cd_T",   "E-6\x86\x43", 12.8,  0.0, 10000.0, 3, ACCESS_1},  //changed from "\x86\x43\x88\x65\x80"
  {BASE_T_R + T_F_T,    FLOAT, INTERNAL,  22,  54,  "T_f_T",    "-",            1.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + ADJ_S_T,  FLOAT, INTERNAL,  23,  56,  "Adj_s_T",  "\x86\x43",   600.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + K_P_T,    FLOAT, INTERNAL,  24,  58,  "K_p_T",    "-",            1.0,  0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + K_D_T,    FLOAT, INTERNAL,  25,  60,  "K_d_T",    "-",             1.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + T_DF_T,   FLOAT, INTERNAL,  26,  62,  "T_df_T",   "с",             1.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + KI_T,     FLOAT, INTERNAL,  27,  64,  "Ki_t",     "-",         26624.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + DISP_T,   FLOAT, INTERNAL,  28,  66,  "Disp_t",   "-",         26624.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + SM_T,     FLOAT, INTERNAL,  29,  68,  "Sm_t",     "-",         26624.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + K_CLC_T,  FLOAT,   INTERNAL,  30,  70,  "K_clc_t",   "-",         26624.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + LIM_LO_T, INT,   INTERNAL,  31,  72,  "Lim_lo_t", "-",         26624.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + LIM_HI_T, INT,   INTERNAL,  32,  74,  "Lim_hi_t", "-",         26624.0, 0.0, 10000.0, 3, ACCESS_1},
  {BASE_T_R + CEL_F_T,  FLOAT, INTERNAL, - 1,  78, "",         "-",         1.0,     0.0, 10000.0, 3, ACCESS_1},  //result
  {CLC_LI_T_R,          INT,   INTERNAL,  -1,  -1, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},  //pwm code for the right channel
  {MISM_T_R,            FLOAT,   INTERNAL,  -1,  80, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  
  {DEBUG0_R,            FLOAT,   INTERNAL,  -1,  82, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {DEBUG1_R,            FLOAT,   INTERNAL,  -1,  84, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {DEBUG2_R,            FLOAT,   INTERNAL,  -1,  86, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {E_FF_D_R,            FLOAT,   INTERNAL,  -1,  88, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {E_E_R,               FLOAT,   INTERNAL,  -1,  90, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {MI_DC_T_R,           FLOAT,   INTERNAL,  -1,  92, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {SK_INT_T_R,          FLOAT,   INTERNAL,  -1,  94, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {L_COMP_T_R,          FLOAT,   INTERNAL,  -1,  96, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {MI_P_T_R,            FLOAT,   INTERNAL,  -1,  98, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, 
  {MI_KD_T_R,           FLOAT,   INTERNAL,  -1,  100, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},
 
  {BASE_O2_L + SHIFT_E, INT,   INTERNAL,  40,  200,  "Shift_K",  "-",         0.0,     0.0, 10000.0, 0, ACCESS_1},  //Переменные настройки канала кислорода
  {BASE_O2_L + K_CD_E,  FLOAT, INTERNAL,  41,  202,  "K_cd_E",   "мкВ",       3.46,    0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_L + T_F_E,   FLOAT, INTERNAL,  42,  204,  "T_f_E",    "c",         1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_L + T_FF_T,  FLOAT, INTERNAL,  43,  206,  "T_ff_T",   "c",         1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_L + T_F_O,   FLOAT, INTERNAL,  44,  208,  "T_f_0",    "c",         1.0,     0.0, 10000.0, 3, ACCESS_1},
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
  {BASE_O2_L + K_I_O,   FLOAT, INTERNAL,  56,  232, "K_i_0",    "1/об%",     200.0,   0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_L + SH_4_O,  INT,   INTERNAL,  57,  234, "Sh_4_0",   "-",         0.0,     0.0, 10000.0, 0, ACCESS_1},
  {BASE_O2_L + C_KL_O,  FLOAT, INTERNAL,  -1,  236, "",         "-",         1.0,     0.0, 10000.0, 2, ACCESS_1},  //o2 result
  {CI_O_O_L,            INT,   INTERNAL,  -1,  -1, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, //dac code for the o2 left channel  
  {BASE_O2_R + SHIFT_E, INT,   INTERNAL,  70,  238,  "Shift_K",  "-",        0.0,     0.0, 10000.0, 0, ACCESS_1},
  {BASE_O2_R + K_CD_E,  FLOAT, INTERNAL,  71,  240,  "K_cd_E",   "мкВ",      3.46,    0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_R + T_F_E,   FLOAT, INTERNAL,  72,  244,  "T_f_E",    "c",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_R + T_FF_T,  FLOAT, INTERNAL,  73,  246,  "T_ff_T",   "c",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_R + T_F_O,   FLOAT, INTERNAL,  74,  248,  "T_f_0",    "c",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_R + N,       INT,   INTERNAL,  75,  250,  "N",        "-",        0.0,     0.0, 5.0,     0, ACCESS_1},
  {BASE_O2_R + X1,      FLOAT, INTERNAL,  76,  252,  "X1",       "об.%",     6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + Y1,      FLOAT, INTERNAL,  77,  254,  "Y1",       "об.%",     6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + X2,      FLOAT, INTERNAL,  78,  256,  "X2",       "об.%",     10.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + Y2,      FLOAT, INTERNAL,  79,  258,  "Y2",       "об.%",     8.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + X3,      FLOAT, INTERNAL,  80,  260,  "X3",       "об.%",     14.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + Y3,      FLOAT, INTERNAL,  81,  262,  "Y3",       "об.%",     6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + X4,      FLOAT, INTERNAL,  82,  264,  "X4",       "об.%",     17.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + Y4,      FLOAT, INTERNAL,  83,  266,  "Y4",       "об.%",     6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + X5,      FLOAT, INTERNAL,  84,  268,  "X5",       "об.%",     20.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + Y5,      FLOAT, INTERNAL,  85,  270,  "Y5",       "об.%",     12.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_O2_R + K_I_O,   FLOAT, INTERNAL,  86,  272,  "K_i_0",    "1/об%",   200.0,    0.0, 10000.0, 3, ACCESS_1},
  {BASE_O2_R + SH_4_O,  INT,   INTERNAL,  87,  274,  "Sh_4_0",   "-",         0.0,    0.0, 10000.0, 0, ACCESS_1},
  {BASE_O2_R + C_KL_O,  FLOAT, INTERNAL,  -1,  276,  "",         "-",         1.0,    0.0, 10000.0, 3, ACCESS_1},  //o2 result  
  {CI_O_O_R,            INT,   INTERNAL,  -1,  -1, "",    "-",        1.0,     0.0, 10000.0, 2, ACCESS_0}, //dac code for the o2 right channel  
  {BASE_HN_L + T_F_H,   FLOAT, INTERNAL, 110,  300, "T_f_h",    "с",        1.0,     0.0, 10000.0, 3, ACCESS_1},  //Переменные настройки канала химнедожога
  {BASE_HN_L + T_FF_H,  FLOAT, INTERNAL, 111,  302, "T_ff_h",   "с",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_L + T_D_H,   FLOAT, INTERNAL, 112,  304, "T_d_h",    "c",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_L + K_R_H,   FLOAT, INTERNAL, 113,  306, "K_r_h",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_L + K_L_H,   FLOAT, INTERNAL, 114,  308, "K_l_h",    "-",        -1.0,    -10.0, 10.0,  3, ACCESS_1},
  {BASE_HN_L + LIM_H,   FLOAT, INTERNAL, 115,  310, "Lim_h",    "мВ",       50.0,    0.0, 5.0,     3, ACCESS_1},
  {BASE_HN_L + KLIM_H,  FLOAT, INTERNAL, 116,  312, "KLim_h",   "%",       1.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + T_FD_H,  FLOAT, INTERNAL, 117,  314, "T_fd_h",   "с",        30.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_X0,   FLOAT, INTERNAL, 118,  316, "X0",      "-",        0.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_Y0,   FLOAT, INTERNAL, 119,  318, "Y0",      "-",        0.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_X1,   FLOAT, INTERNAL, 120,  320, "X1",      "-",        6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_Y1,   FLOAT, INTERNAL, 121,  322, "Y1",      "-",        6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_X2,   FLOAT, INTERNAL, 122,  324, "X2",      "-",        10.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_Y2,   FLOAT, INTERNAL, 123,  326, "Y2",      "-",        8.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_X3,   FLOAT, INTERNAL, 124,  328, "X3",      "-",        14.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_Y3,   FLOAT, INTERNAL, 125,  330, "Y3",      "-",        6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_L + HN_X4,   FLOAT, INTERNAL, 126,  332, "X4",      "-",        17.0,    0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_L + HN_Y4,   FLOAT, INTERNAL, 127,  334, "Y4",      "-",        6.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_L + K_I_H,   FLOAT, INTERNAL, 128,  340, "K_i_h",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_L + SH_4_H,  INT,   INTERNAL, 129,  342, "Sh_4_h",   "-",        0.0,     0.0, 10000.0, 0, ACCESS_1},
  {BASE_HN_L + C_KL_HN, FLOAT, INTERNAL,  -1,  344, "",         "-",        1.0,     0.0, 10000.0, 0, ACCESS_1},  //hn right
  {BASE_HN_L + CI_O_H,  INT,   INTERNAL,  -1,   -1, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, //dac code for the HN left channel
  {BASE_HN_R + T_F_H,   FLOAT, INTERNAL, 150,  370, "T_f_h",    "с",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_R + T_FF_H,  FLOAT, INTERNAL, 151,  372, "T_ff_h",   "с",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_R + T_D_H,   FLOAT, INTERNAL, 152,  374, "T_d_h",    "c",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_R + K_R_H,   FLOAT, INTERNAL, 153,  376, "K_r_h",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_R + K_L_H,   FLOAT, INTERNAL, 154,  378, "K_l_h",    "-",        -1.0,    -10.0, 10.0,  3, ACCESS_1},
  {BASE_HN_R + LIM_H,   FLOAT, INTERNAL, 155,  380, "Lim_h",    "мВ",       50.0,    0.0, 5.0,     3, ACCESS_1},
  {BASE_HN_R + KLIM_H,  FLOAT, INTERNAL, 156,  382, "KLim_h",   "%",        1.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + T_FD_H,  FLOAT, INTERNAL, 157,  384, "T_fd_h",   "с",        30.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_X0,   FLOAT, INTERNAL, 158,  386, "X0",    "-",        0.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_Y0,   FLOAT, INTERNAL, 159,  388, "Y0",    "-",        0.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_X1,   FLOAT, INTERNAL, 160,  390, "X1",    "-",        6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_Y1,   FLOAT, INTERNAL, 161,  392, "Y1",    "-",        6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_X2,   FLOAT, INTERNAL, 162,  394, "X2",    "-",        10.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_Y2,   FLOAT, INTERNAL, 163,  396, "Y2",    "-",        8.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_X3,   FLOAT, INTERNAL, 164,  398, "X3",    "-",        14.0,    0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_Y3,   FLOAT, INTERNAL, 165,  400, "Y3",    "-",        6.0,     0.0, 100.0,   3, ACCESS_1},
  {BASE_HN_R + HN_X4,   FLOAT, INTERNAL, 166,  402, "X4",    "-",        17.0,    0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_R + HN_Y4,   FLOAT, INTERNAL, 167,  404, "Y4",    "-",        6.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_R + K_I_H,   FLOAT, INTERNAL, 168,  410, "K_i_h",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
  {BASE_HN_R + SH_4_H,  INT,   INTERNAL, 169,  412, "Sh_4_h",   "-",        0.0,     0.0, 10000.0, 0, ACCESS_1},
  {BASE_HN_R + C_KL_HN, FLOAT, INTERNAL,  -1,  414, "",         "-",        1.0,     0.0, 10000.0, 0, ACCESS_1},  //hn right    
  {BASE_HN_R + CI_O_H,  INT,   INTERNAL,  -1,   -1, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_0}, //dac code for the HN left channel
  {T_CL_E,              FLOAT, INTERNAL,  -1,  442, "",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},  //cold junction temp  
  {ADC_1,               INT,   IN,        -1,  450,  "",         "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {ADC_2,               INT,   IN,        -1,  452,  "",         "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {ADC_3,               INT,   IN,        -1,  454,  "",         "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {ADC_4,               INT,   IN,        -1,  456,  "",         "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {ADC_1_,              INT,   IN,        -1,  458,  "",         "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {ADC_2_,              INT,   IN,        -1,  460,  "",         "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {ADC_3_,              INT,   IN,        -1,  462,  "",         "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {ADC_4_,              INT,   IN,        -1,  464,  "",         "",         0.0,     0.0, 100.0,   2, ACCESS_0},
  {CHANNEL_STATE_L,     INT,   INTERNAL,  -1,  480, "L status", "",        0.0,     0.0, 2.0,     0, ACCESS_0},
  {CHANNEL_STATE_R,     INT,   INTERNAL,  -1,  482, "R status", "",        0.0,     0.0, 2.0,     0, ACCESS_0},
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
  {HEATER_STATE_L,      BOOLEAN, IN,      -1,  484, "Обрыв Л.",  "",        0.0,     0.0, 1.0, 0, ACCESS_0},  //обрыв цепи нагревателей
  {HEATER_STATE_R,      BOOLEAN, IN,      -1,  486, "Обрыв П.",  "",        0.0,     0.0, 1.0, 0, ACCESS_0},
  {HEATER_OVERLOAD_L,   BOOLEAN, IN,      -1,  488, "Перегр.Л.",  "",        0.0,     0.0, 1.0, 0, ACCESS_0},
  {HEATER_OVERLOAD_R,   BOOLEAN, IN,      -1,  490, "Перегр.П.",  "",        0.0,     0.0, 1.0, 0, ACCESS_0},
  {FLT_CH_L,            BOOLEAN, INTERNAL,  -1, 1480, "", "", 0.0, 0.0, 0.0, 0, ACCESS_1}, 
  {FLT_CH_R,            BOOLEAN, INTERNAL,  -1, 1482, "", "", 0.0, 0.0, 0.0, 0, ACCESS_1},
  {FLT_TP_L,            BOOLEAN, INTERNAL,  -1, 1484, "", "", 0.0, 0.0, 0.0, 0, ACCESS_1},
  {FLT_TP_R,            BOOLEAN, INTERNAL,  -1, 1486, "", "", 0.0, 0.0, 0.0, 0, ACCESS_1},
  {FLT_NE_L,            BOOLEAN, INTERNAL,  -1, 1488, "", "", 0.0, 0.0, 0.0, 0, ACCESS_1},
  {FLT_NE_R,            BOOLEAN, INTERNAL,  -1, 1490, "", "", 0.0, 0.0, 0.0, 0, ACCESS_1},
  {FLT_GA_L,            BOOLEAN, INTERNAL,  -1, 1492, "", "", 0.0, 0.0, 0.0, 0, ACCESS_1},
  {FLT_GA_R,            BOOLEAN, INTERNAL,  -1, 1494, "", "", 0.0, 0.0, 0.0, 0, ACCESS_1},
  {THR_H_L,             FLOAT,   INTERNAL, 180, 1496, "Thr_h",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},     //left hn treshold 
  {THR_H_R,             FLOAT,   INTERNAL, 181, 1498, "Thr_h",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},     //right hn treshold 
  {THR_O_L,             FLOAT,   INTERNAL, 182, 1500, "Thr_o",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},     //left o2 treshold 
  {THR_O_R,             FLOAT,   INTERNAL, 183, 1502, "Thr_o",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},     //right o2 treshold 
  {G_TH_H_L,            FLOAT,   INTERNAL, 184, 1504, "G_th_h",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},    //left hn hysteresis 
  {G_TH_H_R,            FLOAT,   INTERNAL, 185, 1506, "G_th_h",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},    //right hn hysteresis
  {G_TH_O_L,            FLOAT,   INTERNAL, 186, 1508, "G_th_o",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},    //left o2 hysteresis
  {G_TH_O_R,            FLOAT,   INTERNAL, 187, 1510, "G_th_o",    "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},    //right o2 hysteresis
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
  {ETHERNET_IP_GATE_3 , INT,     INTERNAL, 221,  -1, "",          "-",        1.0,     0.0, 10000.0, 3, ACCESS_1},
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
  {LEFT_CH_ON,          BOOLEAN, INTERNAL, 234,  1600, "",         "",         0.0,     0.0, 0.0,     0, ACCESS_1},
  {RIGHT_CH_ON,         BOOLEAN, INTERNAL, 235,  1602, "",         "",         0.0,     0.0, 0.0,     0, ACCESS_1},
  {DEBUG_1,             FLOAT,   INTERNAL,  -1,  -1, "Debug 1",    "",         0.0,     0.0, 0.0,     0, ACCESS_1},
  {DEBUG_2,             FLOAT,   INTERNAL,  -1,  -1, "Debug 2",    "",         0.0,     0.0, 0.0,     0, ACCESS_1},
  {RELAY_OUT_TEST_FLAG, BOOLEAN, INTERNAL,  -1,  -1, "",           "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},
  {DAC_TEST_FLAG,       BOOLEAN, INTERNAL,  -1,  -1, "",           "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},
  {PWM_OUT_TEST_FLAG,   BOOLEAN, INTERNAL,  -1,  -1, "",           "-",        1.0,     0.0, 10000.0, 3, ACCESS_0},
                                                                                                                         //отсюда и далее проставить дефолтные значения и имена!
                                                                                                                         //        |
                                                                                                                         //        V
  {U_IN_1,              FLOAT,   INTERNAL,  -1,  2000, "",          "-",        1.0,    0.0, 10000.0, 2, ACCESS_0},
  {AUTO_RANGE_2,        BOOLEAN, INTERNAL,  250, 2002, "",          "-",        1.0,    0.0, 10000.0, 0, ACCESS_1},
  {CURR_RANGE_2,        INT,     INTERNAL,  -1,  2004, "",          "-",        1.0,    0.0, 10000.0, 0, ACCESS_0},
  {K_2_1,               FLOAT,   INTERNAL,  251, 2006, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {K_2_2,               FLOAT,   INTERNAL,  252, 2008, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {K_2_4,               FLOAT,   INTERNAL,  253, 2010, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {K_2_8,               FLOAT,   INTERNAL,  254, 2012, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {K_2_16,              FLOAT,   INTERNAL,  255, 2014, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {SH_2_1,              FLOAT,   INTERNAL,  256, 2016, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {SH_2_2,              FLOAT,   INTERNAL,  257, 1018, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {SH_2_4,              FLOAT,   INTERNAL,  258, 2020, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {SH_2_8,              FLOAT,   INTERNAL,  259, 2022, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {SH_2_16,             FLOAT,   INTERNAL,  260, 2024, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
   
  {T_F_2,               FLOAT,   INTERNAL,  261, 2026, "",          "-",        1.0,    0.0, 10000.0, 2, ACCESS_1},
  {U_IN_2,              FLOAT,   INTERNAL,  -1,  2028, "",          "-",        1.0,    0.0, 10000.0, 2, ACCESS_0},
  
  {U_IN_3,              FLOAT,   INTERNAL,  -1,  2030, "",          "-",        1.0,    0.0, 10000.0, 2, ACCESS_0},
     
  {AUTO_RANGE_4,        BOOLEAN, INTERNAL,  262, 2032, "",          "-",        1.0,    0.0, 10000.0, 0, ACCESS_1}, 
  {CURR_RANGE_4,        INT,     INTERNAL,  -1,  2034, "",          "-",        1.0,    0.0, 10000.0, 0, ACCESS_0},   
  {K_4_1,               FLOAT,   INTERNAL,  263, 2036, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {K_4_2,               FLOAT,   INTERNAL,  264, 2038, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {K_4_4,               FLOAT,   INTERNAL,  165, 2040, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {K_4_8,               FLOAT,   INTERNAL,  266, 2042, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {K_4_16,              FLOAT,   INTERNAL,  267, 2044, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {SH_4_1,              FLOAT,   INTERNAL,  268, 2046, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {SH_4_2,              FLOAT,   INTERNAL,  269, 2048, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {SH_4_4,              FLOAT,   INTERNAL,  270, 2050, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {SH_4_8,              FLOAT,   INTERNAL,  271, 2052, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
  {SH_4_16,             FLOAT,   INTERNAL,  272, 2054, "",          "-",        1.0,    0.0, 10000.0, 3, ACCESS_1},
   
  {T_F_4,               FLOAT,   INTERNAL,  273, 2056, "",          "-",        1.0,    0.0, 10000.0, 2, ACCESS_1},
  {U_IN_4,              FLOAT,   INTERNAL,  -1,  2058, "",          "-",        1.0,    0.0, 10000.0, 2, ACCESS_0},

  {RANGE_MAX_CODE,      INT,     INTERNAL,  274, 2060, "",          "-",        1.0,    0.0, 10000.0, 0, ACCESS_1},
  {RANGE_MIN_CODE,      INT,     INTERNAL,  275, 2062, "",          "-",        1.0,    0.0, 10000.0, 0, ACCESS_1}
};
/*
typedef struct T_DICT_ENTRY{
  T_VAR curr_val;
  T_VAR prev_val;
} T_DICT_ENTRY;
*/
T_VAR dict_vars[(sizeof dict_var_descrs) / (sizeof dict_var_descrs[0])];
//------------------------------------------------------------------------------
//  Modbus functions
//------------------------------------------------------------------------------
/*
T_DICT_RECORD GetByModbusAddr(int mbaddr);
int GetTypeByModbusAddr(int mbaddr);
int GetIntValueByModbusAddr(int mbaddr);
float GetFloatValueByModbusAddr(int mbaddr);
*/
//------------------------------------------------------------------------------
//  Fram functions
//------------------------------------------------------------------------------

/*
void WriteIntToFram(unsigned int fram_add, unsigned int data);
void WriteFloatToFram(unsigned int fram_add, float data);
void ReadIntFromFram(unsigned int fram_add, unsigned int *data);
void ReadFloatFromFram(unsigned int fram_add, float *data);
*/
char* NotFound(void)
{
  return "nf";
};

void SetDefaultValues(void)
{
  for(int i = 0; dict_var_descrs[i].tag != MAX_RECORD - 1; i++)
    if(dict_var_descrs[i].fram_addr != -1)
    {
      if(dict_var_descrs[i].var_type == INT)
        dict_vars[i].ival = dict_var_descrs[i].def_val;
      if(dict_var_descrs[i].var_type == FLOAT)
        dict_vars[i].fval = dict_var_descrs[i].def_val;
    };
  SendMessage(MSG_VAR_CHANGED);
  SaveValuesToFram();
};

void LoadValuesFromFram(void)
{
  for(int i = 0; dict_var_descrs[i].tag != MAX_RECORD - 1; i++)
    if(dict_var_descrs[i].fram_addr != -1)
    {
      ReadIntFromFram(dict_var_descrs[i].fram_addr,
                      &dict_vars[i].ival);
   //   dict_vars[i].prev_val.ival = dict_vars[i].ival;
      //                                                  //temp comment
    };
  SendMessage(MSG_VAR_CHANGED); 
};

void SaveValuesToFram(void)
{
  for(int i = 0; dict_var_descrs[i].tag != MAX_RECORD - 1; i++)
    if(dict_var_descrs[i].fram_addr != -1)
    {
      WriteIntToFram(dict_var_descrs[i].fram_addr, dict_vars[i].ival);
    //  dict_vars[i].prev_val.ival = dict_vars[i].ival;
    //                                                
    };
  SendMessage(MSG_VAR_CHANGED); 
};
/*
void SaveVar(int number)
{
  if(dict_var_descrs[i].fram_addr != -1)
  {
    if(dict_vars[i].curr_val.ival != dict_vars[i].prev_val.ival)
    {
      WriteIntToFram(dict_var_descrs[i].fram_addr, dict_vars[i].curr_val.ival);
      dict_vars[i].prev_val.ival = dict_vars[i].curr_val.ival;
      SendMessage(MSG_VAR_CHANGED);                                    
    };
  };
}*/

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
  return dict_vars[tag];
}; 

char GetTypeByTag(int tag)
{
  return dict_var_descrs[tag].var_type;
};

signed char GetStringByTag(int tag, char id, char* buff, char buf_size)
{
  char buffer[50];
  char j; //количество символов в строке

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
           sprintf(buffer, "%d", dict_var_descrs[tag].min_val):
             sprintf(buffer, 
                     "%1.*f", 
                     dict_var_descrs[tag].after_point, 
                     dict_var_descrs[tag].min_val));                                 //check it, it may be wrong!
      break;
    case ID_MAX:
      j = (dict_var_descrs[tag].var_type == INT?
           sprintf(buffer, "%d", dict_var_descrs[tag].max_val):
             sprintf(buffer, 
                     "%1.f", 
                     dict_var_descrs[tag].after_point, 
                     dict_var_descrs[tag].max_val));                                 //check it, it may be wrong!
      break;    
    };
    if(j > buf_size)  //fail!
    {
      buff[0] = 0;
      return (char)-1;
    };
    strcpy(buff, buffer); 
    return 0; //normal
};

void SetValueByTag(int tag, T_VAR value)
{
  dict_vars[tag] = value;
  if(dict_var_descrs[tag].fram_addr != -1)
    WriteIntToFram(dict_var_descrs[tag].fram_addr, dict_vars[tag].ival); 
  SendMessage(MSG_VAR_CHANGED);
}

void SetIntValueByTag(int tag, int value)
{
  dict_vars[tag].ival = value;
  if(dict_var_descrs[tag].fram_addr != -1)
    WriteIntToFram(dict_var_descrs[tag].fram_addr, dict_vars[tag].ival);
  SendMessage(MSG_VAR_CHANGED);
};

void SetFloatValueByTag(int tag, float value)
{
  dict_vars[tag].fval = value;
  if(dict_var_descrs[tag].fram_addr != -1)
    WriteIntToFram(dict_var_descrs[tag].fram_addr, dict_vars[tag].ival);
  SendMessage(MSG_VAR_CHANGED);
};

void SetDefaulValueByTag(int tag)
{
  dict_vars[tag].fval = dict_var_descrs[tag].def_val;
  if(dict_var_descrs[tag].fram_addr != -1)
    WriteIntToFram(dict_var_descrs[tag].fram_addr, dict_vars[tag].ival);
  SendMessage(MSG_VAR_CHANGED);
}

T_VAR GetVarByTag(int tag)
{
  return dict_vars[tag];
}
/*
void SetFloatToTVar(T_VAR tvar, char vartype, float val)
{
  if(vartype == INT)
    tvar.ival = (int)val; 
  if(vartype == FLOAT)
    tvar.fval = val;
}
*/
char GetDataByModbusAddr(int addr, unsigned short* data)
{
  int tag;
  if(!(addr%2))
  {
    tag = FindRecordByModbusAddr(addr);
    if(tag > -1)
    {
      *data = dict_vars[tag].ival;
        return 1; 
    };
  }
  else
  {
    tag = FindRecordByModbusAddr(addr - 1);
    if(tag > -1)
    {
      *data = dict_vars[tag].ival >> 16;
        return 2; 
    };
  };
  *data = 0;
  return 0;
  /*
  if(!(addr%2))
  {
    for(int i = 0; dict_var_descrs[i].tag != MAX_RECORD - 1; i++)
      if(dict_var_descrs[i].modbus_addr == addr)
      {
        *data = dict_vars[i].ival;// >> 16;
        return 1;    
      };
  }
  else
  {
    for(int i = 0; dict_var_descrs[i].tag != MAX_RECORD - 1; i++)
      if(dict_var_descrs[i].modbus_addr == addr - 1)
      {
        *data = dict_vars[i].ival >> 16;
        return 2;    
      };
  };
  *data = 0;
  return 0;
  */
};

char SetDataByModbusAddr(int addr, unsigned short value)
{
  /*
  if(!(addr%2))
  {
    for(int i = 0; dict_var_descrs[i].tag != MAX_RECORD - 1; i++)
      if(dict_var_descrs[i].modbus_addr == addr)
      {
        dict_vars[i].ival = value;
        return 1;    
      };
  }
  else
  {
    for(int i = 0; dict_var_descrs[i].tag != MAX_RECORD - 1; i++)
      if(dict_var_descrs[i].modbus_addr == addr - 1)
      {
        dict_vars[i].ival |= (unsigned long)value << 16;
        WriteIntToFram(dict_var_descrs[i].fram_addr, dict_vars[i].ival);
        SendMessage(MSG_VAR_CHANGED);
        return 2;    
      };
  };
  return 0;
  */
  int tag;
  if(!(addr%2))
  {
    tag = FindRecordByModbusAddr(addr);
    if(tag > -1)
    {
      dict_vars[tag].ival = value;
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
      return 2;  
    };
  };
  return 0;  
};
/*
void SaveAllChanges(void)
{
  char var_changed = 0;
  for(int i = 0; dict_var_descrs[i].tag != MAX_RECORD - 1; i++)
    if(dict_var_descrs[i].fram_addr != -1)
    {
      if(dict_vars[i].ival != dict_vars[i].prev_val.ival)
      {
        WriteIntToFram(dict_var_descrs[i].fram_addr, dict_vars[i].ival);
        dict_vars[i].prev_val.ival = dict_vars[i].ival;
        var_changed = 1;                                             
      };
    }; 
  if(var_changed)
    SendMessage(MSG_VAR_CHANGED);
}*/

signed int FindRecordByModbusAddr(int addr)
{
  int high = MAX_RECORD;
  int low = 0;
  int probe;
  char found;
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
  if(dict_var_descrs[low].modbus_addr == addr)
    return low;
  return -1;
}
//------------------------------------------------------------------------------
