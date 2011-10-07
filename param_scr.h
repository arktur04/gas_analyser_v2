//------------------------------------------------------------------------------
// param_scr.cpp
//------------------------------------------------------------------------------
#ifndef PARAM_SCR_h
#define PARAM_SCR_h

#include "usbase.h"
#include "screens.h"
/*
typedef struct{
  char header[25]; //��������� ������
  char buttons[10][11]; //������� �� ������� ����
  char btn_allowed[10]; //������ ���������
  int number; //����� ������
  char back_allowed; //������ "�����" ���������
  char home_allowed; //������ "������� �����" ���������
  char forward_allowed; //������ "������" ���������
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
