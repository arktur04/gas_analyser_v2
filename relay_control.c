//#include "board.h"                      //????
//#include <nxp/iolpc1768.h>             //????
//#include "type.h"                      //????

#include "relay_control.h"
#include "led_control.h"

//#include <intrinsics.h>                 //????

void SetRelayState(char relay, char state)
{
  char leds[] = {SYS_LED_DOUT0, SYS_LED_DOUT1, SYS_LED_DOUT2, SYS_LED_DOUT3, 
  SYS_LED_DOUT4, SYS_LED_DOUT5};
  
  SetSysSpiBusState(leds[relay], state);
};
//------------------------------------------------------------------------------
// End of file
//------------------------------------------------------------------------------
