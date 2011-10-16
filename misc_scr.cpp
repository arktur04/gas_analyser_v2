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
#include "misc_scr.h"
#include "usbase.h"
#include "pass_aux_base_class.h"

//static const int dac_tags[] = {DAC_1, DAC_2, DAC_3, DAC_4};

MiscScreen::MiscScreen():PassAuxBaseScreen(MSG_MISC_SCREEN_ACTIVATE, SCR_MISC)
{
 // message_to_activate = MSG_DAC_OUT_TEST_SCREEN_ACTIVATE;  
};

void MiscScreen::Activated(unsigned long *param)
{
  PassAuxBaseScreen::Activated(param);
 // SetIntValueByTag(DAC_TEST_FLAG, 1);
}
  
void MiscScreen::PlaceControls()
{
 // int dac_tags[4] = {DAC_1, DAC_2, DAC_3, DAC_4};
  AddControl(new usBmpButton(110, 9, 17, 18, 0, BTN_FORWARD, MSG_BTN_FORWARD, 
                             SCR_MISC));
  AddControl(new usBmpButton(110, 27, 17, 18, 1, BTN_HOME, MSG_BTN_HOME, 
                             SCR_MISC));
  AddControl(new usBmpButton(110, 45, 17, 18, 2, BTN_BACK, MSG_BTN_BACKWARD, 
                             SCR_MISC));
  /*
  AddControl(pCheckBox[0] = new usCheckBox(46, 10,
                                           3, MSG_CHECKBOX, LEFT_CH_ON));

  AddControl(pCheckBox[1] = new usCheckBox(101, 10,
                                           4, MSG_CHECKBOX, RIGHT_CH_ON));
  
  AddControl(pBtns[0] = new usTextButton(0, 19, 54, 11, 5,
                                         "Сбр.л.защ.", 
                                         MSG_BTN_MISC,
                                         0));
  
  AddControl(pBtns[1] = new usTextButton(55, 19, 54, 11, 6,
                                         "Сбр.п.защ.", 
                                         MSG_BTN_MISC,
                                         1));
  */
  AddControl(pBtns[2] = new usTextButton(75, 10, 15, 11, 7,                      //changed from AddControl(pBtns[2] = new usTextButton(75, 30, 15, 11, 7,
                                         "", BS_SIMPLE,
                                         MSG_BTN_EDIT, SCR_BACKLIGHT_TIME));
  
  AddControl(pBtns[3] = new usTextButton(75, 21, 15, 11, 8,                     //  AddControl(pBtns[3] = new usTextButton(75, 41, 15, 11, 8,
                                         "", BS_SIMPLE,
                                         MSG_BTN_EDIT, PASS_RESET_TIME));
  
//  AddControl(pBtns[4] = new usTextButton(75, 52, 15, 11, 9,
//                                         "", BS_SIMPLE,
//                                         MSG_BTN_EDIT, PROTECT_RESET_TIME));  
};

void MiscScreen::UpdateButtonValues()
{
  const char BUF_SIZE = 10;
  char str[BUF_SIZE];
  GetStringByTag(SCR_BACKLIGHT_TIME, ID_CURR_VAL, str, BUF_SIZE);
  pBtns[2]->text.assign(str);
  
  GetStringByTag(PASS_RESET_TIME, ID_CURR_VAL, str, BUF_SIZE);
  pBtns[3]->text.assign(str);
  
  GetStringByTag(PROTECT_RESET_TIME, ID_CURR_VAL, str, BUF_SIZE);
  pBtns[4]->text.assign(str); 
};
  
void MiscScreen::Paint(void)
{ 
 // char str[10];
  
  LcdClear();
  SetFont(SMALL_FONT);
  LcdText(1, 0, 118, 7, "Разное");
  LcdLine(0, 8, 127, 8);  
  LcdLine(0, 9, 127, 9);  
  
//  LcdText(1, 11, 45, 17, "Л.кан.вкл");
//  LcdText(56, 11, 100, 17, "П.кан.вкл");
                                                  // was: 
  LcdText(1, 11, 74, 39, "Откл.подсв.экр.");   //LcdText(1, 31, 74, 39, "Откл.подсв.экр.");
  LcdText(92, 11, 109, 39, "мин");             //LcdText(92, 31, 109, 39, "мин");
  LcdText(1, 22, 74, 50, "Сброс пароля");      //LcdText(1, 42, 74, 50, "Сброс пароля");
  LcdText(92, 22, 109, 50, "мин");             //LcdText(92, 42, 109, 50, "мин");    
  
//  LcdText(1, 53, 74, 61, "Сброс защит");
//  LcdText(92, 53, 109, 61, "с");
  
  UpdateButtonValues();

  LcdLine(119, 0, 119, 7);
  if(getPasswordEntered()) 
    LcdText(121, 1, 127, 7, "*");
  
  PassAuxBaseScreen::Paint();
};

void MiscScreen::ActiveLoop()
{
  PassAuxBaseScreen::ActiveLoop();
};

MiscScreen::~MiscScreen()
{
 // SetIntValueByTag(DAC_TEST_FLAG, 0);
}
