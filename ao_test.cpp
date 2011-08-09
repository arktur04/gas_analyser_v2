extern "C"{
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "keyb.h"
#include "timers.h"
#include "variables.h"
#include "screens.h"
#include "pass_controller.h"
};

#include "messages.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ao_test.h"
#include "usbase.h"

static const int dac_tags[] = {DAC_1, DAC_2, DAC_3, DAC_4};

AoTestScreen::AoTestScreen():usScreen(MSG_DAC_OUT_TEST_SCREEN_ACTIVATE, SCR_AO_TEST)
{
 // message_to_activate = MSG_DAC_OUT_TEST_SCREEN_ACTIVATE;  
};

void AoTestScreen::Activated(unsigned long *param)
{
  usScreen::Activated(param);
  SetIntValueByTag(DAC_TEST_FLAG, 1);
}
  
void AoTestScreen::PlaceControls()
{
 // int dac_tags[4] = {DAC_1, DAC_2, DAC_3, DAC_4};
  AddControl(new usBmpButton(110, 9, 17, 18, 0, BTN_FORWARD, MSG_BTN_FORWARD, 
                             SCR_AO_TEST));
  AddControl(new usBmpButton(110, 27, 17, 18, 1, BTN_HOME, MSG_BTN_HOME, 
                             SCR_AO_TEST));
  AddControl(new usBmpButton(110, 45, 17, 18, 2, BTN_BACK, MSG_BTN_BACKWARD, 
                             SCR_AO_TEST));
    
  for(char y = 0; y < 4; y++)
    AddControl(pBtns[y] = new usTextButton(49, y * 11 + 9, 32, 11, y + 3,
                                           "", BS_SIMPLE,
                                           MSG_BTN_EDIT, dac_tags[y]));
};

void AoTestScreen::DrawTableLine(int tag, char line)
{
  LcdText(1, line * 11 + 11, 48, line * 11 + 18, GetNameByTag(tag));
  LcdSetColor(BLACK);
  LcdText(83, line * 11 + 11, 109, line * 11 + 18, GetUnitByTag(tag));
};

void AoTestScreen::UpdateButtonValues()
{
  #define BUF_SIZE 10
  char str[BUF_SIZE];

  for(char i = 0; i < 4; i++)
  {
    DrawTableLine(dac_tags[i], i);
    GetStringByTag(dac_tags[i], ID_CURR_VAL, str, BUF_SIZE);
    pBtns[i]->text.assign(str);
  };
};
  
void AoTestScreen::AoTestScreen::Paint(void)
{ 
  char str[10];
  
   LcdClear();
  SetFont(SMALL_FONT);
  LcdText(1, 0, 118, 7, "Тест аналоговых выходов");
  LcdLine(0, 8, 127, 8);  
  LcdLine(0, 9, 127, 9);  

  LcdLine(0, 20, 109, 20);  
  LcdLine(0, 31, 109, 31);  
  LcdLine(0, 42, 109, 42);  
  LcdLine(0, 53, 109, 53);

  UpdateButtonValues();

  LcdLine(119, 0, 119, 7);
  if(GetPasswordEntered()) 
    LcdText(121, 1, 127, 7, "*");
  
  usScreen::Paint();
};

void AoTestScreen::ActiveLoop()
{
  usScreen::ActiveLoop();
};

AoTestScreen::~AoTestScreen()
{
  SetIntValueByTag(DAC_TEST_FLAG, 0);
}