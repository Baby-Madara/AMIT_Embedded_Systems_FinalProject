#ifndef LEDS_H_INCLUDED
#define LEDS_H_INCLUDED

#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/Timers/Timers.h"


#include "LEDs_Config.h"




void LED_InitLED(	u8 LEDPort, u8 LEDPin			);

void LED_WriteLED(	u8 LEDPort, u8 LEDPin, u8 val	);

void LED_SetLED(	u8 LEDPort, u8 LEDPin			);
void LED_ClearLED(	u8 LEDPort, u8 LEDPin			);
void LED_ToggleLED(	u8 LEDPort, u8 LEDPin			);

u8 	 LED_LEDState(	u8 LEDPort, u8 LEDPin			);


void LED_DimmerVal(u8 pwmVal);
void LED_DimmerInit();



#endif //LEDS_H_INCLUDED