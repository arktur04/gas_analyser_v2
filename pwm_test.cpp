extern "C"
{
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "keyb.h"
#include "timers.h"
#include "messages.h"
#include "variables.h"
#include "screens.h"
#include "checkbox.h"
#include "pass_controller.h"  
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pwm_test.h"
#include "usbase.h"
//#include "msg.h"

PwmTestScreen::PwmTestScreen():usScreen(MSG_PWM_TEST_SCREEN_ACTIVATE, SCR_PWM_TEST)
{
 // message_to_activate = MSG_PWM_TEST_SCREEN_ACTIVATE;  
};

void PwmTestScreen::PlaceControls()
{
  AddControl(new usBmpButton(110, 9, 17, 18, 0, BTN_FORWARD, MSG_BTN_FORWARD, SCR_PWM_TEST));
  AddControl(new usBmpButton(110, 27, 17, 18, 1, BTN_HOME, MSG_BTN_HOME, SCR_PWM_TEST));
  AddControl(new usBmpButton(110, 45, 17, 18, 2, BTN_BACK, MSG_BTN_BACKWARD, SCR_PWM_TEST));
  
  AddControl(pBtns[0] = new usTextButton(50, 20, 30, 11, 3, "",
                                         BS_SIMPLE, MSG_BTN_EDIT, PWM_1));
  
  AddControl(pBtns[1] = new usTextButton(80, 20, 30, 11, 4, "",
                                         BS_SIMPLE, MSG_BTN_EDIT, PWM_2));
};

void PwmTestScreen::Paint(void)
{ 
  #define BUF_SIZE 10
  char str[BUF_SIZE];
  
   LcdClear();
  SetFont(SMALL_FONT);
  LcdText(1, 0, 118, 7, "Тест силовых выходов");
  LcdLine(0, 8, 127, 8);  
  LcdLine(0, 9, 127, 9);  

 // LcdText(1, 11, 48, 18, GetNameByTag(tag));
 // LcdSetColor(BLACK);
 // LcdText(83, 11, 109, 18, GetUnitByTag(tag)); 
  
  LcdLine(0, 20, 109, 20);  
  LcdLine(0, 31, 109, 31);  
  LcdLine(0, 42, 109, 42);  
  LcdLine(0, 53, 109, 53);
  
  LcdLine(50, 10, 50, 52);
  LcdLine(80, 10, 80, 52);
 // LcdLine(84, 10, 84, 52);
  
  LcdText(52, 11, 76, 19, "Печь1");
  LcdText(82, 11, 106, 19, "Печь2");
  
  LcdText(34, 22, 49, 30, "ШИМ");
  LcdText(25, 33, 49, 41, "Обрыв");
  LcdText(0, 44, 49, 52, "Перегрузка");
  
  DrawCheckBox(51, 32, GetIntValueByTag(FLT_NE_L), false);
  DrawCheckBox(81, 32, GetIntValueByTag(FLT_NE_R), false);
   
  DrawCheckBox(51, 43, false, false);                                           // overload checkbox
  DrawCheckBox(81, 43, false, false);                                           // overload checkbox
  
  
  GetStringByTag(PWM_1, ID_CURR_VAL, str, BUF_SIZE);
  pBtns[0]->text.assign(str);
  
  GetStringByTag(PWM_2, ID_CURR_VAL, str, BUF_SIZE);
  pBtns[1]->text.assign(str);  

  LcdLine(119, 0, 119, 7);
  if(getPasswordEntered()) 
    LcdText(121, 1, 127, 7, "*");
  
  usScreen::Paint();
};

void PwmTestScreen::ActiveLoop()
{
  usScreen::ActiveLoop();
};

void PwmTestScreen::Activated(unsigned long *param)
{
  usScreen::Activated(param);
  SetIntValueByTag(PWM_OUT_TEST_FLAG, 1);
};

PwmTestScreen::~PwmTestScreen()
{
  SetIntValueByTag(PWM_OUT_TEST_FLAG, 0);
};