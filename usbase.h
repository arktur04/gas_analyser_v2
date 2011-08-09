//------------------------------------------------------------------------------
// usLib
// base classes 
//------------------------------------------------------------------------------
#ifndef USBASE_h
#define USBASE_h

extern "C"{
//#include "messages.h"
#include "bmps.h"
#include "dict.h"
};

#include <list>
#include <string>
#include "messages.h"
#include "ustype.h"

#define RESULT_CANCEL 0
#define RESULT_OK     1

class usCursor;
class usScreenList;

void usSystemInit(void);
usCursor* getSystemCursor(void);

usScreenList* getScreenList();

//------------------------------------------------------------------------------
typedef struct{
  u16 MsgID;
  union{
    u16 msg_param;
    struct {
      u8 x;
      u8 y;
    };
  };
} USMESSAGE;

class usBase
{
public:
  u8 tag;
 // virtual void Delegate(USMESSAGE msg) {};      
};

typedef void (usBase::*PDELEGATE)(usBase* pSender, USMESSAGE msg); 

typedef struct{
  usBase* pObj;
  PDELEGATE pDelegate;
} __delegate;

__delegate EventHandler(usBase* _pObj, PDELEGATE _pDelegate);

#define EVENT_HANDLER(pObj, pMember) EventHandler(pObj,\
  reinterpret_cast<PDELEGATE>(pMember))

void InvokeEvent(usBase* sender, __delegate d, USMESSAGE msg);

class usFsm: public usBase{
protected:
  u16 state;
  u16 id;
public:
 // usFsm() {state = 0; id = 0;};
  usFsm(u16 _id = 0): state(0),  id(_id) {};
  virtual ~usFsm() {};
  virtual void Process(void) = 0;
  virtual void setState(u16 _newstate) {state = _newstate;};
  virtual u16 getState(void) {return state;};
};

class usCursor: public usFsm{
private:
  char x, y;
  bool active, visible;
  char period;
  char height;
  void DrawCursor(void);
  void ClearCursor(void);
public:
   usCursor(): usFsm(), active(false), visible(false), period(100), height(7) {};
   virtual ~usCursor(){};
   void setCoord(char _x, char _y) {x = _x; y = _y;};
   char getXCoord(void) {return x;};
   char getYCoord(void) {return y;};
   void setActive(char _active) {active = _active;};
   bool getActive(void){return active;};
   void Show() {active = true;};
   void Hide() {
     active = false;
     ClearCursor();
   };
   void Paint(void);
   virtual void Process(void);
};

class usScreen;

class usGraphic: public usFsm{
  friend class usScreen;
private:
protected:
  u8 x, y, width, height;
  virtual void Paint(void){};// = 0;
public:
  usGraphic(u8 _x, u8 _y, u8 _width, u8 _height):
    x(_x), y(_y), width(_width), height(_height) {};
    virtual ~usGraphic(){};
  virtual void Update(void) {Paint();};
  virtual void Process(void){};// = 0;
};

class usControl: public usGraphic{
  friend class usScreen;
private:
protected:
  bool focused;
  u8 secondary_order;
 /* virtual void KeyEvent(char KeyCode){};
  virtual void MessageEvent(MESSAGE Msg){};
  virtual void EnterFocus(){};
  virtual void LeaveFocus(){};*/
  virtual void Enter() {};
public:
  usControl(u8 _x, u8 _y, u8 _width, u8 _height, u8 _secondary_order):
    secondary_order(_secondary_order), focused(false), 
    usGraphic(_x, _y, _width, _height) {};
    virtual ~usControl(){};
  bool getFocused(void){return focused;};
  void setFocused(bool _focused) {
    if(focused != _focused)
    {
      focused = _focused;
      if(focused)
         Focus();
      Update();
    };
  };
  virtual void Focus(void){};
  u8 get_secondary_order(void) {return secondary_order;};
  void set_secondary_order(u8 _secondary_order)
    {secondary_order = _secondary_order;};
};

class usScreenList{
private:
  list<usScreen*>screen_list;                                                       
public:
  usScreenList() {};
  virtual ~usScreenList(){};  //usScreenList should not to be deleted, so dtor is for lulz only
  virtual void RemoveScreens();
  virtual void AddScreen(usScreen* pscreen);
 // virtual void RemoveFinishedScreens;
  virtual void RemoveScreen(int scr_id);
  virtual void Process();
};

class usScreen: public usFsm{
  friend usScreenList;
private:
//  bool auto_activate_first_control;
  bool is_exceptional;
  unsigned long param;
//  bool is_finished;
protected:
  u8 message_to_activate;
  u8 focus_number;
  u8 auto_refresh;
  usControl* pFocusedControl;
  list<usControl*> controlList;
  int scr_id;
  int child_screen;
 // list<usControl*>::iterator iter;
  virtual void Activated(unsigned long *param);
  virtual void ActiveLoop(void) = 0;
  virtual void ChildDeactivated(u8 child_result) {};
  virtual void Deactivate(void);
  virtual void ChildScreenActivate(u8 ScreenId);
  virtual void Paint(void);
  virtual usControl* AddControl(usControl* pcontrol);
  virtual void IncFocus();
  virtual void DecFocus();
  virtual void IncSecondaryOrder();
  virtual void DecSecondaryOrder();
  virtual void PlaceControls();
  virtual void RemoveControls();
public:
  usScreen(u8 _message_to_activate, int _scr_id, bool auto_activate = true,
           bool _is_exceptional = true);
  virtual ~usScreen();
  void setMessageToActivate(char msg) {message_to_activate = msg;};
  virtual void Process(void);
  virtual void ActivateFocusedControl();
  void SetFocus(u8 _focus_number) {focus_number = _focus_number;};
  virtual void Update(void);
  int GetScrId(void) {return scr_id;};
  void setAuto_Refresh(u8 _auto_refresh) {auto_refresh = _auto_refresh;};
  /*void setAutoActivateFirstControl(bool val)
  {auto_activate_first_control = val;};*/
};
//-----------------------------------------
//  button style constants
//-------------------------------------------

