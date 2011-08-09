//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#ifndef DEF_WARN_SCR_h
#define DEF_WARN_SCR_h

#include "usbase.h"

#define OK_MSW    0 //message window w ok button
#define OK_CANCEL 1 //message window w ok & cancel buttons

class MessageWindow: public usScreen{
public:
  MessageWindow(void):
    usScreen(MSG_DEF_WARN_SCREEN_ACTIVATE, SCR_MSG, true, false),
    btns(OK_MSW){};
  MessageWindow(int _btns):
    usScreen(MSG_DEF_WARN_SCREEN_ACTIVATE, SCR_MSG, true, false), 
    btns(_btns){};  
      //  EditorScreen(unsigned long _tag);
  virtual ~MessageWindow() {};
  
 // virtual void Activated(unsigned long * param);
protected:
  virtual void ActiveLoop(void);
  virtual void Paint(void);
  virtual void PlaceControls();
private:
  int btns;
};

#endif
