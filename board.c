#include "board.h"
#include <nxp/iolpc1768.h>
//#include "timers.h"
#include "irq.h"
#include "type.h"
#include "messages.h"

#include <intrinsics.h>

#define REPETITIVE_TICK_PER_SEC   123
#define TIMER0_TICK_PER_SEC   100
#define TIMER1_TICK_PER_SEC   200
#define TIMER2_TICK_PER_SEC   200
#define TIMER3_TICK_PER_SEC   10000

#define TIMER0_IN_FREQ        25000000

void InitRepetitiveTimer(void)
{
// Enable RIT clocks
  PCONP_bit.PCRIT = 1; // enable clock
  RICOMPVAL = (TIMER0_IN_FREQ)/(REPETITIVE_TICK_PER_SEC);
  RIMASK = 0;
  RICTRL_bit.RITENCLR = 1;
  RICTRL_bit.RITENBR  = 1;
  RICTRL_bit.RITEN    = 1;
}

void InitSysTick(void)
{
  STRELOAD  =  9999; // set reload register
 
  STCURR   =  (0x00); // Load the SysTick Counter Value 
  SYSTICKCSR_bit.CLKSOURCE = 1;
  SYSTICKCSR_bit.ENABLE = 1;
  SYSTICKCSR_bit.TICKINT = 1; // Enable SysTick IRQ and SysTick Timer 
}

void InitTimer0(void)
{
// Enable TIM0 clocks
  PCONP_bit.PCTIM0 = 1; // enable clock
// Init Time0
  T0TCR_bit.CE = 0;     // counting  disable
  T0TCR_bit.CR = 1;     // set reset
  T0TCR_bit.CR = 0;     // release reset
  T0CTCR_bit.CTM = 0;   // Timer Mode: every rising PCLK edge
  T0MCR_bit.MR0I = 1;   // Enable Interrupt on MR0
  T0MCR_bit.MR0R = 1;   // Enable reset on MR0
  T0MCR_bit.MR0S = 0;   // Disable stop on MR0
  // set timer 0 period
  T0PR = 25-1;
  T0MR0 = (TIMER0_IN_FREQ)/(25 * TIMER0_TICK_PER_SEC);
  // init timer 0 interrupt
  T0IR_bit.MR0INT = 1;  // clear pending interrupt
  T0TCR_bit.CE = 1;     // counting Enable
  //Enable NVIC TMR0 Interrupt
  //NVIC_IntEnable(NVIC_TIMER0);
}

void InitTimer1(void)
{
// Enable TIM0 clocks
  PCONP_bit.PCTIM1 = 1; // enable clock  
// Init Time1
  T1TCR_bit.CE = 0;     // counting  disable
  T1TCR_bit.CR = 1;     // set reset
  T1TCR_bit.CR = 0;     // release reset
  T1CTCR_bit.CTM = 0;   // Timer Mode: every rising PCLK edge
  T1MCR_bit.MR0I = 1;   // Enable Interrupt on MR0
  T1MCR_bit.MR0R = 1;   // Enable reset on MR0
  T1MCR_bit.MR0S = 1;   // Enable stop on MR0
  // set timer 1 period
  T1PR = 25-1;
  T1MR0 = (TIMER0_IN_FREQ)/(25 * TIMER1_TICK_PER_SEC);
  // init timer 0 interrupt
  T1IR_bit.MR0INT = 1;  // clear pending interrupt
  T1TCR_bit.CE = 1;     // counting Enable
  /*Enable NVIC TMR1 Interrupt*/
  //NVIC_IntEnable(NVIC_TIMER1);
}

