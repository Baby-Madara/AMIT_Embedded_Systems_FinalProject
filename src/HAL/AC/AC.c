#include "AC.h"


void AC_manualLvl()
{

}




void AC_AutoLvl()
{
    // ADC_Read(DIO_A1_ANALOG);
}

u16 AC_currentTemperature()
{
    return MAP(ADC_Read(DIO_A1_ANALOG), 0, 1023, 10 , 70); //assume 0-> 10deg    1023->70deg Celcuis
}


















