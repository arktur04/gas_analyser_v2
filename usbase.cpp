extern "C"{

#include "lcd.h"
#include "font.h"
#include "bmps.h"  
#include "dict.h"
#include "keyb.h"
 #include "timers.h"
#include "variables.h"
// #include "variables.h"
  #include "messages.h"
};

//#include "msg.h"
#include <string>
//using namespace std;

#include "usbase.h"

usCursor* cursor;

usScreenList*screen_list;  //global list

usScreenList* getScreenList()
{
  return screen_list;
};

usCursor* getSystemCursor(void)
{
  return cursor;
};

void usDrawTagValue(char x, char y, int tag)
{
  #define BUF_SIZE 10
  char str[BUF_SIZE];
  
  GetStringByTag(tag, ID_CURR_VAL, str, BUF_SIZE);
  LcdText(x, y, x + strlen(str) * GetCharWidth(' '), y + GetFontHeight(), str);
}

void usSystemInit(void)
{
  cursor = new usCursor();
  screen_list = new usScreenList();
};
//------------------------------------------------------------------------------
__delegate EventHandler(usBase* _pObj, PDELEGATE _pDelegate){
  __delegate d;
  d.pObj = _pObj;
  d.pDelegate = _pDelegate;
  return d;
};

void InvokeEvent(usBase* sender, __delegate d, USMESSAGE msg)
{
  if(d.pObj && d.pDelegate) (d.pObj->*(d.pDelegate))(sender, msg);
};

//------------------------------------------------------------------------------
// usCursor
void usCursor::DrawCursor(void)
{
  LcdLine(x, y, x, y + height);
};

void usCursor::ClearCursor(void)
{
 // LcdSetColor(WHITE);
  LcdInvertCurrentColor();
  LcdLine(x, y, x, y + height);
  LcdInvertCurrentColor();
//  LcdSetColor(BLACK);
};

void usCursor::Process(void)
{
  switch(state)
  {
    case 0:  //inactive state
      if(active)
      {
        state = 1;
       // DrawCursor();
       // LcdDraw();
        ResetTimer(CURSOR_TIMER);
      };
      break;
    case 1:  //курсор активен
      if(!active)
      {
        //выключение курсора
       // ClearCursor();    
       // LcdDraw();
        state = 0;
      };
      //the cursor blinks 
      if (GetTimer(CURSOR_TIMER) > (period / 2))
      {
        if(visible)
        {
          visible = false;
       //   ClearCursor();
         // LcdDraw();
        }
        else
        {
          visible = true;
       //   DrawCursor();
       //   LcdDraw();
        };
     // LcdDraw();
      ResetTimer(CURSOR_TIMER);
      };
      break;
  }
};

void usCursor::Paint(void)
{
  if(active && visible)
    DrawCursor();
  else
    ClearCursor(); 
}
//------------------------------------------------------------------------------
struct pred  //the predicate of an equality of c->scr_id and i
{
  pred( int i ) : n(i) {}
  bool operator () ( usScreen* & c )                                               
  {
    return (c->GetScrId() == n);                                                   
  }
private:
  int n;    
};

void usScreenList::RemoveScreens()
{
  for(list<usScreen*>::iterator iter = screen_list.begin();
      iter != screen_list.end();
      iter++)
  {
    delete (*iter);                                                          
  };
  screen_list.clear();
}

void usScreenList::RemoveScreen(int scr_id)
{
  screen_list.remove_if(pred(scr_id));                                                 //проверить вызов деструктороы экрана и освобождение памяти
}                                                                                      //remove_if удаляет только указатель, но не сам экран!

void usScreenList::AddScreen(usScreen* pscreen)
{
  usScreen*curr_screen;
  //get current screen
 // list<usScreen*>::reverse_iterator rit;                                            
  if(screen_list.rbegin() != screen_list.rend())
  {
    curr_screen = (*screen_list.rbegin());                                          
    curr_screen->setState(2);
    curr_screen->child_screen = pscreen->GetScrId();
  };
  //--------------
  screen_list.push_back(pscreen);
};

