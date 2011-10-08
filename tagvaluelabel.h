//------------------------------------------------------------------------------
// usTagValueLabel class
//------------------------------------------------------------------------------
#ifndef TAGVALUELABEL_h
#define TAGVALUELABEL_h
/*
extern "C"{
//#include "messages.h"
#include "bmps.h"
#include "dict.h"
};

#include <list>
#include <string>
#include "messages.h"
#include "ustype.h"
*/
#include "usbase.h"
#include "editor_scr.h"
#include "pass_scr.h"

class usTagValueLabel: public usTextButton{
private:
  int tag;
  EditorScreen *editor_scr;
  PassScreen *pass_scr;
protected:
  //virtual void Paint(void);  
  virtual void Click();
public:
  usTagValueLabel(u8 _x, u16 _y, u16 _width, u16 _height, u8 _secondary_order,
                  int _tag):
    usTextButton(_x, _y, _width, _height, _secondary_order, "", BS_SIMPLE,
                 MSG_NULL, 0),
    tag(_tag) {};
    virtual void Update(void);
    virtual ~usTagValueLabel() {};
};

#endif
