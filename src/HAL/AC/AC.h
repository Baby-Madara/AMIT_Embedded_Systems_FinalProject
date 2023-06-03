#ifndef AC_H
#define AC_H

#include "../../UTILS/BitMath.h"
#include "../../UTILS/Maths.h"
#include "../../UTILS/STD_Types.h"
#include "../../Memory_map/mem_map.h"

#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/ADC/ADC.h"
#include "../../MCAL/Timers/Timers.h"



// manualy control the air conditioner either on or off
void AC_manualLvl();


// automaticaly control air conditioner according to temperature (needs no input)
void AC_AutoLvl();

//  check temperature read by sensor and  return it
u16   AC_currentTemperature();

#endif