void usScreenList::Process()
{
  u32 scr_id;
  usScreen*curr_screen;
  
  if(GetParamMessage(MSG_CHILD_SCREEN_DEACTIVATED, &scr_id))
  {
    RemoveScreen(scr_id);
    //  SendParamMessage(MSG_CHILD_SCREEN_DEACTIVATED, scr_id);
    //get current screen
    list<usScreen*>::reverse_iterator rit;                              
    if(screen_list.rbegin() != screen_list.rend())
    {
      curr_screen = *screen_list.rbegin();                                     
      curr_screen->setState(1);
      curr_screen->Update();
    };
  };
  list<usScreen*>::iterator iter;                                                   
  for(iter = screen_list.begin(); iter != screen_list.end(); iter++)
  {
    (*iter)->Process();                                                           
  };
};
//------------------------------------------------------------------------------
// usControlList

usControl*usControlList::operator[] (int i)
{
  int cnt = 0;
  for(iterator iter = begin(); iter != end(); iter++)
  {
    if(i == cnt)
      return *iter;
    cnt++;
  };
  
  return *begin();  //normally unreachable condition
};
//------------------------------------------------------------------------------
// usScreen

usScreen::usScreen(u8 _message_to_activate, int _scr_id, bool auto_activate, 
                   bool _is_exceptional)
{
 // is_finished = false;
  scr_id = _scr_id;
  child_screen = -1;
  message_to_activate = _message_to_activate;
  auto_refresh = true;
  is_exceptional = _is_exceptional;
  focus_number = 0;
  pFocusedControl = (usControl*)0;
  // is_exceptional = true;
  if(is_exceptional)
    getScreenList()->RemoveScreens();
  if(auto_activate)
    SendMessage(message_to_activate);
  
  getScreenList()->AddScreen(this);
};

usScreen::~usScreen()
{ 
  for(list<usControl*>::iterator iter = control_list.begin();
      iter != control_list.end();
      iter++)
  {
    delete (*iter);
    *iter = (usControl*)(0);
  };
  
  control_list.clear();

/*
  for(list<usControl*>::iterator iter = controlList.begin();
      iter != controlList.end();
      iter++)
  {
    delete (*iter);
    *iter = (usControl*)(0);
  };
  
  controlList.clear();*/
};

usControl* usScreen::AddControl(usControl* pcontrol)
{
  control_list.push_back(pcontrol);
  return pcontrol;
};

void usScreen::Paint(void)
{
  list<usControl*>::iterator iter = control_list.begin();
  while(iter != control_list.end())
  {
    usControl* pcontrol = *iter;
    pcontrol->Paint();
    iter++;
  };
};

void usScreen::IncFocus()
{
//  list<usControl*>::iterator iter = controlList.begin();
  do
  {
    if(focus_number < control_list.size() - 1)
    {
      focus_number++;
    }
    else
    {
      focus_number = 0;
    };
  }
  while(!control_list[focus_number]->focusEnabled);
  Update();
};

void usScreen::DecFocus()
{
  do
  {
    if(focus_number > 0)
    {
      focus_number--;
    }
    else
    {
      focus_number = control_list.size() - 1 ;
    };
  }
  while(!control_list[focus_number]->focusEnabled);
  Update();
};
/* DO NOT REMOVE YET!
void usScreen::usControl* usScreen::GetControlByOrder(s8 x){

  s8 i = 0;
  iter = controlList.begin();
  while(iter != controlList.end()){
    if(i == x) return *iter;
    iter++;
    i++;
  };
  return null;
};

void usScreen::usControl* usScreen::GetControlBySecondaryOrder(s8 so){
  s8 i = 0;
  if(so < controlList.size() - 1){
    i = 0;
    iter = controlList.begin();
    while(iter != controlList.end()){
      if((*iter)->secondary_order == so) return *iter;
      iter++;
      i++;
    };
  };
  return null;
};
*/

usControl* usScreen::FindFocused()
{
  s8 i = 0;
  list<usControl*>::iterator iter = control_list.begin();
  while(iter != control_list.end())
  {
    if(i == focus_number)
      return (*iter);
    iter++;
    i++;
  };
  return (usControl*)0; //not reachable normally;
};

void usScreen::IncSecondaryOrder()
{
  s8 so = -1;
  s8 i = 0;
  if(pFocusedControl)
  {
    so = pFocusedControl->secondary_order + 1;
  }
  else
  {
    so = 0;
  };
  
  if(so <= control_list.size() - 1)
  {
    i = 0;
    list<usControl*>::iterator iter = control_list.begin();
    while(iter != control_list.end())
    {
      if((*iter)->secondary_order == so) 
      {
        if((*iter)->focusEnabled)
        {
          focus_number = i;
          break;
        }
        else
        {
          ++so;
        };
      };
      ++iter;
      ++i;
    };
  };
  Update();
};

