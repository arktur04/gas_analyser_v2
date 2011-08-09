#include "board.h"
#include <nxp/iolpc1768.h>
#include "type.h"
#include "timers.h"
#include "variables.h"
#include "lcd_control.h"
#include "messages.h"
#include <intrinsics.h>

char lcd_control_state = 0;
int /*reset_time,*/ scr_backlight_time;

void ProcessLcdControl(void)
{
  switch(lcd_control_state)
  {
  case 0:
    scr_backlight_time = GetIntValueByTag(SCR_BACKLIGHT_TIME) * 60 * 100;
    if(scr_backlight_time)
    {
      if((GetTimer(BACKLIGHT_TIMER) >= scr_backlight_time) &&
         (scr_backlight_time != 0))
      {
        lcd_control_state = 1;
      };
    };
    if(GetMessage(MSG_ANYKEY))
    {
      ResetTimer(BACKLIGHT_TIMER);
    };
    OutputSet(LCD_LED);
    break;
  case 1:
    //if(GetMessage(MSG_ANYKEY))
    if(GetMessage(MSG_KEYPRESSED) ||
       GetMessage(MSG_L_ENCODER_CW) || GetMessage(MSG_L_ENCODER_CCW)|| GetMessage(MSG_R_ENCODER_CW) ||
                    GetMessage(MSG_R_ENCODER_CCW) ||
                         GetMessage(MSG_L_ENCODER_PRESSED) ||
                         GetMessage(MSG_R_ENCODER_PRESSED)
       )
    {
      ResetTimer(BACKLIGHT_TIMER);
      
      lcd_control_state = 0;
    };
    OutputClr(LCD_LED);
    break;
  };
  /*
  reset_time = GetIntValueByTag(SCR_RESET_TIME) * 60 * 100;
  if(reset_time < 30000)
    reset_time = 30000; // reset time can't be less then 5 min
  
  
 // reset_time = 6000;
  
  if(GetTimer(DISP_RESET_TIMER) >= reset_time)
  {
    ResetTimer(DISP_RESET_TIMER);
    LcdInitModule();
  };
  */
}

//------------------------------------------------------------------------------
// End of file
//------------------------------------------------------------------------------
