//*******************************************************************************************************************
//
//  Author(s)...: DOOMSDAY
//
//  Target(s)...: STM8l
//
//  Compiler....: IAR EW for STM8
//
//  Description.: Библиотека для работы с индикатором STM8l-Discovery
//
//  Data........: 15.11.11 
//
//*******************************************************************************************************************

#ifndef LCD_H
#define LCD_H

#include "stdbool.h"
//определение порядка битов в символьных константах
#define A_ 6
#define B_ 2
#define C_ 5
#define D_ 4
#define E_ 0
#define F_ 7
#define G_ 3
#define H_ 15
#define J_ 14
#define K_ 10
#define M_ 1
#define N_ 12
#define P_ 8
#define Q_ 11
#define DP 13
#define COL 9


/***********************************************************************************
*   Function name :   LCD_Init
*   Returns :         нет       
*   Parameters :      нет    
*   Purpose :         инициализация контроллера LCD
************************************************************************************/
void LCD_Init(void);
/***********************************************************************************
*   Function name :   LCD_Contrast
*   Returns :         нет       
*   Parameters :      cntr - значение контрасности 0-7   
*   Purpose :         установка контрасности LCD
************************************************************************************/
void LCD_Contrast(unsigned char cntr);

/***********************************************************************************
*   Function name :   LCD_Char_Find
*   Returns :         cur_char - маскa символа
*   Parameters :      *с - код символа ASCII, 
*   Purpose :         определяет соответствующую символу маску
***********************************************************************************/
static unsigned int LCD_Char_Find(unsigned char* symb);

/***********************************************************************************
*   Function name :   LCD_Write_Char
*   Returns :         нет       
*   Parameters :      *ch - код символа, point - дес. точка, column - двоеточие,
		      position - порядковый номер знакоместа
*   Purpose :         Выводит символ на индикатор в соответствующем знакоместе
***********************************************************************************/
void LCD_Write_Char(unsigned char* ch, bool point, bool column, unsigned char position);

/***********************************************************************************
*   Function name :   LCD_Write_String
*   Returns :         нет       
*   Parameters :      * str - указатель на начало строки символов
*   Purpose :         Выводит строку
***********************************************************************************/
void LCD_Write_String(unsigned char* str);


void LCD_Scroll(unsigned char* str);

#endif //LCD_H