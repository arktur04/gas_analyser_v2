#include "screens.h"
// #include "clapp_screen.h"
// #include "param_screen.h"
#include "variables.h"
// #include "messages.h"

const T_SCREEN_DESCRIPTOR screens[] = {                                    
  {PARAM_SCREEN, {"��������� ����� (1/3)",
                  SHIFT_T_L,
                  K_CD_T_L,
                  T_F_T_L, 
                  ADJ_S_T_L,
                  K_P_T_L,
                  0, TRUE,  TRUE, TRUE}},  //0
  
  {PARAM_SCREEN, {"��������� ����� (2/3)",
                  K_D_T_L,
                  T_DF_T_L, 
                  KI_T_L,
                  DISP_T_L, 
                  EMPTY_CELL,
                  1, TRUE, TRUE, TRUE}},  //1
  
  {PARAM_SCREEN, {"��������� ����� (3/3)",
                  SM_T_L,
                  K_CLC_T_L,   
                  LIM_LO_T_L,
                  LIM_HI_T_L,
                  EMPTY_CELL, 2, TRUE, TRUE, TRUE}}, //2
  
  {PARAM_SCREEN, {"��������� ������ (1/3)",
                  SHIFT_T_R, 
                  K_CD_T_R,  
                  T_F_T_R, 
                  ADJ_S_T_R, 
                  K_P_T_R,
                  3, TRUE,  TRUE, TRUE}},  //3
  
  {PARAM_SCREEN, {"��������� ������ (2/3)", 
                  K_D_T_R, 
                  T_DF_T_R, 
                  KI_T_R,   
                  DISP_T_R,  
                  EMPTY_CELL,
                  4, TRUE,  TRUE, TRUE}},  //4
  
  {PARAM_SCREEN, {"��������� ������ (3/3)",
                  SM_T_R,
                  K_CLC_T_R, 
                  LIM_LO_T_R,
                  LIM_HI_T_R,
                  EMPTY_CELL, 5, TRUE, TRUE, TRUE}}, //5

  {PARAM_SCREEN, {"�������� ����� (1/3)",
                  SHIFT_E_L,
                  K_CD_E_L,
                  T_F_E_L,
                  T_FF_T_L,  
                  T_F_O_L,
                  6, TRUE, TRUE, TRUE}},      //6
                  
  {CLAPP_SCREEN, .scr.clapp_screen = {"����� ��������� �. (2/3)", 
                                      X1_L, Y1_L,
                                      X2_L, Y2_L,
                                      X3_L, Y3_L,
                                      X4_L, Y4_L,
                                      X5_L, Y5_L,
                                      7, TRUE,  TRUE, TRUE}},
                                      
  {PARAM_SCREEN, {"�������� ����� (3/3)",   
                  K_I_O_L,   
                  SH_4_O_L,
                  EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, 8, TRUE, TRUE, TRUE}}, //8
                                                              
  {PARAM_SCREEN, {"�������� ������ (1/3)",  
                  SHIFT_E_R,
                  K_CD_E_R,
                  T_F_E_R, 
                  T_FF_T_R,  
                  T_F_O_R,
                  9, TRUE, TRUE, TRUE}},     //9
  
  {CLAPP_SCREEN, .scr.clapp_screen = {"����� ��������� �. (2/3)",
                                      X1_R, Y1_R,
                                      X2_R, Y2_R,
                                      X3_R, Y3_R,
                                      X4_R, Y4_R,
                                      X5_R, Y5_R, 
                                      10, TRUE,  TRUE, TRUE}},
  {PARAM_SCREEN, {"�������� ������ (3/3)",  
                  K_I_O_R,
                  SH_4_O_R, 
                  EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
                  11, TRUE, TRUE, TRUE}}, //11

  {PARAM_SCREEN, {"�� ����� (1/3)",
                  T_F_H_L,
                  T_FF_H_L, 
                  T_D_H_L,  
                  K_R_H_L,  
                  K_L_H_L,
                  12, TRUE, TRUE, TRUE}},              //12
                  
  {PARAM_SCREEN, {"�� ����� (2/3)", 
                  LIM_H_L,
                  KLIM_H_L,
                  T_FD_H_L, 
                  K_I_H_L,  
                  SH_4_H_L, 
                  13, TRUE, TRUE, TRUE}},             //13
                  
  {CLAPP_SCREEN, .scr.clapp_screen = {"����� �� �. (3/3)",
                                      HN_X0_L, HN_Y0_L,
                                      HN_X1_L, HN_Y1_L,
                                      HN_X2_L, HN_Y2_L,
                                      HN_X3_L, HN_Y3_L,
                                      HN_X4_L, HN_Y4_L, 
                                      14, TRUE,  TRUE, TRUE}},                                                                                                             
  {PARAM_SCREEN, {"�� ������ (1/3)",
                   T_F_H_R,
                   T_FF_H_R,
                   T_D_H_R,
                   K_R_H_R,
                   K_L_H_R,
                   15, TRUE, TRUE, TRUE}},             //15
  
  {PARAM_SCREEN, {"�� ������ (2/3)",  
                  LIM_H_R,
                  KLIM_H_R,
                  T_FD_H_R,
                  K_I_H_R,
                  SH_4_H_R,
                  16, TRUE, TRUE, TRUE}},            //16
                  
  {CLAPP_SCREEN, .scr.clapp_screen = {"����� �� �. (3/3)",
                                      HN_X0_R, HN_Y0_R,
                                      HN_X1_R, HN_Y1_R,
                                      HN_X2_R, HN_Y2_R,
                                      HN_X3_R, HN_Y3_R,
                                      HN_X4_R, HN_Y4_R,
                                      17, TRUE,  TRUE, FALSE}},
  {PARAM_SCREEN, {"������ �.",
                  THR_H_L,
                  THR_O_L,
                  G_TH_H_L,
                  G_TH_O_L,
                  EMPTY_CELL, 18, TRUE, TRUE, TRUE}},          //18
  {PARAM_SCREEN, {"������ �.",
                  THR_H_R,
                  THR_O_R,
                  G_TH_H_R,
                  G_TH_O_R,
                  EMPTY_CELL, 19, TRUE, TRUE, TRUE}},           //19                                                         

  {PARAM_SCREEN, {"������ ����. (1/2)",
                  INPUT0_RESISTANCE_DETECTOR_LOW_THRESHOLD,
                  INPUT0_RESISTANCE_DETECTOR_HI_THRESHOLD,
                  INPUT1_RESISTANCE_DETECTOR_LOW_THRESHOLD,
                  INPUT1_RESISTANCE_DETECTOR_HI_THRESHOLD,
                  EMPTY_CELL, 20, TRUE, TRUE, TRUE}},           //20}

  {PARAM_SCREEN, {"������ ����. (2/2)",
                  INPUT2_RESISTANCE_DETECTOR_LOW_THRESHOLD,
                  INPUT2_RESISTANCE_DETECTOR_HI_THRESHOLD,
                  INPUT3_RESISTANCE_DETECTOR_LOW_THRESHOLD,
                  INPUT3_RESISTANCE_DETECTOR_HI_THRESHOLD,
                  EMPTY_CELL, 21, TRUE, TRUE, TRUE}}           //21}   
};

char scr_num = 0;

T_SCREEN_DESCRIPTOR GetScreen(int n)
{
  return screens[n];
}