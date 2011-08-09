//------------------------------------------------------------------------------
// ai_test.h
//------------------------------------------------------------------------------
#ifndef AI_TEST_SCR_h
#define AI_TEST_SCR_h

#include "usbase.h"

class AiTestScreen: public usScreen
{
private:
 int
  adc1_code, adc2_code, adc3_code, adc4_code,
  adc1_code_, adc2_code_, adc3_code_, adc4_code_;
  
  usBmpButton* pBmpButtons[3];
//  char scr_num;
protected:
  virtual void Paint(void);
  virtual void ActiveLoop();
  virtual void PlaceControls();
public:
  AiTestScreen();
  virtual ~AiTestScreen() {};
};

#endif