void InitTimer2(void)
{
// Enable TIM0 clocks
  PCONP_bit.PCTIM2 = 1; // enable clock  
// Init Time1
  T2TCR_bit.CE = 0;     // counting  disable
  T2TCR_bit.CR = 1;     // set reset
  T2TCR_bit.CR = 0;     // release reset
  T2CTCR_bit.CTM = 0;   // Timer Mode: every rising PCLK edge
  T2MCR_bit.MR0I = 1;   // Enable Interrupt on MR0
  T2MCR_bit.MR0R = 1;   // Enable reset on MR0
  T2MCR_bit.MR0S = 1;   // Enable stop on MR0
  // set timer 1 period
  T2PR = 25-1;
  T2MR0 = (TIMER0_IN_FREQ)/(25 * TIMER2_TICK_PER_SEC);
  // init timer interrupt
  T2IR_bit.MR0INT = 1;  // clear pending interrupt
  T2TCR_bit.CE = 1;     // counting Enable
  /*Enable NVIC TMR2 Interrupt*/
  //NVIC_IntEnable(NVIC_TIMER2);
}

void InitTimer3(void)
{
// Enable TIM0 clocks
  PCONP_bit.PCTIM3 = 1; // enable clock  
// Init Time1
  T3TCR_bit.CE = 0;     // counting  disable
  T3TCR_bit.CR = 1;     // set reset
  T3TCR_bit.CR = 0;     // release reset
  T3CTCR_bit.CTM = 0;   // Timer Mode: every rising PCLK edge
  T3MCR_bit.MR0I = 1;   // Enable Interrupt on MR0
  T3MCR_bit.MR0R = 1;   // Enable reset on MR0
  T3MCR_bit.MR0S = 0;   // Disable stop on MR0
  // set timer 1 period
  T3PR = 25-1;
  T3MR0 = (TIMER0_IN_FREQ)/(25 * TIMER3_TICK_PER_SEC);
  // init timer interrupt
  T3IR_bit.MR0INT = 1;  // clear pending interrupt
  T3TCR_bit.CE = 1;     // counting Enable
  /*Enable NVIC TMR2 Interrupt*/
  //NVIC_IntEnable(NVIC_TIMER3);
}

void FlashCfg(void)
{
    FLASHCFG = (0x5UL<<12) | 0x3AUL;
}

/*************************************************************************
 * Function Name: InitClock
 * Parameters: void
 * Return: void
 *
  * Description: Initialize PLL and clocks' dividers. Hclk - 300MHz,
 *              Fcckl = 100MHz
 *
 *************************************************************************/
void InitClock(void)
{
  // 1. Init OSC
  SCS_bit.OSCRANGE = 0;
  SCS_bit.OSCEN = 1;
  // 2.  Wait for OSC ready
  while(!SCS_bit.OSCSTAT);
  // 3. Disconnect PLL
  PLL0CON_bit.PLLC = 0;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
  // 4. Disable PLL
  PLL0CON_bit.PLLE = 0;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
  // 5. Select source clock for PLL
  CLKSRCSEL_bit.CLKSRC = 1;   // Selects the main oscillator as a PLL clock source.
  PCLKSEL0 = PCLKSEL1  = 0;   // other peripherals 100/4 = 25MHz
  // 6. Set PLL settings 300 MHz
  PLL0CFG_bit.MSEL = 25-1;
  PLL0CFG_bit.NSEL = 2-1;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
  // 7. Enable PLL
  PLL0CON_bit.PLLE = 1;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
  // 8. Wait for the PLL to achieve lock
  while(!PLL0STAT_bit.PLOCK);
  // 9. Set clk divider settings
  CCLKCFG   = 3-1;            // 1/3 Fpll
  // 10. Connect the PLL
  PLL0CON_bit.PLLC = 1;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
}

void FlashInit(void)
{
  FlashCfg();
  InitClock();
  /*
  // Flash accelerator init
  FLASHCFG = (0x5UL<<12) | 0x3AUL;
  // Init clock
  InitClock();*/
#if FCCLK_FREQ < 20000000
  FLASHCFG = (0x0UL<<12) | 0x3AUL; 
#elif FCCLK_FREQ < 40000000
  FLASHCFG = (0x1UL<<12) | 0x3AUL;
#elif FCCLK_FREQ < 60000000
  FLASHCFG = (0x2UL<<12) | 0x3AUL;
#elif FCCLK_FREQ < 80000000
  FLASHCFG = (0x3UL<<12) | 0x3AUL;
#elif FCCLK_FREQ < 100000000
  FLASHCFG = (0x4UL<<12) | 0x3AUL;
#endif
}

