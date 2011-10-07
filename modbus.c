//------------------------------------------------------------------------------
// MODBUS
//------------------------------------------------------------------------------
#include "modbus.h"
#include "LPC_Uart.h"
#include "messages.h"

volatile WRITEMULTIPLEDATA write_multiple_data;
volatile char data_busy = 0;

// Таблица значений старшего байта CRC
const unsigned char auchCRCHi[] = {
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
} ;

// Таблица значений младшего байта CRC
const unsigned char auchCRCLo[] = {
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2,
0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04,
0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8,
0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6,
0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10,
0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE,
0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA,
0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C,
0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0,
0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62,
0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE,
0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C,
0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76,
0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54,
0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98,
0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A,
0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86,
0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40
} ;
//------------------------------------------------------------------------------
// Функция возвращает значение CRC для сообщения puchMsg.
// Параметры:
//   *puchMsg - указатель на сообщение
//   usDataLen - длина сообщения
//------------------------------------------------------------------------------
unsigned short CRC16(unsigned char *puchMsg, unsigned short usDataLen)
//  unsigned char *puchMsg ; // message to calculate CRC upon
//  unsigned short usDataLen ; // quantity of bytes in message
{
  unsigned char uchCRCHi = 0xFF ; // high byte of CRC initialized
  unsigned char uchCRCLo = 0xFF ; // low byte of CRC initialized
  unsigned uIndex ; // will index into CRC lookup table
  while (usDataLen--) // pass through message buffer
  {
    uIndex = uchCRCHi ^ *puchMsg++ ; // calculate the CRC
    uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ;
    uchCRCLo = auchCRCLo[uIndex] ;
  }
  return (uchCRCHi << 8 | uchCRCLo) ;
}

WRITEMULTIPLEDATA GetWriteMultipleData(void)
{
  return write_multiple_data;
}

void DataUnlock(void)
{
  data_busy = 0;
}

void DataLock(void)
{
  data_busy = 1;
}

char GetDeviceAddr(void)
{
  return 1;                                                                           //debug
}

void uartTransmit(int length, char uartNum)
{
  switch(uartNum)
  {
  case 0:   
    Uart0Transmit(length);
    SendMessage(MSG_UART0_TX);
    break;
  case 1:   
    Uart1Transmit(length);
    SendMessage(MSG_UART1_TX);
    break;
  };
}

char ReadMultipleHoldingsAnswer(unsigned short start_addr, unsigned short num,
                                unsigned short *data, char uartNum)
{
  int crc;
  int i;

  char* tx_buffer;
  
  switch(uartNum)
  {
  case 0:   
    tx_buffer = GetUart0TxBuffer();
    break;
  case 1:   
    tx_buffer = GetUart1TxBuffer();
    break;
  };
  //---------------------------------
  tx_buffer[0] = GetDeviceAddr();
  tx_buffer[1] = 0x03;  
  tx_buffer[2] = num * 2;
 
  for(i = 0; i < num; i++)
  {
    tx_buffer[i * 2 + 3] = data[i] >> 8;
    tx_buffer[i * 2 + 4] = data[i];
  };
  
  crc = CRC16((unsigned char*)tx_buffer, num * 2 + 3);
  
  tx_buffer[num * 2 + 3] = crc >> 8;
  tx_buffer[num * 2 + 4] = crc;

  uartTransmit(num * 2 + 5, uartNum);

  return 1;
}

char WriteSingleRegisterAnswer(unsigned short start_addr, unsigned short value,
                               char uartNum)
{
  int crc;
  char* tx_buffer;
  
  switch(uartNum)
  {
  case 0:   
    tx_buffer = GetUart0TxBuffer();
    break;
  case 1:   
    tx_buffer = GetUart1TxBuffer();
    break;
  };
  //---------------------------------
  tx_buffer[0] = GetDeviceAddr();
  tx_buffer[1] = 0x06;  
  tx_buffer[2] = start_addr >> 8;
  tx_buffer[3] = start_addr;
  tx_buffer[4] = value >> 8;
  tx_buffer[5] = value;
    
  crc = CRC16((unsigned char*)tx_buffer, 6);
  
  tx_buffer[6] = crc >> 8;
  tx_buffer[7] = crc;

  uartTransmit(8, uartNum);
  
  return 1;
}

char WriteMultipleHoldingsAnswer(unsigned short start_addr, unsigned short num, char uartNum)
{
  int crc;
  char* tx_buffer;
  
  switch(uartNum)
  {
  case 0:   
    tx_buffer = GetUart0TxBuffer();
    break;
  case 1:   
    tx_buffer = GetUart1TxBuffer();
    break;
  };
  //---------------------------------
  tx_buffer[0] = GetDeviceAddr();
  tx_buffer[1] = 0x10;  
  tx_buffer[2] = start_addr >> 8;
  tx_buffer[3] = start_addr;
  tx_buffer[4] = num >> 8;
  tx_buffer[5] = num;
    
  crc = CRC16((unsigned char*)tx_buffer, 6);
  
  tx_buffer[6] = crc >> 8;
  tx_buffer[7] = crc;
  
  uartTransmit(8, uartNum);
  return 1;
}

