#ifndef AC_H
#define AC_H

#include "../../UTILS/BitMath.h"
#include "../../UTILS/Maths.h"
#include "../../UTILS/STD_Types.h"
#include "../../Memory_map/mem_map.h"

#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/ADC/ADC.h"
#include "../../MCAL/Timers/Timers.h"




void AC_manualLvl();
void AC_AutoLvl();

u8   AC_currentTemperature();


#endif