/*************************************************************************
 * Function Name: GpioInit
 * Parameters: void
 * Return: void
 *
 * Description: Reset all GPIO pins to default: primary function
 *
 *************************************************************************/
void GpioInit(void)
{
  // Set to inputs
  FIO0DIR = \
  FIO1DIR = \
  FIO2DIR = \
  FIO3DIR = \
  FIO4DIR = 0;

  // clear mask registers
  FIO0MASK =\
  FIO1MASK =\
  FIO2MASK =\
  FIO3MASK =\
  FIO4MASK = 0;

  // Reset all GPIO pins to default primary function
  PINSEL0 =\
  PINSEL1 =\
  PINSEL2 =\
  PINSEL3 =\
  PINSEL4 =\
  PINSEL7 =\
  PINSEL8 =\
  PINSEL9 = 0;
}

void TargetResetInit(void)
{
  FlashInit();
  GpioInit();
}

//------------------------------------------------------------------------------

#define INIT_STATE 0 

unsigned long board_state;

void BoardInit(void)
{
  board_state = INIT_STATE;
  SpiWriteUInt32(board_state); 
}

void OutputSet(unsigned long x)
{
  board_state |= x;
  SpiWriteUInt32(board_state);
}

void OutputClr(unsigned long x)
{
  board_state &= ~x;
  SpiWriteUInt32(board_state);
}

void SpiWriteUInt32(unsigned long UInt32)
{
  SpiCsClr();
  for (char i = 0; i < 24; i++)
  {
    SpiSclkClr();
    if(UInt32 & (1 << (23 - i)))
    {
      SpiMosiSet();
    }
    else
    {
      SpiMosiClr();
    };
    SpiSclkSet();
  };
  SpiCsSet(); 
}

void LcdInitPio(void)
{
  FIO0DIR = SPI_MOSI | SPI_SCLK;
  FIO1DIR = A0 | E | D0 | D1 | D2 | D3 | D4 | D5 | D6 | D7 | SPI_CS;
}

void LcdData(char data)
{
  if (data & 0x01)
  {
    FIO1SET = D0;
  }
  else
  {
    FIO1CLR = D0;
  };

  if (data & 0x02)
  {
    FIO1SET = D1;
  }
  else
  {
    FIO1CLR = D1;
  };

  if (data & 0x04)
  {
    FIO1SET = D2;
  }
  else
  {
    FIO1CLR = D2;
  };
  
  if (data & 0x08)
  {
    FIO1SET = D3;
  }
  else
  {
    FIO1CLR = D3;
  };  
 
  if (data & 0x10)
  {
    FIO1SET = D4;
  }
  else
  {
    FIO1CLR = D4;
  };
  
  if (data & 0x20)
  {
    FIO1SET = D5;
  }
  else
  {
    FIO1CLR = D5;
  };  
  
  if (data & 0x40)
  {
    FIO1SET = D6;
  }
  else
  {
    FIO1CLR = D6;
  };    
  
  if (data & 0x80)
  {
    FIO1SET = D7;
  }
  else
  {
    FIO1CLR = D7;
  };
}

#pragma optimize = none
void Delay(int delay)
{
  for(; delay > 0; delay--);
}

char GetKbdBus(void)
{
  char result;
  unsigned long bus;
  FIO1DIR &= ~(D0 | D1 | D2 | D3 | D4 | D5 | D6);
  Delay(1000);
  bus = FIO1PIN;
  result  = ((bus & D0) ? 0x01 : 0);
  result |= ((bus & D1) ? 0x02 : 0);
  result |= ((bus & D2) ? 0x04 : 0);
  result |= ((bus & D3) ? 0x08 : 0);
  result |= ((bus & D4) ? 0x10 : 0);
  result |= ((bus & D5) ? 0x20 : 0);
  result |= ((bus & D6) ? 0x40 : 0);
  
  FIO1DIR |= (D0 | D1 | D2 | D3 | D4 | D5 | D6);
  return result;
}
//------------------------------------------------------------------------------
// Fram, temp sensor and system leds interface
//------------------------------------------------------------------------------
void SysSpiWriteByte(char byte);

