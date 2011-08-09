//------------------------------------------------------------------------------
// Password controller
//------------------------------------------------------------------------------

#include "type.h"
#include "timers.h"
#include "messages.h"
#include "pass_controller.h"
#include "variables.h"
//#include "password_screen.h"

char pass_state = 0;
int password_reset_time;

/* if((GetTimer(BACKLIGHT_TIMER) >= scr_backlight_time) &&
         (scr_backlight_time != 0))
*/
char EditAllowed(void)
{
//  return 1;                                    //debug !!!
  if(pass_state == 0)  
  {
   // SendMessage(MSG_PASSWORD_SCREEN_ACTIVATE);
    pass_state = 1;
  };
  if(pass_state == 2)
  {
    ResetTimer(PASS_TIMER);
    return 1;
  };
  return 0;
}

char GetPasswordEntered(void)
{
  return ((pass_state == 2) || (GetIntValueByTag(PASS_RESET_TIME) == -1));
}

void ProcessPassController(void)
{
 switch(pass_state)
  {
    case 0: //password not entered
      break;
    case 1: //password window is active
      if(GetMessage(MSG_PASS_CANCEL) || GetMessage(MSG_PASS_WRONG))                              
      {
        pass_state = 0;
      };      
      if(GetMessage(MSG_PASS_OK))
      {
        ResetTimer(PASS_TIMER);
        pass_state = 2;
      };                                                               
      break;
  case 2: //password is entered
    password_reset_time = GetIntValueByTag(PASS_RESET_TIME) * minute;
    if((GetTimer(PASS_TIMER) >= password_reset_time) &&
       (password_reset_time > 0))
      pass_state = 0;
    break;
  };
};
