#ifndef KEYPAD_H_CONFIG_INCLUDED
#define KEYPAD_H_CONFIG_INCLUDED

#include "../Kit_config.h"


// ROWS: INPUTS  -  COLUMNS: OUTPUTS

#ifdef AMIT_KIT

#define KEYPAD_R0	DIO_C0
#define KEYPAD_R1	DIO_C1
#define KEYPAD_R2	DIO_D4
#define KEYPAD_R3	DIO_C3

#define KEYPAD_C0	DIO_C4
#define KEYPAD_C1	DIO_C5
#define KEYPAD_C2	DIO_C6
#define KEYPAD_C3	DIO_D5

#endif

#ifdef FARES_KIT

#define KEYPAD_R0	DIO_C5
#define KEYPAD_R1	DIO_C4
#define KEYPAD_R2	DIO_C3
#define KEYPAD_R3	DIO_C2

#define KEYPAD_C0	DIO_D7
#define KEYPAD_C1	DIO_D6
#define KEYPAD_C2	DIO_D5
#define KEYPAD_C3	DIO_D3

#endif





#endif







