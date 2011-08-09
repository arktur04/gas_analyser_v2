//------------------------------------------------------------------------------
// Модуль реализует экран редактора значений
//------------------------------------------------------------------------------
#ifndef EDITOR_SCR_h
#define EDITOR_SCR_h

#include "usbase.h"
#include "variables.h"

class EditorScreen: public usScreen{
public:
  EditorScreen(void);
  EditorScreen(unsigned long _tag);
  virtual ~EditorScreen() {};
  void setCheckInterval(bool _check_interval) 
  {check_interval = _check_interval;};
  void setVarTag(int _tag) {var_tag = _tag;};
  
  virtual void Activated(unsigned long * param);
 
protected:
  virtual void ActiveLoop(void);
  virtual void Paint(void);
  virtual void PlaceControls();
private:
  bool check_interval;
  int var_tag;
  T_DICT_VAR_DESCR var;
  usEditor * editor;
  int getTag(int x, int y);
};

//void SetEditorVarByTag(int tag);
//void ProcessEditorScreen(void);

#endif
