#include "screens.h"
// #include "clapp_screen.h"
// #include "param_screen.h"
#include "variables.h"
// #include "messages.h"

const T_SCREEN_DESCRIPTOR screens[] = {                                    
  {PARAM_SCREEN, {"Термостат левый (1/3)",
  SHIFT_T_L,
  K_CD_T_L,
  T_F_T_L, 
  ADJ_S_T_L,
  K_P_T_L,
  0, TRUE,  TRUE, TRUE}},  //0
  
  {PARAM_SCREEN, {"Термостат левый (2/3)",
  K_D_T_L,
  T_DF_T_L, 
  KI_T_L,
  DISP_T_L, 
  EMPTY_CELL,
  1, TRUE, TRUE, TRUE}},  //1
  
  {PARAM_SCREEN, {"Термостат левый (3/3)",
  SM_T_L,
  K_CLC_T_L,   
  LIM_LO_T_L,
  LIM_HI_T_L,
  EMPTY_CELL, 2, TRUE, TRUE, TRUE}}, //2
  
  {PARAM_SCREEN, {"Термостат правый (1/3)",
  SHIFT_T_R, 
  K_CD_T_R,  
  T_F_T_R, 
  ADJ_S_T_R, 
  K_P_T_R,
  3, TRUE,  TRUE, TRUE}},  //3
  
  {PARAM_SCREEN, {"Термостат правый (2/3)", 
  K_D_T_R, 
  T_DF_T_R, 
  KI_T_R,   
  DISP_T_R,  
  EMPTY_CELL,
  4, TRUE,  TRUE, TRUE}},  //4
  
  {PARAM_SCREEN, {"Термостат правый (3/3)",
  SM_T_R,
  K_CLC_T_R, 
  LIM_LO_T_R,
  LIM_HI_T_R,
  EMPTY_CELL, 5, TRUE, TRUE, TRUE}}, //5
  
  {PARAM_SCREEN, {"Кислород левый (1/3)",
  SHIFT_E_L,
  K_CD_E_L,
  T_F_E_L,
  T_FF_T_L,  
  T_F_O_L,
  6, TRUE, TRUE, TRUE}},      //6
  
  {CLAPP_SCREEN, .scr.clapp_screen = {"КЛАПП кислорода л. (2/3)", 
  X1_L, Y1_L,
  X2_L, Y2_L,
  X3_L, Y3_L,
  X4_L, Y4_L,
  X5_L, Y5_L,
  7, TRUE,  TRUE, TRUE}}, //7
  
  {PARAM_SCREEN, {"Кислород левый (3/3)",   
  K_I_O_L,   
  SH_O_L,
  EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, 8, TRUE, TRUE, TRUE}}, //8
  
  {PARAM_SCREEN, {"Кислород правый (1/3)",  
  SHIFT_E_R,
  K_CD_E_R,
  T_F_E_R, 
  T_FF_T_R,  
  T_F_O_R,
  9, TRUE, TRUE, TRUE}},     //9
  
  {CLAPP_SCREEN, .scr.clapp_screen = {"КЛАПП кислорода п. (2/3)",
  X1_R, Y1_R,
  X2_R, Y2_R,
  X3_R, Y3_R,
  X4_R, Y4_R,
  X5_R, Y5_R, 
  10, TRUE,  TRUE, TRUE}}, //10
  
  {PARAM_SCREEN, {"Кислород правый (3/3)",  
  K_I_O_R,
  SH_O_R, 
  EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
  11, TRUE, TRUE, TRUE}}, //11
  
  {PARAM_SCREEN, {"ХН левый (1/3)",
  T_F_H_L,
  T_FF_H_L, 
  T_D_H_L,  
  K_R_H_L,  
  K_L_H_L,
  12, TRUE, TRUE, TRUE}},              //12
  
  {PARAM_SCREEN, {"ХН левый (2/3)", 
  LIM_H_L,
  KLIM_H_L,
  T_FD_H_L, 
  K_I_H_L,  
  SH_H_L, 
  13, TRUE, TRUE, TRUE}},             //13
  
  {CLAPP_SCREEN, .scr.clapp_screen = {"КЛАПП ХН л. (3/3)",
  HN_X0_L, HN_Y0_L,
  HN_X1_L, HN_Y1_L,
  HN_X2_L, HN_Y2_L,
  HN_X3_L, HN_Y3_L,
  HN_X4_L, HN_Y4_L, 
  14, TRUE,  TRUE, TRUE}},   //14
  
  {PARAM_SCREEN, {"ХН правый (1/3)",
  T_F_H_R,
  T_FF_H_R,
  T_D_H_R,
  K_R_H_R,
  K_L_H_R,
  15, TRUE, TRUE, TRUE}},             //15
  
  {PARAM_SCREEN, {"ХН правый (2/3)",  
  LIM_H_R,
  KLIM_H_R,
  T_FD_H_R,
  K_I_H_R,
  SH_H_R,
  16, TRUE, TRUE, TRUE}},            //16
  
  {CLAPP_SCREEN, .scr.clapp_screen = {"КЛАПП ХН п. (3/3)",
  HN_X0_R, HN_Y0_R,
  HN_X1_R, HN_Y1_R,
  HN_X2_R, HN_Y2_R,
  HN_X3_R, HN_Y3_R,
  HN_X4_R, HN_Y4_R,
  17, TRUE,  TRUE, FALSE}},  //17
  
  {PARAM_SCREEN, {"Пороги л.",
  THR_H_L,
  THR_O_L,
  G_TH_H_L,
  G_TH_O_L,
  EMPTY_CELL, 18, TRUE, TRUE, TRUE}},          //18
  
  {PARAM_SCREEN, {"Пороги п.",
  THR_H_R,
  THR_O_R,
  G_TH_H_R,
  G_TH_O_R,
  EMPTY_CELL, 19, TRUE, TRUE, TRUE}},           //19                                                         
  
  {PARAM_SCREEN, {"Пороги сопр. (1/2)",
  INPUT0_RESISTANCE_DETECTOR_LOW_THRESHOLD,
  INPUT0_RESISTANCE_DETECTOR_HI_THRESHOLD,
  INPUT1_RESISTANCE_DETECTOR_LOW_THRESHOLD,
  INPUT1_RESISTANCE_DETECTOR_HI_THRESHOLD,
  EMPTY_CELL, 20, TRUE, TRUE, TRUE}},           //20}
  
  {PARAM_SCREEN, {"Пороги сопр. (2/2)",
  INPUT2_RESISTANCE_DETECTOR_LOW_THRESHOLD,
  INPUT2_RESISTANCE_DETECTOR_HI_THRESHOLD,
  INPUT3_RESISTANCE_DETECTOR_LOW_THRESHOLD,
  INPUT3_RESISTANCE_DETECTOR_HI_THRESHOLD,
  EMPTY_CELL, 21, TRUE, TRUE, TRUE}},           //21}   
  
  {TWO_COL_SCREEN, .scr.two_col_screen = {"Калибровка кан. ТП-Л", 
  ADC_1, EMPTY_CELL,
  U_T_L, T_T_L,
  SHIFT_T_L, K_CD_T_L,
  T_CL_E, CEL_T_L,
  EMPTY_CELL, EMPTY_CELL, 
  22, TRUE,  TRUE, TRUE}},
  
  {TWO_COL_SCREEN, .scr.two_col_screen = {"Калибровка кан. ТП-П", 
  ADC_3, EMPTY_CELL,
  U_T_R, T_T_R,
  SHIFT_T_R, K_CD_T_R,
  T_CL_E, CEL_T_R,
  EMPTY_CELL, EMPTY_CELL, 
  23, TRUE,  TRUE, TRUE}},
  
  {TWO_COL_SCREEN, .scr.two_col_screen = {"Калибровка кан. ЧЭ-Л", 
  ADC_2, EMPTY_CELL,
  E_F_E_L, C_KL_O_L,
  SHIFT_E_L, K_CD_E_L,
  /*CEL_F_T_L*/CEL_T_L, EMPTY_CELL,
  EMPTY_CELL, EMPTY_CELL, 
  24, TRUE,  TRUE, TRUE}},
  
  {TWO_COL_SCREEN, .scr.two_col_screen = {"Калибровка кан. ЧЭ-П", 
  ADC_4, EMPTY_CELL,
  E_F_E_R, C_KL_O_R,
  SHIFT_E_R, K_CD_E_R,
  /*CEL_F_T_R*/CEL_T_R, EMPTY_CELL,
  EMPTY_CELL, EMPTY_CELL, 
  25, TRUE,  TRUE, TRUE}},
  
  {TWO_COL_SCREEN, .scr.two_col_screen = {"Калибровка выходов", 
  REPR_O2_L, MAX_O2_L,
  REPR_H_L, MAX_XH_L,
  REPR_O2_R, MAX_O2_R,
  REPR_H_R,  MAX_XH_R,
  EMPTY_CELL, EMPTY_CELL, 
  26, TRUE,  TRUE, TRUE}},
};

char scr_num = 0;

T_SCREEN_DESCRIPTOR GetScreen(int n)
{
  return screens[n];
}
