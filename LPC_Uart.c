/*************************************************************************
 * UART functions
 **************************************************************************/

#include "LPC_Uart.h"
#include <nxp/iolpc1768.h>
#include "irq.h"

void (*uart0_rx_handler)(char *buf, int length);
void (*uart1_rx_handler)(char *buf, int length);   

char uart0_rx_buff[RXBUFSIZE];
volatile int uart0_rx_count = 0;
volatile char uart0_rx_flag = 0;   //not used
volatile int uart0_rx_error_flag = 0;

char uart0_tx_buff[TXBUFSIZE];
volatile int uart0_tx_count = 0;  //tx busy flag
volatile int uart0_tx_len;
volatile char uart0_tx_flag = 0;

char uart1_rx_buff[RXBUFSIZE];
volatile int uart1_rx_count = 0;
volatile char uart1_rx_flag = 0;    //not used
volatile int uart1_rx_error_flag = 0;

char uart1_tx_buff[TXBUFSIZE];
volatile int uart1_tx_count = 0;    //tx busy used
volatile int uart1_tx_len;
volatile char uart1_tx_flag = 0;

/*
typedef struct {
	unsigned long BaudRate;	        // Baud Rate
	
	LPC_Uart_WordLenth_t WordLenth;	// Frame format
	BOOL TwoStopBitsSelect;
	BOOL ParityEnable;
	LPC_Uart_ParitySelect_t ParitySelect;
	BOOL BreakEnable;

	BOOL FIFOEnable;
	int FIFORxTriggerLevel;

	unsigned long InterruptEnable ;	// Interrupt Type: RBR, THRE, RLS

	LPC_Uart_MethodMode_t MethodMode;
	LPC_Uart_Buffer_t  UartBuffer;
	
} LPC_Uart_Config_t;
*/

// Define globe variable
LPC_Uart_Config_t Uart0Config = {BD19200, WordLength8, false, false,
ParitySelOdd};//, false, true, FIFORXLEV2, IER_RBR | IER_THRE | IER_RLS};
							
LPC_Uart_Config_t Uart1Config = {BD19200, WordLength8, false, false,
ParitySelOdd};//, false, true, FIFORXLEV2, IER_RBR | IER_THRE | IER_RLS};

//---------------------------------------------
void Uart0ResetRxBuf(void)
{
  uart0_rx_count = 0;
  uart0_rx_flag = 0;
}

void Uart0ResetTxBuf(void)
{
  uart0_tx_count = 0;
  uart0_tx_flag = 0;
}

char* GetUart0TxBuffer(void)
{
  return uart0_tx_buff;
}

#pragma inline
int Uart0WriteRxBuf(char *ch)
{
  if(uart0_rx_count == RXBUFSIZE)
  {
    Uart0ResetRxBuf();
  };
  
  while(U0LSR_bit.DR)
    uart0_rx_buff[uart0_rx_count++] = *ch;
  return 1;
}

void FillUart0TransmitBuffer(void)
{
  for(char i = 0; i < FIFODEEP; i++)
  {
    if(uart0_tx_count == uart0_tx_len)
      break;
    U0THR = uart0_tx_buff[uart0_tx_count];
    uart0_tx_count++;
  };
  
  U0IER_bit.THREIE = true;
  
  if(uart0_tx_count == uart0_tx_len)
    uart0_tx_flag = 0;
}

void SetUart0RxHandler(void (*_rx_handler)(char *buf, int length))
{
  uart0_rx_handler = _rx_handler;
}

unsigned int SYS_GetFpclk(void)
{
  return 25000000;
}

char Uart0Init(void)
{
  unsigned long Divisor, Frame, FIFO;
  
  if ((Uart0Config.BaudRate == 0) || (Uart0Config.BaudRate > BD115200))
    return 0;
  
  // baut rate
  Divisor = (SYS_GetFpclk() >> 4) / Uart0Config.BaudRate;
  
  // frame format
  Frame = Uart0Config.WordLenth;
  if ( Uart0Config.TwoStopBitsSelect )
    Frame |= ( 1 << LCR_STOPBITSEL_BIT );
  if ( Uart0Config.ParityEnable )
  {
    Frame |= ( 1 << LCR_PARITYENBALE_BIT );
    Frame |= ( Uart0Config.ParitySelect<<LCR_PARITYSEL_BIT );
  }
  
  FIFO = ((FIFORXLEV2 & 0x3)<<6) | 0x07;
  
  // Set baut rate
  U0LCR_bit.DLAB = true;	// DLAB = 1
  U0DLM = Divisor >> 8;
  U0DLL = Divisor;
  
  // Set frame format
  U0LCR = Frame;	        // DLAB = 0
  
  // Set FIFO
  U0FCR = FIFO;
  
  // Set Interrupt Enable Register
  U0IER = IER_RBR | IER_THRE | IER_RLS;
  NVIC_IntEnable(NVIC_UART0);
  NVIC_IntPri(NVIC_UART0, HIGHEST_PRIORITY);
  
  // Enable TxD0 and RxD0, bit 0~3=0101
  PINSEL0_bit.P0_2 = 0x1;
  PINSEL0_bit.P0_3 = 0x1;
  
  return 1;
};

int Uart0Transmit(int length)
{
  if(uart0_tx_flag) 
    return 0;
  
  uart0_tx_count = 0;
  uart0_tx_len = length;
  uart0_tx_flag = 1;

  FillUart0TransmitBuffer(); //start transmit
  U0IER_bit.THREIE = true;
  return 1;
}

