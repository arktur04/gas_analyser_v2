//------------------------------------------------------------------------------
// trend_scr.h
//------------------------------------------------------------------------------
#ifndef TREND_SCR_h
#define TREND_SCR_h

#include "usbase.h"

class TrendScreen: public usScreen
{
private:
 int var_tag;
 float min, max;
 static const int TREND_SIZE = 80;
 float curr_value;
 float trend_values[TREND_SIZE];
 int curr_pos;
 
  usBmpButton* pBmpButtons[3];
//  char scr_num;
  void Shift();
  char ValueToCoord(float value);
protected:
  virtual void Paint(void);
  virtual void ActiveLoop();
  virtual void PlaceControls();
public:
  TrendScreen(int _var_tag, float _min, float _max, char scr_id);
  virtual ~TrendScreen() {};
  void setTag(int _var_tag) {var_tag = _var_tag;};
  void setMinMax(float _min, float _max) {min = _min; max = _max;};
};

#endif
