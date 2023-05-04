#ifndef AIRCOND_H_INCLUDED
#define AIRCOND_H_INCLUDED
//#include "../../MCAL/PWM/PWM.h"

#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/ADC/ADC.h"
#include "AIRCOND_Config.h"

void Air_conditioner_on(u8 OMega);// turn on compressor
void Air_conditioner_off();//turn off compressor
int Air_conditionar_check();//check if air conditioner is needed to be turned off or on and return temp
void ending_sequance();// preshutdown protcol
void Intialise_smart_home();//start protocol

#endif
