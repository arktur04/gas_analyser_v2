//------------------------------------------------------------------------------
// ������ ��������� �������������� ������� ������ � ��������
//------------------------------------------------------------------------------
#ifndef LCD_LOW_h
#define LCD_LOW_h

void LcdWriteByte(char byte);

void LcdSetPage(char chip, char page);
void SetChip(char chip);

void LcdSetAddress(char chip, char addr);

void LcdSetLine(char chip, char line);
//------------------------------------------------------------------------------
// ������������� LCD ��� ��������� �������
//------------------------------------------------------------------------------
void LcdInitModule(void);

#endif
