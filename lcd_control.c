#include "board.h"
#include <nxp/iolpc1768.h>
#include "type.h"
#include "timers.h"
#include "variables.h"
#include "lcd_control.h"
#include "messages.h"
#include <intrinsics.h>

char lcd_control_state = 0;
int scr_backlight_time;

void ProcessLcdControl(void)
{
  scr_backlight_time = GetIntValueByTag(SCR_BACKLIGHT_TIME) * 60 * 100;
  switch(lcd_control_state)
  {
  case 0:
    if(scr_backlight_time)
    {
      if((GetTimer(BACKLIGHT_TIMER) >= scr_backlight_time) &&
         (scr_backlight_time >= 0))
      {
        lcd_control_state = 1;
      };
    }
    else
    {
      lcd_control_state = 1;
    };  
    if(GetMessage(MSG_ANYKEY))
    {
      ResetTimer(BACKLIGHT_TIMER);
    };
    OutputSet(LCD_LED);
    break;
  case 1:
    if(((scr_backlight_time > 0) && GetMessage(MSG_ANYKEY))
       || (scr_backlight_time < 0))
   // if(GetMessage(MSG_KEYPRESSED)
    {
      ResetTimer(BACKLIGHT_TIMER);
      lcd_control_state = 0;
    };
    OutputClr(LCD_LED);
    break;
  };
}
//------------------------------------------------------------------------------
// End of file
//------------------------------------------------------------------------------
