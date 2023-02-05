/**
 * @author			Ahmed Farahat : @Baby-Madara ahmed.farahat1@msa.edu.eg - ahmedfarahat1177@gmail.com - +201119027639
 * @details			ATMega32 drivers for AMIT Kit with the following hardware (in the HAL layer). Using PlatformIO as IDE on VS Code
 * @date:			start date: 24-09-2022			-		completed: 	__-__-2022
 * @aknowledgement:	learned embedded systems interfacing from different instructors but special thanks for Moatasem El-Sayed & Sara Abd Rabbo
 * @datasheet:		for any technical details, refer to datasheet: https://ww1.microchip.com/downloads/en/DeviceDoc/doc2503.pdf
 * 	DIO				|
 * 	ADC 			|201
 * 	Interrupts		|
 * 	Registers Page 	||	327
 *  
 * @pinout:					          
 *                                      [PDIP]:
 *                                 __________________
 *      Btn0         (XCK/T0) PB0 |1       @       40| PA0 (ADC0)       N/C
 *      LCD_RS           (T1) PB1 |2               39| PA1 (ADC1)       Pot
 *      LCD_RW    (INT2/AIN0) PB2 |3               38| PA2 (ADC2)       Relay
 *      LCD_EN     (OC0/AIN1) PB3 |4               37| PA3 (ADC3)       Buzzer
 *      SS              (_SS) PB4 |5               36| PA4 (ADC4)       LCD_D4
 *      MOSI           (MOSI) PB5 |6               35| PA5 (ADC5)       LCD_D5
 *      MISO           (MISO) PB6 |7               34| PA6 (ADC6)       LCD_D6
 *      SCK             (SCK) PB7 |8               33| PA7 (ADC7)       LCD_D7
 *                         _RESET |9               32| AREF
 *                            VCC |10   ATMega32   31| GND
 *                            GND |11              30| AVCC
 *                          XTAL2 |12              29| PC7 (TOSC2)      LED1
 *                          XTAL1 |13              28| PC6 (TOSC1)      H_A4
 *       RX             (RXD) PD0 |14              27| PC5 (TDI)        H_A3
 *       TX             (TXD) PD1 |15              26| PC4 (TDO)        H_A2
 *       Btn2          (INT0) PD2 |16              25| PC3 (TMS)        H_A1
 *       LED2          (INT1) PD3 |17              24| PC2 (TCK)        LED0
 *       H_En1         (OC1B) PD4 |18              23| PC1 (SDA)        SDA
 *       H_En2         (OC1A) PD5 |19              22| PC0 (SCL)        SCL
 *       Btn1          (ICP1) PD6 |20              21| PD7 (OC2)        Servo
 *                                |__________________|
 *                                                                           
 *                            * (_PIN) means inverse logic
 *  
 * @sw_archeticture: 
 *     **************************************** Software Architecture ****************************************
 *     * [UTILS]    || [APP]         |                     main.c                                            *
 *     *            || [Services]    |     structs - classes - user-defined data types - ...                 *
 *     *            || [HAL]         | LEDs - Buttons - SevenSegmrnt - LCD - KeyPad - ...                    *
 *     *  STD_Types || [MCAL]        | DIO - General_Interrupts - External_Interrupts - ADC - Timers - ...   *
 *     *  BIT_MATH  || [MEM_MAPPING] |                 MCU registers                                         *
 *     *******************************************************************************************************
 *  
 * @warnings:		
 * 					-LCD and SevenSegments cannot be used together
 * 					-sevenSegments must be used with parallel programming (NO SEQUENTIAL DELAY CAN BE USED to work properly)
 * 					-
 *  
 *  
 * @main: 			IT IS USED FOR TESTING DRIVERS. THE DRIVER YOU WANT TO TEST, UNCOMMENT "#define TESTING_DRIVER_NAME" and type the codes you want in its section, this is for ensuring no loss of old trials
 * 
 */




// #include <avr/io.h>
// #include <avr/interrupt.h>
#include <util/delay.h>

#include "Memory_map/mem_map.h"
#include "UTILS/BitMath.h"
#include "UTILS/Maths.h"
#include "MCAL/DIO/DIO.h"
#include "HAL/LEDs/LEDs.h"
#include "HAL/Buttons/Buttons.h"
#include "HAL/LCD/LCD.h"
#include "HAL/KeyPad/KeyPad.h"
#include "HAL/SevenSegment/SevenSegment.h"


#include "MCAL/Ex_Interrupts/Ex_Interrupts.h"
#include "MCAL/ADC/ADC.h"
#include "MCAL/Timers/Timers.h"
#include "MCAL/WatchDog_Timer/WatchDog_Timer.h"

#include "HAL/Servo/Servo.h"

#include "MCAL/ICU/ICU.h"

#include "MCAL/SPI/SPI.h"
#include "MCAL/I2C/I2C.h"
#include "MCAL/USART/USART.h"



// ************   uncomment ONLY the line corresponding to the driver you test   ************ //
// #define TESTING_SPI
// #define TESTING_I2C
// #define TESTING_USART
// #define TESTING_ICU
// #define TESTING_WATCHDOG_TIMER
#define TESTING_TIMERS
// #define TESTING_ADC
// #define TESTING_EX_INTERRUPTS
//////
// #define TESTING_SERVO
// #define TESTING_SEVEN_SEGMENTS
// #define TESTING_KEYPAD
// #define TESTING_LCD
// #define TESTING_BUTTONS
// #define TESTING_LEDS
// #define TESTING_DIO
// #define TESTING_BIT_MATH
//////
// #define GENERAL_TEST





#ifdef TESTING_I2C				/////////////////////
int main(){
while(1){

}
}
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

TIMERS_ENABLE_T0_WATCH

int main(){

	LCD_Init();	
	// LED_InitLED(LED0);
	// LCD_GoTo(0,1); LCD_WriteInt(sizeof(u64));
	
	// Timers_T0_Init(TIMERS_T0_CLK_PS_1024, TIMERS_T0_MODE_FASTPWM, TIMERS_T0_OCPIN_NON_INVERTING_MODE, 127);
	// Timers_T0_Init(TIMERS_T0_COUNT_EXT_ON_FALLING_B0, TIMERS_T0_MODE_CTC, TIMERS_T0_OCPIN_DISCONNECT, 10);
	// Timers_T0_IntCompMtchEnable();
	
	Timers_T0_WatchInit();

while (1)
{
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
int main(){
while(1){

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




