void usScreen::DecSecondaryOrder()
{
  s8 so = -1;
  s8 i = 0;
  if(pFocusedControl)
  {
    so = pFocusedControl->secondary_order - 1;
  }
  else
  {
    so = 0;
  };
  
  if(so >= 0)
  {
    i = control_list.size() - 1;
    list<usControl*>::reverse_iterator iter = control_list.rbegin();
    while(iter != control_list.rend())
    {
      if((*iter)->secondary_order == so) 
      {
        if((*iter)->focusEnabled)
        {
          focus_number = i;
          break;
        }
        else
        {
          --so;
        };
      };
      ++iter;
      --i;
    };
  };
  Update();  
};
  
void usScreen::Update(void)
{
  s8 i = 0;
  for(list<usControl*>::iterator iter = control_list.begin();
      iter != control_list.end();
      iter++)
  {
    (*iter)->setFocused(i == focus_number);
    (*iter)->Update();
    if((*iter)->focused) pFocusedControl = *iter;
    i++;
  };
  Paint();
  LcdDraw();
};

void usScreen::Activated(unsigned long *param)
{
  // usControl control;
  list<usControl*>::iterator iter = control_list.begin();
  if(!control_list.empty()){
    (*iter)->focused = true;
    pFocusedControl = *iter;  //focus the first control on the screen
 /*   if(auto_activate_first_control){
      ActivateFocusedControl();  //and activate it
    
    };*/
  };
  ResetTimer(SCREEN_REFRESH_TIMER);
};

void usScreen::ActivateFocusedControl()
{
  if(pFocusedControl)
  {
    pFocusedControl->Enter();
   // state = 2;
  };
};

void usScreen::PlaceControls()
{
  //empty spaces...
};

void usScreen::RemoveControls()
{
  for(list<usControl*>::iterator iter = control_list.begin();
      iter != control_list.end();
      iter++)
    delete (*iter);
};

void usScreen::ActiveLoop()
{
  unsigned long key_code;
  if(pFocusedControl)
  {
    pFocusedControl->Process();
  };
  if(GetMessage(MSG_L_ENCODER_CW))
  {
    IncFocus();
  };
  if(GetMessage(MSG_L_ENCODER_CCW))
  {
    DecFocus();
  };
  if(GetParamMessage(MSG_KEYPRESSED, &key_code))
  {
  //  key_code = GetKeyCode();
    
    switch(key_code)
    {
    case KEY_DOWN:
      IncSecondaryOrder();
      break;
    case KEY_UP:
      DecSecondaryOrder();
      break;          
    case KEY_RIGHT:
      IncFocus();
      break;
    case KEY_LEFT:
      DecFocus();
      break;
    case KEY_ENTER:
      ActivateFocusedControl();
      break;             
    };
  };
  if(auto_refresh)
    if(GetTimer(SCREEN_REFRESH_TIMER) > 50)
    {
      Update();
      ResetTimer(SCREEN_REFRESH_TIMER);
    };
};

void usScreen::Process(void)
{
  switch(state) 
  {
  case 0: //inactive state
    if(GetParamMessage(message_to_activate, &param))
      {
        state = 1;
     /*   if(is_exceptional)
          getScreenList()->RemoveScreens();*/
        PlaceControls();
        Activated(&param);
      /*  if(pFocusedControl)
          pFocusedControl->Enter();*/
        Update();
      };
    break;
  case 1: //active screen
    {/*
      if(GetParamMessage(MSG_CHILD_SCREEN_ACTIVATE, &param))
      {
        state = 2;
        child_screen = param;
      };*/
      ActiveLoop();
    };
    break;
  case 2: //child screen active
    {
      /*
      if(pFocusedControl)
          pFocusedControl->Process();
      */
      /*
      if(GetMessage(MSG_CONTROL_OK) )
      {
        state = 1;
        
        Update();
      };*/
      /*
      if(GetParamMessage(MSG_SCREEN_OK, &param) )
      {
        state = 1;
       // delete reinterpret_cast<usScreen*> param;
        ChildDeactivated(RESULT_OK);
        Update();
      };
      if(GetParamMessage(MSG_SCREEN_CANCEL, &param) )
      {
       // delete reinterpret_cast<usScreen*> param;
        state = 1;
        ChildDeactivated(RESULT_CANCEL);
        Update();
      };
      */
      
      
      /*                                                                                   //??????????????
      if(GetParamMessage(MSG_CHILD_SCREEN_DEACTIVATED, &param))
      {
        if(param == child_screen)
        {
          state = 1;
          Update();
        }
        else
        {
          SendParamMessage(MSG_CHILD_SCREEN_DEACTIVATED, param); //rethrow the Message
        };
      };
      */
    };
    break;
  };
};
 
