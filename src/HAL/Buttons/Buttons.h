#ifndef BUTTONS_H_INCLUDED
#define BUTTONS_H_INCLUDED

#include "../../MCAL/DIO/DIO.h"
#include "Buttons_Config.h"



void 	Button_InitNoPullUp	(u8 port, u8 pin);
void 	Button_InitPullUp	(u8 port, u8 pin);

u8 		Button_GetValue		(u8 port, u8 pin);



#endif //BUTTONS_H_INCLUDED