#include "board.h"
#include "messages.h"                                                 
#include "timers.h"
#include "led_control.h"
#include "power_control.h"

char pow_l_state = 0;
char pow_r_state = 0;

void InitPowerControl(void)
{

}

void ProcessLeftPowerControl(void)
{
  switch(pow_r_state)
  {
  case 0:
    SetSysSpiBusState(SYS_TRG_RES_L, OFF);  //reset trigger
    pow_l_state = 1;
    break;
  case 1:
    SetSysSpiBusState(SYS_TRG_RES_L, ON);
    pow_l_state = 2;    
    break;
  }; 
}

void ProcessRightPowerControl(void)
{
  switch(pow_r_state)
  {
  case 0:
    SetSysSpiBusState(SYS_TRG_RES_R, OFF);  //reset trigger
    pow_r_state = 1;
    break;
  case 1:
    SetSysSpiBusState(SYS_TRG_RES_R, ON);
    pow_r_state = 2;    
    break;
  };
}