#ifndef LCD_CONFIG_H_INCLUDED
#define LCD_CONFIG_H_INCLUDED

#include "../Kit_config.h"


#ifdef AMIT_KIT 
#define LCD_RS	DIO_B1
#define LCD_RW	DIO_B2
// #define LCD_En	DIO_B3
#define LCD_En	DIO_A0      // (modified for better connections)

#define LCD_D4 	DIO_A4
#define LCD_D5 	DIO_A5
#define LCD_D6 	DIO_A6
#define LCD_D7 	DIO_A7

#endif

#ifdef FARES_KIT

#define LCD_RS	DIO_A3
#define LCD_En	DIO_A2

#define LCD_D4 	DIO_B0
#define LCD_D5 	DIO_B1
#define LCD_D6 	DIO_B2
#define LCD_D7 	DIO_B4

#endif


#endif // LCD_CONFIG_H_INCLUDED
