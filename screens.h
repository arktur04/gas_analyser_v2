//------------------------------------------------------------------------------
// Модуль реализует функции screen list
//------------------------------------------------------------------------------
#ifndef SCREENS_h
#define SCREENS_h

//#include "arm_comm.h"
//------------------------------------------------------------------------------
//  screen type id's 
//------------------------------------------------------------------------------
#define PARAM_SCREEN 0
#define CLAPP_SCREEN 1
//------------------------------------------------------------------------------
//  screens id's
//------------------------------------------------------------------------------
#define SCR_MAIN      0 
#define SCR_MENU_0    1
#define SCR_MENU_1    2
#define SCR_MENU_2    3
#define SCR_MENU_3    4

#define SCR_THERM_L_0 5
#define SCR_THERM_L_1 6
#define SCR_THERM_L_2 7

#define SCR_THERM_R_0 8
#define SCR_THERM_R_1 9
#define SCR_THERM_R_2 10

#define SCR_O2_L_0    11
#define SCR_O2_L_1    12
#define SCR_O2_L_2    13

#define SCR_O2_R_0    14
#define SCR_O2_R_1    15
#define SCR_O2_R_2    16

#define SCR_HN_L_0    17
#define SCR_HN_L_1    18
#define SCR_HN_L_2    19

#define SCR_HN_R_0    20
#define SCR_HN_R_1    21
#define SCR_HN_R_2    22

#define SCR_TH_L      23
#define SCR_TH_R      24

#define SCR_RS232     25
#define SCR_RS485     26
#define SCR_ETHERNET  27

#define SCR_DO_TEST   28
#define SCR_AI_TEST   29
#define SCR_AO_TEST   30
#define SCR_PWM_TEST  31
#define SCR_TREND_L   32
#define SCR_TREND_R   33
#define SCR_MISC      34

#define SCR_EDITOR    35
#define SCR_PASS      36
#define SCR_MSG       37

#define SCR_RES_THR_0   38
#define SCR_RES_THR_1   39
//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------
typedef struct{
  char header[25]; //заголовок экрана
  int var[5]; //тэги переменных
  int number; //номер экрана
  char back_allowed; //кнопка "назад" разрешена
  char home_allowed; //кнопка "главный экран" разрешена
  char forward_allowed; //кнопка "вперед" разрешена
} T_PARAM_SCREEN_DESCRIPTOR;


typedef struct{
  char header[25]; //заголовок экрана
  struct{int x; int y;} var[5];
  int number; //номер экрана
  char back_allowed; //кнопка "назад" разрешена
  char home_allowed; //кнопка "главный экран" разрешена
  char forward_allowed; //кнопка "вперед" разрешена
} T_CLAPP_SCREEN_DESCRIPTOR;
/*
typedef struct{
  char header[25]; //заголовок экрана
  int var_x1; //тэг переменной x1
  int var_y1; //тэг переменной y1
  int var_x2; //тэг переменной x2
  int var_y2; //тэг переменной y2
  int var_x3; //тэг переменной x3
  int var_y3; //тэг переменной y3
  int var_x4; //тэг переменной x4
  int var_y4; //тэг переменной y4
  int var_x5; //тэг переменной x5
  int var_y5; //тэг переменной y5
  int number; //номер экрана
  char back_allowed; //кнопка "назад" разрешена
  char home_allowed; //кнопка "главный экран" разрешена
  char forward_allowed; //кнопка "вперед" разрешена
} T_CLAPP_SCREEN_DESCRIPTOR;
*/
typedef union 
{
  T_PARAM_SCREEN_DESCRIPTOR param_screen;
  T_CLAPP_SCREEN_DESCRIPTOR clapp_screen;
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
