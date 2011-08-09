//------------------------------------------------------------------------------
// Модуль реализует редактор значений (контрол)
//------------------------------------------------------------------------------
#ifndef EDITOR_h
#define EDITORN_h

#include "dict.h"

void SetEditorCoord(char x1, char y1, char x2, char y2);
void SetEditorMode(char e_type, T_VAR e_init_val);//, T_VAR e_min, T_VAR e_max);

void DrawEditor(void);
//void DrawEditor(char x1, char y1, char x2, char y2, char active);

float GetEditorValue(void);
void ProcessEditor(void);

#endif
