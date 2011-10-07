extern "C"{
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "keyb.h"
// #include "timers.h"
#include "messages.h"
#include "variables.h"
#include "screens.h"
#include "pass_controller.h"  
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lut_scr.h"
#include "usbase.h"

LutScreen::LutScreen(char _scr_num, int _scr_id):
  usScreen(MSG_CLAPP_SCREEN_ACTIVATE, _scr_id)
{
  
  scr_num = _scr_num;
  
  screen = GetScreen(scr_num).scr.clapp_screen;
  
//  char btn;
 // message_to_activate = MSG_CLAPP_SCREEN_ACTIVATE;  
};

void LutScreen::PlaceControls(){
  const char buf_size = 10;
  char str[buf_size];
  AddControl(new usBmpButton(110, 9, 17, 18, 0, BTN_FORWARD, MSG_BTN_FORWARD,
                             scr_id));
  AddControl(new usBmpButton(110, 27, 17, 18, 1, BTN_HOME, MSG_BTN_HOME,
                             scr_id));
  AddControl(new usBmpButton(110, 45, 17, 18, 2, BTN_BACK, MSG_BTN_BACKWARD, 
                             scr_id));  
  
  for(char y = 0; y < 5; y++)
    for(char x = 0; x < 2; x++)
    {
      GetStringByTag((x?screen.var[y].x:screen.var[y].y), ID_CURR_VAL,
                     str, buf_size);
      
      AddControl(pBtns[y][x] = new usTextButton(x?78:22, y * 11 + 9,
                                                33, 11, y + 5 * x + 3,  str,
                                                BS_SIMPLE, MSG_BTN_EDIT,
                                                x?screen.var[y].y:screen.var[y].x));
    };
};

void LutScreen::DrawTableLine(int tag_x, int tag_y, char line)
{
  const char buf_size = 10;
  char str[buf_size];
  
  if(tag_x != EMPTY_CELL)
  {
    LcdText(1, line * 11 + 11, 21, line * 11 + 18, GetNameByTag(tag_x));
    LcdText(57, line * 11 + 11, 77, line * 11 + 18, GetNameByTag(tag_y));
    
 /*   if(cls_focus == (line * 2))
   
      LcdSetColor(BLACK);
      LcdRect(22, line * 11 + 10, 53, line * 11 + 19);
      LcdSetColor(WHITE);
    };
    */
    /*
    GetStringByTag(tag_x, ID_CURR_VAL, str, BUF_SIZE);
    LcdText(23, line * 11 + 11, 52, line * 11 + 18, str);
    LcdSetColor(BLACK);
    */
    /*
    if(cls_focus == (line * 2 + 1))
    {
      LcdSetColor(BLACK);
      LcdRect(78, line * 11 + 10, 109, line * 11 + 19);
      LcdSetColor(WHITE);
    };
    */
    /*
    GetStringByTag(tag_y, ID_CURR_VAL, str, BUF_SIZE);
    LcdText(79, line * 11 + 11, 108, line * 11 + 18, str);
    LcdSetColor(BLACK);
    */
  }
};

void LutScreen::Paint(void)
{ 
  int tag;
  const char buf_size = 10;
  char str[buf_size];
  T_CLAPP_SCREEN_DESCRIPTOR screen;
  screen = GetScreen(scr_num).scr.clapp_screen;
  
  LcdClear();
  SetFont(SMALL_FONT);
  LcdText(1, 0, 118, 7, screen.header);
  LcdLine(0, 8, 127, 8);  
  LcdLine(0, 9, 127, 9);
  LcdLine(0, 20, 109, 20);  
  LcdLine(0, 31, 109, 31);  
  LcdLine(0, 42, 109, 42);  
  LcdLine(0, 53, 109, 53); 
  
  for(char y = 0; y < 5; y++)
    for(char x = 0; x < 2; x++)
    {
       DrawTableLine(screen.var[y].x, screen.var[y].y, y);
       GetStringByTag((x?screen.var[y].y:screen.var[y].x), ID_CURR_VAL, str,
                      buf_size);
       pBtns[y][x]->text.assign(str);
    };
  
  LcdLine(119, 0, 119, 7);
  if(GetPasswordEntered()) 
    LcdText(121, 1, 127, 7, "*");
  usScreen::Paint();
}
/*
void LutScreen::Activated(unsigned long *param)                                   //to remove ???
{
  usScreen::Activated();//(param);
};

void LutScreen::ActiveLoop(void)                              
{
 usScreen::ActiveLoop();
};
*/