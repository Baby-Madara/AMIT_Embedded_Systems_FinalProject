
#ifndef AIRCOND_CONFIG_H_INCLUDED
#define AIRCOND_CONFIG_H_INCLUDED

#include "../Kit_config.h"

#define TEMPSENS1 			DIO_A1          //tempsenseor pin
#define COMPERASOR1 		DIO_B7          // the pin where it controls the comperassor or relay for the motor
#define TEMPADC				1           // the adc pin on which the pin is connectet on
#define Vrefrence			5.00        // voltage of adc refrence used
#define LMfactor			0.01            // sensor factor : generated voltage/celcius
//#define PWMld_EN_1            DIO_B1  //GND
//#define PWMld_EN_2            DIO_B0 // VCC
#endif