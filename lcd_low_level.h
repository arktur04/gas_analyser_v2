//------------------------------------------------------------------------------
// Модуль реализует низкоуровневые функции работы с дисплеем
//------------------------------------------------------------------------------
#ifndef LCD_LOW_h
#define LCD_LOW_h

void LcdWriteByte(char byte);

void LcdSetPage(char chip, char page);
void SetChip(char chip);

void LcdSetAddress(char chip, char addr);

void LcdSetLine(char chip, char line);
//------------------------------------------------------------------------------
// Инициализация LCD при включении питания
//------------------------------------------------------------------------------
void LcdInitModule(void);

#endif