void SysSpiInitPio(void)
{
  FIO0DIR |= SYS_MOSI | SYS_SCLK | TEMP_CS;
  FIO4DIR |= FRAM_CS;
  FIO2DIR |= REG_CS;
  SysFramCsSet();
  SysTempCsSet();
  SysRegCsSet();
}

void SysSpiWriteByte(char byte)
{
  for (char i = 0; i < 8; i++)
  {
   // Delay(5);
    SysSclkClr();
   // Delay(5);
    if(byte & (1 << (7 - i)))
      SysMosiSet();
    else
      SysMosiClr();
    SysSclkSet();
  }; 
 // Delay();
//  SpiCsSet();
 // Delay();
}

char SysSpiReadByte(void)
{
  char byte = 0;
  
  SysSclkSet();
  for (char i = 0; i < 8; i++)
  {
    SysSclkClr();
  //  Delay(10);
    SysSclkSet();
    byte |= GetSysMiso() << (7 - i);
  };
  return byte;
 // Delay();
//  SpiCsSet();
 // Delay();
}

void SysSpiWriteBuffer(unsigned int fram_addr, char *buffer, char size)
{
  char addr_lo, addr_hi;
  addr_lo = fram_addr % 256;
  addr_hi = fram_addr / 256; //addr * 4
  
  SysFramCsClr();
  SysSpiWriteByte(0x06); //WREN opcode
  SysFramCsSet();
  Delay(10);
  
  SysFramCsClr();
  SysSpiWriteByte(0x02); //WRITE opcode
  SysSpiWriteByte(addr_hi);
  SysSpiWriteByte(addr_lo);
  for(char i = 0; i < size; i++)
    SysSpiWriteByte(*(buffer + i));
  SysFramCsSet();
}

void SysSpiReadBuffer(unsigned int fram_addr, char *buffer, char size)
{
  char addr_lo, addr_hi;
  addr_lo = fram_addr % 256;
  addr_hi = fram_addr / 256; //addr * 4
    
  SysFramCsClr();
  SysSpiWriteByte(0x03); //READ opcode
  SysSpiWriteByte(addr_hi);
  SysSpiWriteByte(addr_lo);
  for(char i = 0; i < size; i++)
    *(buffer + i) = SysSpiReadByte();
  SysFramCsSet();

  Delay(10);        //!!!
}

void WriteIntToFram(unsigned int fram_add, signed int data)
{
  SysSpiWriteBuffer(fram_add << 2, (char*)&data, sizeof data);
}

void WriteFloatToFram(unsigned int fram_add, float data)
{
  SysSpiWriteBuffer(fram_add << 2, (char*)&data, sizeof data);
}

void ReadIntFromFram(unsigned int fram_add, signed int *data)
{
  SysSpiReadBuffer(fram_add << 2, (char*)data, sizeof data);
}

void ReadFloatFromFram(unsigned int fram_add, float *data)
{
  SysSpiReadBuffer(fram_add << 2, (char*)data, sizeof data);
}

float ReadTemp(void)
{
  char hi_byte, lo_byte;
  int code;
  SysTempCsClr();
  hi_byte = SysSpiReadByte();
  lo_byte = SysSpiReadByte();
  SysTempCsSet();
  code = hi_byte * 256 + lo_byte;
  return code / 32.0; //only for positive temperatures
}

void WriteSysReg(unsigned long data)
{
  SysRegCsClr();
  SysSpiWriteByte(data);
  SysSpiWriteByte(data >> 8);
  SysSpiWriteByte(data >> 16);
  SysSpiWriteByte(data >> 24);
  SysRegCsSet();
}

