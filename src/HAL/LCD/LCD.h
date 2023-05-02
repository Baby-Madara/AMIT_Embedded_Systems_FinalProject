#ifndef LCD_INTERFACE_H_INCLUDED
#define LCD_INTERFACE_H_INCLUDED

// #include <string.h>

#include "../../MCAL/DIO/DIO.h"
#include "../../UTILS/Maths.h"
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



void LCD_Cycle();	//Latching

void LCD_Init();	

void LCD_WriteData(u8 data);	//Give Data to LCD to display it	(one char) 
void LCD_WriteCMD(u8 cmd);	//Give Command to LCD to Do it


void LCD_Clear();	
void LCD_GoTo(u8 line, u8 col);	//Go to specific location in LCD (line max = 2, col max = 8)


void LCD_WriteString(u8* str);	//Write string (many char)
void LCD_WriteStringWithLength(u8* str, s8 len);	//Write string (many char) with specific Length
void LCD_WriteInt(s64 num);	//Write integer number (0 ==> 9)
void LCD_WriteFloat(float64 num, u8 digits);	//Write Float Number (EX. 10.5)

void LCD_WriteNumWithLength(float64 num, u8 len); //Write integer numbers (0 ==> 9)





#endif //LCD_INTERFACE_H_INCLUDED