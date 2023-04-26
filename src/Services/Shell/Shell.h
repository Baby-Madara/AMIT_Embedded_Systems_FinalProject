#ifndef SYSTEM_H
#define SYSTEM_H

#include "../../UTILS/STD_Types.h"
#include "../../UTILS/BitMath.h"
#include "../../UTILS/Maths.h"

#include "../../HAL/LCD/LCD.h"
#include "../../HAL/KeyPad/KeyPad.h"
#include "../../HAL/LEDs/LEDs.h"
#include "../../HAL/Buttons/Buttons.h"
#include "../../HAL/Servo/Servo.h"

#define SHELL_INIT_USER_BTN BUTTON_BTN2


#define SHELL_ADD_USER          0
#define SHELL_REMOVE_USER       1
// #define SHELL_             2
// #define SHELL_             3
// #define SHELL_             4
// #define SHELL_             5









void Shell_systemInit();
void Shell_login();
void Shell_cmdChecker();

void Shell_firstLogin();



#endif //SYSTEM_H