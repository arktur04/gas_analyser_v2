extern "C"{
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "keyb.h"
#include "timers.h"
#include "variables.h"
#include "screens.h"
#include "messages.h"
#include "pass_controller.h"
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ai_test.h"
#include "usbase.h"
#include "pass_aux_base_class.h"

AiTestScreen::AiTestScreen():PassAuxBaseScreen(MSG_ADC_IN_TEST_SCREEN_ACTIVATE, SCR_AI_TEST)
{
 // message_to_activate = MSG_ADC_IN_TEST_SCREEN_ACTIVATE;  
};

void AiTestScreen::PlaceControls(){
  AddControl(new usBmpButton(110, 9, 17, 18, 0, BTN_FORWARD, MSG_BTN_FORWARD, SCR_AI_TEST));
  AddControl(new usBmpButton(110, 27, 17, 18, 1, BTN_HOME, MSG_BTN_HOME, SCR_AI_TEST));
  AddControl(new usBmpButton(110, 45, 17, 18, 2, BTN_BACK, MSG_BTN_BACKWARD, SCR_AI_TEST));  
};

void AiTestScreen::Paint(void)
{ 
  char str[10];
  
   LcdClear();
  SetFont(SMALL_FONT);
  LcdText(1, 0, 118, 7, "Тест аналоговых входов");
  LcdLine(0, 8, 127, 8);
  LcdLine(0, 9, 127, 9);

  LcdLine(0, 20, 109, 20);
  LcdLine(0, 31, 109, 31);
  LcdLine(0, 42, 109, 42);
  LcdLine(0, 53, 109, 53);
  
  LcdLine(20, 10, 20, 52);
  LcdLine(62, 10, 62, 52);
  LcdLine(84, 10, 84, 52);
  
  LcdText(0, 11, 19, 19, "ADC1");
  LcdText(0, 22, 19, 30, "ADC2");
  LcdText(0, 33, 19, 41, "ADC3");
  LcdText(0, 44, 19, 52, "ADC4");
  
  LcdText(64, 11, 83, 19, "AD1'");
  LcdText(64, 22, 83, 30, "AD2'");
  LcdText(64, 33, 83, 41, "AD3'");
  LcdText(64, 44, 83, 52, "AD4'");

  //ADC
  sprintf(str, "%X", adc1_code);
  LcdText(22, 11, 61, 19, str);
  sprintf(str, "%X", adc2_code);
  LcdText(22, 22, 61, 30, str);
  sprintf(str, "%X", adc3_code);
  LcdText(22, 33, 61, 41, str);
  sprintf(str, "%X", adc4_code);
  LcdText(22, 44, 61, 52, str);
  
  sprintf(str, "%X", adc1_code_);
  LcdText(88, 11, 107, 19, str);
  sprintf(str, "%X", adc2_code_);
  LcdText(88, 22, 107, 30, str);
  sprintf(str, "%X", adc3_code_);
  LcdText(88, 33, 107, 41, str);
  sprintf(str, "%X", adc4_code_);
  LcdText(88, 44, 107, 52, str);

  LcdLine(119, 0, 119, 7);
  if(getPasswordEntered()) 
    LcdText(121, 1, 127, 7, "*");
  
  PassAuxBaseScreen::Paint();
};

void AiTestScreen::ActiveLoop()
{
 // if(GetTimer(SCREEN_REFRESH_TIMER) >= 50)
     // {
        adc1_code = GetIntValueByTag(ADC_1);
        adc2_code = GetIntValueByTag(ADC_2);
        adc3_code = GetIntValueByTag(ADC_3);
        adc4_code = GetIntValueByTag(ADC_4);
        
        adc1_code_ = GetIntValueByTag(ADC_1_);
        adc2_code_ = GetIntValueByTag(ADC_2_);
        adc3_code_ = GetIntValueByTag(ADC_3_);
        adc4_code_ = GetIntValueByTag(ADC_4_);
        
   //     ResetTimer(SCREEN_REFRESH_TIMER); 
        Update();
     // };
  PassAuxBaseScreen::ActiveLoop();
};
