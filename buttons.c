//------------------------------------------------------------------------------
// Модуль реализует отрисовку кнопок
//------------------------------------------------------------------------------
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "buttons.h"
/*
#define BTN_OK      0
#define BTN_CANCEL  1
#define BTN_DEFAULT 2
#define BTN_FORWARD 3
#define BTN_BACK    4
#define BTN_HOME    5
*/
static char* buttons[6] = {
  "OK",
  "Отмена",
  "Умолч.",
  "Вперед",
  "Назад",
  "Гл.экр."};

static char bmp_ids[6] = {-1, -1, -1, BMP_FORWARD, BMP_BACKWARD, BMP_HOME};

void DrawTextButton(char x1, char y1, char x2, char y2, char *text, char active)
{
  SetFont(SMALL_FONT);
  LcdSetColor(BLACK);
  if(active){
    LcdRect(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
    LcdSetColor(WHITE);
  };
  LcdText(x1 + 2, y1 + 2, x2 - 1, y2 - 2, text);
  LcdSetColor(BLACK); 
  LcdLine(x1 + 2, y1, x2 - 2, y1);
  LcdLine(x1 + 2, y2, x2 - 2, y2);
  LcdLine(x1, y1 + 2, x1, y2 - 2);
  LcdLine(x2, y1 + 2, x2, y2 - 2);
  
  LcdLine(x1 + 1, y1 + 1, x1 + 1, y1 + 1);
  LcdLine(x2 - 1, y1 + 1, x2 - 1, y1 + 1);
  LcdLine(x1 + 1, y2 - 1, x1 + 1, y2 - 1);
  LcdLine(x2 - 1, y2 - 1, x2 - 1, y2 - 1);
}

void DrawBmpButton(char x1, char y1, char x2, char y2, char btn_id, char active)
{
  char bmp_id = bmp_ids[btn_id];
//  SetFont(SMALL_FONT);
//  LcdSetColor(BLACK);
  if(active){
    LcdSetColor(BLACK);
    LcdRect(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
    LcdSetColor(WHITE);
  }
  else
  {
    LcdSetColor(WHITE);
    LcdRect(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
    LcdSetColor(BLACK);
  };
 // LcdText(x1 + 2, y1 + 2, x2 - 1, y2 - 2, text);
  LcdBmp(x1 + 2, y1 + 2, GetBmpWidth(bmp_id), GetBmpHeight(bmp_id), GetBmp(bmp_id));
  LcdSetColor(BLACK); 
  LcdLine(x1 + 2, y1, x2 - 2, y1);
  LcdLine(x1 + 2, y2, x2 - 2, y2);
  LcdLine(x1, y1 + 2, x1, y2 - 2);
  LcdLine(x2, y1 + 2, x2, y2 - 2);
  
  LcdLine(x1 + 1, y1 + 1, x1 + 1, y1 + 1);
  LcdLine(x2 - 1, y1 + 1, x2 - 1, y1 + 1);
  LcdLine(x1 + 1, y2 - 1, x1 + 1, y2 - 1);
  LcdLine(x2 - 1, y2 - 1, x2 - 1, y2 - 1);
}

void DrawButton(char x, char y, char btn_id, char active)
{
  DrawTextButton(x, y, x + 42, y + 10, buttons[btn_id], active);
};

void DrawButton2(char x, char y, char btn_id, char active)
{
  DrawBmpButton(x, y, x + 16, y + 18, btn_id, active);
};
