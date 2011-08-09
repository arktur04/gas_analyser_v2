//------------------------------------------------------------------------------
// Модуль реализует функции словаря
//------------------------------------------------------------------------------
#ifndef DICT_h
#define DICT_h

#include "arm_comm.h"
//------------------------------------------------------------------------------
// var_type
//------------------------------------------------------------------------------
#define INT   0
#define FLOAT 1
#define BOOLEAN 2

//------------------------------------------------------------------------------
// io_type
//------------------------------------------------------------------------------
#define IN       0
#define OUT      1
#define INTERNAL 2

typedef union 
{
  signed int ival;
  float fval;
} T_VAR;
/*
typedef struct 
{
  int tag; //variable id
  char var_type;
  char io_type;
  int fram_addr;
  int modbus_addr;  
  char var_name[11]; 
  char var_unit[8]; //название единицы измерения
  T_VAR def_val;
  T_VAR min_val;
  T_VAR max_val;
  char after_point; //знаков после запятой
  char edit_allowed; //разрешено редактирование пользователем
  //----------------------------------------
  // данные в RAM, в описании переменной должны быть = 0
  T_VAR curr_val;
  T_VAR prev_val;
  
} T_DICT_RECORD;
*/

typedef struct 
{
  int tag; //variable id
  char var_type;
  char io_type;
  int fram_addr;
  int modbus_addr;  
  char var_name[11]; 
  char var_unit[8]; //название единицы измерения
  float def_val;
  float min_val;
  float max_val;
  char after_point; //знаков после запятой
  char edit_allowed; //разрешено редактирование пользователем
} T_DICT_VAR_DESCR;

//void DrawCheckBox(char x, char y, char checked, char selected);
//------------------------------------------------------------------------------
// Init и Process
//------------------------------------------------------------------------------
//void InitCursor(void);
//void ProcessCursor(void);

#endif