//------------------------------------------------------------------------------
// DAC interface
//------------------------------------------------------------------------------
  //DAC AD5620 - 12-bit (code 0-4095)
// Data format:
  // MSB | ...                              ...| LSB
  //----------------------------------------------------------------------------
  // 0   | 0  | D11 | D10 | ...   |D1 | D0 | X | X |
  //----------------------------------------------------------------------------
  
  //------------------------------
  //  Signal  | Pin | Port
  //------------------------------
  // DAC_SYNC | 76  | P0.9
  // DAC_SCLK | 77  | P0.8
  // DINT0    | 67  | P2.6
  // DINT1    | 68  | P2.5
  // DINT2    | 69  | P2.4
  // DINT3    | 70  | P2.3

void DacInitPio(void)
{
  FIO0DIR |= DAC_SYNC | DAC_SCLK;
  FIO2DIR |= DIN0 | DIN1 | DIN2 | DIN3;
  DacSyncSet();
  DacSclkSet();
}

void WriteToDac(unsigned int value[4])
{
  unsigned int code[4];
  
  for(char i = 0; i < 4; i++)
  {
    if (value[i] > 4095)
      value[i] = 4095;
    code[i] = value[i] << 2;
  };
  
  DacSclkSet();
  DacSyncClr();
  for(char i = 0; i < 16; i++)
  {
    DacSclkSet();
    Delay(10);
    for(char j = 0; j < 4; j++)
      if(code[j] & (1 << (15 - i)))
        DinSet(j);
      else
        DinClr(j);
      Delay(10);
    DacSclkClr();  
    Delay(10);
  };
  DacSyncSet();
}
//------------------------------------------------------------------------------
// ADC interface
//------------------------------------------------------------------------------

/*
#define SYS_ADC0_CLK  2
#define SYS_ADC1_CLK  3
#define SYS_ADC2_CLK  4
#define SYS_ADC3_CLK  5
#define SYS_ADC_MOSI  6
#define SYS_RES0      7

void SetSysBit(char bit_num);
void ClrSysBit(char bit_num);

const char clk_arr[4] = {SYS_ADC0_CLK, SYS_ADC1_CLK, SYS_ADC2_CLK,
  SYS_ADC3_CLK};

void AdcClkClr(char n)
{
    ClrSysBit(clk_arr[n]);
    UpdateSysBus();
}

void AdcClkSet(char n)
{
    SetSysBit(clk_arr[n]);
    UpdateSysBus();
}

void AdcMosiClr(void)
{
    ClrSysBit(SYS_ADC_MOSI);
    UpdateSysBus();
}

void AdcMosiSet(void)
{
    SetSysBit(SYS_ADC_MOSI);
    UpdateSysBus();
}
*/
const unsigned int clk_arr[4] = {ADC_CLK0, ADC_CLK1, ADC_CLK2, ADC_CLK3};

void AdcClkClr(char n)
{
  FIO0CLR = clk_arr[n];
}

void AdcClkSet(char n)
{
  FIO0SET = clk_arr[n];
}

void AdcMosiClr(void)
{
  FIO2CLR = ADC_MOSI;
}

void AdcMosiSet(void)
{
  FIO2SET = ADC_MOSI;
}

void AdcInitPio(void)
{
  FIO2DIR |= ADC_KEY | ADC_MOSI;
  FIO0DIR |= ADC_CLK0 | ADC_CLK1 | ADC_CLK2 | ADC_CLK3;
  for(char i = 0; i < 4; i++)
    AdcClkSet(i);
  AdcKeyClr();  
}

void WriteByteToAdc(char adc_num, char byte)
{ 
  for(char j = 0; j < 8; j++)
  {
    AdcClkClr(adc_num);
    if(byte & (1 << (7 - j))) 
        AdcMosiSet();
      else
        AdcMosiClr();
    AdcClkSet(adc_num);
  };
}

