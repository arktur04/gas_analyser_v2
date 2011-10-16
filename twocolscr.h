//------------------------------------------------------------------------------
// twocolscr.h
//------------------------------------------------------------------------------
#ifndef TWOCOLSCR_h
#define TWOCOLSCR_h

#include "usbase.h"
#include "pass_aux_base_class.h"

class TwoColScr: public PassAuxBaseScreen
{
private:
  usTextButton* pBtns[5][2];
  usBmpButton* pBmpButtons[3];
  char scr_num;
  T_TWO_COL_SCREEN_DESCRIPTOR screen;
  void DrawTableLine(int tag_1, int tag_2, char line);
protected:
  virtual void Paint(void);
  virtual void PlaceControls();
public:
  TwoColScr(char _scr_num, int _scr_id);
  virtual ~TwoColScr() {};
  
  void set_scr_num(char _scr_num)
  {
    scr_num = _scr_num;
    screen = GetScreen(scr_num).scr.two_col_screen;
  };
  char get_scr_num() {return scr_num;};
};

#endif
