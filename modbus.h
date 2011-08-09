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

void ModbusRxHandler(char *buf, int len);

char ReadMultipleHoldingsAnswer(unsigned short start_addr, unsigned short num,
                                unsigned short *data);

char WriteSingleRegisterAnswer(unsigned short start_addr, unsigned short value);

char WriteMultipleHoldingsAnswer(unsigned short start_addr, unsigned short num);

void WritePrintScreenAnswer(char *data);

#endif
