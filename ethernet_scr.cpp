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

//#include "messages.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ethernet_scr.h"
#include "usbase.h"

EthernetScreen::EthernetScreen():usScreen(MSG_ETHERNET_SCREEN_ACTIVATE, SCR_ETHERNET)
{
 // message_to_activate = MSG_ETHERNET_SCREEN_ACTIVATE; 
};

int getTag(int x, int y)
{
  int eth_tags[3][4] = {{ETHERNET_IP_ADDR_0, ETHERNET_IP_ADDR_1,
  ETHERNET_IP_ADDR_2, ETHERNET_IP_ADDR_3}, {ETHERNET_IP_MASK_0,
  ETHERNET_IP_MASK_1, ETHERNET_IP_MASK_2, ETHERNET_IP_MASK_3}, 
  {ETHERNET_IP_GATE_0, ETHERNET_IP_GATE_1, ETHERNET_IP_GATE_2, 
  ETHERNET_IP_GATE_2}};
  return eth_tags[y][x];
};

void EthernetScreen::PlaceControls()
{
  AddControl(new usBmpButton(110, 9, 17, 18, 0, BTN_FORWARD, MSG_BTN_FORWARD, SCR_ETHERNET));
  AddControl(new usBmpButton(110, 27, 17, 18, 1, BTN_HOME, MSG_BTN_HOME, SCR_ETHERNET));
  AddControl(new usBmpButton(110, 45, 17, 18, 2, BTN_BACK, MSG_BTN_BACKWARD, SCR_ETHERNET)); 
  
  for(char y = 0; y < 3; y++ )
    for(char x = 0; x < 4; x++)
      AddControl(pBtns[y * 4 + x] = new usTextButton(30 + x * 20, 9 + y * 11,
                                                     20, 11, x + y * 4 + 3, "",
                                                     BS_SIMPLE, 
                                                     MSG_BTN_EDIT, getTag(x, y)));
};

void EthernetScreen::Paint(void)
{  
  #define BUF_SIZE 4
  char str[BUF_SIZE];
  u32 ip_addr, ip_mask, ip_gate;
  
  LcdClear();
  SetFont(SMALL_FONT);
  LcdText(1, 0, 118, 7, "Настройки TCP/IP");
  LcdLine(0, 8, 127, 8);  
  LcdLine(0, 9, 127, 9);  
  
  LcdLine(0, 20, 109, 20);  
  LcdLine(0, 31, 109, 31);  
  LcdLine(0, 42, 109, 42);  
 // LcdLine(0, 53, 109, 53);
  
  LcdText(0, 11, 29, 19, "   IP:");
  LcdText(0, 22, 29, 30, "Маска:");
  LcdText(0, 33, 29, 41, "Шлюз");
  
  for(int y = 0; y < 3; y++)
    for(int x = 0; x < 4; x++)
    {
      GetStringByTag(getTag(x, y), ID_CURR_VAL, str, BUF_SIZE);
      pBtns[y * 4 + x]->text.assign(str);
    }; 
  
  LcdLine(119, 0, 119, 7);
  if(getPasswordEntered()) 
    LcdText(121, 1, 127, 7, "*");

  usScreen::Paint();
};

void EthernetScreen::ActiveLoop()
{
  usScreen::ActiveLoop();
};
