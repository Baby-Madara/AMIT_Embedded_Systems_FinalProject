#ifndef KEYPAD_H_INCLUDED
#define KEYPAD_H_INCLUDED

#include "../../MCAL/DIO/DIO.h"
#include <util/delay.h>
#include "KeyPad_Config.h"




void KeyPad_Init();
u8 KeyPad_GetRead();



#endif	//KEYPAD_H_INCLUDED