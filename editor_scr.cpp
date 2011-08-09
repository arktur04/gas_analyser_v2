//------------------------------------------------------------------------------
// Editor screen class
//------------------------------------------------------------------------------
extern "C"{
//#include <stdio.h>
//#include <string.h>
//#include "messages.h"
//#include "type.h"
#include "keyb.h"
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "screens.h"
//#include "dict.h"
//#include "buttons.h"
//#include "message_window.h"
#include "variables.h"
//#include "editor.h"
//#include "editor_screen.h"
#include "pass_controller.h"

#include "messages.h"
};
#include <string>
#include "usbase.h"
#include "editor_scr.h"
#include "pass_scr.h"
#include "msg_scr.h"
//#include "msg.h"

EditorScreen::EditorScreen(void):usScreen(MSG_EDITOR_SCREEN_ACTIVATE,
                                          SCR_EDITOR, true, false)
{
 // message_to_activate = MSG_EDITOR_SCREEN_ACTIVATE;
  check_interval = false;
  auto_refresh  = false;
  /*
  AddControl(new usEditor(25, 26, 54, 13, 0));
  
  AddControl(new usTextButton(0, 52, 42, 11, 1, "OK", MSG_BTN_OK));      //BTN_OK
  AddControl(new usTextButton(42, 52, 42, 11, 2, "Умолч.", MSG_BTN_DEFAULT)); //BTN_DEFAULT
  AddControl(new usTextButton(84, 52, 42, 11, 3, "Отмена", MSG_BTN_CANCEL));  //BTN_CANCEL
  */
};

EditorScreen::EditorScreen(unsigned long _tag):usScreen(MSG_EDITOR_SCREEN_ACTIVATE,
                                          SCR_EDITOR, false, false)
{
  var_tag = _tag;
  check_interval = false;
};

void EditorScreen::PlaceControls(){
  AddControl(editor = new usEditor(25, 26, 54, 13, 0));
  
  AddControl(new usTextButton(0, 52, 42, 11,
                              1, "OK", MSG_BTN_OK, SCR_EDITOR));      //BTN_OK
  AddControl(new usTextButton(42, 52, 42, 11,
                              2, "Умолч.", MSG_BTN_DEFAULT, SCR_EDITOR)); //BTN_DEFAULT
  AddControl(new usTextButton(84, 52, 42, 11,
                              3, "Отмена", MSG_BTN_CANCEL, SCR_EDITOR));  //BTN_CANCEL
};

void EditorScreen::Activated(unsigned long * param)
{
  usScreen::Activated(param);
  var_tag = *param;
  //   ActivateFocusedControl(); 
  editor->setMode(GetTypeByTag(var_tag)?EM_FLOAT:EM_INT);
  //editor->setValue(GetValueByTag(var_tag));
  editor->setTag(var_tag);
  ActivateFocusedControl(); //editor

 // SendParamMessage(MSG_CHILD_SCREEN_ACTIVATE, SCR_EDITOR);
    /*
  if(!EditAllowed())                                                                    //!!!!!!!!!!!!!!
  {
    PassScreen*pass_screen = new PassScreen();
  };*/

 /* else
  {
    SendParamMessage(MSG_CHILD_SCREEN_ACTIVATE, SCR_EDITOR);
    SendMessage(MSG_PASSWORD_SCREEN_ACTIVATE);
  };  
  
  */
};

