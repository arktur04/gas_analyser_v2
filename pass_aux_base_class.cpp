extern "C"{   
  #include "lcd.h"
  #include "pass_controller.h"    
};

#include "usbase.h"
#include "pass_aux_base_class.h"

static const char*passSign[4] = {" ", "*", "+", "!"};

void PassAuxBaseScreen::Paint(void)
{
  usScreen::Paint();
  LcdText(121, 1, 127, 7, passSign[getPasswordEntered()]); 
};
