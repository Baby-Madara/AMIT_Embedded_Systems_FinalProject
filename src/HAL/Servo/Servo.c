#include "Servo.h"





void Servo_init()
{
    Timers_T2_Init(TIMERS_T2_CLK_PS_64, TIMERS_T2_MODE_FASTPWM, TIMERS_T2_OCPIN_NON_INVERTING_MODE, 255);


    Servo_attach();
}

void Servo_write(s16 _angle)
{
    // SERVO_angle = _angle;
    volatile u16    highTime_us  = MAP(_angle, -180, 180, 500, 2500),
                    totalTime_us = 20000,
                    highCyclesCtr  = 0, // 
                    totalCyclesCtr = 0; //19.53125 cycles

    

}

void Servo_detattach()
{
    DIO_PinMode(DIO_D7, INPUT );
    
}

void Servo_attach()
{
    DIO_PinMode(DIO_D7, OUTPUT);
}











