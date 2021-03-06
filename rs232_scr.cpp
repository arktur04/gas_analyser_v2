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

//#include "msg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rs232_scr.h"
#include "usbase.h"
#include "pass_aux_base_class.h"

Rs232Screen::Rs232Screen():PassAuxBaseScreen(MSG_RS232_SCREEN_ACTIVATE, SCR_RS232)
{
 // message_to_activate = MSG_RS232_SCREEN_ACTIVATE;   
};

void Rs232Screen::PlaceControls()
{
  AddControl(new usBmpButton(110, 9, 17, 18, 0, BTN_FORWARD, MSG_BTN_FORWARD, SCR_RS232));
  AddControl(new usBmpButton(110, 27, 17, 18, 1, BTN_HOME, MSG_BTN_HOME, SCR_RS232));
  AddControl(new usBmpButton(110, 45, 17, 18, 2, BTN_BACK, MSG_BTN_BACKWARD, SCR_RS232)); 
  
  AddControl(pBtns[0] = new usTextButton(49, 9, 37, 11, 3, "",
                                         BS_SIMPLE, MSG_BTN_EDIT, RS_232_SPEED));
  
  AddControl(new usCheckBox(60, 21, 4, MSG_CHECKBOX, RS_232_EVEN));
  AddControl(new usCheckBox(95, 21, 5, MSG_CHECKBOX, RS_232_ODD));

  AddControl(pBtns[1] = new usTextButton(49, 31, 17, 11, 6, "",
                                         BS_SIMPLE, MSG_BTN_EDIT, RS_232_STOP)); 
};

void Rs232Screen::Paint(void)
{ 
  char str[10];
  
  LcdClear();
  SetFont(SMALL_FONT);
  LcdText(1, 0, 118, 7, "��������� RS-232");
  LcdLine(0, 8, 127, 8);  
  LcdLine(0, 9, 127, 9);  
  
  LcdLine(0, 20, 109, 20);  
  LcdLine(0, 31, 109, 31);  
  LcdLine(0, 42, 109, 42);  
  //LcdLine(0, 53, 109, 53);
  
  // LcdLine(20, 10, 20, 52);
  // LcdLine(62, 10, 62, 52);
  // LcdLine(84, 10, 84, 52);
  
  LcdText(0, 11, 44, 19, "��������:");
  LcdText(0, 22, 59, 30, "��������:���");
  LcdText(70, 22, 94, 30, "�����");
  
  LcdText(0, 33, 44, 41, "����.���:");
 // LcdText(0, 44, 44, 52, "   �����:");
  
  GetStringByTag(RS_232_SPEED, ID_CURR_VAL, str, 10);
  pBtns[0]->text.assign(str);
  
  GetStringByTag(RS_232_STOP, ID_CURR_VAL, str, 10);
  pBtns[1]->text.assign(str);
 /* 
  GetStringByTag(RS_485_ADDR, ID_CURR_VAL, str, 10);
  pBtns[2]->text.assign(str);
 */ 
  
  LcdLine(119, 0, 119, 7);
  if(getPasswordEntered()) 
    LcdText(121, 1, 127, 7, "*");
  PassAuxBaseScreen::Paint();
};

void Rs232Screen::ActiveLoop()
{
  PassAuxBaseScreen::ActiveLoop();
};
