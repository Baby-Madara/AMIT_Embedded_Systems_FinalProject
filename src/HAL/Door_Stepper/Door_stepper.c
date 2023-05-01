#include"Door_stepper.h"

void Stepper_init()
{
    DIO_PinMode(STEPPER1, OUTPUT);
    DIO_PinMode(STEPPER2, OUTPUT);
    DIO_PinMode(STEPPER3, OUTPUT);
    DIO_PinMode(STEPPER4, OUTPUT);
}

void Stepper_rotate(u8 Rotate_value, u8 Rotate_direction, u8 stepTime)
{
    u8 Counter_1 = 0;
    if (Rotate_direction == 0)
    {
        for (; Counter_1 < Rotate_value;)
        {
            DIO_DigitalWritePin(STEPPER1, LOW);
            DIO_DigitalWritePin(STEPPER2, LOW);
            DIO_DigitalWritePin(STEPPER3, LOW);
            DIO_DigitalWritePin(STEPPER4, HIGH);
            _delay_ms(stepTime);

            DIO_DigitalWritePin(STEPPER1, LOW);
            DIO_DigitalWritePin(STEPPER2, LOW);
            DIO_DigitalWritePin(STEPPER3, HIGH);
            DIO_DigitalWritePin(STEPPER4, LOW);
            _delay_ms(stepTime);

            DIO_DigitalWritePin(STEPPER1, LOW);
            DIO_DigitalWritePin(STEPPER2, HIGH);
            DIO_DigitalWritePin(STEPPER3, LOW);
            DIO_DigitalWritePin(STEPPER4, LOW);
            _delay_ms(stepTime);

            DIO_DigitalWritePin(STEPPER1, HIGH);
            DIO_DigitalWritePin(STEPPER2, LOW);
            DIO_DigitalWritePin(STEPPER3, LOW);
            DIO_DigitalWritePin(STEPPER4, LOW);
            _delay_ms(stepTime);

            Counter_1 = Counter_1 + 4;
        }
    }
    else
    {
        for (; Counter_1 < Rotate_value;)
        {
            DIO_DigitalWritePin(STEPPER1, HIGH);
            DIO_DigitalWritePin(STEPPER2, LOW);
            DIO_DigitalWritePin(STEPPER3, LOW);
            DIO_DigitalWritePin(STEPPER4, LOW);
            _delay_ms(stepTime);

            DIO_DigitalWritePin(STEPPER1, LOW);
            DIO_DigitalWritePin(STEPPER2, HIGH);
            DIO_DigitalWritePin(STEPPER3, LOW);
            DIO_DigitalWritePin(STEPPER4, LOW);
            _delay_ms(stepTime);

            DIO_DigitalWritePin(STEPPER1, LOW);
            DIO_DigitalWritePin(STEPPER2, LOW);
            DIO_DigitalWritePin(STEPPER3, HIGH);
            DIO_DigitalWritePin(STEPPER4, LOW);
            _delay_ms(stepTime);

            DIO_DigitalWritePin(STEPPER1, LOW);
            DIO_DigitalWritePin(STEPPER2, LOW);
            DIO_DigitalWritePin(STEPPER3, LOW);
            DIO_DigitalWritePin(STEPPER4, HIGH);
            _delay_ms(stepTime);

            Counter_1 = Counter_1 + 4;
        }
    }
}

void Stepper_open()
{
    Stepper_rotate(50, STEPPER_RIGHT, 5);
}

void Stepper_close()
{
    Stepper_rotate(50, STEPPER_LEFT, 5);
}