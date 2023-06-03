/**
 * @project:		Smart home using ATMega32A
 * @IDE:			platformIO on VSCode
 * @connections:	shown in @pinout (the outer layers is the last connections)
 * 
 * @author			Ahmed Farahat : @Baby-Madara  	ahmed.farahat1@msa.edu.eg - ahmedfarahat1177@gmail.com - +201119027639
 * @author			Shehab Ashraf : @ShehabAshraf 	
 * @author			Yousef Gamal  : @yousefamar5678 
 * @author			Tarek Fouad   : @tarekfouad2000 
 * @author			Mohamed Magdy : 
 * 
 * @details			ATMega32 drivers for AMIT Kit with the following hardware (in the HAL layer). Using PlatformIO as IDE on VS Code
 * @date			start date: 24-09-2022			-		completed: 	02-05-2023
 * @aknowledgement:	learned embedded systems interfacing from different instructors but special thanks for Moatasem El-Sayed & Sara Abd Rabbo
 * @datasheet:		for any technical details, refer to datasheet: https://ww1.microchip.com/downloads/en/DeviceDoc/doc2503.pdf
 * 	DIO				|
 * 	ADC 			|201
 * 	Interrupts		|
 * 	Registers Page 	||	327
 *  
 * @pinout:					          
 *                                                [PDIP]:                                              
 *             .                             __________________                          .             
 *             .  Btn0         (XCK/T0) PB0 |1       @       40| PA0 (ADC0)       N/C    .    LCD_EN   
 *      LCD_RS .  LCD_RS           (T1) PB1 |2               39| PA1 (ADC1)       Pot    .    Pot (as a temperature sensor)      
 *      LCD_RW .  LCD_RW    (INT2/AIN0) PB2 |3               38| PA2 (ADC2)       Relay  .             
 *      LCD_EN .  LCD_EN     (OC0/AIN1) PB3 |4               37| PA3 (ADC3)       Buzzer .             
 *             .  SS              (_SS) PB4 |5               36| PA4 (ADC4)       LCD_D4 .    LCD_D4   
 *             .  MOSI           (MOSI) PB5 |6               35| PA5 (ADC5)       LCD_D5 .    LCD_D5   
 *             .  MISO           (MISO) PB6 |7               34| PA6 (ADC6)       LCD_D6 .    LCD_D6   
 *             .  SCK             (SCK) PB7 |8               33| PA7 (ADC7)       LCD_D7 .    LCD_D7   
 *             .                     _RESET |9               32| AREF                    .             
 *             .                        VCC |10   ATMega32   31| GND                     .             
 *             .                        GND |11              30| AVCC                    .             
 *             .                      XTAL2 |12              29| PC7 (TOSC2)      LED1   .             
 *             .                      XTAL1 |13              28| PC6 (TOSC1)      H_A4   .    KEYPAD_C2
 *             .   RX             (RXD) PD0 |14              27| PC5 (TDI)        H_A3   .    KEYPAD_C1
 *             .   TX             (TXD) PD1 |15              26| PC4 (TDO)        H_A2   .    KEYPAD_C0
 *             .   Btn2          (INT0) PD2 |16              25| PC3 (TMS)        H_A1   .    KEYPAD_R3
 *             .   LED2          (INT1) PD3 |17              24| PC2 (TCK)        LED0   .             
 *   KEYPAD_R2 .   H_En1         (OC1B) PD4 |18              23| PC1 (SDA)        SDA    .    KEYPAD_R1
 *   KEYPAD_C3 .   H_En2         (OC1A) PD5 |19              22| PC0 (SCL)        SCL    .    KEYPAD_R0
 *             .   Btn1          (ICP1) PD6 |20              21| PD7 (OC2)        Servo  .             
 *             .                            |__________________|                         .             
 *             .                                                                         .             
 *             .                        * (_PIN) means inverse logic                     .             
 *  
 * @sw_archeticture: 
 *     **************************************** Software Architecture *******************************************************************************
 *     *|   [UTILS]   || [main]        |                     main.c                                                                                   *
 *     *|             ||------------------------------------------------------------------------------------------------------------------------------*
 *     *|             || [Services]    |     users_LinkedList - Shell                                                                                 *
 *     *|             ||------------------------------------------------------------------------------------------------------------------------------*
 *     *|             || [HAL]         | Lamps[1:5] - Dimmer[L6] - Door ctrlr - AC ctrlr - alarm - LCD - keaypad - tempSensor - EEPROM - Btns         *
 *     *|             ||------------------------------------------------------------------------------------------------------------------------------*
 *     *|  STD_Types  || [MCAL]        | DIO - General_Interrupts - External_Interrupts - ADC - Timers WDTimer - UART - I2C - SPI                     *
 *     *|             ||------------------------------------------------------------------------------------------------------------------------------*
 *     *|  BIT_MATH   || [MEM_MAPPING] |                 MCU registers                                                                                *
 *     **********************************************************************************************************************************************
 *  
 * @warnings:		
 * 					-LCD and SevenSegments cannot be used together
 * 					-sevenSegments must be used with parallel programming (NO SEQUENTIAL DELAY CAN BE USED to work properly)
 * 					-
 *  
 *  
 * @main: 			IT IS USED FOR TESTING DRIVERS (before the last project). THE DRIVER YOU WANT TO TEST, UNCOMMENT "#define <TESTING_DRIVER_NAME>" and type the codes you want in its section, this is for ensuring no loss of old trials
 * 
 */




// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>
// #include "UTILS/BitMath.h"
// #include "UTILS/Maths.h"

// #include "Memory_map/mem_map.h"

// #include "MCAL/ADC/ADC.h"
// #include "MCAL/DIO/DIO.h"
// #include "MCAL/Ex_Interrupts/Ex_Interrupts.h"
// #include "MCAL/I2C/I2C.h"
// #include "MCAL/ICU/ICU.h"
// #include "MCAL/SPI/SPI.h"
// #include "MCAL/Timers/Timers.h"
// #include "MCAL/UART_Trial/UART_Trial.h"
// #include "MCAL/USART/USART.h"
// #include "MCAL/WatchDog_Timer/WatchDog_Timer.h"

// #include "HAL/Bluetooth/Bluetooth.h"
// #include "HAL/Buttons/Buttons.h"
// #include "HAL/KeyPad/KeyPad.h"
// #include "HAL/LCD/LCD.h"
// #include "HAL/LEDs/LEDs.h"
// #include "HAL/Servo/Servo.h"
// #include "HAL/SevenSegment/SevenSegment.h"

// #include "Services/Users/Users.h"
#include "Services/Shell/Shell.h"





// ************   uncomment ONLY the line corresponding to sketch you test   ************ //
#define TESTING_SHELL
// #define TESTING_EEPROM
// #define TESTING_EEPROM_USERS
// #define TESTING_BLUETOOTH
// #define TESTING_USART
// #define TESTING_TIMERS
// #define TESTING_ADC
// #define TESTING_EX_INTERRUPTS
// #define TESTING_SPI
// #define TESTING_I2C
// #define TESTING_ICU
// #define TESTING_WATCHDOG_TIMER
//////
// #define TESTING_KEYPAD
// #define TESTING_LCD
// #define TESTING_LEDS
// #define TESTING_DIO
// #define TESTING_BIT_MATH
// #define TESTING_BUTTONS
// #define TESTING_SERVO
// #define TESTING_SEVEN_SEGMENTS
//////
// #define GENERAL_TEST



#ifdef TESTING_EEPROM_USERS




int main(){



while(1){

	
	
}
}


#endif


#ifdef TESTING_EEPROM

volatile u16 baseAddr = 0x0005;


int main(){
	
	LCD_Init();
	LCD_Clear();
	
	EEPROM_writeStr("Ahmed ", baseAddr);
	
	volatile u8 temP = 0;
	volatile u8 buf[100] ="";
	

while(1){
	temP = EEPROM_readChar(baseAddr)+3;
	
	EEPROM_writeChar(temP, baseAddr);
	_delay_ms(500);
	
	EEPROM_readStr(baseAddr, buf);
	LCD_WriteString(buf);
	
	
}
}


