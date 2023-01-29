#ifndef LCD_INTERFACE_H_INCLUDED
#define LCD_INTERFACE_H_INCLUDED

// #include <string.h>

#include "../../MCAL/DIO/DIO.h"
#include <util/delay.h>
#include "LCD_Config.h"

#include <stdio.h>






// N 0 --> 1line disp
// F 0 --> 5*7 dot font

// D 0 --> disp off
// C 0 --> cursor off
// B 0 --> blink off

// i/d 1 (+1 increment mode)
// S   0 no disp shift op




typedef enum LCD_cmdSet{
	LCD_clr			= 0x01,
	LCD_4bit_mode 	= 0x22,
	LCD_DDRAM_addr	= 0x80	// 1000 0000
	
	// LCD_Init_4bit_57_2line_cursor_off_blink_off,



} LCD_cmdSet;
LCD_cmdSet LCD_Commands;

extern u8 LCD_cursorTracer;



void LCD_Cycle();

void LCD_Init();

void LCD_WriteData(u8 data);
void LCD_WriteCMD(u8 cmd);


void LCD_Clear();
void LCD_GoTo(u8 line, u8 col);


void LCD_WriteString(u8* str);
void LCD_WriteStringWithLength(u8* str, s8 len);
void LCD_WriteInt(s64 num);
void LCD_WriteFloat(float64 num, u8 digits);

void LCD_WriteNumWithLength(float64 num, u8 len);




void reverse( u8 *str, 		s32 len				);
s64  intToStr(s32 x, 		u8 str[], 	s32 d	);
void ftoa(    float64 n, 	u8 *res, 	s32 afterpoint);





#endif //LCD_INTERFACE_H_INCLUDED