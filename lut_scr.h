//------------------------------------------------------------------------------
// lut_scr.cpp
//------------------------------------------------------------------------------
#ifndef LUT_SCR_h
#define LUT_SCR_h

extern "C"{
#include "screens.h"
};

#include "usbase.h"
#include "pass_aux_base_class.h"

class LutScreen: public PassAuxBaseScreen
{
private:
  usTextButton* pBtns[5][2];
  usBmpButton* pBmpButtons[3];
  char scr_num;
  T_CLAPP_SCREEN_DESCRIPTOR screen;
  void DrawTableLine(int tag_x, int tag_y, char line);
protected:
 // virtual void Update(void);
//  virtual void ActiveLoop(void);
 // virtual void Activated(unsigned long *param);
  virtual void Paint(void);
  virtual void PlaceControls();
public:
  LutScreen(char _scr_num, int _scr_id);
  virtual ~LutScreen(){};
  void set_scr_num(char _scr_num)
  {
    scr_num = _scr_num;
    screen = GetScreen(scr_num).scr.clapp_screen;
  };
  char get_scr_num() {return scr_num;};
};

#endif
