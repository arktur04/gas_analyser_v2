//------------------------------------------------------------------------------
// do_test.h
//------------------------------------------------------------------------------
#ifndef DO_TEST_SCR_h
#define DO_TEST_SCR_h

#include "usbase.h"

class DoTestScreen: public usScreen
{
private:
  usCheckBox* pCheckBox[3][2];
  
  usBmpButton* pBmpButtons[3];
  
  int getTag(char x);
 // char scr_num;
protected:
  virtual void Paint(void);
  virtual void Activated(unsigned long * param);
  virtual void ActiveLoop();
  virtual void PlaceControls();
public:
  DoTestScreen();
  virtual ~DoTestScreen();
};

#endif
