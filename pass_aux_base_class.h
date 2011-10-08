//------------------------------------------------------------------------------
// Aux base class for screen with the password mark in the corner
//------------------------------------------------------------------------------
#ifndef BASE_SCREEN_h
#define BASE_SCREEN_h

#include "usbase.h"
//#include "pass_aux_base_class.h"
//#include "screens.h"

class PassAuxBaseScreen: public usScreen
{
private: 
protected:
  virtual void Paint(void);
public:
  PassAuxBaseScreen(u8 _message_to_activate, int _scr_id, bool auto_activate = true,
           bool _is_exceptional = true):
    usScreen::usScreen(_message_to_activate, _scr_id, auto_activate, 
                       _is_exceptional){};
};

#endif
