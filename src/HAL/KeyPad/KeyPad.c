#include "KeyPad.h"





void KeyPad_Init(){

	DIO_PinMode(KEYPAD_R0, INPUT_PULLUP);
	DIO_PinMode(KEYPAD_R1, INPUT_PULLUP);
	DIO_PinMode(KEYPAD_R2, INPUT_PULLUP);
	DIO_PinMode(KEYPAD_R3, INPUT_PULLUP);

	DIO_PinMode(KEYPAD_C0, OUTPUT);
	DIO_PinMode(KEYPAD_C1, OUTPUT);
	DIO_PinMode(KEYPAD_C2, OUTPUT);
	DIO_PinMode(KEYPAD_C3, OUTPUT);

	DIO_DigitalWritePin(KEYPAD_C0,HIGH);
	DIO_DigitalWritePin(KEYPAD_C1,HIGH);
	DIO_DigitalWritePin(KEYPAD_C2,HIGH);
	DIO_DigitalWritePin(KEYPAD_C3,HIGH);

}


u8 KeyPad_GetRead(){
	volatile u8 reading =0;

	if(reading == 0){
		DIO_DigitalWritePin(KEYPAD_C0, LOW); 		_delay_ms(1);
		if		(DIO_DigitalReadPin(KEYPAD_R0) == LOW){	reading = '1';}	
		else if	(DIO_DigitalReadPin(KEYPAD_R1) == LOW){	reading = '4';}	
		else if	(DIO_DigitalReadPin(KEYPAD_R2) == LOW){	reading = '7';}	
		else if	(DIO_DigitalReadPin(KEYPAD_R3) == LOW){	reading = '*';}	
		DIO_DigitalWritePin(KEYPAD_C0, HIGH); 		
	}
	if(reading == 0){
		DIO_DigitalWritePin(KEYPAD_C1, LOW); 		_delay_ms(1);
		if		(DIO_DigitalReadPin(KEYPAD_R0) == LOW){	reading = '2';}	
		else if	(DIO_DigitalReadPin(KEYPAD_R1) == LOW){	reading = '5';}	
		else if	(DIO_DigitalReadPin(KEYPAD_R2) == LOW){	reading = '8';}	
		else if	(DIO_DigitalReadPin(KEYPAD_R3) == LOW){	reading = '0';}	
		DIO_DigitalWritePin(KEYPAD_C1, HIGH); 		
	}
	if(reading == 0){
		DIO_DigitalWritePin(KEYPAD_C2, LOW); 		_delay_ms(1);
		if		(DIO_DigitalReadPin(KEYPAD_R0) == LOW){	reading = '3';}	
		else if	(DIO_DigitalReadPin(KEYPAD_R1) == LOW){	reading = '6';}	
		else if	(DIO_DigitalReadPin(KEYPAD_R2) == LOW){	reading = '9';}	
		else if	(DIO_DigitalReadPin(KEYPAD_R3) == LOW){	reading = '#';}	
		DIO_DigitalWritePin(KEYPAD_C2, HIGH); 		
	}
	if(reading == 0){
		DIO_DigitalWritePin(KEYPAD_C3, LOW); 		_delay_ms(1);
		if		(DIO_DigitalReadPin(KEYPAD_R0) == LOW){	reading = 'A';}	
		else if	(DIO_DigitalReadPin(KEYPAD_R1) == LOW){	reading = 'B';}	
		else if	(DIO_DigitalReadPin(KEYPAD_R2) == LOW){	reading = 'C';}	
		else if	(DIO_DigitalReadPin(KEYPAD_R3) == LOW){	reading = 'D';}	
		DIO_DigitalWritePin(KEYPAD_C3, HIGH); 		
	}

	return reading;

}


u8 KeyPad_GetRead_click()
{
	volatile static u8 prevRead = 0;
	volatile u8 newRead = KeyPad_GetRead();

	if(newRead == prevRead)		{	return 0;		}
	else						{	prevRead = newRead; 	return newRead;}
}








