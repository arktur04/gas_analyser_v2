//------------------------------------------------------------------------------
// menu_scr.cpp
//------------------------------------------------------------------------------
#ifndef MENU_SCR_h
#define MENU_SCR_h

#include "usbase.h"
#include "pass_aux_base_class.h"

typedef struct{
  char header[25]; //��������� ������
  char buttons[10][11]; //������� �� ������� ����
  signed char sec_order[10]; //if -1, the button is disabled
  int number; //����� ������
  char back_allowed; //������ "�����" ���������
  char home_allowed; //������ "������� �����" ���������
  char forward_allowed; //������ "������" ���������
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
