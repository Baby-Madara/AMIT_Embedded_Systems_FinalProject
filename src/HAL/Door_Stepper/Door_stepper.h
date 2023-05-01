#ifndef DOOR_STEPPER_H_INCLUDED
#define DOOR_STEPPER_H_INCLUDED


#include "../../MCAL/DIO/DIO.h"
#include <util/delay.h>

#define STEPPER1  DIO_B4
#define STEPPER2  DIO_B5
#define STEPPER3  DIO_B6
#define STEPPER4  DIO_B7



#define STEPPER_RIGHT 0
#define STEPPER_LEFT 1

void Stepper_init();
void Stepper_rotate(u8 Rotate_value, u8 Rotate_direction, u8 stepTime);

void Stepper_open();
void Stepper_close();

#endif   //door_H_INCLUDED