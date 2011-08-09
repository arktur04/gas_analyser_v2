//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#ifndef MSG_SCR_h
#define MSG_SCR_h

#include "usbase.h"

#define OK_MSW        0 //message window w ok button
#define OK_CANCEL_MSW 1 //message window w ok & cancel buttons

class MessageWindow: public usScreen{
public:
  MessageWindow(void):
    usScreen(MSG_DEF_WARN_SCREEN_ACTIVATE, SCR_MSG, true, false),
    btns(OK_MSW){};  //default ctor just for lulz, use the second one
    
  MessageWindow(int _btns, char*_str1, char*_str2, char*_str3, char*_str4):
    usScreen(MSG_DEF_WARN_SCREEN_ACTIVATE, SCR_MSG, true, false), 
    btns(_btns), str1(_str1), str2(_str2), str3(_str3), str4(_str4){};  
      //  EditorScreen(unsigned long _tag);
  virtual ~MessageWindow() {};
  
 // virtual void Activated(unsigned long * param);
protected:
  virtual void ActiveLoop(void);
  virtual void Paint(void);
  virtual void PlaceControls();
private:
  int btns;
  char*str1;
  char*str2;
  char*str3;
  char*str4;
};

#endif
