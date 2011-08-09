//------------------------------------------------------------------------------
// ethernet_scr.h
//------------------------------------------------------------------------------
#ifndef ETHERNET_SCR_h
#define ETHERNET_SCR_h

#include "usbase.h"

class EthernetScreen: public usScreen
{
private:
  usTextButton* pBtns[13];
  usBmpButton* pBmpButtons[3];
  void UpdateButtonValues();
  void DrawTableLine(int tag, char line);
//  char scr_num;
protected:
  virtual void Paint(void);
  virtual void ActiveLoop();
  virtual void PlaceControls();
public:
  EthernetScreen();
  virtual ~EthernetScreen() {};
};

#endif
