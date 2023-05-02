#ifndef LEDS_H_INCLUDED
#define LEDS_H_INCLUDED

#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/Timers/Timers.h"


#include "LEDs_Config.h"




void LED_InitLED(	u8 LEDPort, u8 LEDPin			);  // Makes LED as Output

void LED_WriteLED(	u8 LEDPort, u8 LEDPin, u8 val	);  //Makes LED value (HIGH,LOW)

void LED_SetLED(	u8 LEDPort, u8 LEDPin			);  //Makes LED on (HIGH)
void LED_ClearLED(	u8 LEDPort, u8 LEDPin			);  //Makes LED off (LOW)
void LED_ToggleLED(	u8 LEDPort, u8 LEDPin			);  //Changes current value of led (HIGH==>LOW, LOW==>HIGH)

u8 	 LED_LEDState(	u8 LEDPort, u8 LEDPin			);  //Get LED current state (HIGH,LOW)


void LED_DimmerVal(u8 pwmVal);  // Makes LED on with level of bightness using Timer(Fast PWM mode)
void LED_DimmerInit();  



#endif //LEDS_H_INCLUDED