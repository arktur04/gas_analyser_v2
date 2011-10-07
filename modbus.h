//------------------------------------------------------------------------------
// MODBUS protocol
//------------------------------------------------------------------------------
#ifndef MODBUS_h
#define MODBUS_h
#include "LPC_Uart.h"

#define DATABUFSIZE 512

typedef struct WRITEMULTIPLEDATA_{
  unsigned short start_addr;
  unsigned short num;
  char data_len;
  unsigned short data[DATABUFSIZE];
} WRITEMULTIPLEDATA;

void DataUnlock(void);

void ModbusRxHandler0(char *buf, int len);
void ModbusRxHandler1(char *buf, int len);

char ReadMultipleHoldingsAnswer(unsigned short start_addr, unsigned short num,
                                unsigned short *data, char uartNum);

char WriteSingleRegisterAnswer(unsigned short start_addr, unsigned short value, 
                               char uartNum);

char WriteMultipleHoldingsAnswer(unsigned short start_addr, unsigned short num, 
                                 char uartNum);

void WritePrintScreenAnswer(char *data, char uartNum);

#endif