char ReadMultipleHoldings(unsigned short start_addr, unsigned short num, char uartNum)
{
  switch(uartNum)
  {
  case 0:
    SendParamMessage(MSG_UART0READHOLDINGS, (start_addr << 16) | num);
    break;
  case 1:
    SendParamMessage(MSG_UART0READHOLDINGS, (start_addr << 16) | num);
    break;
  };  
  return 1;
}

char WriteSingleRegister(unsigned short start_addr, unsigned short value, char uartNum)
{
  switch(uartNum)
  {
  case 0:
    SendParamMessage(MSG_UART0WRITESINGLEHOLDING, (start_addr << 16) | value);
    break;
  case 1:
    SendParamMessage(MSG_UART1WRITESINGLEHOLDING, (start_addr << 16) | value);
    break;
  };
  return 1;
}

char WriteMultipleHoldings(unsigned short start_addr, unsigned short num,
                           char data_len, char* data, char uartNum)
{
  if(data_busy) 
    return 0; // denial of service
  
  DataLock();
  
  write_multiple_data.start_addr = start_addr;
  write_multiple_data.num = num;
  write_multiple_data.data_len = data_len;

  for(int i = 0; i < data_len; i += 2)
    write_multiple_data.data[i / 2] = (data[i] << 8) | data[i + 1] ;
  
  switch(uartNum)
  {
  case 0:
    SendParamMessage(MSG_UART0WRITEMULTIPLEHOLDINGS,
                     (unsigned long)&write_multiple_data);
  case 1:
    SendParamMessage(MSG_UART1WRITEMULTIPLEHOLDINGS,
                     (unsigned long)&write_multiple_data);   
  };
  return 1;
}

char PrintScreen(char uartNum)
{
  switch(uartNum)
  {
  case 0:
    SendMessage(MSG_UART0PRINTSCREEN);
    break;
  case 1:
    SendMessage(MSG_UART1PRINTSCREEN);
    break;
  };
  return 1;
}

void WritePrintScreenAnswer(char *data, char uartNum)
{
  char* tx_buffer;
  
  switch(uartNum)
  {
  case 0:
    tx_buffer = GetUart0TxBuffer();
    break;
  case 1:
    tx_buffer = GetUart1TxBuffer();
    break;
  };
  
  for(int i = 0; i< 1024; i++)
  {
    tx_buffer[i] = data[i];
  };
  uartTransmit(1024, uartNum);
}
//------------------------------------------------------------------------------
signed int ModbusDecode(char *buf, int len, char uartNum)
{
  char i;
  unsigned short start_addr, num, value, crc;
  char data_len;
  char* data;
  
  if(len < 4)
    return -1; //error: wrong length
  //--------------------------------------------------------------------------
  if(buf[0] != GetDeviceAddr())
    return 0; // address does not match
  //--------------------------------------------------------------------------
  switch(buf[1])
  {
  case 0x03: //read multiple holding registers (0x04)
    start_addr = (buf[2] << 8) | buf[3];
    num = (buf[4] << 8) | buf[5];
    i = 6;
    break;
    //--------------------------------------------------------------------------
  case 0x06: //write single register (0x06)
    start_addr = (buf[2] << 8) | buf[3];
    value = (buf[4] << 8) | buf[5];
    i = 6;
    break;
    //--------------------------------------------------------------------------
  case 0x10: //write multiple registers (0x10)
    start_addr = (buf[2] << 8) | buf[3];
    num = (buf[4] << 8) | buf[5];
    data_len = buf[6];
    data = &buf[7];
    i = 7 + data_len;
    break;
    //--------------------------------------------------------------------------
  case 0xFF:                                                                        //the secret command
    i = 2;
    break;
  default:
    return 0; // the function does not supported
  };
  crc = (buf[i] << 8) | buf[i + 1];
  if(CRC16((unsigned char*)buf, len - 2) != crc)
    return -1; //CRC does not match
  if(i + 2!= len)
    return -1; //  message length does not match
  //----------------------------------------------------------------------------
  // do function
  //----------------------------------------------------------------------------
  switch(buf[1])
  {
  case 0x03: //read multiple holding registers (0x04)
    return ReadMultipleHoldings(start_addr, num, uartNum);
    //--------------------------------------------------------------------------
  case 0x06: //write single register (0x06)
    return WriteSingleRegister(start_addr, value, uartNum);
    //--------------------------------------------------------------------------
  case 0x10: //write multiple registers (0x10)
    return WriteMultipleHoldings(start_addr, num, data_len, data, uartNum);
  case 0xFF:
    return PrintScreen(uartNum);
  };
  return 0; //just for lulz
};
    
void ModbusRxHandler0(char *buf, int len)
{
  ModbusDecode(buf, len, 0);
  SendMessage(MSG_UART0_RX);
}

void ModbusRxHandler1(char *buf, int len)
{
  ModbusDecode(buf, len, 1);
  SendMessage(MSG_UART1_RX);
}