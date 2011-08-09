//------------------------------------------------------------------------------
// ������ ��������� ������� �����
//------------------------------------------------------------------------------
#ifndef MAIN_SCREEN_h
#define MAIN_SCREEN_h

#include "usbase.h"
#include "screens.h"

class MainScreen: public usScreen
{
private: 
  char main_sub_state;
protected:
 // virtual void Update(void);
  virtual void ActiveLoop(void);
  virtual void Activated(unsigned long *param);
  virtual void Paint(void);
 // virtual void PlaceControls();
public:
 /* usScreen(_message_to_activate = MSG_SCREEN_ACTIVATE):
    message_to_activate(u8 _message_to_activate) {}; */
  MainScreen():usScreen::usScreen(MSG_MAIN_SCREEN_ACTIVATE, SCR_MAIN)
   {main_sub_state = 0; auto_refresh = false;};
    virtual ~MainScreen() {};
};

#endif