void usScreen::Deactivate(void)
{
  state = 0;
 /* if(pFocusedControl)
    pFocusedControl->LeaveFocus();*/
  RemoveControls();
};

void usScreen::ChildScreenActivate(u8 ScreenId)
{
  state = 2;
 /* if(pFocusedControl)
    pFocusedControl->LeaveFocus();*/
};
//------------------------------------------------------------------------------
void usButton::Paint(void)
{
  char x = getLeft();
  char y = getTop();
  char x2 = getLeft() + getWidth();
  char y2 = getTop() + getHeight();
    
  LcdSetColor(BLACK); 
  if(btn_style & BS_ROUNDED)
  {
    LcdLine(x + 2, y,     x2 - 2, y);
    LcdLine(x + 2, y2,    x2 - 2, y2);
    LcdLine(x,     y + 2, x,      y2 - 2);
    LcdLine(x2,    y + 2, x2,     y2 - 2);
    
    LcdLine(x + 1,  y + 1,  x + 1,  y + 1);
    LcdLine(x2 - 1, y + 1,  x2 - 1, y + 1);
    LcdLine(x + 1,  y2 - 1, x + 1,  y2 - 1);
    LcdLine(x2 - 1, y2 - 1, x2 - 1, y2 - 1);
  }
  else
  {
    LcdLine(x, y,  x2, y);
    LcdLine(x, y2, x2, y2);
    LcdLine(x, y,  x,  y2);
    LcdLine(x2,y,  x2, y2);
  };  
  
};
/*
void usButton::KeyEvent(char KeyCode)
{
  if(KeyCode == KEY_ENTER) Click();
};

void usButton::MessageEvent(MESSAGE Msg)
{
  if(Msg == MSG_L_ENCODER_PRESSED) Click();
};
*/

void usButton::Enter()
{
 // SendMessage(MSG_CONTROL_OK);
  Click();
};

void usButton::Click()
{
  SendParamMessage(msg_on_click, msg_param);
//  USMESSAGE msg;
 // InvokeEvent(reinterpret_cast<usBase*>(this), OnClick, msg);
};
//------------------------------------------------------------------------------
void usTextButton::Paint(void)
{
  char x = getLeft(),
  y = getTop(), 
  width = getWidth(),
  height = getHeight();
  
  usButton::Paint();
  SetFont(SMALL_FONT);
  LcdSetColor(BLACK);
  if(focused && (btn_style & BS_ROUNDED)){
    LcdRect(x + 1, y + 1, x + width - 1, y + height - 1);
    LcdSetColor(WHITE);
  };
  if(focused && !(btn_style & BS_ROUNDED)){
    LcdFrame(x + 1, y + 1, x + width - 1, y + height - 1);
   // LcdSetColor(WHITE);
  };
  LcdText(x + 2, y + 2, x + width - 2, y + height - 2, (char*)text.c_str()); //(&text[0]);
  LcdSetColor(BLACK); 
};
//------------------------------------------------------------------------------
static char bmp_ids[6] = {-1, -1, -1, BMP_FORWARD, BMP_BACKWARD, BMP_HOME};

void usBmpButton::Paint(void)
{
  char bmp_id = bmp_ids[btn_id];
  char x = getLeft(),
  y = getTop(), 
  width = getWidth(),
  height = getHeight();
  
  if(focused){
    LcdSetColor(BLACK);
    LcdRect(x + 1, y + 1, x + width - 1, y + height - 1);
    LcdSetColor(WHITE);
  }
  else
  {
    LcdSetColor(WHITE);
    LcdRect(x + 1, y + 1, x + width - 1, y + height - 1);
    LcdSetColor(BLACK);
  };
  LcdBmp(x + 2, y + 2, GetBmpWidth(bmp_id), GetBmpHeight(bmp_id),
         GetBmp(bmp_id));
  LcdSetColor(BLACK); 
  
  usButton::Paint();
};

