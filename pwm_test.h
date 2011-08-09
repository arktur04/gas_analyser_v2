//------------------------------------------------------------------------------
// pwm_test.h
//------------------------------------------------------------------------------
#ifndef PWM_TEST_SCR_h
#define PWM_TEST_SCR_h

#include "usbase.h"
/*
class AoTestScreen: public usScreen
{
private:
  usTextButton* pBtns[4];
  usBmpButton* pBmpButtons[3];
  void UpdateButtonValues();
  void DrawTableLine(int tag, char line);
//  char scr_num;
protected:
  virtual void Paint(void);
  virtual void ActiveLoop();
public:
  AoTestScreen();
*/

class PwmTestScreen: public usScreen
{
private:
  int pwm1, pwm2;
  usTextButton* pBtns[2];
  usBmpButton* pBmpButtons[3];
  void UpdateButtonValues();
//  char scr_num;
protected:
  virtual void Paint(void);
  virtual void ActiveLoop();
  virtual void PlaceControls();
  virtual void Activated(unsigned long *param);
public:
  PwmTestScreen();
  virtual ~PwmTestScreen();
};

#endif
