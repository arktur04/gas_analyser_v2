extern "C"{
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "keyb.h"
#include "timers.h"
#include "variables.h"
//#include "menu_screen.h"
  #include "messages.h"
  #include "pass_controller.h"
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_scr.h"
#include "usbase.h"
#include "pass_aux_base_class.h"

char flash_flag = 0;
/*
class usScreen: public usFsm{
private:
protected:
char message_to_activate;
virtual void Activated(void) {};
virtual void ActiveLoop(void) = 0;
virtual void ChildDeactivated(char child_result) {};
virtual void Deactivate(void);
virtual void ChildScreenActivate(char ScreenId);
virtual void Process(void);
public:
usScreen(void) {message_to_activate = MSG_SCREEN_ACTIVATE;};
void setMessageToActivate(char msg) {message_to_activate = msg;};
virtual void Paint(void) = 0;
};

class MainScreen: public usScreen
{
protected:
// virtual void Update(void);
virtual void ActiveLoop(void);
virtual void Activated(void);
virtual void Paint(void);
};
*/

void MainScreen::Paint(void)
{ 
  #define BUF_SIZE 10
  char str[BUF_SIZE];
  const char tp_fault[] = "Îáðûâ";
  const char blank_str[] = "-----";
  
  char flag_tp_l, flag_che_l, flag_ne_l, flag_o2_l, flag_hn_l, flag_tp_r,
  flag_che_r, flag_ne_r, flag_o2_r, flag_hn_r, flag_gf_l, flag_gf_r;                                                                          
  
  char curr_color;
  
  flag_tp_l = GetIntValueByTag(FLT_TP_L);
  flag_che_l = GetIntValueByTag(FLT_CH_L);
  flag_ne_l = GetIntValueByTag(FLT_NE_L);
  flag_o2_l = GetIntValueByTag(FTH_O2_L);
  flag_hn_l = GetIntValueByTag(FTH_H_L);

  flag_tp_r = GetIntValueByTag(FLT_TP_R);
  flag_che_r = GetIntValueByTag(FLT_CH_R);
  flag_ne_r = GetIntValueByTag(FLT_NE_R);
  flag_o2_r = GetIntValueByTag(FTH_O2_R);
  flag_hn_r = GetIntValueByTag(FTH_H_R);
  
  flag_gf_l = GetIntValueByTag(FLT_GA_L);
  flag_gf_r = GetIntValueByTag(FLT_GA_R);
  
 // flag_tp_l = flag_che_l = flag_ne_l = flag_o2_l = flag_hn_l = flag_tp_r =
 // flag_che_r = flag_ne_r = flag_o2_r = flag_hn_r = flag_gf_l = flag_gf_r = 0;    //temp       
  
  LcdClear();
  SetFont(SMALL_FONT);
  LcdSetColor(BLACK);
  LcdText(44, 0, 84, 8, "Ëåâûé");
  LcdText(88, 0, 127, 8, "Ïðàâûé");
  LcdLine(119, 0, 119, 7);
  
 // PassAuxBaseScreen::Paint();
  
  LcdLine(0, 8, 127, 8);
  LcdLine(0, 9, 127, 9);
  
  LcdBmp(0, 12, GetBmpWidth(BMP_HN), GetBmpHeight(BMP_HN), GetBmp(BMP_HN));
  
  LcdLine(0, 25, 127, 25);
  LcdBmp(0, 28, GetBmpWidth(BMP_O2), GetBmpHeight(BMP_O2), GetBmp(BMP_O2)); 
  
  LcdLine(0, 41, 127, 41);
  SetFont(SMALL_FONT);
  
  LcdText(0, 43, 38, 51, "T,\x86\x43");
  LcdLine(0, 52, 127, 52);
  LcdLine(0, 53, 127, 53);
  
//  tmp = GetFloatValueByTag(T_CL_E);
  sprintf(str, "Tõ%.1f\x86\x43", GetFloatValueByTag(T_CL_E));
  LcdText(0, 55, 39, 63, str);
  //----------------------------------------------------------------------------

  LcdText(1, 0, 38, 7, "ÓðàëÝÊÎ");
  
  if(flash_flag)
    LcdSetColor(WHITE);
 
  if(flag_tp_l)
    LcdBmp(40, 54, GetBmpWidth(BMP_SMALL_TP), GetBmpHeight(BMP_SMALL_TP),
           GetBmp(BMP_SMALL_TP));
  if(flag_che_l)
    LcdBmp(49, 54, GetBmpWidth(BMP_SMALL_CHE), GetBmpHeight(BMP_SMALL_CHE),
           GetBmp(BMP_SMALL_CHE)); 
  if(flag_ne_l)
    LcdBmp(58, 54, GetBmpWidth(BMP_SMALL_NE), GetBmpHeight(BMP_SMALL_NE), 
           GetBmp(BMP_SMALL_NE)); 
  if(flag_o2_l)
    LcdBmp(67, 54,  GetBmpWidth(BMP_SMALL_O2), GetBmpHeight(BMP_SMALL_O2), 
           GetBmp(BMP_SMALL_O2)); 
  if(flag_hn_l)
    LcdBmp(75, 54,  GetBmpWidth(BMP_SMALL_HN), GetBmpHeight(BMP_SMALL_HN), 
           GetBmp(BMP_SMALL_HN));
 
  if(flag_tp_r)
    LcdBmp(84, 54,  GetBmpWidth(BMP_SMALL_TP), GetBmpHeight(BMP_SMALL_TP),
           GetBmp(BMP_SMALL_TP));
  if(flag_che_r)
    LcdBmp(93, 54,  GetBmpWidth(BMP_SMALL_CHE), GetBmpHeight(BMP_SMALL_CHE), 
           GetBmp(BMP_SMALL_CHE)); 
  if(flag_ne_r)
    LcdBmp(102, 54,  GetBmpWidth(BMP_SMALL_NE), GetBmpHeight(BMP_SMALL_NE), 
           GetBmp(BMP_SMALL_NE));
  if(flag_o2_r)
    LcdBmp(111, 54,  GetBmpWidth(BMP_SMALL_O2), GetBmpHeight(BMP_SMALL_O2), 
           GetBmp(BMP_SMALL_O2));  
  if(flag_hn_r)
    LcdBmp(119, 54,  GetBmpWidth(BMP_SMALL_HN), GetBmpHeight(BMP_SMALL_HN), 
           GetBmp(BMP_SMALL_HN));
        
  LcdSetColor(BLACK);
  
  //----------------------------------------------------------------------------
  LcdLine(39, 0, 39, 51);
  LcdLine(84, 0, 84, 51);
  
  SetFont(BIG_FONT);
  
  curr_color = ((flag_hn_l || flag_gf_l) && flash_flag)?WHITE:BLACK;      
  //--------   
  LcdSetColor(~curr_color);
  LcdRect(40, 10, 83, 24);
  LcdSetColor(curr_color);
  if(flag_gf_l)
  {
    LcdText(43, 12, 83, 24, blank_str);
  }
  else
  {  
    GetStringByTag(C_KL_HN_L, ID_CURR_VAL, str, BUF_SIZE);
    LcdText(43, 12, 83, 24, str);   //hn left
  };
  
  //---------
  curr_color = ((flag_hn_r || flag_gf_r) && flash_flag)?WHITE:BLACK;      
  LcdSetColor(~curr_color);
  LcdRect(85, 10, 127, 24);
  LcdSetColor(curr_color);
  if(flag_gf_r)
  { 
    LcdText(88, 12, 127, 24, blank_str);
  }
  else
  {
    GetStringByTag(C_KL_HN_R, ID_CURR_VAL, str, BUF_SIZE);
    LcdText(88, 12, 127, 24, str);  //hn right
  };
  //---------------------------------
  
  curr_color = ((flag_o2_l || flag_gf_l) && flash_flag)?WHITE:BLACK;      
  LcdSetColor(~curr_color);
  LcdRect(40, 26, 83, 40);
  LcdSetColor(curr_color); 
  
  if(flag_gf_l)
  { 
    LcdText(43, 28, 83, 40, blank_str);
  }
  else
  {
    sprintf(str, "%.2f", GetFloatValueByTag(C_KL_O_L));
//    GetStringByTag(C_KL_O_L, ID_CURR_VAL, str, BUF_SIZE);
    LcdText(43, 28, 83, 40, str);  //o2 left
  };
   
  curr_color = ((flag_o2_r || flag_gf_r) && flash_flag)?WHITE:BLACK;      
  LcdSetColor(~curr_color);
  LcdRect(85, 26, 127, 40);
  LcdSetColor(curr_color);
  
  if(flag_gf_r)
  { 
    LcdText(88, 28, 127, 40, blank_str);
  }
  else
  {
    sprintf(str, "%.2f", GetFloatValueByTag(C_KL_O_R));
//    GetStringByTag(C_KL_O_R, ID_CURR_VAL, str, BUF_SIZE);
    LcdText(88, 28, 127, 40, str);  //o2 right
  };
  //---------------------------------
  SetFont(SMALL_FONT);
   
  curr_color = (flash_flag && flag_tp_l)?WHITE:BLACK;   
  LcdSetColor(~curr_color); 
  LcdRect(40, 42, 83, 51);
  LcdSetColor(curr_color); 
  if(flag_tp_l)
  { 
    LcdText(43, 43, 83, 51, tp_fault);
  }
  else
  {
    sprintf(str, "%.1f", GetFloatValueByTag(CEL_F_T_L));
    LcdText(43, 43, 83, 51, str);  //temp left
  };
  curr_color = (flash_flag && flag_tp_r)?WHITE:BLACK;   
  LcdSetColor(~curr_color); 
  LcdRect(85, 42, 127, 51);
  LcdSetColor(curr_color); 
  if(flag_tp_r)
  { 
    LcdText(88, 43, 127, 51, tp_fault);
  }
  else
  {
    sprintf(str, "%.1f", GetFloatValueByTag(CEL_F_T_R));
    LcdText(88, 43, 127, 51, str);  //temp right
  };
  PassAuxBaseScreen::Paint();
}

void MainScreen::Activated(unsigned long *param)
{
  usScreen::Activated(param);
  main_sub_state = 0;
  ResetTimer(SCREEN_REFRESH_TIMER);
};

void MainScreen::ActiveLoop(void)
{
  switch(main_sub_state)
  {
  case 0:
    if(GetTimer(SCREEN_REFRESH_TIMER) > 50)
    {
      flash_flag = 1;
      main_sub_state = 1;
      Update();
      ResetTimer(SCREEN_REFRESH_TIMER);
    };
    break;
  case 1:
    if(GetTimer(SCREEN_REFRESH_TIMER) > 50)
    {
      flash_flag = 0;
      main_sub_state = 0;
      Update();
      ResetTimer(SCREEN_REFRESH_TIMER);
    };
    break;
  };
  //end of switch
  if(GetMessage(MSG_KEYPRESSED)) //press Any Key
  {
    //main_state = 0;
  //  setState(0);
    //SetMenuScreen(0);
   
    SendMessage(MSG_MAIN_SCREEN_DEACTIVATED);
  };
};
