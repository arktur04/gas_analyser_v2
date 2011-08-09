//------------------------------------------------------------------------------
// ������ ��������� ������� ������ � ��������
//------------------------------------------------------------------------------
#ifndef LCD_h
#define LCD_h

#define SMALL_FONT 0
#define BIG_FONT 1

#define BLACK 0
#define WHITE ~BLACK

#define NON_INVERT_MODE 0
#define INVERT_MODE ~NON_INVERT_MODE

char * GetVideoBuff(void);

void LcdSetColor(char color);

void LcdInvertCurrentColor(void);

void LcdSetFont(char font);

void LcdSetInvertMode(char invert_mode);

//------------------------------------------------------------------------------
// �-��� ������� �����
//------------------------------------------------------------------------------
void LcdClear(void);

//------------------------------------------------------------------------------
// �-��� �������� � LCD ���������� �����������
//------------------------------------------------------------------------------
void LcdDraw(void);

//------------------------------------------------------------------------------
void LcdLine(char x1, char y1, char x2, char y2);

//------------------------------------------------------------------------------
void LcdText(char x1, char y1, char x2, char y2, const char *text);

//------------------------------------------------------------------------------
void LcdRect(char x1, char y1, char x2, char y2);

//------------------------------------------------------------------------------
void LcdFrame(char x1, char y1, char x2, char y2);

//------------------------------------------------------------------------------
// �-��� ������� �� ����� �����������
// ���������:
// x1, y1 - ����������
// w, h - ������ � ������
// *address - ����� ������� � ������������
//------------------------------------------------------------------------------
void LcdBmp(char x1, char y1, char w, char h, const char *address);

/*
//------------------------------------------------------------------------------
// �-��� ������ �������������� ����� ������� �����
// ���������:
// x1, y1, x2 - ����������
//------------------------------------------------------------------------------
void LCD_horline(char x1, char y1, char x2);

//------------------------------------------------------------------------------
// �-��� ������ �������������� ����� ������ �����
// ���������:
// x1, y1, x2 - ����������
//------------------------------------------------------------------------------
void LCD_horlineinv(char x1, char y1, char x2);

//------------------------------------------------------------------------------
// �-��� ������ ������������ ����� ������� �����
// ���������:
// x1, y1, �2 - ����������
//------------------------------------------------------------------------------
void LCD_vertline(char x1, char y1, char y2);

//------------------------------------------------------------------------------
// �-��� ������ ������������ ����� ������ �����
// ���������:
// x1, y1, �2 - ����������
//------------------------------------------------------------------------------
void LCD_vertlineinv(char x1, char y1, char y2);

//------------------------------------------------------------------------------
// �-��� ������ ������������� ������� �����
// ���������:
// x1, y1, �2, �2 - ����������
//------------------------------------------------------------------------------
void LCD_rect(char x1, char y1, char x2, char y2);

//------------------------------------------------------------------------------
// �-��� ������ ������������� ������ �����
// ���������:
// x1, y1, �2, �2 - ����������
//------------------------------------------------------------------------------
void LCD_rectinv(char x1, char y1, char x2, char y2);

//------------------------------------------------------------------------------
// �-��� ������� �� ����� ����� ������� �����
// ���������:
// x1, y1 - ����������
// str - �����
//------------------------------------------------------------------------------
void LCD_textout(char x1, char y1, char *str);

//------------------------------------------------------------------------------
// �-��� ������� �� ����� ����� ������ �����
// ���������:
// x1, y1 - ����������
// str - �����
//------------------------------------------------------------------------------
void LCD_textoutinv(char x1, char y1, char *str);
*/
#endif