void ReadByteFromAdc(char adc_num, char byte)
{
  byte = 0;
  
  for(char j = 0; j < 8; j++)
  {
    AdcClkClr(adc_num);
 //   Delay(10);
 //   for(char i = 0; i < 4; i++)
    byte |= (GetAdcMiso(adc_num) << (7 - j));
  //  Delay(10);
    AdcClkSet(adc_num);
  //  Delay(10);    
  };
}
/*
void WriteByteToAdc(char bytes[4])
{
  for(char j = 0; j < 8; j++)
  {
    AdcClkClr();
    for(char i = 0; i < 4; i++)
      if(bytes[i] & (1 << (7 - j))) 
        AdcMosiSet(i);
      else
        AdcMosiClr(i);
    AdcClkSet();
  };
}

void WriteByteToAllAdc(char byte)
{
  char bytes[4];
  bytes[0] = bytes[1] = bytes[2] = bytes[3] = byte;
  WriteByteToAdc(bytes);
}

void ReadByteFromAdc(char bytes[4])
{
  for(char i = 0; i < 4; i++)
      bytes[i] = 0;
  
  for(char j = 0; j < 8; j++)
  {
    AdcClkClr();
    Delay(10);
    for(char i = 0; i < 4; i++)
      bytes[i] |= (GetAdcMiso(i) << (7 - j));
    Delay(10);
    AdcClkSet();
    Delay(10);    
  };
}
*/
char RdyIsLow(char adc_num)
{
  if (GetAdcMiso(adc_num))
      return 0;
  /*
  for(char i = 0; i < 4; i++)        
    if (GetAdcMiso(i))
      return 0;
  */
  return 1;
}

unsigned int GetAdcValue(char adc_num, char bits)
{
  unsigned int result = 0;
  
  for(char j = 0; j < bits; j++)
  {
    AdcClkClr(adc_num);
    result |= (GetAdcMiso(adc_num) << (bits - 1 - j));
    AdcClkSet(adc_num);
  };
  
  if(bits == 24) result >>= 8;
  return result;
}
/*
unsigned int GetAdcValue(char i)
{
  unsigned int result = 0;
  
  for(char j = 0; j < BITS; j++)
  {
    AdcClkClr();
    result |= (GetAdcMiso(i) << (BITS - 1 - j));
    AdcClkSet();
  };
  return result;
}

void GetAdcValues(unsigned int values[4])
{
  for(char i = 0; i < 4; i++)
    values[i] = 0;
  
  for(char j = 0; j < BITS; j++)
  {
    AdcClkClr();
    for(char i = 0; i < 4; i++)
      values[i] |= (GetAdcMiso(i) << (BITS - 1 - j));
    AdcClkSet();
  };  
}*/
//------------------------------------------------------------------------------
// PWM Control
//------------------------------------------------------------------------------
void PwmInitPio(void)
{
  FIO3DIR |= PWM0_OUT | PWM1_OUT;
  Pwm0Set();
  Pwm1Set();
}
//------------------------------------------------------------------------------
// Debug Control
//------------------------------------------------------------------------------
#define DEBUG_0 (1 << 12)

void initDebugPin(void)
{
  FIO2DIR |= DEBUG_0;
}

void setDebugPin(void)
{
  FIO2SET |= DEBUG_0;
}

void clrDebugPin(void)
{
  FIO2CLR |= DEBUG_0;
}
//------------------------------------------------------------------------------
//  WDT
//------------------------------------------------------------------------------
void InitWdt(void)
{
  #define IRCFreq 4000000
  #define WDFreq 10
  WDTC = IRCFreq / (4 * WDFreq);
  WDCLKSEL_bit.WDSEL = 0x10;
  WDMOD_bit.WDEN = 1;
  WDMOD_bit.WDRESET = 1;
  ResetWdt();
}

void ResetWdt(void)
{
  __disable_interrupt();
  WDFEED =  0xAA;
  WDFEED =  0x55;
  __enable_interrupt();
}
//------------------------------------------------------------------------------
// End of file
//------------------------------------------------------------------------------
