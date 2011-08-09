//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------
#ifndef PASS_SCR_h
#define PASS_SCR_h

#include "usbase.h"
#include "variables.h"

class PassScreen: public usScreen{
public:
  PassScreen(void):usScreen(MSG_PASSWORD_SCREEN_ACTIVATE,
                            SCR_PASS, true, false) {};
  virtual ~PassScreen() {};
protected:
  virtual void Activated(unsigned long * param);
  virtual void ActiveLoop(void);
  virtual void Paint(void);
  virtual void PlaceControls();
private:
  usEditor * editor;
};
#endif
