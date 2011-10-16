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
#include "param_scr.h"
#include "usbase.h"
#include "pass_aux_base_class.h"

ParamScreen::ParamScreen(char _scr_num, int _scr_id):
  PassAuxBaseScreen(MSG_PARAM_SCREEN_ACTIVATE, _scr_id)
{
  scr_num = _scr_num;
};

void ParamScreen::PlaceControls()
{
  T_PARAM_SCREEN_DESCRIPTOR screen;

  screen = GetScreen(scr_num).scr.param_screen;  
  
  AddControl(new usBmpButton(110, 9, 17, 18, 0, BTN_FORWARD, MSG_BTN_FORWARD, 
                             scr_id));
  AddControl(new usBmpButton(110, 27, 17, 18, 1, BTN_HOME, MSG_BTN_HOME,
                             scr_id));
  AddControl(new usBmpButton(110, 45, 17, 18, 2, BTN_BACK, MSG_BTN_BACKWARD, 
                             scr_id));  
  for(char y = 0; y < 5; y++)
  {
    if(screen.var[y] == EMPTY_CELL)
      break;
    
    AddControl(pBtns[y] = new usTextButton(49, y * 11 + 9,
                                           33, 11, y + 3,
                                           "", BS_SIMPLE,
                                           MSG_BTN_EDIT, 
                                           screen.var[y]));
  };
};

void ParamScreen::UpdateButtonValues(T_PARAM_SCREEN_DESCRIPTOR screen)
{
  #define BUF_SIZE 10
  char str[BUF_SIZE];
  int tag;
   
  for(int i = 0; i < 5; i++)
  {
    tag = screen.var[i];
    DrawTableLine(tag, i);
    if(tag != EMPTY_CELL)
    {
      GetStringByTag(tag, ID_CURR_VAL, str, BUF_SIZE);
      pBtns[i]->text.assign(str);
    };
  }; 
};

void ParamScreen::DrawTableLine(int tag, char line)
{
  if(tag != EMPTY_CELL)
  {
    LcdText(1, line * 11 + 11, 48, line * 11 + 18, GetNameByTag(tag));
  };
 /*   if(ps_focus == line)
    {
      LcdSetColor(BLACK);
      LcdRect(50, line * 11 + 10, 80, line * 11 + 19);
      LcdSetColor(WHITE);
    }; */
  if(tag != EMPTY_CELL)
  {
   // LcdText(51, line * 11 + 11, 80, line * 11 + 18, str);
    LcdSetColor(BLACK);
    LcdText(84, line * 11 + 11, 109, line * 11 + 18, GetUnitByTag(tag));
  };
};

void ParamScreen::Paint(void)
{   
  T_PARAM_SCREEN_DESCRIPTOR screen;
  
  screen = GetScreen(scr_num).scr.param_screen;  
  LcdClear();
  SetFont(SMALL_FONT);
  LcdText(1, 0, 118, 7, screen.header);
  LcdLine(0, 8, 127, 8);
  LcdLine(0, 9, 127, 9); 
  for(int i = 0; (i < 5) && (screen.var[i] != EMPTY_CELL); i++)
    LcdLine(0, 20 + i * 11, 127, 20 + i * 11);
  
/*  LcdLine(0, 20, 109, 20);  
  LcdLine(0, 31, 109, 31);  
  LcdLine(0, 42, 109, 42);  
  LcdLine(0, 53, 109, 53); */
  
 // LcdLine(49, 10, 49, 63);
 // LcdLine(81, 10, 81, 63);
  LcdLine(119, 0, 119, 7);
  if(getPasswordEntered()) 
    LcdText(121, 1, 127, 7, "*");
  UpdateButtonValues(screen);   
   
  PassAuxBaseScreen::Paint();
};
/*
void ParamScreen::Activated(unsigned long *param)                                   //to remove ???
{
  PassAuxBaseScreen::Activated();//(param);
};

void ParamScreen::ActiveLoop(void)                            
{
  PassAuxBaseScreen::ActiveLoop();
};
*/