void EditorScreen::ActiveLoop(void)
{
  unsigned long param;
 // MESSAGE msg;
 // T_VAR value;

  usScreen::ActiveLoop();
  
  if(GetMessage(MSG_EDITOR_FINISHED))
  {
   // SendMessage(MSG_CUR_DEACTIVATE);
    //(getSystemCursor())->Hide();
    SetFocus(1);
    Update();
  };
  if(GetMessage(MSG_EDITOR_CANCELLED))
  {
    //(getSystemCursor())->Hide();
    SetFocus(3);
    Update();
  };

  if(GetMessage(MSG_EDITOR_KEY_UP))
  {
    //(getSystemCursor())->Hide();
    SetFocus(1);
    Update();
  };
  if(GetMessage(MSG_EDITOR_KEY_DOWN))
  {
  //  (getSystemCursor())->Hide();
    SetFocus(3);
    Update();
  };
  
  if(GetParamMessage(MSG_BTN_OK, &param))
  {
    if(param == SCR_EDITOR)
    {
      SetValueByTag(var_tag, editor->getValue());
      
      SendParamMessage(MSG_CHILD_SCREEN_DEACTIVATED, SCR_EDITOR);
    }
    else
    {
      SendParamMessage(MSG_BTN_OK, param);
    };
  };
  
  if(GetParamMessage(MSG_BTN_DEFAULT, &param))
  {
    if(param == SCR_EDITOR)
    {
      SendParamMessage(MSG_CHILD_SCREEN_DEACTIVATED, SCR_EDITOR);
      SetDefaulValueByTag(var_tag);
    }
    else
    {
      SendParamMessage(MSG_BTN_DEFAULT, param);
    };
  };
  
  if(GetParamMessage(MSG_BTN_CANCEL, &param))
  {
    if(param == SCR_EDITOR)
    {
      SendParamMessage(MSG_CHILD_SCREEN_DEACTIVATED, SCR_EDITOR);
    }
    else
    {
      SendParamMessage(MSG_BTN_CANCEL, param);
    };
  };
};
/*
void EditorScreen::OnClick1(usBase* Sender, USMESSAGE msg)
{
  
 char buffer1[10];   
  LcdText(82, 28, 127, 35, (reinterpret_cast<usTextButton*>(Sender))->gettext());

//  LcdText(82, 28, 127, 35, (reinterpret_cast<usTextButton*>(Sender))->gettext());
//LcdText(82, 28, 127, 35, "1");
LcdDraw();
};

void EditorScreen::OnClick2(usBase* Sender, USMESSAGE msg)
{
  LcdText(82, 28, 127, 35, "2");
  LcdText(82, 28, 127, 35, (reinterpret_cast<usTextButton*>(Sender))->gettext());
  LcdDraw();
}; 

void EditorScreen::OnClick3(usBase* Sender, USMESSAGE msg)
{
LcdText(82, 28, 127, 35, "3");
 LcdText(82, 28, 127, 35, (reinterpret_cast<usTextButton*>(Sender))->gettext());
  LcdDraw();
};  
*/
void EditorScreen::Paint(void)
{
  char buffer1[50];
  char buffer2[9];
  char buffer3[9];
  
  LcdClear();
  usScreen::Paint();
  //debug
 // SetIntValueByTag(_tag, 123456);
  //-------------------------
  SetFont(SMALL_FONT);
 
 // tag = SHIFT_T_L;                                                            // DEBUG!!!
  
  sprintf(buffer1, "Введите %s", GetNameByTag(var_tag));
  
 // void(usBase::*)() pDelegate = &this.Delegate();
  usBase Base;
 // PDELEGATE myDelegate = &EditorScreen::OnClick;
  
  USMESSAGE some_msg; //  FOR DEBUG
 // sprintf(buffer1, "%d", sizeof myDelegate);
         // (this->*myDelegate)(some_msg);
  
  LcdText(25, 0, 127, 7, buffer1);
  if(check_interval)
  {
    //  GetStringByTag(SHIFT_T_L, ID_CURR_VAL, buffer2, 8);
    LcdText(25, 8, 127, 15, "в диапазоне");
    
    GetStringByTag(var_tag, ID_MIN, buffer2, 8);
    GetStringByTag(var_tag, ID_MAX, buffer3, 8);
    sprintf(buffer1,"от %s до %s", buffer2, buffer3);
    LcdText(25, 16, 127, 23, buffer1);
  }; 
//  SetEditorMode(GetTypeByTag(SHIFT_T_L), GetValueByTag(SHIFT_T_L));
 // SetEditorMode(GetTypeByTag(_tag), var.curr_val);//, var.min_val, var.max_val);
 // SetEditorCoord(25, 26, 80, 39);
  
  sprintf(buffer1,", %s", GetUnitByTag(var_tag));
  LcdText(82, 28, 127, 35, buffer1);
  
//  LcdBmp(4, 20, BMP_KEY_INPUT_WIDTH, BMP_KEY_INPUT_HEIGHT, bmp_key_input); 
  LcdBmp(4, 20,
         GetBmpWidth(BMP_KEY_INPUT), GetBmpHeight(BMP_KEY_INPUT),
         GetBmp(BMP_KEY_INPUT)); 
  
};





























#ifdef OLDCODE

