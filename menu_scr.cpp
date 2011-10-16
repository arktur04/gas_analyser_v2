extern "C"{
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "keyb.h"
#include "timers.h"
#include "messages.h"
#include "variables.h"
#include "pass_controller.h"
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu_scr.h"
#include "usbase.h"

#define MAX_MENU 5

const T_MENU_DESCRIPTOR menues[MAX_MENU] = {
  {" Главное меню",
  {
    "Л.термост.", "П.термост.",
    "Л.кислород", "П.кислород",
    "Л.химнед.",  "П.химнед.",
    "Л.пороги",   "П.пороги",
    "Пароль", ""
  },
  {3, 8, 4, 9, 5, 10, 6, 11, 7, -1},
  0,
  true, true, true
  },

  {" Меню тестов",
  {"Дискр.вых.",  "Ан.входы",
  "Ан.выходы",   "Сил.вых.",
  "","", //"Тест RS232", "Тест RS485",
  "", "",
  "", ""
  },
  {3, 5, 4, 6, -1, -1, -1, -1, -1, -1},
  0,
  true, true, true
  },
  
  {" Меню калибровок",
  {
    "Вх. ТП лев", "Вх. ТП пр.",
    "Вх. ЧЭ лев", "Вх. ЧЭ пр.",
    "Выходы", "",
    "", "",
    "", ""
  },
  {3, 6, 4, 7, 5, -1, -1, -1, -1, -1},
  0,
  true, true, true
  },
  
  {" Порты",
  {"RS-232", "RS-485",
   "Ethernet", "",
   "", "",
   "", "",
   "", ""
  },
  {3, 5, 4, -1, -1, -1, -1, -1, -1, -1},
  0,
  true, true, true
  },
  
  {" Разное",
  {"По умолч.",  "Настр.обр.",
  // "Тренд л.т", "Тренд п.т",
   "Разное", "",
   "", "",
   "", "",
   "", ""  
  },
  {3, 5, 4, -1, -1, -1, -1, -1, -1, -1},
  0,
  true, true, true
  }
};

MenuScreen::MenuScreen(char _scr_num, int _scr_id):
  PassAuxBaseScreen(MSG_MENU_SCREEN_ACTIVATE, _scr_id)
{
  scr_num = _scr_num;
  auto_refresh = false;
};

void MenuScreen::PlaceControls()
{
 // char f_num, f_num2;
  AddControl(new usBmpButton(110, 9, 17, 18, 0, BTN_FORWARD, MSG_BTN_FORWARD,
                             scr_id));
  AddControl(new usBmpButton(110, 27, 17, 18, 1, BTN_HOME, MSG_BTN_HOME,
                             scr_id));
  AddControl(new usBmpButton(110, 45, 17, 18, 2, BTN_BACK, MSG_BTN_BACKWARD,
                             scr_id));  
  
//  f_num = 3;
  for(char y = 0; y < 5; y++)
    for(char x = 0; x < 2; x++)
      if(menues[scr_num].sec_order[x + y * 2] != -1)
      {
        AddControl(pTextButtons[x + y * 2] = 
                   new usTextButton(x * 55, y * 11 + 8,
                                    54, 11, menues[scr_num].sec_order[x + y * 2], //y + x * 5 + 3,
                                    menues[scr_num].buttons[x + y * 2], 
                                    MSG_BTN_MENU,
                                    (scr_num << 4) + x + y * 2));
      //  f_num++;
      };
  
//  AddControl(new usBmpButton(110, 45, 17, 18, f_num, BTN_BACK, MSG_BTN_BACKWARD,
  //                           scr_id));
};

void MenuScreen::Paint(void)
{ 
  
  LcdClear();
  LcdSetColor(BLACK);
  SetFont(SMALL_FONT);
  LcdText(0, 0, 127, 7, menues[scr_num].header);
  LcdLine(119, 0, 119, 8);
  if(getPasswordEntered()) 
    LcdText(121, 1, 127, 7, "*");  
 // LcdLine(0, 8, 127, 8);  
  
//  LcdSetColor(BLACK);
 // LcdFrame(109, 0, 127, 9);
 // LcdLine(111, 2, 111, 3);
 // LcdLine(111, 4, 111, 4);
  
  PassAuxBaseScreen::Paint();
};

void MenuScreen::ActiveLoop(void)   
{
  PassAuxBaseScreen::ActiveLoop(); 
};