#endif


#ifdef TESTING_SHELL

static Users_usersList usersList;

int main(){
	
	Users_initList(&usersList, 20);
	Users_AddEntry(&usersList, "1234", "1234", TRUE);

	Shell_systemInit();
	Shell_login(&usersList);


while(1){
	Shell_cmdChecker();
	Shell_cmdExecuter(&usersList);
	Shell_devicesUpdate();
	Shell_ScreenUpdate();
}
}
#endif



#ifdef TESTING_BLUETOOTH

int main(){
	Bluetooth_Init();
	LCD_Init();

while(1){
	volatile u8 ch = Bluetooth_RxChar();

	if(ch){LCD_WriteData(ch);}


}
}
#endif


	// DIO_PinMode(DIO_D7, OUTPUT);
	// Timers_T2_Init(TIMERS_T2_CLK_PS_64, TIMERS_T2_MODE_FASTPWM, TIMERS_T2_OCPIN_NON_INVERTING_MODE, 200);


#ifdef TESTING_I2C				/////////////////////

void TWI_Init(void)
{

	// set_bit(TWCR,6);
	TWSR = 0;
	TWBR = 0x07;
	TWCR |= (1 << TWEN);
}

void TWI_Start(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (GET_BIT(TWCR, TWINT) == 0)
	{	}
}


void TWI_Stop(void)
{
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

void TWI_Write(char data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (GET_BIT(TWCR, TWINT) == 0)
	{	}
}

void TWI_Read_Nack(char *ptr) // The function argument is a pointer to a memory place in the MCU to store the received data in
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (GET_BIT(TWCR, TWINT) == 0)
	{	}
	*ptr = TWDR;
}

void EEPROM_Write(char data, char address)
{
	TWI_Start();
	TWI_Write(0xA8); // slave address is 1010.100 and a 0 in the 8th bit to indicate Writting.

	TWI_Write(address);

	TWI_Write(data);

	TWI_Stop();
}

void EEPROM_Read(char address, char *ptr) // the function arguments are an address in the EEPROM to read from and a pointer to a memory place in the MCU to store the read data in

{

	TWI_Start();

	TWI_Write(0xA8);

	TWI_Write(address);

	TWI_Start();

	TWI_Write(0xA9);

	TWI_Read_Nack(ptr);

	TWI_Stop();
}

int main(void)

{

	char R;

	DDRD = 0b11111111;

	TWI_Init();

	while (1)

	{

		EEPROM_Write(0xE0, 0x00);

		_delay_ms(1000); // You must allow suffcent delay for the EEPROM to complete the its internal write cycle

		EEPROM_Read(0x00, &R);

		if (R == 0xE0)
		{

			LED_ToggleLED(LED2);
		}
	}
}

// int main(){
// 	LCD_Init();


// 	I2C_init(0x40,FALSE, 3, I2C_PRESCALER_1);

// while(1){

// 	I2C_connectTo_SelectRW(0x10, I2C_WRITE);

// 	I2C_sendByte('C');
// 	I2C_stopConnection();
// 	_delay_ms(1000);
// }
// }





/*
int main(){

	volatile u8 ch='n', sState=0;

	I2C_init(0x40,TRUE, 3, I2C_PRESCALER_1);
	LCD_Init();
	LCD_WriteData(ch);




while (1)
{
	sState = I2C_Start(34, I2C_READ);
	ch = I2C_Read_Ack();
	I2C_Stop();
	// while(sState != 1){
	// 	sState = I2C_Start(34, I2C_READ);
	// }
	// if(sState ==1){
	// 	// I2C_Stop();
		
	// }
	

	LCD_WriteData(ch);
	LCD_WriteData(ch);
	// LCD_WriteInt(sState);

	_delay_ms(110);


}
}
*/





// int main(){
// 	sei();


// 	volatile u8 ch='n';

// 	I2C_init(0x40,FALSE, 3, I2C_PRESCALER_1);
// 	LCD_Init();
// 	LCD_WriteData(ch);


// while (1)
// {
// 	volatile u8 stat=0;
// 	// ch = 
// 	stat = I2C_Start(16, I2C_WRITE);
	
