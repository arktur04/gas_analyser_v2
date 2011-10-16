//------------------------------------------------------------------------------
// do_test.h
//------------------------------------------------------------------------------
#ifndef DO_TEST_SCR_h
#define DO_TEST_SCR_h

#include "usbase.h"
#include "pass_aux_base_class.h"

static const int discrOutTags[6] = {RELAY_OUT_0, RELAY_OUT_1, RELAY_OUT_2,
  RELAY_OUT_3, RELAY_OUT_4, RELAY_OUT_5};

class DoTestScreen: public PassAuxBaseScreen
{
private:
  usCheckBox*pCheckBox[3][2];
  usBmpButton*pBmpButtons[3];
 // int getTag(char x);
  
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
