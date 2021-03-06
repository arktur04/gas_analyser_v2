//------------------------------------------------------------------------------
// ������ ��������� ������� screen list
//------------------------------------------------------------------------------
#ifndef SCREENS_h
#define SCREENS_h

//#include "arm_comm.h"
//------------------------------------------------------------------------------
//  screen type id's 
//------------------------------------------------------------------------------
#define PARAM_SCREEN 0
#define CLAPP_SCREEN 1
#define TWO_COL_SCREEN 2
//------------------------------------------------------------------------------
//  screens id's
//------------------------------------------------------------------------------
#define SCR_MAIN      0 
#define SCR_MENU_0    1
#define SCR_MENU_1    2
#define SCR_MENU_2    3
#define SCR_MENU_3    4
#define SCR_MENU_4    5

#define SCR_THERM_L_0 6
#define SCR_THERM_L_1 7
#define SCR_THERM_L_2 8

#define SCR_THERM_R_0 9
#define SCR_THERM_R_1 10
#define SCR_THERM_R_2 11

#define SCR_O2_L_0    12
#define SCR_O2_L_1    13
#define SCR_O2_L_2    14

#define SCR_O2_R_0    15
#define SCR_O2_R_1    16
#define SCR_O2_R_2    17

#define SCR_HN_L_0    18
#define SCR_HN_L_1    19
#define SCR_HN_L_2    20
#define SCR_HN_L_3    21

#define SCR_HN_R_0    22
#define SCR_HN_R_1    23
#define SCR_HN_R_2    24
#define SCR_HN_R_3    25

#define SCR_TH_L      26
#define SCR_TH_R      27

#define SCR_RS232     28
#define SCR_RS485     29
#define SCR_ETHERNET  30

#define SCR_DO_TEST   31
#define SCR_AI_TEST   32
#define SCR_AO_TEST   33
#define SCR_PWM_TEST  34
#define SCR_TREND_L   35
#define SCR_TREND_R   36
#define SCR_MISC      37

#define SCR_EDITOR    38
#define SCR_PASS      39
#define SCR_MSG       40

#define SCR_RES_THR_0 41
#define SCR_RES_THR_1 42

#define SCR_TC_CALIBR_L 43
#define SCR_TC_CALIBR_R 44

#define SCR_CH_CALIBR_L 45
#define SCR_CH_CALIBR_R 46

#define SCR_OUT_CALIBR  47
//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------
typedef struct{
  char header[25]; //��������� ������
  int var[5]; //���� ����������
  int number; //����� ������
  char back_allowed; //������ "�����" ���������
  char home_allowed; //������ "������� �����" ���������
  char forward_allowed; //������ "������" ���������
} T_PARAM_SCREEN_DESCRIPTOR;


typedef struct{
  char header[25]; //��������� ������
  struct{int x; int y;} var[5];
  int number; //����� ������
  char back_allowed; //������ "�����" ���������
  char home_allowed; //������ "������� �����" ���������
  char forward_allowed; //������ "������" ���������
} T_CLAPP_SCREEN_DESCRIPTOR;


typedef struct{
  char header[25]; //��������� ������
  int var[5][2];
  int number; //����� ������
  char back_allowed; //������ "�����" ���������
  char home_allowed; //������ "������� �����" ���������
  char forward_allowed; //������ "������" ���������
} T_TWO_COL_SCREEN_DESCRIPTOR;
/*
typedef struct{
  char header[25]; //��������� ������
  int var_x1; //��� ���������� x1
  int var_y1; //��� ���������� y1
  int var_x2; //��� ���������� x2
  int var_y2; //��� ���������� y2
  int var_x3; //��� ���������� x3
  int var_y3; //��� ���������� y3
  int var_x4; //��� ���������� x4
  int var_y4; //��� ���������� y4
  int var_x5; //��� ���������� x5
  int var_y5; //��� ���������� y5
  int number; //����� ������
  char back_allowed; //������ "�����" ���������
  char home_allowed; //������ "������� �����" ���������
  char forward_allowed; //������ "������" ���������
} T_CLAPP_SCREEN_DESCRIPTOR;
*/
typedef union 
{
  T_PARAM_SCREEN_DESCRIPTOR param_screen;
  T_CLAPP_SCREEN_DESCRIPTOR clapp_screen;
  T_TWO_COL_SCREEN_DESCRIPTOR two_col_screen;
} T_SCREEN_;

typedef struct 
{
  int scr_type; //screen type
  T_SCREEN_ scr;
} T_SCREEN_DESCRIPTOR;

//#define MAX_SCREEN 39 //20

T_SCREEN_DESCRIPTOR GetScreen(int n);
void NextScreen(void);
void PrevScreen(void);
void SetScreen(char scr);
  
#endif
