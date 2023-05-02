#ifndef KEYPAD_H_INCLUDED
#define KEYPAD_H_INCLUDED

#include "../../MCAL/DIO/DIO.h"
#include <util/delay.h>
#include "KeyPad_Config.h"




void KeyPad_Init();

// Get Reading and return it (as a u8 character)
u8 KeyPad_GetRead();

//Makes Reading 1 time only for 1 char
u8 KeyPad_GetRead_click();


#endif	//KEYPAD_H_INCLUDED