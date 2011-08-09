//------------------------------------------------------------------------------
// Модуль реализует окно сообщений
//------------------------------------------------------------------------------
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "buttons.h"
#include "message_window.h"
#include "messages.h"
#include "keyb.h"

char mw_focus = 0, mw_state = 0;
char* _message_line1;
char* _message_line2;
char* _message_line3;
char _buttons;
                         
void SetMessageScreenMode(char* message_line1, char* message_line2,
                       char* message_line3, char buttons)
{
 _message_line1 = message_line1;
 _message_line2 = message_line2;
 _message_line3 = message_line3;
 _buttons = buttons;
}

void DrawMessageWindow(void)
{
  SetFont(SMALL_FONT);
  LcdSetColor(WHITE);
  LcdRect(5, 9, 123, 54);
  LcdSetColor(BLACK);
  
  LcdLine(6,   9,   122, 9);
  LcdLine(6,   55,  122, 55);
  LcdLine(4,   11,  4,   53);
  LcdLine(124, 11,  124, 53);
  
  LcdLine(5,   10,  5,   10);
  LcdLine(5,   54,  5,   54);
  LcdLine(123, 10,  123, 10);
  LcdLine(123, 54,  123, 54);
  
  LcdBmp(6, 26, GetBmpWidth(BMP_EXLAMATION), GetBmpHeight(BMP_EXLAMATION), GetBmp(BMP_EXLAMATION)); 
  //LcdBmp(6, 26, BMP_KEY_INPUT_WIDTH, BMP_KEY_INPUT_HEIGHT, bmp_key_input); 
  
  LcdText(29, 12, 122, 18,_message_line1);
  LcdText(29, 21, 122, 27, _message_line2);
  LcdText(29, 30, 122, 36, _message_line3);
  
  if(_buttons & MB_OK)
    DrawButton(29, 40, BTN_OK, mw_focus == 0);
  if(_buttons & MB_CANCEL)
    DrawButton(75, 40, BTN_CANCEL, mw_focus == 1);
  
  LcdDraw();
};

void ProcessMessageWindow(void)
{
  //--------------------------------------
  // mw_focus
  //--------------------------------------
  //  0         OK button
  //  1         Cancel button
/*
 switch(mw_state)
  {
    case 0://Inactive state
      if(GetMessage(MSG_MESSAGE_SCREEN_ACTIVATE))
      {
        mw_state = 1;
        mw_focus = 0;
        DrawMessageWindow();
      };
      break;
    case 1: //active state;
      if(GetMessage(MSG_KEY_PRESSED))
        switch (GetKeyCode())
        {
        case KEY_RIGHT:
          if((mw_focus == 0) && (_buttons & MB_OK))
          {
            mw_focus = 1;
            DrawMessageWindow();
          };
          break;
        case KEY_LEFT:
          if((mw_focus == 1) && (_buttons & MB_CANCEL))
          {
            mw_focus = 0;
            DrawMessageWindow();
          };
          break;
        case KEY_ENTER:
          mw_state = 0;
          mw_focus = 0;
          if(mw_focus == 0)
            SendMessage(MSG_MESSAGE_SCREEN_OK);
          if(mw_focus == 1)
            SendMessage(MSG_MESSAGE_SCREEN_CANCEL);
          break;
        };
      break;
   };
  */                                                                                //temporary removed
};
