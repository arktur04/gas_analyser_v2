//------------------------------------------------------------------------------
// ������ ��������� ������� ���������� ��������
//------------------------------------------------------------------------------
#ifndef CURSOR_h
#define CURSOR_h

#define cur_period 100  //������ ������� ������� 1� = 100 * 10 ��

//------------------------------------------------------------------------------
// ������� SetCursorPos
// ������� ������������� ������� �������
// ���������
// x, y - ���������� �������
//------------------------------------------------------------------------------
void SetCursorPos(char x, char y);

//------------------------------------------------------------------------------
// Init � Process
//------------------------------------------------------------------------------
void InitCursor(void);
void ProcessCursor(void);

#endif