//------------------------------------------------------------------------------
/*
class usEditor: public usControl{
public:
  usEditor(u8 _x, u8 _y, u8 _width, u8 _height, u8 _secondary_order);
  virtual ~usEditor(){};
   virtual void Process(void);
   virtual void Enter();
   //------------
   void setMode(editor_mode _mode);
   void setValue(T_VAR init_val);
   float getValue();
protected:
  virtual void Paint();
//  virtual void KeyEvent(char KeyCode);
//  virtual void MessageEvent(MESSAGE Msg);
//  virtual void EnterFocus(){};
//  virtual void LeaveFocus(){};
private:
 // char str[10];
  string str;
  char pos;
  editor_mode mode;
  float value;
  
  void CursorLeft();
  void CursorRight();
  bool ValueIsValid();
  
  void CursorUpdate();
  bool IncreaseValue(char cur_pos);
  bool DecreaseValue(char cur_pos);
};
*/

usEditor::usEditor(u8 _x, u8 _y, u8 _width, u8 _height, u8 _secondary_order):
  usControl(_x, _y, _width, _height, _secondary_order)
{
  cur_pos = 1;
  strcpy(str, "0");
  str[max_pos] = 0;
  text_selected = true;
  mode = EM_INT;
};

void usEditor::Paint()
{
  char x = getLeft(),
  y = getTop(), 
  width = getWidth(),
  height = getHeight();
  
  char x2 = x + width;
  char y2 = y + height;
    
  LcdSetColor(BLACK); 
  
  LcdFrame(x , y , x2, y2);
  if(focused)
    LcdFrame(x + 1 , y + 1, x2 - 1, y2 - 1);
  
  LcdSetColor(text_selected&&focused?WHITE:BLACK);
  LcdText(x + 3, y + 3, x + width - 3, y + height - 3, &str[0]);
  cursor->Paint();
};

void usEditor::Process()
{
 // char ch;
  unsigned long key_code;
  if(GetMessage(MSG_L_ENCODER_CCW))
  {
    text_selected = false;
    CursorLeft();
    Update();
    LcdDraw();    
  };
  if(GetMessage(MSG_L_ENCODER_CW))
  {
    text_selected = false;
    CursorRight();
    Update();
    LcdDraw();    
  };
  if(GetMessage(MSG_R_ENCODER_CCW))
  {
    text_selected = false;
    DecreaseValue(cur_pos);
    Update();
    LcdDraw();
  };
  if(GetMessage(MSG_R_ENCODER_CW))
  {
    text_selected = false;
    IncreaseValue(cur_pos);
    Update();
    LcdDraw();
  };
/*
#define MSG_EDITOR_ACTIVATE      26
#define MSG_EDITOR_KEY_UP        27
#define MSG_EDITOR_KEY_DOWN      28
#define MSG_EDITOR_KEY_LEFT      29
#define MSG_EDITOR_KEY_RIGHT     30
#define MSG_EDITOR_FINISHED      31
#define MSG_EDITOR_CANCELLED     32
#define MSG_EDITOR_DEACTIVATED   33
  */
  
  if(GetParamMessage(MSG_KEYPRESSED, &key_code))
  {
  //  char key_code = GetKeyCode();
    switch(key_code)
    {
    case KEY_0:
    case KEY_1:     
    case KEY_2:    
    case KEY_3:     
    case KEY_4:     
    case KEY_5:     
    case KEY_6:     
    case KEY_7:     
    case KEY_8:     
    case KEY_9:
    case KEY_MINUS: 
    case KEY_DOT:
      if(InsertChar(keyCodeToASCII(key_code)))
      {
         Update();
         LcdDraw();
      };
      break;
    
    case KEY_UP:
      cursor->Hide();
      SendMessage(MSG_EDITOR_KEY_UP);
      break;
    case KEY_DOWN:
      cursor->Hide();
      SendMessage(MSG_EDITOR_KEY_DOWN);
      break;
    case KEY_LEFT:
      text_selected = false;
      CursorLeft();
      Update();
      LcdDraw(); 
      break;
    case KEY_RIGHT:
      text_selected = false;
      CursorRight();
      Update();
      LcdDraw(); 
      break;
      
    case KEY_DEL:    // F + Right
      if(text_selected)
      {
        text_selected = false;
        str[0] = 0;
        Update();
        LcdDraw();        
      }
      else
        if(cur_pos < strlen(str))
        {
          for(char i = cur_pos; i < max_pos; i++)
            str[i] = str[i + 1];
          Update();
          LcdDraw();
        };
      break;
    case KEY_BACK:    // F + Left
      if(text_selected)
      {
        text_selected = false;
        str[0] = 0;
        cur_pos = 0;
        CursorUpdate();
        Update();
        LcdDraw();        
      }
      else
        if((cur_pos > 0) && (cur_pos <= strlen(str)))
        {
          for(char i = cur_pos - 1; i < max_pos; i++)
            str[i] = str[i + 1];
          cur_pos--;
          CursorUpdate();
          Update();
          LcdDraw();
        };
      break;

    case KEY_ESC:
      cursor->Hide();
      SendMessage(MSG_EDITOR_CANCELLED);
      break;      
    case KEY_START:
      cursor->Hide();
      SendMessage(MSG_EDITOR_FINISHED);
      break;
    case KEY_STOP:
      cursor->Hide();
      SendMessage(MSG_EDITOR_CANCELLED);
      break;
    case KEY_ENTER:
      cursor->Hide();
      SendMessage(MSG_EDITOR_FINISHED);
      break;
    };
  };
};

