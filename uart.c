/*****************************************************************************
 *   uart.c:  UART API file for NXP LPC23xx/24xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.07.12  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include <nxp/iolpc1768.h>
#include "type.h"
#include "target.h"
#include "irq.h"
#include "uart.h"

#include <intrinsics.h>

volatile DWORD UART0Status;
volatile BYTE UART0TxEmpty = 1;
volatile BYTE UART0Buffer[BUFSIZE];
volatile DWORD UART0Count = 0;

volatile DWORD UART1Status;
volatile BYTE UART1TxEmpty = 1;
volatile BYTE UART1Buffer[BUFSIZE];
volatile DWORD UART1Count = 0;

/*****************************************************************************
** Function name:   UART0_IRQHandler
**
** Descriptions:    UART0 interrupt handler
**
** parameters:      None
** Returned value:    None
**
*****************************************************************************/
void UART0_IRQHandler (void)
{
BYTE IIRValue, LSRValue;
volatile BYTE Dummy;

  __enable_interrupt();   /* handles nested interrupt */

  IIRValue = U0IIR;
  IIRValue >>= 1;     /* skip pending bit in IIR */
  IIRValue &= 0x07;     /* check bit 1~3, interrupt identification */
  if ( IIRValue == IIR_RLS )    /* Receive Line Status */
  {
    LSRValue = U0LSR;
    /* Receive Line Status */
    if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
    {
      /* There are errors or break interrupt */
      /* Read LSR will clear the interrupt */
      UART0Status = LSRValue;
      Dummy = U0RBR;    /* Dummy read on RX to clear interrupt, then bail out */
      NVIC_ClrPend(NVIC_UART0); /* Acknowledge Interrupt */
      return;
    }
    if ( LSRValue & LSR_RDR ) /* Receive Data Ready */
    {
      /* If no error on RLS, normal ready, save into the data buffer. */
      /* Note: read RBR will clear the interrupt */
      UART0Buffer[UART0Count] = U0RBR;
      UART0Count++;
      if ( UART0Count == BUFSIZE )
      {
        UART0Count = 0; /* buffer overflow */
      }
    }
  }
  else if ( IIRValue == IIR_RDA ) /* Receive Data Available */
  {
    /* Receive Data Available */
    UART0Buffer[UART0Count] = U0RBR;
    UART0Count++;
    if ( UART0Count == BUFSIZE )
    {
      UART0Count = 0; /* buffer overflow */
    }
  }
  else if ( IIRValue == IIR_CTI ) /* Character timeout indicator */
  {
    /* Character Time-out indicator */
    UART0Status |= 0x100; /* Bit 9 as the CTI error */
  }
  else if ( IIRValue == IIR_THRE )  /* THRE, transmit holding register empty */
  {
    /* THRE interrupt */
    LSRValue = U0LSR; /* Check status in the LSR to see if valid data in U0THR or not */
    if ( LSRValue & LSR_THRE )
    {
      UART0TxEmpty = 1;
    }
    else
    {
      UART0TxEmpty = 0;
    }
  }

  NVIC_ClrPend(NVIC_UART0); /* Acknowledge Interrupt */
  return;
}

/*****************************************************************************
** Function name:   UART0_IRQHandler
**
** Descriptions:    UART0 interrupt handler
**
** parameters:      None
** Returned value:    None
**
*****************************************************************************/
void UART1_IRQHandler (void)
{
BYTE IIRValue, LSRValue;
volatile BYTE Dummy;

  __enable_interrupt();   /* handles nested interrupt */

  IIRValue = U1IIR;
  IIRValue >>= 1;     /* skip pending bit in IIR */
  IIRValue &= 0x07;     /* check bit 1~3, interrupt identification */
  if ( IIRValue == IIR_RLS )    /* Receive Line Status */
  {
    LSRValue = U1LSR;
    /* Receive Line Status */
    if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
    {
      /* There are errors or break interrupt */
      /* Read LSR will clear the interrupt */
      UART1Status = LSRValue;
      Dummy = U1RBR;    /* Dummy read on RX to clear interrupt, then bail out */
      NVIC_ClrPend(NVIC_UART1); /* Acknowledge Interrupt */
      return;
    }
    if ( LSRValue & LSR_RDR ) /* Receive Data Ready */
    {
      /* If no error on RLS, normal ready, save into the data buffer. */
      /* Note: read RBR will clear the interrupt */
      UART1Buffer[UART1Count] = U1RBR;
      UART1Count++;
      if ( UART1Count == BUFSIZE )
      {
        UART1Count = 0; /* buffer overflow */
      }
    }
  }
  else if ( IIRValue == IIR_RDA ) /* Receive Data Available */
  {
    /* Receive Data Available */
    UART1Buffer[UART1Count] = U1RBR;
    UART1Count++;
    if ( UART1Count == BUFSIZE )
    {
      UART1Count = 0; /* buffer overflow */
    }
  }
  else if ( IIRValue == IIR_CTI ) /* Character timeout indicator */
  {
    /* Character Time-out indicator */
    UART1Status |= 0x100; /* Bit 9 as the CTI error */
  }
  else if ( IIRValue == IIR_THRE )  /* THRE, transmit holding register empty */
  {
    /* THRE interrupt */
    LSRValue = U1LSR; /* Check status in the LSR to see if valid data in U0THR or not */
    if ( LSRValue & LSR_THRE )
    {
      UART1TxEmpty = 1;
    }
    else
    {
      UART1TxEmpty = 0;
    }
  }

  NVIC_ClrPend(NVIC_UART1); /* Acknowledge Interrupt */
  return;
}