#define BS_SIMPLE    0x00
#define BS_ROUNDED   0x01
#define BS_FILLED    0x02
#define BS_RESERVED1 0x04 
#define BS_RESERVED2 0x10
#define BS_RESERVED3 0x20

#define BS_RESERVED4 0x40
#define BS_RESERVED5 0x80

class usButton: public usControl{
protected:
  char btn_style;
  virtual void Paint(void);
  /*  virtual void KeyEvent(char KeyCode);
  virtual void MessageEvent(MESSAGE Msg);*/
  virtual void Enter();
  void Click();
  
  int msg_on_click;
  int msg_param;
public:
  usButton(u8 _x, u16 _y, u16 _width, u16 _height, u8 _secondary_order, 
           int _msg_on_click, int _msg_param): 
    usControl(_x, _y, _width, _height, _secondary_order)
    {msg_on_click = _msg_on_click; msg_param = _msg_param;
    btn_style = BS_ROUNDED | BS_FILLED;};
    
  usButton(u8 _x, u16 _y, u16 _width, u16 _height, u8 _secondary_order, 
           u8 _btn_style, int _msg_on_click, int _msg_param): 
    usControl(_x, _y, _width, _height, _secondary_order)
    {msg_on_click = _msg_on_click;
    msg_param = _msg_param;
    btn_style = _btn_style;};
    virtual ~usButton(){};  
    void setBtnStyle(char _btn_style) {btn_style = _btn_style;};
};

class usTextButton: public usButton{
private:
  
  virtual void Paint(void);
public:
  usTextButton(u8 _x, u16 _y, u16 _width, u16 _height, u8 _secondary_order, 
               const char* _text, int _msg_on_click, int _msg_param):
    usButton(_x, _y, _width, _height, _secondary_order, _msg_on_click,
             _msg_param),
    text(_text) {};
    
  usTextButton(u8 _x, u16 _y, u16 _width, u16 _height, u8 _secondary_order, 
               const char* _text, u8 _btn_style,
               int _msg_on_click, int _msg_param):
    usButton(_x, _y, _width, _height, _secondary_order, _btn_style,
             _msg_on_click, _msg_param),
    text(_text) {};
    virtual ~usTextButton(){}; 
    string text;
 // char* gettext() {return text;};
};

enum button_id{BTN_OK, BTN_CANCEL, BTN_DEFAULT, BTN_FORWARD, BTN_BACK,
BTN_HOME};

class usBmpButton: public usButton{
private:
  button_id btn_id;
  virtual void Paint(void);
public:
  usBmpButton(u8 _x, u16 _y, u16 _width, u16 _height, u8 _secondary_order, 
              button_id _btn_id, int _msg_on_click, int _msg_param):
    usButton(_x, _y, _width, _height, _secondary_order, _msg_on_click, _msg_param),
    btn_id(_btn_id) {};
    virtual ~usBmpButton(){};
};
//------------------------------------------------------------------------------
enum editor_mode{EM_INT, EM_FLOAT};

class usEditor: public usControl{
public:
  usEditor(u8 _x, u8 _y, u8 _width, u8 _height, u8 _secondary_order);
  virtual ~usEditor(){};
  virtual void Process(void);
  virtual void Enter();
   //------------
  void setMode(editor_mode _mode);
  editor_mode getMode() {return mode;};
  void setValue(T_VAR init_val);
  void setTag(int tag);
  T_VAR getValue();
  bool text_selected;
  
//  virtual void Focus(void);

protected:
  virtual void Paint();
/*  virtual void KeyEvent(char KeyCode);
  virtual void MessageEvent(MESSAGE Msg);
  virtual void EnterFocus(){};
  virtual void LeaveFocus(){};*/
private:
  static const char max_pos = 10;
  char str[max_pos + 1];
  char cur_pos;
  editor_mode mode;
  T_VAR value;
  
  virtual void Update();
  char InsertChar(char ch);
  void CursorLeft();
  void CursorRight();
  bool ValueIsValid();
  
  void CursorUpdate();
  bool IncreaseValue(char cur_pos);
  bool DecreaseValue(char cur_pos);
};

class usCheckBox: public usControl{
public:
  usCheckBox(u8 _x, u8 _y, u8 _secondary_order, int _msg_on_click, int _msg_param): 
    msg_on_click(_msg_on_click), msg_param(_msg_param),
    checked(false), usControl(_x, _y, 10, 10, _secondary_order) {};
    virtual ~usCheckBox(){};
    
    virtual void Enter();
    //------------
    void setChecked(bool _checked)
    {
      if(checked != _checked)
      {
        checked = _checked;
        Update();
      };
    };
    bool getChecked() {return checked;};
protected:
  virtual void Paint();
private:
  bool checked;
  int msg_on_click;
  int msg_param;
};

//------------------------------------------------------------------------------
/*                        DO NOT DELETE YET !!!
class usBmp{
public:
  usBmp(char* _data, char _width, char _height):
    data(_data), width(_width), height(_height) {};
  virtual void Paint() {};
  void set_id(char _id){id = _id;};
  char get_id(void){return id;};
private:
  char id;
  char width, height;
  char* data;
};
*/

/* for debug purpose
class usTestScreen: public usScreen{
protected:
  virtual void ActiveLoop(void) {};
  virtual void Paint(void) {};
};
*/
#endif