// 	while(1){
// 		if(stat == 2 || stat == 3 || stat == 0){
// 			I2C_Stop();
// 			stat = I2C_Start(16, I2C_WRITE);
// 		}
// 		else{break;}
// 	}

// 	LCD_WriteData(ch);
// 	I2C_Write(ch++);
// 	I2C_Stop();

// 	_delay_ms(1000);
// }
// }

#endif


#ifdef TESTING_SPI				/////////////////////
int main(){
while(1){

}
}
#endif


#ifdef TESTING_USART				/////////////////////
int main(){
while(1){

}
}
#endif














#ifdef TESTING_TIMERS				/////////////////////


// ISR(TIMER0_COMP_vect){
// 	LED_ToggleLED(LED0);
// 	Timers_T0_IntCompMtchEnable();
// }

// TIMERS_ENABLE_T0_WATCH

int main(){

	LCD_Init();	
	// LED_InitLED(LED0);
	// LCD_GoTo(0,1); LCD_WriteInt(sizeof(u64));
	
	Timers_T0_Init(TIMERS_T0_CLK_PS_1024, TIMERS_T0_MODE_FASTPWM, TIMERS_T0_OCPIN_NON_INVERTING_MODE, 127);
	// Timers_T0_Init(TIMERS_T0_COUNT_EXT_ON_FALLING_B0, TIMERS_T0_MODE_CTC, TIMERS_T0_OCPIN_DISCONNECT, 10);
	// Timers_T0_IntCompMtchEnable();
	
	Timers_T0_WatchInit();

while (1)
{
	// Timers_T0_WG__PWM_B3(0); _delay_ms(1000);
	// Timers_T0_WG__PWM_B3(128); _delay_ms(1000);
	// Timers_T0_WG__PWM_B3(255); _delay_ms(1000);




	LCD_GoTo(1,0); 
	LCD_WriteInt(Timers_T0_days()				);LCD_WriteData(':');
	LCD_WriteInt(Timers_T0_hours()%24			);LCD_WriteData(':');
	LCD_WriteInt(Timers_T0_minutes()%60		);LCD_WriteData(':');
	LCD_WriteInt(Timers_T0_secs()%60			);LCD_WriteData('.');
	LCD_WriteInt(Timers_T0_milliSecs()%1000	);


}
}
#endif


#ifdef TESTING_ADC					/////////////////////

u8 i=0;
void myADCISR(){
	LED_ToggleLED(LED1);
	// LCD_GoTo(0,13);
	// LCD_WriteInt(i);
	// ++i;
}

int main(){
	LED_InitLED(LED1);
	LCD_Init();
	// ADC_IntSetCallBack(myADCISR);
	ADC_DisableAutoTrigger();
	// ADC_IntEnable();
	ADC_Init(ADC_CLK_PS_128);

while (1)
{
	LCD_GoTo(0,1);
	LCD_WriteNumWithLength(ADC_Read(DIO_A1_ANALOG),11);
	_delay_ms(200);
	

	LCD_GoTo(1,1);
	LCD_WriteNumWithLength(ADC_Read(DIO_A2_ANALOG),11);
	_delay_ms(200);

}
}
#endif


#ifdef TESTING_EX_INTERRUPTS		/////////////////////



volatile u8 i=0;

void myISR0(void){	 

	LED_ToggleLED(LED0);		
	i++;
	LCD_GoTo(1,4);
	LCD_WriteInt(i);
}


int main(){

	LCD_Init();

	LED_InitLED(LED0);
	LED_InitLED(LED1);

	EX_Int0_D2_Init(EX_INT0_RISING);
	EX_Int0_D2_SetCallBack(myISR0);

	

while (1){
	LED_ToggleLED(LED1); 	_delay_ms(1000);
	

}
}

#endif


#ifdef TESTING_WATCHDOG_TIMER		/////////////////////


int main(){


while(1){

}
}
#endif


#ifdef TESTING_SERVO				/////////////////////

// D7 OC2 servo

volatile u8 OVFcntr = 0, i =0;
volatile float64 angl = 60;

