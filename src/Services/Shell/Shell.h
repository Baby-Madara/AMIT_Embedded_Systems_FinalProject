#ifndef SYSTEM_H
#define SYSTEM_H


// #include <avr/io.h>
// #include <avr/interrupt.h>

#include <util/delay.h>
#include "../../UTILS/BitMath.h"
#include "../../UTILS/Maths.h"
#include "../../UTILS/STD_Types.h"

#include "../../HAL/Buttons/Buttons.h"
#include "../../HAL/Bluetooth/Bluetooth.h"
#include "../../HAL/KeyPad/KeyPad.h"
#include "../../HAL/LCD/LCD.h"
#include "../../HAL/LEDs/LEDs.h"
#include "../../HAL/SevenSegment/SevenSegment.h"
#include "../../HAL/Servo/Servo.h"

#include "../../MCAL/ADC/ADC.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/Ex_Interrupts/Ex_Interrupts.h"
#include "../../MCAL/I2C/I2C.h"
#include "../../MCAL/ICU/ICU.h"
#include "../../MCAL/SPI/SPI.h"
#include "../../MCAL/Timers/Timers.h"
#include "../../MCAL/USART/USART.h"
#include "../../MCAL/UART_Trial/UART_Trial.h"
#include "../../MCAL/WatchDog_Timer/WatchDog_Timer.h"

#include "../../Memory_map/mem_map.h"


#include "../Users/Users.h"







#define SHELL_INIT_USER_BTN      BUTTON_BTN2

#define SHELL_CMD_USERMANUAL             'A'
#define SHELL_CMD_LOGOUT                 'B'
#define SHELL_CMD_ADD_USER               'C'
#define SHELL_CMD_EDIT_USER              'D'
#define SHELL_CMD_CONTINUE              '#'
#define SHELL_CMD_ESCAPE                '*'

#define SHELL_CMD_DOOR_TOGGLE          '0'
#define SHELL_CMD_LED1_TOGGLE          '1'
#define SHELL_CMD_LED2_TOGGLE          '2'
#define SHELL_CMD_LED3_TOGGLE          '3'
#define SHELL_CMD_LED4_TOGGLE          '4'
#define SHELL_CMD_LED5_TOGGLE          '5'
#define SHELL_CMD_LED_DIMMER_LEVEL     '6'
#define SHELL_CMD_AC_AUTO              '7'
#define SHELL_CMD_AC_MANUAL            '8'
#define SHELL_CMD_PRINT_USERS_LIST    '9'

#define SHELL_DOOR_LOCKED   LOW
#define SHELL_DOOR_UNLOCKED HIGH


#define SHELL_BLUETOOTH_LOGIN       HIGH
#define SHELL_KEYPAD_LOGIN          LOW

// extern static Users_usersList usersList;
// static Users_usersList usersList;







void Shell_systemInit();
void Shell_login(Users_usersList *usersList);
void Shell_cmdChecker();
void Shell_cmdExecuter(Users_usersList *usersList);
void Shell_firstLogin();

void Shell_Pause();
void Shell_wrongUser();
u8   Shell_WaitCmd();
u8*  Shell_enterStr(bool isHidden);
// u8   Shell_Pause_cmdCheck();





#endif //SYSTEM_H
