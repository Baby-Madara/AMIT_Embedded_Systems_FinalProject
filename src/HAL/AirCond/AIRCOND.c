#include "../../MCAL/DIO/DIO.h"
//#include "../../MCAL/PWM/PWM.h"
#include "../../MCAL/ADC/ADC.h"

#include "AIRCOND_Config.h"
void Air_conditioner_on(u8 OMega)
{
DIO_DigitalWritePin	(DIO_B7,HIGH);// activate relay 
//Analog_W(DIO_B7,OMega)
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Air_conditioner_off(){
DIO_DigitalWritePin	(DIO_B7,LOW);//relay off
//disable timer
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Air_conditionar_check(){
float64 Il=0, TEMP_senseor_reading, TEMP_senseor_readingavg=0;// some variables used for mathematical calculation of tempreture
for(;Il<11;){// read the temprature 1000 times to make sure no error in reading as much as possiple
TEMP_senseor_reading=ADC_Read(TEMPADC);//read adc on that pin
TEMP_senseor_readingavg += Vrefrence*TEMP_senseor_reading/1023.00/LMfactor;//read the data from pin  and convert it to celicius  taken to consideration number of bits is  1024
Il++;
}
TEMP_senseor_readingavg=TEMP_senseor_readingavg/10.00;// take average

if (TEMP_senseor_readingavg >(27))// if tempretaure more htan 27 turn on air conditioner
{
Air_conditioner_on(TEMP_senseor_readingavg*1023/40);// max temp related which has max speed for comperssor is 40
}
else if (TEMP_senseor_readingavg <(20))// if temp below 20 turn of air conditioner
 {Air_conditioner_off();}
 return TEMP_senseor_readingavg ;// return temprature reading
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Intialise_smart_home(){//intialise needed adc or other functions
ADC_Init(7);//air conditioner prescaller 128

DIO_PinMode(DIO_B7,OUTPUT);
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ending_sequance(){// disable for sake of shutdown
Air_conditioner_off();
ADC_Disable();	
}














