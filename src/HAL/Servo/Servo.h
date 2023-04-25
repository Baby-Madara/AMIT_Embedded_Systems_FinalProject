#ifndef SERVO_H_INCLUDED
#define SERVO_H_INCLUDED

#include "../../MCAL/Timers/Timers.h"
#include "../../MCAL/DIO/DIO.h"

#include "Servo_Config.h"



// servo ON time (of 20ms):
//  500      1000       1500     2000      2500   us
// -180      -90         0        90        180   deg


// 1/180'000 s timer resolution minimum

// (64/16'000'000) s 
// if target is 90  --> |----|----|----|____________________|
//                  --> | 500|----|2500|____________________|
//                  --> |-----------^____20'000_____________|
//                  --> |-----------^____20'000_____________|

// extern s16 SERVO_angle;

void Servo_init();

void Servo_write(s16 _angle);

void Servo_detattach();

void Servo_attach();


// 976.5625 Hz






#endif // SERVO_H_INCLUDED