//------------------------------------------------------------------------------
// Модуль реализует функции работы с дисплеем
//------------------------------------------------------------------------------
#include "board.h"
#include "lcd_low_level.h"

char _chip = 3;
//   LCD_A0 - состояние линии A0
void SetA0(char a0)
{
  if (a0)
    LcdA0Set();
  else
    LcdA0Clr();
}
//   chip - номер контроллера
void SetChip(char chip)
{
  if (chip == 0)
    {
      LcdE1Set();
      LcdE2Clr();
    }
    else
    {
      LcdE1Clr();
      LcdE2Set();
    }; 
}
//------------------------------------------------------------------------------
// Ф-ция предназначена для записи байта в LCD
// Параметры:
//   byte - передаваемый байт
//------------------------------------------------------------------------------
void LcdWriteByte(char byte)
{
  Delay(80);
  LcdESet();
  Delay(50);
  LcdData(byte);
  Delay(50);
  LcdEClr();
}

//------------------------------------------------------------------------------
// Ф-ция предназначена для установки текущей страницы LCD
// Параметры:
//   chip - номер контроллера
//   page - страница
//------------------------------------------------------------------------------
void LcdSetPage(char chip, char page)
{ 
  SetA0(0);
  SetChip(chip);
  LcdWriteByte(0xB8 | page);
}

//------------------------------------------------------------------------------
// Ф-ция предназначена для установки текущего адреса в странице
// Параметры:
//   chip - номер контроллера
//   addr - адрес
//------------------------------------------------------------------------------
void LcdSetAddress(char chip, char addr)
{
  SetA0(0);
  SetChip(chip);
  LcdWriteByte(0x40 | addr);
}

void LcdSetLine(char chip, char line)
{
  SetA0(0);
  SetChip(chip);
  LcdWriteByte(0xC0 | line);
}

//------------------------------------------------------------------------------
// Инициализация LCD при включении питания
//------------------------------------------------------------------------------
void LcdInitModule(void)
{
//  PIOcfgout( LCD_CONTROLS );
//  PIOcfgout(LCD_DATA);
  OutputSet(KEY_ROW0);
  OutputSet(KEY_ROW1);
  OutputSet(KEY_ROW2);
  OutputSet(KEY_ROW3);
  
  LcdResClr();
  Delay(500);
  LcdResSet();
  Delay(500);
  LcdEClr();
  Delay(50);
  SetA0(0);
  Delay(50);
  SetChip(0);
  Delay(50);
  LcdWriteByte(0x3F);  //turn on
  Delay(50);
  LcdWriteByte(0xC0);  //set start line 0
  Delay(50);
  LcdWriteByte(0xB8);  //set page 0
  Delay(50);
  LcdWriteByte(0x40);  //set address 0
  SetChip(1);
  LcdWriteByte(0x3F);  //turn on
  Delay(50);
  LcdWriteByte(0xC0);  //set start line 0
  Delay(50);
  LcdWriteByte(0xB8);  //set page 0
  Delay(50);
  LcdWriteByte(0x40);  //set address 0
}
