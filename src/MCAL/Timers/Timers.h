#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "../General_Interrupts/General_Interrupts.h"

#include "../../UTILS/BitMath.h"
#include "../../UTILS/STD_Types.h"
#include "../../Memory_map/mem_map.h"



// TCNT		Timer/Counter        Reg
// TCCR 	Timer/Counter Ctrl   Reg
// OCR		Output Compare       Reg
// TIMSK	Timer Interrupt Mask Reg
// TIFR		Timer Interrupt Flag Reg
// 

// Normal:			
// CTC: 			fOCnCTC   = fclk_I/O / ( 2 * N * (1 + OCRn)    )
// fast_PWM:		fOCnPWM   = fclk_I/O / ( N * 256 )
// PhCorrect_PWM:	fOCnPCPWM = fclk_I/O / ( N * 510 )


// ***************************  Timer0  *************************** //

// in TCCR0: [ CS02:0 ] Clock select & prescalers
#define TIMERS_T0_CLK_DISABLE				0
#define TIMERS_T0_CLK_PS_1					1
#define TIMERS_T0_CLK_PS_8					2
#define TIMERS_T0_CLK_PS_64					3
#define TIMERS_T0_CLK_PS_256				4
#define TIMERS_T0_CLK_PS_1024				5
#define TIMERS_T0_COUNT_EXT_ON_FALLING_B0	6
#define TIMERS_T0_COUNT_EXT_ON_RISING_B0	7

// in TCCR0: [ WGM00 - WGM01 ]
#define TIMERS_T0_MODE_NORMAL	0
#define TIMERS_T0_MODE_PCPWM	1
#define TIMERS_T0_MODE_CTC		2	//clear timer on compare match (for wave generation)
#define TIMERS_T0_MODE_FASTPWM	3

// in TCCR0: [ COM00:1 ] Compare output modes
#define TIMERS_T0_OCPIN_DISCONNECT 				0
#define TIMERS_T0_OCPIN_TOGGLE_ON_COMP_MTCH 	1 	//doesnt work while PWM Modes
#define TIMERS_T0_OCPIN_NON_INVERTING_MODE		2	
#define TIMERS_T0_OCPIN_INVERTING_MODE 			3



extern void (*Timers_T0__OCfPtr)(void);
extern void (*Timers_T1a_OCfPtr)(void);
extern void (*Timers_T1b_OCfPtr)(void);
extern void (*Timers_T2__OCfPtr)(void);

extern void (*Timers_T0__OVfPtr)(void);
extern void (*Timers_T1a_OVfPtr)(void);
extern void (*Timers_T1b_OVfPtr)(void);
extern void (*Timers_T2__OVfPtr)(void);



void Timers_T0_Init					(u8 ps, u8 mode, u8 outputCompareMode, u8 OutputCompareVal);
void Timers_T0_Disable				();
void Timers_T0_WG__PWM_B3			(u8 outCompVal);
void Timers_T0_IntCompMtchEnable	();
void Timers_T0_IntOverFlowEnable	();
void Timers_T0_IntCompMtchDisable	();
void Timers_T0_IntOverFlowDisable	();
u8   Timers_T0_ReturnCurrentTime	();
void Timers_T0_ForceOutputCompare	();



// ***************************  Timer1  *************************** //
void Timers_T1_Init				(u8 ps);
void Timers_T1_Disable			();
void Timers_T1_SetPreScaler		(u8 ps);
void Timers_T1_SetCallBack		(void (*ptr)(void));
void Timers_T1_Mode				(u8 mode);
void Timers_T1_IntEnable		();
void Timers_T1_IntDisable		();
u16  Timers_T1_ReturnCurrentTime();
void Timers_T1_FastPWM1aD5		(u16 onTime, 	u16 periodicTime, u8 ps);
void Timers_T1_phCorrectPWM1aD5	(u16 onTime, 	u16 periodicTime, u8 ps);
void Timers_T1_waveGenerate1aD5	(u16 freq, 		u8 ps);
void Timers_T1_FastPWM1bD4		(u16 onTime, 	u16 periodicTime, u8 ps);
void Timers_T1_phCorrectPWM1bD4	(u16 onTime, 	u16 periodicTime, u8 ps);
void Timers_T1_waveGenerate1bD4	(u16 freq, 		u8 ps);



// ***************************  Timer2  *************************** //
void Timers_T2_Init				(u8 ps);
void Timers_T2_Disable			();
void Timers_T2_SetPreScaler		(u8 ps);
void Timers_T2_SetCallBack		(void (*ptr)(void));
void Timers_T2_Mode				(u8 mode);
void Timers_T2_IntEnable		();
void Timers_T2_IntDisable		();
u8   Timers_T2_ReturnCurrentTime();
void Timers_T2_FastPWMD7		(u16 onTime, 	u16 periodicTime, u8 ps);
void Timers_T2_phCorrectPWMD7	(u16 onTime, 	u16 periodicTime, u8 ps);
void Timers_T2_waveGenerateD7	(u16 freq, 		u8 ps);












#endif 		//TIMER_H_INCLUDED























