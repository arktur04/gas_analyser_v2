extern "C"{
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "keyb.h"
#include "timers.h"
#include "messages.h"
#include "variables.h"
#include "screens.h"
#include "pass_controller.h"  
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "twocolscr.h"
#include "usbase.h"
#include "tagvaluelabel.h"

TwoColSrc::TwoColSrc(char _scr_num, int _scr_id):
  usScreen(MSG_TWOCOL_SCREEN_ACTIVATE, _scr_id)
{
  scr_num = _scr_num;
 // message_to_activate = MSG_TC_CALIBR_SCREEN_ACTIVATE;   
  screen = GetScreen(scr_num).scr.two_col_screen;
};

void TwoColSrc::PlaceControls()
{
  AddControl(new usBmpButton(110, 9, 17, 18, 0, BTN_FORWARD, MSG_BTN_FORWARD, 
                             scr_id));
  AddControl(new usBmpButton(110, 27, 17, 18, 1, BTN_HOME, MSG_BTN_HOME, 
                             scr_id));
  AddControl(new usBmpButton(110, 45, 17, 18, 2, BTN_BACK, MSG_BTN_BACKWARD, 
                             scr_id));  
  
  for(char y = 0; y < 5; y++)
    for(char x = 0; x < 2; x++)
    {
      if(screen.var[y][x] != EMPTY_CELL)
        AddControl(pBtns[y][x] = new usTagValueLabel(x?77:21, y * 11 + 9,
                                                     33, 11, y + 5 * x + 3,  
                                                     screen.var[y][x]));
    };
};

void TwoColSrc::DrawTableLine(int tag_1, int tag_2, char line)
{
 // const char buf_size = 10;
 // char str[buf_size];
  if(tag_1 != EMPTY_CELL)
  {
    LcdText(1, line * 11 + 11, 21, line * 11 + 18, GetNameByTag(tag_1));
  };
  if(tag_2 != EMPTY_CELL)
  {
    LcdText(57, line * 11 + 11, 77, line * 11 + 18, GetNameByTag(tag_2));
  };
}

void TwoColSrc::Paint(void)
{
  const char buf_size = 10;
  char str[buf_size];
  T_TWO_COL_SCREEN_DESCRIPTOR screen = GetScreen(scr_num).scr.two_col_screen;
  
  LcdClear();
  SetFont(SMALL_FONT);//
  
  LcdText(1, 0, 118, 7, screen.header);
  LcdLine(0, 8, 127, 8);  
  LcdLine(0, 9, 127, 9);
  LcdLine(0, 20, 109, 20);
  LcdLine(0, 31, 109, 31);  
  LcdLine(0, 42, 109, 42);  
  LcdLine(0, 53, 109, 53);
  LcdLine(54, 10, 54, 63);  
  LcdLine(55, 10, 55, 63);
  
  for(char y = 0; y < 5; y++)
    for(char x = 0; x < 2; x++)
    {
       DrawTableLine(screen.var[y][0], screen.var[y][1], y);
       GetStringByTag(screen.var[y][x], ID_CURR_VAL, str, buf_size);
    };

  LcdLine(119, 0, 119, 7);
  if(getPasswordEntered()) 
    LcdText(121, 1, 127, 7, "*");
  
  usScreen::Paint();
};
