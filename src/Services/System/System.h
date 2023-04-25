#ifndef SYSTEM_H
#define SYSTEM_H

#include "../../UTILS/STD_Types.h"
#include "../../UTILS/BitMath.h"
#include "../../UTILS/Maths.h"

#include "../../HAL/LCD/LCD.h"
#include "../../HAL/KeyPad/KeyPad.h"
#include "../../HAL/LEDs/LEDs.h"
#include "../../HAL/Servo/Servo.h"



void SYS_systemInit();
void SYS_cmdChecker();




#endif //SYSTEM_H