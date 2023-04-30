#include "LEDs.h"




void LED_InitLED(	u8 LEDPort, u8 LEDPin			){
	DIO_PinMode(LEDPort, LEDPin, OUTPUT);
}

void LED_WriteLED(	u8 LEDPort, u8 LEDPin, u8 val	){
	DIO_DigitalWritePin(LEDPort, LEDPin, val);

}

void LED_SetLED(	u8 LEDPort, u8 LEDPin			){
	DIO_DigitalWritePin(LEDPort, LEDPin, HIGH);

}


void LED_ClearLED(	u8 LEDPort, u8 LEDPin			){
	DIO_DigitalWritePin(LEDPort, LEDPin, LOW);

}


void LED_ToggleLED(	u8 LEDPort, u8 LEDPin			){
	DIO_DigitalTogglePin(LEDPort, LEDPin);
}



u8 	 LED_LEDState(	u8 LEDPort, u8 LEDPin			){
	return DIO_ReturnOutputValue(LEDPort, LEDPin);
}


void LED_Dimmer(u16 pwmVal)
{
	
}








