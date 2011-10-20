#include "board.h"
#include <nxp/iolpc1768.h>
#include "type.h"
#include "timers.h"
#include "led_control.h"
#include "messages.h"

#include <intrinsics.h>

#define DISP_LED_NUM 8
#define SYS_SPI_BUS_WIDTH 32

const unsigned long disp_leds[DISP_LED_NUM] =
{0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000};
/*
const unsigned long sys_spi[SYS_SPI_BUS_WIDTH] =
{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000,
0x10000, 0x20000, 0x40000, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000};
*/
char disp_led_states[DISP_LED_NUM] = {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF};

char sys_spi_states[SYS_SPI_BUS_WIDTH] = {ON, ON, OFF, OFF, OFF, OFF, OFF, OFF,
OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF,
BLINK, OFF, OFF, OFF, OFF, OFF, OFF, OFF};

char blinkFlag = 0, fastBlinkFlag = 0;
volatile unsigned long sys_state = 0;

void SetDispLedState(char led, char state)
{
  disp_led_states[led] = state;
}

void SetSysSpiBusState(char led, char state)
{
  sys_spi_states[led] = state;
}

void ProcessLeds(void)
{
  unsigned long disp_on_state = 0, disp_off_state = 0;
  
  if(GetTimer(LED_BLINK_TIMER) > 50)
  {
    ResetTimer(LED_BLINK_TIMER);
    
    blinkFlag = ~blinkFlag;
  };
  if(GetTimer(LED_FAST_BLINK_TIMER) > 15)
  {
    ResetTimer(LED_FAST_BLINK_TIMER);
    
    fastBlinkFlag = ~fastBlinkFlag;
  }; 
  for(char i = 0; i < DISP_LED_NUM; i++)
  {
    switch(disp_led_states[i])
    {
    case OFF:
      disp_off_state |= disp_leds[i];
      break;
    case ON:
      disp_on_state |= disp_leds[i];
      break;
    case BLINK:
      if(blinkFlag)
        disp_on_state |= disp_leds[i];
      else
        disp_off_state |= disp_leds[i];
      break;
    case FAST_BLINK:
      if(fastBlinkFlag)
        disp_on_state |= disp_leds[i];
      else
        disp_off_state |= disp_leds[i];
      break;
    };
  };
  
  for(char i = 0; i < SYS_SPI_BUS_WIDTH; i++)
  {
    switch(sys_spi_states[i])
    {
    case OFF:
      ClrSysBit(i);
      break;
    case ON:
      SetSysBit(i);
      break;
    case BLINK:
      if(blinkFlag)
        SetSysBit(i);
      else
        ClrSysBit(i);
      break;
      case FAST_BLINK:
      if(fastBlinkFlag)
        SetSysBit(i);
      else
        ClrSysBit(i);
      break;
    };
  };
  
  OutputSet(disp_on_state);
  OutputClr(disp_off_state);
};

void SetSysBit(char bit_num)
{
  sys_state |= (1UL << bit_num);
}

void ClrSysBit(char bit_num)
{
  sys_state &= ~(1UL << bit_num);
}

void UpdateSysBus(void)
{
  WriteSysReg(sys_state);
}

void ProcessSysState(void)
{
 // while(GetSemaphore(SIS_SPI_SEMAPHORE));
  WriteSysReg(sys_state);
}
//------------------------------------------------------------------------------
// End of file
//------------------------------------------------------------------------------
