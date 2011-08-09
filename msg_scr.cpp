//------------------------------------------------------------------------------
// Editor screen class
//------------------------------------------------------------------------------
extern "C"{
#include "keyb.h"
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "screens.h"
#include "messages.h"
#include "variables.h"
};
#include <string>
#include "usbase.h"
#include "msg_scr.h"

void MessageWindow::PlaceControls()
{
 if(btns == OK_MSW)
 {
  AddControl(new usTextButton(86, 44, 42, 11,
                              3, "ОК", MSG_BTN_OK, SCR_MSG));
 }
 if(btns == OK_CANCEL_MSW)
 {
  AddControl(new usTextButton(15, 44, 42, 11,
                              1, "Отмена", MSG_BTN_CANCEL, SCR_MSG)); 
  AddControl(new usTextButton(71, 44, 42, 11,
                              3, "ОК", MSG_BTN_OK, SCR_MSG));
 }
};

void MessageWindow::ActiveLoop(void)
{
  if(GetMessage(MSG_BTN_OK))
  {   
    SetDefaultValues();
    SendParamMessage(MSG_CHILD_SCREEN_DEACTIVATED, SCR_MSG);
  };
  
  if(GetMessage(MSG_BTN_CANCEL))
  {
    SendParamMessage(MSG_CHILD_SCREEN_DEACTIVATED, SCR_MSG);
  };
  
  usScreen::ActiveLoop();
};

void MessageWindow::Paint(void)
{
  LcdSetColor(WHITE);
  LcdRect(1, 7, 126, 57);
  LcdSetColor(BLACK);
  LcdFrame(1, 7, 126, 57);
  
  //-------------------------
  SetFont(SMALL_FONT);

  LcdText(20, 9, 125, 17, str1); 
  LcdText(20, 18, 125, 26, str2);
  LcdText(20, 27, 125, 35, str3);
  LcdText(20, 36, 125, 44, str4);
  
  LcdBmp(3, 19,
         GetBmpWidth(BMP_EXLAMATION), GetBmpHeight(BMP_EXLAMATION),
         GetBmp(BMP_EXLAMATION));
  
  usScreen::Paint();
};
