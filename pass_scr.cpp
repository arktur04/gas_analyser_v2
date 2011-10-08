//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------
extern "C"
{
#include "keyb.h"
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "screens.h"
#include "variables.h"
#include "messages.h"
#include "pass_controller.h"
};
#include <string>
#include "usbase.h"
#include "pass_scr.h"

void PassScreen::PlaceControls(void)
{
  AddControl(editor = new usEditor(37, 25, 54, 13, 0));
  
  AddControl(new usTextButton(15, 44, 42, 11,
                              1, "Отмена", MSG_BTN_CANCEL, SCR_PASS)); 
  AddControl(new usTextButton(71, 44, 42, 11,
                              2, "ОК", MSG_BTN_OK, SCR_PASS)); 
};

void PassScreen::Activated(unsigned long * param)
{
  T_VAR zero;
  zero.ival = 0;
  usScreen::Activated(param);
  //   ActivateFocusedControl(); 
  editor->setMode(EM_INT);
  editor->setValue(zero);
  ActivateFocusedControl(); //editor
  
  SendParamMessage(MSG_CHILD_SCREEN_ACTIVATE, SCR_PASS);
};

void PassScreen::ActiveLoop(void)
{
  unsigned long param;
 // MESSAGE msg;
  usScreen::ActiveLoop();
  if(GetMessage(MSG_EDITOR_FINISHED))
  {
    SetFocus(2);
    Update();
  };
  if(GetMessage(MSG_EDITOR_CANCELLED))
  {
    SetFocus(1);
    Update();
  };

  if(GetMessage(MSG_EDITOR_KEY_UP))
  {
    SetFocus(2);
    Update();
  };
  if(GetMessage(MSG_EDITOR_KEY_DOWN))
  {
    SetFocus(2);
    Update();
  };
  
  if(GetParamMessage(MSG_BTN_OK, &param))
  {
    if(param == SCR_PASS)
    {
      SendParamMessage(MSG_CHILD_SCREEN_DEACTIVATED, SCR_PASS);
      if(editor->getValue().ival == 1111)   //  password 1                                               
      {
        SendMessage(MSG_PASS1_OK);
      }
      else
      {
        if(editor->getValue().ival == 3141)        //  password 2                                          
        {
          SendMessage(MSG_PASS2_OK);
        }
        else
        {
          if(editor->getValue().ival == 1337)    //  password 3
          {
            SendMessage(MSG_PASS3_OK);
          }
          else
          {
            SendMessage(MSG_PASS_WRONG);
          };
        };
      };
    };
  };
 
  if(GetParamMessage(MSG_BTN_CANCEL, &param))
  {
    if(param == SCR_PASS)
    {
      SendParamMessage(MSG_CHILD_SCREEN_DEACTIVATED, SCR_PASS);
      SendMessage(MSG_PASS_CANCEL);
    };
  };
};

void PassScreen::Paint(void)
{
  LcdSetColor(WHITE);
  LcdRect(1, 7, 126, 57);
  LcdSetColor(BLACK);
  LcdFrame(1, 7, 126, 57);
  
  //-------------------------
  SetFont(SMALL_FONT);

  LcdText(37, 12, 125, 20, "Введите пароль");
  
  LcdBmp(9, 19,
         GetBmpWidth(BMP_KEY_INPUT), GetBmpHeight(BMP_KEY_INPUT),
         GetBmp(BMP_KEY_INPUT));
  
  usScreen::Paint();
};