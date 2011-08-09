//------------------------------------------------------------------------------
// misc_test.h
//------------------------------------------------------------------------------
#ifndef MISC_TEST_SCR_h
#define MISC_TEST_SCR_h

#include "usbase.h"

class MiscScreen: public usScreen
{
private:
  usTextButton* pBtns[5];
  usCheckBox* pCheckBox[2];
  usBmpButton* pBmpButtons[3];
  void UpdateButtonValues();
 // void DrawTableLine(int tag, char line);
//  char scr_num;
protected:
  virtual void Activated(unsigned long *param);
  virtual void Paint(void);
  virtual void ActiveLoop();
  virtual void PlaceControls();
public:
  MiscScreen();
  virtual ~MiscScreen();
};

#endif
