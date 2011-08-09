/*************************************************************************
*  UART functions
*  32bit.me (c)2010  
**************************************************************************/

#ifndef __LPC_UART_H
#define __LPC_UART_H

#include "type.h"

#define FIFODEEP    16

#define RXBUFSIZE  1024
#define TXBUFSIZE  1024

#define BD115200    115200
#define BD38400     38400
#define BD19200     19200
#define BD9600      9600

/* Uart line control register bit descriptions */
#define LCR_WORDLENTH_BIT         0
#define LCR_STOPBITSEL_BIT        2
#define LCR_PARITYENBALE_BIT      3
#define LCR_PARITYSEL_BIT         4
#define LCR_BREAKCONTROL_BIT      6
#define LCR_DLAB_BIT              7

// Uart Interrupt Identification 
#define IIR_RSL                   0x3
#define IIR_RDA                   0x2
#define IIR_CTI                   0x6
#define IIR_THRE                  0x1

// Uart Interrupt Enable Type
#define IER_RBR                   0x1
#define IER_THRE                  0x2
#define IER_RLS                   0x4

/* Uart Receiver Errors*/
#define RC_FIFO_OVERRUN_ERR       0x1
#define RC_OVERRUN_ERR            0x2
#define RC_PARITY_ERR             0x4
#define RC_FRAMING_ERR            0x8
#define RC_BREAK_IND              0x10

typedef enum {
  UART0 = 0,
  UART1
} LPC_UartChanel_t;

// Word Lenth type
typedef enum {
  WordLength5 = 0,
  WordLength6,
  WordLength7,
  WordLength8
} LPC_Uart_WordLenth_t;

// Parity Select type
typedef enum {
  ParitySelOdd = 0,
  ParitySelEven,
  ParitySelStickHigh,
  ParitySelEvenLow
} LPC_Uart_ParitySelect_t;

// FIFO Rx Trigger Level type
typedef enum {
  FIFORXLEV0 = 0,	// 0x1
  FIFORXLEV1,		// 0x4
  FIFORXLEV2,		// 0x8
  FIFORXLEV3		// 0xe
} LPC_Uart_FIFORxTriggerLevel_t;

typedef struct {
  unsigned long BaudRate;	        // Baud Rate
  
  LPC_Uart_WordLenth_t WordLenth;	// Frame format
  BOOL TwoStopBitsSelect;
  BOOL ParityEnable;
  LPC_Uart_ParitySelect_t ParitySelect;
} LPC_Uart_Config_t;

void SetUart0RxHandler(void (*_rx_handler)(char *buf, int length));

char Uart0Init(void);

int Uart0Transmit(int length);

char* GetUart0TxBuffer(void);

void SetUart1RxHandler(void (*_rx_handler)(char *buf, int length));

char Uart1Init(void);

int Uart1Transmit(int lenght);

char* GetUart1TxBuffer(void);

#endif //__LPC_UART_H
