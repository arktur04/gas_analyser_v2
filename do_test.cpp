extern "C"{
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "keyb.h"
// #include "timers.h"
#include "variables.h"
#include "screens.h"
#include "pass_controller.h"
};

#include "messages.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "do_test.h"
#include "usbase.h"

/*

class DoTestScreen: public usScreen
{
private:
  usCheckBox* pCheckBox[3][2];
  
  usBmpButton* pBmpButtons[3];
  char scr_num;
protected:
 // virtual void Update(void);
  virtual void Paint(void);
public:
  DoTestScreen();
};
*/

DoTestScreen::DoTestScreen():usScreen(MSG_DISCR_OUT_TEST_SCREEN_ACTIVATE,
                                      SCR_DO_TEST)
{
};

int DoTestScreen::getTag(char x)
{
  int discr_out[6] = {RELAY_OUT_0, RELAY_OUT_1, RELAY_OUT_2, RELAY_OUT_3,
  RELAY_OUT_4, RELAY_OUT_5};
  return discr_out[x];
};

void DoTestScreen::PlaceControls()
{
  AddControl(new usBmpButton(110, 9, 17, 18, 0, BTN_FORWARD, MSG_BTN_FORWARD,
                             SCR_DO_TEST));
  AddControl(new usBmpButton(110, 27, 17, 18, 1, BTN_HOME, MSG_BTN_HOME,
                             SCR_DO_TEST));
  AddControl(new usBmpButton(110, 45, 17, 18, 2, BTN_BACK, MSG_BTN_BACKWARD,
                             SCR_DO_TEST));   
  
  for(char y = 0; y < 3; y++)
    for(char x = 0; x < 2; x++)
      AddControl(pCheckBox[y][x] = new usCheckBox(x * 55 + 43, y * 11 + 11,
                                                  y + x * 3 + 3,
                                                  MSG_CHECKBOX, 
                                                  getTag(y * 2 + x)));
};

void DoTestScreen::Paint(void)
{ 
  LcdClear();
  SetFont(SMALL_FONT);
  LcdText(1, 0, 118, 7, "Тест дискретных выходов");
  LcdLine(0, 8, 127, 8);  
  LcdLine(0, 9, 127, 9);  
  
  LcdText(5,  12, 40, 19, "Выход 1");
  LcdText(60, 12, 95, 19, "Выход 2");
  LcdText(5,  23, 40, 30, "Выход 3");
  LcdText(60, 23, 95, 30, "Выход 4");
  LcdText(5,  34, 40, 41, "Выход 5");
  LcdText(60, 34, 95, 41, "Выход 6");
  
  for(char y = 0; y < 3; y++)
    for(char x = 0; x < 2; x++)
      pCheckBox[y][x]->setChecked(GetIntValueByTag(getTag(y * 2 + x)));
  
  LcdLine(119, 0, 119, 7);
  if(GetPasswordEntered()) 
    LcdText(121, 1, 127, 7, "*");
  
  usScreen::Paint();
};

void DoTestScreen::ActiveLoop()
{
  usScreen::ActiveLoop();
};

void DoTestScreen::Activated(unsigned long * param)
{
  usScreen::Activated(param);
  SetIntValueByTag(RELAY_OUT_TEST_FLAG, 1);
};

DoTestScreen::~DoTestScreen()
{
  SetIntValueByTag(RELAY_OUT_TEST_FLAG, 0);
};
