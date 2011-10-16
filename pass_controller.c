//------------------------------------------------------------------------------
// Password controller
//------------------------------------------------------------------------------

#include "type.h"
#include "timers.h"
#include "messages.h"
#include "pass_controller.h"
#include "variables.h"
//#include "password_screen.h"

char passState = 0;
char passLevel = 0;
int password_reset_time;

char EditAllowed(void)
{
  if(passState == 0)  
  {
   // SendMessage(MSG_PASSWORD_SCREEN_ACTIVATE);
    passState = 1;
  };
  if(passState == 2)
  {
    ResetTimer(PASS_TIMER);
    return 1;
  };
  return 0;
}

char getPasswordEntered(void)
{
  if(passState == 2)
    return passLevel;
  if(GetIntValueByTag(PASS_RESET_TIME) == -1)
    return 1;
  return 0;
}

void ProcessPassController(void)
{
 switch(passState)
  {
    case 0: //password not entered
      passLevel = 0;
      break;
    case 1: //password window is active
      if(GetMessage(MSG_PASS_CANCEL) || GetMessage(MSG_PASS_WRONG))                              
      {
        passState = 0;
        passLevel = 0;
      };      
      if(GetMessage(MSG_PASS1_OK))
      {
        ResetTimer(PASS_TIMER);
        passState = 2;
        passLevel = 1;
      };  
      if(GetMessage(MSG_PASS2_OK))
      {
        ResetTimer(PASS_TIMER);
        passState = 2;
        passLevel = 2;
      };
      if(GetMessage(MSG_PASS3_OK))
      {
        ResetTimer(PASS_TIMER);
        passState = 2;
        passLevel = 3;
      };
      break;
  case 2: //password is entered
    if(GetMessage(MSG_PASS_WRONG))                              
    {
      passState = 0;
      passLevel = 0;
    };      
    if(GetMessage(MSG_PASS1_OK))
    {
      ResetTimer(PASS_TIMER);
      passLevel = 1;
    };  
    if(GetMessage(MSG_PASS2_OK))
    {
      ResetTimer(PASS_TIMER);
      passLevel = 2;
    };
    if(GetMessage(MSG_PASS3_OK))
    {
      ResetTimer(PASS_TIMER);
      passLevel = 3;
    };
    
    password_reset_time = GetIntValueByTag(PASS_RESET_TIME) * minute;
    if((GetTimer(PASS_TIMER) >= password_reset_time) &&
       (password_reset_time > 0))
      passState = 0;
    break;
  };
};
