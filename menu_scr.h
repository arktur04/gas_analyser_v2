//------------------------------------------------------------------------------
// menu_scr.cpp
//------------------------------------------------------------------------------
#ifndef MENU_SCR_h
#define MENU_SCR_h

#include "usbase.h"
#include "pass_aux_base_class.h"

typedef struct{
  char header[25]; //заголовок экрана
  char buttons[10][11]; //надписи на кнопках меню
  signed char sec_order[10]; //if -1, the button is disabled
  int number; //номер экрана
  char back_allowed; //кнопка "назад" разрешена
  char home_allowed; //кнопка "главный экран" разрешена
  char forward_allowed; //кнопка "вперед" разрешена
} T_MENU_DESCRIPTOR;

class MenuScreen: public PassAuxBaseScreen
{
private:
  usTextButton* pTextButtons[10];
  usBmpButton* pBmpButtons[3];
  char scr_num;
protected:
 // virtual void Update(void);
  virtual void PlaceControls();
  virtual void ActiveLoop(void);
  //virtual void Activated();//(unsigned long *param);
  virtual void Paint(void);
public:
  MenuScreen(char _scr_num, int _scr_id);
  virtual ~MenuScreen() {};
  void set_scr_num(char _scr_num) {scr_num = _scr_num;};
  char get_scr_num() {return scr_num;};
};

#endif