void OC2IntFn()
{
	if (OVFcntr == 0)
	{
		OCR2 = 0;
	}
	else if (OVFcntr == 1)
	{
		OCR2 = MAP(angl, 0, 180, 200, 231.25);
		// TCNT2 = 200;
		// OCR2 = MAP(angl, 0, 180, 200, 231.25);


	}
}

void OV2IntFn(void)
{
	if (OVFcntr == 0)
	{
		OVFcntr = 1;
		// TCNT2 = 0x00;
	}
	else if (OVFcntr == 1)
	{
		TCNT2 = 200;
		OVFcntr = 0;
		OCR2 = MAP(angl, 0, 180, 200, 231.25);
	}
}

int main()
{
	volatile u8 tempOCR=0, tempTCNT=0;
	LCD_Init();
	LCD_GoTo(1,2);
	// LCD_WriteInt(i);
	
	DIO_PinMode (DIO_D7,OUTPUT);
	
	// _delay_ms(1000);
	// Timer_2_INIT_With_OCV(FAST,OCV_2_Clear,MAP(angl,    0, 180,    200, 231.25));

	// TCNT2 = 200;     //Not affecting


	// SET_BIT(TCCR2,CS20);
	// SET_BIT(TCCR2,CS21);
	// SET_BIT(TCCR2,CS22);
	
	Timers_T2_IntOverFlowEnable();
	Timers_T2_IntCompMtchEnable();

	Timers_T2_IntOverFlowSetCallBack(OV2IntFn);
	Timers_T2_IntCompMtchSetCallBack(OC2IntFn);
	Timers_T2_Init(TIMERS_T2_CLK_PS_1024, TIMERS_T2_MODE_FASTPWM, TIMERS_T2_OCPIN_NON_INVERTING_MODE, MAP(angl,    0, 180,    200, 231.25));
	
	while (1)
	{	
		tempOCR = OCR2, tempTCNT=TCNT2;

		LCD_GoTo(0, 3);	LCD_WriteInt(tempTCNT);
		if (tempOCR == 0)
		{
			LCD_Clear();
			LCD_GoTo(1,1);	LCD_WriteInt(0);
		}
		else
		{
			LCD_GoTo(1,7);	LCD_WriteInt(tempOCR);
		}
		
		
		// LCD_GoTo(1,2);
		// LCD_WriteInt(i);
		// _delay_ms(100);
		i = OCR2;
		// angl = 0; _delay_ms(1000);
		// angl = 60; _delay_ms(1000);
		// angl = 120; _delay_ms(1000);
		// angl = 180; _delay_ms(1000);
	}
	


}
#endif


#ifdef TESTING_SEVEN_SEGMENTS		/////////////////////
int main(){

	SEG_Init();
	volatile u8 i=0;
while (1)
{
	SEG_Display(9876);
	// _delay_ms(1000);
	++i;
}
}
#endif


#ifdef TESTING_KEYPAD				/////////////////////
int main(){
	LCD_Init();
	KeyPad_Init();
	u8 buf =0;
while(1){
	LCD_GoTo(1,2);
	LCD_WriteData('_');
	buf = KeyPad_GetRead();
	if (buf != 0){
		LCD_WriteData(buf);
	}

}
}
#endif


#ifdef TESTING_LCD					/////////////////////
int main(){
	volatile u8 i=0;
	LCD_Init();

while (1)
{
	LCD_GoTo(1,1);
	LCD_WriteInt(i);
	_delay_ms(500);
	i++;
}
}
#endif


#ifdef TESTING_BUTTONS				/////////////////////
int main(){
while(1){

}
}
#endif


#ifdef TESTING_LEDS					/////////////////////
int main(){
	LED_InitLED(LED0);
while(1){
	LED_ToggleLED(LED0);
	_delay_ms(500);
}
}
#endif


#ifdef TESTING_DIO					/////////////////////
int main(){
while(1){

}
}
#endif


#ifdef TESTING_BIT_MATH				/////////////////////
int main(){
while(1){

}
}
#endif


#ifdef GENERAL_TEST					/////////////////////

int main(){
	
while(1){

}

}
#endif




