/*
MenuScreen::MenuScreen(char _scr_num):usScreen()
{
  scr_num = _scr_num;
  
  char btn;
  message_to_activate = MSG_MENU_SCREEN_ACTIVATE;
  for(char y = 0; y < 5; y++)
    for(char x = 0; x < 2; x++)
    {
      btn = x + y * 2;
      pTextButtons[btn] = new usTextButton(x * 55, y * 11 + 8,
                                           54, 11, y + x * 5,
                                           menues[scr_num].buttons[btn]);
      AddControl(pTextButtons[x + y * 2]);
    };
  AddControl(new usBmpButton(110, 9, 17, 18, 10, BTN_FORWARD));
  AddControl(new usBmpButton(110, 27, 17, 18, 11, BTN_HOME));
  AddControl(new usBmpButton(110, 45, 17, 18, 12, BTN_BACK));
};

void MenuScreen::Paint(void)
{ 
  
  LcdClear();
  LcdSetColor(WHITE);
  SetFont(SMALL_FONT);
  LcdText(0, 0, 118, 7, menues[scr_num].header);
  LcdLine(0, 8, 127, 8);  
  
  usScreen::Paint();
}
*/

//------------------------------------------------------------------------------
char es_focus = 0;
char es_state = 0;
int _tag;

static const char check_interval = 0;
// char es_pos = 0;
// char es_input[10]; //input string

/*
typedef struct 
{
  int tag; //числовой идентификатор переменной
  char var_type;
  char io_type;
  int fram_addr;
  int modbus_addr;  
  char var_name[8]; 
  char var_unit[8]; //название единицы измерения
  T_VAR def_val;
  T_VAR min_val;
  T_VAR max_val;
  char after_point; //знаков после запятой
  char edit_allowed; //разрешено редактирование пользователем
  //----------------------------------------
  // данные в RAM, в описании переменной должны быть = 0
  T_VAR curr_val;
  T_VAR prev_val;
  
} T_DICT_RECORD;
*/

T_DICT_RECORD var;

char ValueIsValid(void)
{
  float val;
  val = GetEditorValue();

  if((val <= var.max_val.fval) && (val >= var.min_val.fval))
  {
/*    if(var.var_type == INT)
      SetIntValueByTag(_tag, (int)val);
    if(var.var_type == FLOAT)
      SetFloatValueByTag(_tag, val);*/
    return 1;
  };
  return 0;
}

void SetDefaultValue(void)
{
  SetDefaulValueByTag(_tag);
}

void SetEditorVarByTag(int tag)
{
  _tag = tag;
  var = GetVarByTag(tag);
  
  SetEditorMode(GetTypeByTag(_tag), var.curr_val);//, var.min_val, var.max_val);
  SetEditorCoord(25, 26, 80, 39);
}

void DrawEditorScreen(void)
{
  char buffer1[50];
  char buffer2[9];
  char buffer3[9];
 
  //debug
 // SetIntValueByTag(_tag, 123456);
  //-------------------------
  SetFont(SMALL_FONT);
  LcdClear();
  sprintf(buffer1, "Введите %s", var.var_name);//GetNameByTag(_tag));
  LcdText(25, 0, 127, 7, buffer1);
  if(check_interval)
  {
    //  GetStringByTag(SHIFT_T_L, ID_CURR_VAL, buffer2, 8);
    LcdText(25, 8, 127, 15, "в диапазоне");
    
    GetStringByTag(_tag, ID_MIN, buffer2, 8);
    GetStringByTag(_tag, ID_MAX, buffer3, 8);
    sprintf(buffer1,"от %s до %s", buffer2, buffer3);
    LcdText(25, 16, 127, 23, buffer1);
  }; 
//  SetEditorMode(GetTypeByTag(SHIFT_T_L), GetValueByTag(SHIFT_T_L));
 // SetEditorMode(GetTypeByTag(_tag), var.curr_val);//, var.min_val, var.max_val);
 // SetEditorCoord(25, 26, 80, 39);
  DrawEditor();
  
  sprintf(buffer1,", %s", GetUnitByTag(_tag));
  LcdText(82, 28, 127, 35, buffer1);
  
//  LcdBmp(4, 20, BMP_KEY_INPUT_WIDTH, BMP_KEY_INPUT_HEIGHT, bmp_key_input); 
  LcdBmp(4, 20, GetBmpWidth(BMP_KEY_INPUT), GetBmpHeight(BMP_KEY_INPUT), GetBmp(BMP_KEY_INPUT)); 
  
  DrawButton(0, 53, BTN_OK, es_focus == 1);
  DrawButton(42, 53, BTN_DEFAULT, es_focus == 2);
  DrawButton(84, 53, BTN_CANCEL, es_focus == 3);
  LcdDraw();
}