char usEditor::InsertChar(char ch)
{
  if(text_selected)
  {
    str[0] = ch;
    str[1] = 0;
    cur_pos = 1;
    CursorUpdate();
    text_selected = false;
    return cur_pos;    
  };
  if(cur_pos < max_pos)
  {
    for(signed char i = max_pos - 2; i >= cur_pos; i--)
      str[i + 1] = str[i];
    str[cur_pos] = ch;  
    cur_pos++;
    CursorUpdate();
    return cur_pos; // pos always > 0
  }
  return 0;
};

void usEditor::Update()
{
  usControl::Update();
  cursor->Paint();
 // LcdDraw();
 // if(cursor->getActive())
   // CursorUpdate();
};
  
void usEditor::CursorUpdate()
{
  char x = getLeft(),
  y = getTop(), 
  width = getWidth(),
  height = getHeight();
  char x_coord, y_coord;
  
  x_coord = x + 2 + cur_pos * 5;
  y_coord = y + 3;
  if((cursor->getXCoord() != x_coord) || (cursor->getYCoord() != y_coord))
  {
    cursor->Hide();
    cursor->setCoord(x_coord, y_coord);
  };
  cursor->Show();
};
/*
void usEditor::Focus(void)
{
  usControl::Focus();
  cursor->Show();
};
  */
void usEditor::Enter()
{
  CursorUpdate();
};

T_VAR usEditor::getValue()
{
  T_VAR result;
  if(mode == EM_INT)
    result.ival = strtol(&str[0], (char**)0, 10);
  if(mode == EM_FLOAT)
    result.fval = strtod(&str[0], (char**)0);
  return result;
};

void usEditor::setValue(T_VAR init_val) 
{
  if(mode == EM_INT)
  {
  sprintf(&str[0], "%d", init_val.ival);
  };
  
  if(mode == EM_FLOAT)
  {
 //   GetStringByTag(tag, ID_CURR_VAL, str, BUF_SIZE);
  sprintf(&str[0], "%.7f", init_val.fval);
  }; 
  cur_pos = strlen(str);
  Update();
/*  if(e_type == INT) 
  {
    sprintf(buffer, "%d", e_init_val.ival);
    _e_value = e_init_val.ival;    
  };
  if(e_type == FLOAT)
  {
    sprintf(buffer, "%.3f", e_init_val.fval);
    _e_value = e_init_val.ival;
  };*/
};

void usEditor::setTag(int tag)
{
  (GetTypeByTag(tag)== FLOAT)? mode = EM_FLOAT: mode = EM_INT;
   GetStringByTag(tag, ID_CURR_VAL, str, max_pos);
/*  
  if(mode == EM_INT)
  {
  sprintf(&str[0], "%d", init_val.ival);
  };
  
  if(mode == EM_FLOAT)
  {
 //   GetStringByTag(tag, ID_CURR_VAL, str, BUF_SIZE);
  sprintf(&str[0], "%.7f", init_val.fval);
  }; */
  cur_pos = strlen(str);
  Update();
}