/*****************************************************************************
** Function name:   UARTInit
**
** Descriptions:    Initialize UART0 port, setup pin select,
**            clock, parity, stop bits, FIFO, etc.
**
** parameters:      UART baudrate
** Returned value:    true or false, return false only if the
**            interrupt handler can't be installed to the
**            VIC table
**
*****************************************************************************/
DWORD UART0Init( DWORD baudrate )
{
DWORD Fdiv;
const long Fpclk = 25000000; // 100 Mhz / 4

PINSEL0 = 0x00000050;       /* RxD0 and TxD0 */

  U0LCR = 0x83;   /* 8 bits, no Parity, 1 Stop bit */
  Fdiv = ( Fpclk / 16 ) / baudrate ;  /*baud rate */
  U0DLM = Fdiv / 256;
  U0DLL = Fdiv % 256;
  U0LCR = 0x03;   /* DLAB = 0 */
  U0FCR = 0x07;   /* Enable and reset TX and RX FIFO. */

  NVIC_IntEnable(NVIC_UART0);
  NVIC_IntPri(NVIC_UART0, HIGHEST_PRIORITY);

  U0IER = IER_RBR | IER_THRE | IER_RLS; /* Enable UART0 interrupt */
  return (TRUE);
}

/*****************************************************************************
** Function name:   UARTInit
**
** Descriptions:    Initialize UART0 port, setup pin select,
**            clock, parity, stop bits, FIFO, etc.
**
** parameters:      UART baudrate
** Returned value:    true or false, return false only if the
**            interrupt handler can't be installed to the
**            VIC table
**
*****************************************************************************/
DWORD UART1Init( DWORD baudrate )
{
DWORD Fdiv;
const long Fpclk = 25000000; // 100 Mhz / 4

  PINSEL4 |= 0x0AUL | (0x02UL << 14);       /* RxD0 and TxD0 */

  U1LCR = 0x83;   /* 8 bits, no Parity, 1 Stop bit */
  Fdiv = ( Fpclk / 16 ) / baudrate ;  /*baud rate */
  U1DLM = Fdiv / 256;
  U1DLL = Fdiv % 256;
  U1LCR = 0x03;   /* DLAB = 0 */
  U1FCR = 0x07;   /* Enable and reset TX and RX FIFO. */
  U1RS485CTRL = (1UL << 4) | (1UL << 5); //DCTRL | OINV

  NVIC_IntEnable(NVIC_UART1);
  NVIC_IntPri(NVIC_UART1, HIGHEST_PRIORITY);

  U1IER = IER_RBR | IER_THRE | IER_RLS; /* Enable UART0 interrupt */
  return (TRUE);
}

/*****************************************************************************
** Function name:   UARTSend
**
** Descriptions:    Send a block of data to the UART 0 port based
**        on the data length
**
** parameters:      buffer pointer, and data length
** Returned value:    None
**
*****************************************************************************/
void UART0Send(BYTE *BufferPtr, DWORD Length )                                      // ���������� ��� ������ � ������������
{
  while ( Length != 0 )
  {
    /* THRE status, contain valid data */
    while ( !(UART0TxEmpty & 0x01) );
    U0THR = *BufferPtr;
    UART0TxEmpty = 0; /* not empty in the THR until it shifts out */
    BufferPtr++;
    Length--;
  }
  return;
}

/*****************************************************************************
** Function name:   UARTSend
**
** Descriptions:    Send a block of data to the UART 0 port based
**        on the data length
**
** parameters:      buffer pointer, and data length
** Returned value:    None
**
*****************************************************************************/
void UART1Send(BYTE *BufferPtr, DWORD Length )                                      // ���������� ��� ������ � ������������
{
  while ( Length != 0 )
  {
    /* THRE status, contain valid data */
    while ( !(UART1TxEmpty & 0x01) );
    U1THR = *BufferPtr;
    UART1TxEmpty = 0; /* not empty in the THR until it shifts out */
    BufferPtr++;
    Length--;
  }
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
