//------------------------------------------------------------------------------
// rs485_scr.h
//------------------------------------------------------------------------------
#ifndef RS485_SCR_h
#define RS485_SCR_h

#include "usbase.h"
#include "pass_aux_base_class.h"

class Rs485Screen: public PassAuxBaseScreen
{
private:
  usTextButton* pBtns[3];
  usCheckBox* pCheckBox[2];
  usBmpButton* pBmpButtons[3];
  void UpdateButtonValues();
  void DrawTableLine(int tag, char line);
//  char scr_num;
protected:
  virtual void Paint(void);
  virtual void ActiveLoop();
  virtual void PlaceControls();
public:
  Rs485Screen();
  virtual ~Rs485Screen() {};
};

#endif
