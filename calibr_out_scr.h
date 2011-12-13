//------------------------------------------------------------------------------
// calibr_out_scr.h
//------------------------------------------------------------------------------
#ifndef CALIBR_OUT_SCR_h
#define CALIBR_OUT_SCR_h

#include "usbase.h"
#include "twocolscr.h"
#include "screens.h"

class CalibrOutScreen: public TwoColScr
{
public:
  CalibrOutScreen():TwoColScr(28, SCR_OUT_CALIBR) {};
  virtual void Activated(unsigned long * param);
  virtual ~CalibrOutScreen();
};

#endif