void IncEsFocus(void)
{
  if(es_focus < 3)
  {
    es_focus++;
    DrawEditorScreen();
  };
}

void DecEsFocus(void)
{
  if(es_focus > 1)
  {
    es_focus--;
    DrawEditorScreen();
  };
}

void ProcessEditorScreen(void)
{
  //--------------------------------------
  // es_focus
  //--------------------------------------
  //  0         editor
  //  1         OK button
  //  2         Default button
  //  3         Cancel button
 switch(es_state)
  {
    case 0://Inactive state
      if(GetMessage(MSG_EDITOR_SCREEN_ACTIVATE))
      {
        es_state = 1;
        es_focus = 0;
        DrawEditorScreen();

  //void SetEditorMode(char e_type, T_VAR e_init_val, T_VAR e_min, T_VAR e_max)      
 //       SetEditorMode(GetTypeByTag(_tag), GetValueByTag(_tag));
        SendMessage(MSG_EDITOR_ACTIVATE);
      };
      break;
    case 1: //active state; editor is active
      if(GetMessage(MSG_EDITOR_KEY_UP))
      {
        es_state = 2;
        es_focus = 3;
        DrawEditorScreen();
      };
      if(GetMessage(MSG_EDITOR_KEY_DOWN))
      {
        es_state = 2;
        es_focus = 1;
        DrawEditorScreen();
      };
      if(GetMessage(MSG_EDITOR_CANCELLED))
      {
        es_state = 2;
        es_focus = 3;
        DrawEditorScreen();  
      //  SendMessage(MSG_EDITOR_SCREEN_DEACTIVATED);
      };
      if(GetMessage(MSG_EDITOR_FINISHED))
      {
        if(var.var_type == INT)
          var.curr_val.ival = GetIntEditorValue();
        if(var.var_type == FLOAT)
          var.curr_val.fval = GetFloatEditorValue(); 
      //  SetFloatToTVar(var.curr_val, var.var_type,  GetEditorValue());
       // SetFloatValueByTag(_tag, GetEditorValue());
        es_state = 2;
        es_focus = 1;
        DrawEditorScreen();        
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
      if(GetMessage(MSG_L_ENCODER_CW))
        IncEsFocus();
      if(GetMessage(MSG_L_ENCODER_CCW))
        DecEsFocus();
      
      if(GetMessage(MSG_KEY_PRESSED))
        switch(GetKeyCode())
        {
        case KEY_RIGHT:
          IncEsFocus();
          break;
        case KEY_LEFT:
          DecEsFocus();
          break;
        case KEY_UP:
          es_state = 1;
          es_focus = 0;
          SendMessage(MSG_EDITOR_ACTIVATE);
          DrawEditorScreen();
          break;          
        case KEY_ENTER:
          if(es_focus == 1) // OK pressed
          {
            if(check_interval && !ValueIsValid())
            {
              es_state = 3;
              SetMessageScreenMode("Введено неверное", "значение", "", MB_OK);
              SendMessage(MSG_MESSAGE_SCREEN_ACTIVATE);
            }
            else
            {
              es_state = 0;
              SendMessage(MSG_EDITOR_SCREEN_OK);
              SendMessage(MSG_EDITOR_SCREEN_DEACTIVATED);
              if(var.var_type == INT)
                SetIntValueByTag(_tag, var.curr_val.ival);
              else
                SetFloatValueByTag(_tag, var.curr_val.fval);
              //  SetValueByTag();
            };
          };
          if(es_focus == 2) // Default pressed
          {
            SetDefaultValue();
            es_state = 0;
            SendMessage(MSG_EDITOR_SCREEN_OK);
            SendMessage(MSG_EDITOR_SCREEN_DEACTIVATED);
          };
          if(es_focus == 3) // Cancel pressed
          {
            es_state = 0;
            SendMessage(MSG_EDITOR_SCREEN_CANCEL);
            SendMessage(MSG_EDITOR_SCREEN_DEACTIVATED);
          };
          break;
        case KEY_ESC:
          es_state = 0;
          SendMessage(MSG_EDITOR_SCREEN_CANCEL);
          SendMessage(MSG_EDITOR_SCREEN_DEACTIVATED);
          break;          
        };
      break;
      case 3://not active state; message window active
        if(GetMessage(MSG_MESSAGE_SCREEN_OK))
        {
          es_state = 1;
          es_focus = 0;
          SendMessage(MSG_EDITOR_ACTIVATE);
          DrawEditorScreen();
        };
        break;
  };
};
#endif

