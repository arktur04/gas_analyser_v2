#include "timers.h"
#include "board.h"
#include "irq.h"
#include "led_control.h"
#include <nxp/iolpc1768.h>
#include <intrinsics.h>

unsigned int Timers[MAX_TIMERS];

const unsigned int max_width = 19000;
const unsigned int min_width = 3500;

char pwm_ch = 0;
int ch0_width;// = 15000;
int ch1_width;// = 15000;

char ch0_flag, ch1_flag;

void SetTimer1Width(int width)
{
  int _width;
  
  _width = 20000 - width;
  if(_width <= min_width)
  {
    ch0_width = min_width;
    return;
  };
  
  if(_width >= max_width)
  {
    ch0_width = max_width;
    return;
  };
  
  ch0_width = _width;
}

void SetTimer2Width(int width)
{
  int _width;

  _width = 20000 - width;
  if(_width <= min_width)
  {
    ch1_width = min_width;
    return;
  };
  
  if(_width >= max_width)
  {
    ch1_width = max_width;
    return;
  };
  
  ch1_width = _width;
}

void ProcessTimers(void)
{
  //----------------------------------------------------------------------------
  // PWM control
  //----------------------------------------------------------------------------
  if(pwm_ch)
  {
    T1TCR_bit.CR = 1;     // set reset
    T1TCR_bit.CR = 0;     // release reset
    T1MR0 = ch0_width;
    pwm_ch = 0;
    ch0_flag = !GetPwm0(); //check the line state
    Pwm0Set();                                                                               //temp
    // Pwm1Clr();
    T1TCR_bit.CE = 1; 
  }
  else
  {
    T2TCR_bit.CR = 1;     // set reset
    T2TCR_bit.CR = 0;     // release reset
    T2MR0 = ch1_width;
    pwm_ch = 1;
    //  Pwm0Clr();
    ch1_flag = !GetPwm1();  //check the line state
    Pwm1Set();       
    T2TCR_bit.CE = 1; 
  };
  
  //----------------------------------------------------------------------------
  for(char i = 0; i < MAX_TIMERS; i++)
    Timers[i]++;
}

void ProcessTimer1(void)
{
//  ch0_flag = ~GetPwm0();
  Pwm0Clr();
}

void ProcessTimer2(void)
{
 // ch1_flag = ~GetPwm1();
  Pwm1Clr();
}

char key_flag = 0;

void ProcessTimer3(void)
{
  if(key_flag)
  {
    AdcKeyClr();
  }
  else
  {
    AdcKeySet();
  };
  key_flag = !key_flag;  
}

unsigned int GetTimer(char Timer)
{
  return Timers[Timer];
}

void ResetTimer(char Timer)
{
  Timers[Timer] = 0;
}

void InitTimers(void)
{
  for(char i = 0; i < MAX_TIMERS; i++)
    Timers[i] = 0;
}

char GetHeater0State(void)
{
  return ch0_flag;
}

char GetHeater1State(void)
{
  return ch1_flag;
}

//-----------------------

/*************************************************************************
 * Function Name: TMR0_IRQHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: Timer 0 interrupt handler
 *
 *************************************************************************/
void (*processing_handler)(void);

void SetProcessingHandler(void (*_processing_handler)(void))
{
  processing_handler = _processing_handler;
}
  /*   
void TMR0_IRQHandler(void)
{
  ProcessTimers();
  //clear interrupt
  T0IR_bit.MR0INT = 1;
  NVIC_ClrPend(NVIC_TIMER0);
}
*/

void SysTick_Handler(void)
{
  ProcessTimer3();

  ICSR_bit.PENDSTCLR = 1;
}

void RIT_IRQHandler(void)
{
  RICTRL_bit.RITINT = 1;
 // ProcessTimers();
  processing_handler();
 // ProcessSysState();
}