void usEditor::setMode(editor_mode _mode)
{
  mode = _mode;
  /*
  _e_type = e_type;
  if(e_type == INT) 
  {
    sprintf(buffer, "%d", e_init_val.ival);
    _e_value = e_init_val.ival;
  //  _e_min = e_min.ival;
  //  _e_max = e_max.ival;    
  };
  if(e_type == FLOAT)
  {
    sprintf(buffer, "%.3f", e_init_val.fval);
    _e_value = e_init_val.ival;
   // _e_min = e_min.fval;
   // _e_max = e_max.fval;      
  };
  */
};

void usEditor::CursorRight()
{
  if((cur_pos < strlen(str)) && (cur_pos <= max_pos)) 
  {
    cur_pos++;
    CursorUpdate();
    //Update();
  };
};

void usEditor::CursorLeft()
{
  if(cur_pos > 0)
  {
    cur_pos--;
    CursorUpdate();
    //Update();
  };
};

bool usEditor::IncreaseValue(char cur_pos)
{
  if((str[cur_pos] >= '0') && (str[cur_pos] < '9'))
    {
      str[cur_pos]++;
      return true;
    };
  if((str[cur_pos] == '9') && (cur_pos > 0))
  {
    if(IncreaseValue(cur_pos - 1))
    {
      str[cur_pos] = '0';
      return true;
    };
  };
  return false;
};

bool usEditor::DecreaseValue(char cur_pos)
{
  if((str[cur_pos] > '0') && (str[cur_pos] <= '9'))
    {
      str[cur_pos]--;
      return true;
    };
  if((str[cur_pos] == '0') && (cur_pos > 0))
  {
    if(DecreaseValue(cur_pos - 1))
    {
    str[cur_pos] = '9';
    return true;
    };
  };
  return false;
};

bool usEditor::ValueIsValid()
{
  return true;
};
//-----------------------------------------------
void usCheckBox::Enter()
{
  setChecked(!checked);
  SendParamMessage(msg_on_click, (msg_param & 0xFFFFUL) | (checked << 16));
};

void usCheckBox::Paint()
{
  char x = getLeft(),
  y = getTop(), 
  width = getWidth(),
  height = getHeight();
  
  static char checked_cb[8] = {0xFF, 0x99, 0xB1, 0xE1, 0xF1, 0x9D, 0x87, 0xFF};
  static char cb[8] = {0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF};
  LcdSetColor(BLACK);
  
  if(focused)
  {
    LcdLine(x, y, x + 9, y);
    LcdLine(x + 9, y, x + 9, y + 9);
    LcdLine(x, y + 9, x + 9, y + 9);
    LcdLine(x, y, x, y + 9);
  };
  if(checked)
  {
    LcdBmp(x + 1, y + 1, 8, 8, checked_cb);
  }
  else
  {
    LcdBmp(x + 1, y + 1, 8, 8, cb);
  };   
};
//------------------------------------------------------------------------------
/*
virtual void usCustomTextLabel::Paint(void)
{
  usGraphic::Paint();
  SetFont(SMALL_FONT);
  LcdSetColor(BLACK);
  LcdText(x + 2, y + 2, x + width - 2, y + height - 2, (char*)text.c_str());
};
//------------------------------------------------------------------------------
usTagLabel::usTagLabel(u8 _x, u8 _y, int _tag)
{
  usCustomTextLabel(_x, _y, )
}
*/
#ifdef OLDCODE 
   
  char key_code;
  
  if(GetMessage(MSG_L_ENCODER_CW)){
    IncFocus();
    if(pFocusedControl)
      pFocusedControl->MessageEvent(MSG_L_ENCODER_CW);
  };
  if(GetMessage(MSG_L_ENCODER_CCW)){
    if(pFocusedControl)
      pFocusedControl->MessageEvent(MSG_L_ENCODER_CCW);
        DecFocus();
  };
  if(GetMessage(MSG_KEY_PRESSED))
  {
    key_code = GetKeyCode();
    switch(key_code)
    {
        case KEY_DOWN:
          IncSecondaryOrder();
          break;
        case KEY_UP:
          DecSecondaryOrder();
          break;          
        case KEY_RIGHT:
          IncFocus();
          break;
        case KEY_LEFT:
          DecFocus();
          break;
      /*  case KEY_ENTER:
          break;             */
    };
    if(pFocusedControl)
      pFocusedControl->KeyEvent(key_code);
  };
};
#endif