/*************************************************************************
 * Function Name: UART0_ISR
 * Parameters: void
 * Return: void
 *
 * Description: Uart0 interrupt subroutine
 *
 *************************************************************************/
void UART0_IRQHandler (void)
{
  switch((U0IIR >> 1) & 0x7) 
  {
  case IIR_THRE:  // continue sending data
    FillUart0TransmitBuffer();
    break;
  case IIR_RSL:	// error manage
    uart0_rx_error_flag = U0LSR & 0x8E;
    if(uart0_rx_error_flag)
      Uart0ResetRxBuf();
    break;
  case IIR_RDA:	// receive data
    if(uart0_rx_count == RXBUFSIZE)
      Uart0ResetRxBuf();
    uart0_rx_buff[uart0_rx_count++] = U0RBR;
    break;
  case IIR_CTI:	// time out   
    Uart0WriteRxBuf((char*)&U0RBR);
    (*uart0_rx_handler)(uart0_rx_buff, uart0_rx_count);
    Uart0ResetRxBuf();
    break;
  }
  NVIC_ClrPend(NVIC_UART0);
}

//------------------------------------------------------------------------------
//     UART 1 functions
//------------------------------------------------------------------------------
void Uart1ResetRxBuf(void)
{
  uart1_rx_count = 0;
  uart1_rx_flag = 0;
}

void Uart1ResetTxBuf(void)
{
  uart1_tx_count = 0;
  uart1_tx_flag = 0;
}

char* GetUart1TxBuffer(void)
{
  return uart1_tx_buff;
}

#pragma inline
int Uart1WriteRxBuf(char *ch)
{
  if(uart1_rx_count == RXBUFSIZE)
  {
    Uart1ResetRxBuf();
  };
  
  while(U1LSR_bit.DR)
    uart1_rx_buff[uart1_rx_count++] = *ch;
  return 1;
}

void FillUart1TransmitBuffer(void)
{
  for(char i = 0; i < FIFODEEP; i++)
  {
    if(uart1_tx_count == uart1_tx_len)
      break;
    U1THR = uart1_tx_buff[uart1_tx_count];
    uart1_tx_count++;
  };
  
  U1IER_bit.THREIE = false;
  
  if(uart1_tx_count == uart1_tx_len)
    uart1_tx_flag = 0;
}

void SetUart1RxHandler(void (*_rx_handler)(char *buf, int length)) 
{
  uart1_rx_handler = _rx_handler;
}

char Uart1Init(void)
{
  unsigned long Divisor, Frame, FIFO;
  
  if ((Uart1Config.BaudRate == 0) || (Uart1Config.BaudRate > BD115200))
    return 0;
  
  // baut rate
  Divisor = (SYS_GetFpclk() >> 4) / Uart1Config.BaudRate;
  
  // frame format
  Frame = Uart1Config.WordLenth;
  if ( Uart1Config.TwoStopBitsSelect )
    Frame |= ( 1 << LCR_STOPBITSEL_BIT );
  if ( Uart1Config.ParityEnable )
  {
    Frame |= ( 1 << LCR_PARITYENBALE_BIT );
    Frame |= ( Uart1Config.ParitySelect << LCR_PARITYSEL_BIT );
  }
  
  FIFO = ((FIFORXLEV2 & 0x3) << 6) | 0x07;
  
  // Set baut rate
  U1LCR_bit.DLAB = true;	// DLAB = 1
  U1DLM = Divisor >> 8;
  U1DLL = Divisor;
  
  // Set frame format
  U1LCR = Frame;	        // DLAB = 0
  
  // Set FIFO
  U1FCR = FIFO;
  
  U1RS485CTRL = (1UL << 4) | (1UL << 5); //DCTRL | OINV
  // Set Interrupt Enable Register
  U1IER = IER_RBR | IER_THRE | IER_RLS;
  NVIC_IntEnable(NVIC_UART1);
  NVIC_IntPri(NVIC_UART1, HIGHEST_PRIORITY);
  
  // Enable TxD1, RxD1 and RTS1
  PINSEL4_bit.P2_0 = 0x02;
  PINSEL4_bit.P2_1 = 0x02;
  PINSEL4_bit.P2_7 = 0x02;
  
  return 1;
};

int Uart1Transmit(int length)
{
  if(uart1_tx_flag) 
    return 0;
  
  uart1_tx_count = 0;
  uart1_tx_len = length;
  uart1_tx_flag = 1;
  
  FillUart1TransmitBuffer(); //start transmit
  U1IER_bit.THREIE = true;
  return 1;
}

/*************************************************************************
 * Function Name: UART1_ISR
 * Parameters: void
 * Return: void
 *
 * Description: Uart1 interrupt subroutine
 *
 *************************************************************************/
void UART1_IRQHandler(void)
{
  switch((U1IIR >> 1) & 0x7) 
  {
  case IIR_THRE:  // continue sending data
    FillUart1TransmitBuffer();
    break;
  case IIR_RSL:	// error manage
    uart1_rx_error_flag = U1LSR & 0x8E;
    if(uart1_rx_error_flag)
      Uart1ResetRxBuf();
    break;
  case IIR_RDA:	// receive data
    uart1_rx_error_flag = U1LSR & 0x8E;
    if(uart1_rx_error_flag)
      Uart1ResetRxBuf();
    break;
  case IIR_CTI:	// time out   
    Uart1WriteRxBuf((char*)&U1RBR);
    (*uart1_rx_handler)(uart1_rx_buff, uart0_rx_count);
    Uart1ResetRxBuf();
    break;
  }
  NVIC_ClrPend(NVIC_UART1);
}
