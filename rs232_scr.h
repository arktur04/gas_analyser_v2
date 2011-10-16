//------------------------------------------------------------------------------
// rs232_scr.h
//------------------------------------------------------------------------------
#ifndef RS232_SCR_h
#define RS232_SCR_h

#include "usbase.h"
#include "pass_aux_base_class.h"

class Rs232Screen: public PassAuxBaseScreen
{
private:
  usTextButton* pBtns[2];
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
  Rs232Screen();
  virtual ~Rs232Screen() {};
};

#endif
