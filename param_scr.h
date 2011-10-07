//------------------------------------------------------------------------------
// param_scr.cpp
//------------------------------------------------------------------------------
#ifndef PARAM_SCR_h
#define PARAM_SCR_h

#include "usbase.h"
#include "screens.h"
/*
typedef struct{
  char header[25]; //заголовок экрана
  char buttons[10][11]; //надписи на кнопках меню
  char btn_allowed[10]; //кнопка разрешена
  int number; //номер экрана
  char back_allowed; //кнопка "назад" разрешена
  char home_allowed; //кнопка "главный экран" разрешена
  char forward_allowed; //кнопка "вперед" разрешена
} T_MENU_DESCRIPTOR;
*/
class ParamScreen: public usScreen
{
private:
  usTextButton* pBtns[5];
  usBmpButton* pBmpButtons[3];
  char scr_num;
  
  void DrawTableLine(int tag, char line);
  void UpdateButtonValues(T_PARAM_SCREEN_DESCRIPTOR screen);
protected:
 // virtual void Update(void);
//  virtual void ActiveLoop(void);
 // virtual void Activated();//(unsigned long *param); 
  virtual void Paint(void);
  virtual void PlaceControls();
public:
  ParamScreen(char _scr_num, int _scr_id);
  virtual ~ParamScreen() {};
  void set_scr_num(char _scr_num) {scr_num = _scr_num;};
  char get_scr_num() {return scr_num;};
};

#endif
