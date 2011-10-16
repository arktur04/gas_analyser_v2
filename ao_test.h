//------------------------------------------------------------------------------
// ao_test.h
//------------------------------------------------------------------------------
#ifndef AO_TEST_SCR_h
#define AO_TEST_SCR_h

#include "usbase.h"
#include "pass_aux_base_class.h"

class AoTestScreen: public PassAuxBaseScreen
{
private:
  usTextButton* pBtns[4];
  usBmpButton* pBmpButtons[3];
  void UpdateButtonValues();
  void DrawTableLine(int tag, char line);
//  char scr_num;
protected:
  virtual void Activated(unsigned long *param);
  virtual void Paint(void);
  virtual void ActiveLoop();
  virtual void PlaceControls();
public:
  AoTestScreen();
  virtual ~AoTestScreen();
};

#endif
