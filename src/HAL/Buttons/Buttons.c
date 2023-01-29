#include "Buttons.h"





void 	Button_InitNoPullUp	(u8 port, u8 pin){
	DIO_PinMode(port, pin, INPUT_NOPULLUP);
}

void 	Button_InitPullUp	(u8 port, u8 pin){
	DIO_PinMode(port, pin, INPUT_PULLUP);
}

u8 		Button_GetValue		(u8 port, u8 pin){
	return DIO_DigitalReadPin(port, pin);
}












