//------------------------------------------------------------------------------
// Модуль реализует экран установки параметров
//------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include "messages.h"
#include "type.h"
#include "keyb.h"
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "dict.h"
#include "buttons.h"
#include "message_window.h"
#include "variables.h"
#include "editor.h"
#include "editor_screen.h"

char pes_focus = 0;
char pes_state = 0;
T_VAR curr_pass_val;

char PassIsValid(void)
{
  return (GetEditorValue() == 31415.0);
 // return (curr_pass_val.ival == 31415);
}
/*
void SetDefaultValue(void)
{
  SetDefaulValueByTag(_tag);
}
*/
void DrawPassEditorScreen(void)  //
{
  char buffer1[50];
 // char buffer2[9];
 // char buffer3[9];

  //-------------------------
  SetFont(SMALL_FONT);
  LcdClear();

  LcdText(25, 8, 127, 7, "Введите пароль");
  /*
//  GetStringByTag(SHIFT_T_L, ID_CURR_VAL, buffer2, 8);
  LcdText(25, 8, 127, 15, "в диапазоне");
  
  GetStringByTag(SHIFT_T_L, ID_MIN, buffer2, 8);
  GetStringByTag(SHIFT_T_L, ID_MAX, buffer3, 8);
  sprintf(buffer1,"от %s до %s", buffer2, buffer3);
  LcdText(25, 16, 127, 23, buffer1);
  
//  SetEditorMode(GetTypeByTag(SHIFT_T_L), GetValueByTag(SHIFT_T_L));
  */
 // SetEditorMode(INT, (T_VAR) {.ival = 0});//, var.min_val, var.max_val);
  SetEditorCoord(25, 26, 80, 39);
  DrawEditor();
  /*
  sprintf(buffer1,", %s", GetUnitByTag(SHIFT_T_L));*/
  LcdText(82, 28, 127, 35, buffer1);
  
//  LcdBmp(4, 20, BMP_KEY_INPUT_WIDTH, BMP_KEY_INPUT_HEIGHT, bmp_key_input); 
  LcdBmp(4, 20, GetBmpWidth(BMP_KEY_INPUT), GetBmpHeight(BMP_KEY_INPUT), GetBmp(BMP_KEY_INPUT)); 
  
  DrawButton(42, 53, BTN_OK, pes_focus == 1);
  DrawButton(84, 53, BTN_CANCEL, pes_focus == 2);
  LcdDraw();
}

void ProcessPassEditorScreen(void)
{
  //--------------------------------------
  // pes_focus
  //--------------------------------------
  //  0         editor
  //  1         OK button
  //  2         Cancel button
 switch(pes_state)
  {
    case 0://Inactive state
      if(GetMessage(MSG_PASSWORD_SCREEN_ACTIVATE))
      {
        pes_state = 1;
        pes_focus = 0;
        curr_pass_val.ival = 0;
        DrawPassEditorScreen();      
        
  //void SetEditorMode(char e_type, T_VAR e_init_val, T_VAR e_min, T_VAR e_max)      
        SetEditorMode(INT, curr_pass_val);
        SendMessage(MSG_EDITOR_ACTIVATE);
      };
      break;
    case 1: //active state; editor is active
      /*
      if(GetMessage(MSG_EDITOR_KEY_UP))
      {
        es_state = 4;
        es_focus = 3;
        DrawEditorScreen();
      };
      if(GetMessage(MSG_EDITOR_KEY_DOWN))
      {
        es_state = 2;
        es_focus = 1;
        DrawEditorScreen();
      };*/
      if(GetMessage(MSG_EDITOR_CANCELLED))
      {
        
        pes_state = 2;
        pes_focus = 1;
        DrawPassEditorScreen();
      //  SendMessage(MSG_EDITOR_SCREEN_DEACTIVATED);
      };
      if(GetMessage(MSG_EDITOR_FINISHED))
      {
      //  SetFloatToTVar(var.curr_val, var.var_type,  GetEditorValue());
       // SetFloatValueByTag(_tag, GetEditorValue());
        pes_state = 2;
        pes_focus = 1;
        DrawPassEditorScreen();        
      };
    /*  if(GetMessage(MSG_EDITOR_DEACTIVATED))
      {
        es_state = 2;
        es_focus = 1;
        DrawEditorScreen();
      };*/
      break;
    case 2://active state; editor is not active, buttons active
      // OK  - es_focus = 1
      // Default - es_focus = 2
      // Cancel  - es_focus = 3
      if(GetMessage(MSG_KEY_PRESSED))
        switch(GetKeyCode())
        {
        case KEY_RIGHT:
          if(pes_focus < 2)
          {
            pes_focus++;
            DrawPassEditorScreen();
          };
          break;
        case KEY_LEFT:
          if(pes_focus > 1)
          {
            pes_focus--;
            DrawPassEditorScreen();
          };
          break;
        case KEY_UP:
          pes_state = 1;
          pes_focus = 0;
          SendMessage(MSG_EDITOR_ACTIVATE);
          DrawPassEditorScreen();
          break;          
        case KEY_ENTER:
          if(pes_focus == 1) // OK pressed
          {
            if(PassIsValid())
            {
              pes_state = 0;
              SendMessage(MSG_PASSWORD_SCREEN_OK);
            } 
            else
            {
              pes_state = 3;
              SetMessageScreenMode("Введен неверный", "пароль", "", MB_OK);
              SendMessage(MSG_MESSAGE_SCREEN_ACTIVATE);
            };
          };
          if(pes_focus == 2) // Cancel pressed
          {
            pes_state = 0;
            SendMessage(MSG_PASSWORD_SCREEN_CANCEL);
          };
          break;
        case KEY_ESC:
          pes_state = 0;
          SendMessage(MSG_PASSWORD_SCREEN_CANCEL);
          break;          
        };
      break;
      case 3://not active state; message window active
        if(GetMessage(MSG_MESSAGE_SCREEN_OK))
        {
          pes_state = 1;
          pes_focus = 0;
          SendMessage(MSG_EDITOR_ACTIVATE);
          DrawPassEditorScreen();
        };
        break;
  };
};
