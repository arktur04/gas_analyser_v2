extern "C"{
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "keyb.h"
#include "timers.h"
//#include "messages.h"
#include "variables.h"
#include "screens.h"
   #include "messages.h"
};

//#include "msg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>


#include "trend_scr.h"
#include "usbase.h"

TrendScreen::TrendScreen(int _var_tag, float _min, float _max, char scr_id):
  usScreen(MSG_TREND_SCREEN_ACTIVATE, scr_id)
{
  var_tag = _var_tag;
  min = _min;
  max = _max;
  curr_pos = 0;
//  message_to_activate = MSG_TREND_SCREEN_ACTIVATE;
  /*
  for(i = 1; i < TREND_SIZE - 1)
    trend_values[i] = sin(i)
  */
};

void TrendScreen::PlaceControls()
{
  AddControl(new usBmpButton(110, 9, 17, 18, 0, BTN_FORWARD, MSG_BTN_FORWARD,
                             scr_id));
  AddControl(new usBmpButton(110, 27, 17, 18, 1, BTN_HOME, MSG_BTN_HOME,
                             scr_id));
  AddControl(new usBmpButton(110, 45, 17, 18, 2, BTN_BACK, MSG_BTN_BACKWARD,
                             scr_id));  
};

void TrendScreen::Paint(void)
{ 
  float y_step;
  char str[20], str1[10];
  
   LcdClear();
  SetFont(SMALL_FONT);
  str[0] = 0;
  
  strcpy(str, "Тренд ");
  strcat(str, GetNameByTag(var_tag));
  
  LcdText(1, 0, 118, 7, str);
  LcdLine(0, 8, 127, 8);  
  LcdLine(0, 9, 127, 9);
  LcdLine(0, 55, 110, 55);
  
  LcdLine(25, 10, 25, 55); 
  LcdLine(105, 20, 105, 55);
  
  LcdLine(105, 20, 105, 55);
  LcdLine(83, 10, 83, 20);
  LcdLine(83, 20, 110, 20);

  for(char x = 30; x <= 30 + 2 * 25; x += 25)
    for(char y = 15; y <= 55; y += 10)
      LcdLine(x, y - 1, x, y + 1);
  
  for(char y = 15; y <= 45; y += 10)
    for(char x = 30; x <= 30 + 3 * 25; x += 25)
      LcdLine(x - 1, y, x + 1, y);
  
  for(char i = 0; i < curr_pos; i++)
    LcdLine(105 - i, ValueToCoord(trend_values[i - 1]),
            105 - i, ValueToCoord(trend_values[i]));
    
  LcdText(0, 56, 109, 63, "t,мин-15  -10  -5    0");
  
  y_step = (max - min) / 4.5;
  for(char i = 1; i  <= 4; i++)
  {
    sprintf(str, "%f", min + i * y_step);
    LcdText(0, 51 - i * 10, 24, 59 - i * 10, str);
  };
  
  sprintf(str, "%f", curr_value);
  LcdText(85, 12, 109, 19, str);
  
  usScreen::Paint();
};

char TrendScreen::ValueToCoord(float value)
{
  const char bottom_coord = 55;
  const char top_coord = 10;
  float a, coord;//, b;
  a = (top_coord - bottom_coord) / (max - min);
//  b = top_coord - a * max;
  coord = top_coord - a * (max - value);
  coord = (coord < bottom_coord)?coord:bottom_coord;
  coord = (coord > top_coord)?coord:top_coord;
  return (char)coord;
};

void TrendScreen::Shift()
{
  if(curr_pos < TREND_SIZE - 1)
    curr_pos++;
  
  for(char i = curr_pos; i > 0; i--)
    trend_values[i] = trend_values[i - 1];
  
  trend_values[0] = curr_value;
};

void TrendScreen::ActiveLoop()
{
  
  if(GetTimer(TREND_REFRESH_TIMER) >= 100)
      {
        curr_value = GetFloatValueByTag(var_tag);
        Shift();
        ResetTimer(TREND_REFRESH_TIMER); 
      };
  
  usScreen::ActiveLoop();
};
