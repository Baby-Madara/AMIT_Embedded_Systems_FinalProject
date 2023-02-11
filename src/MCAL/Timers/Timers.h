#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "../General_Interrupts/General_Interrupts.h"

#include "../../UTILS/BitMath.h"
#include "../../UTILS/Maths.h"
#include "../../UTILS/STD_Types.h"
#include "../../Memory_map/mem_map.h"

#include <string.h>




extern void (*Timers_T0__OCfPtr)(void) ;
extern void (*Timers_T1a_OCfPtr)(void) ;
extern void (*Timers_T1b_OCfPtr)(void) ;
extern void (*Timers_T2__OCfPtr)(void) ;
extern void (*Timers_T0__OVfPtr)(void) ;
extern void (*Timers_T1a_OVfPtr)(void) ;
extern void (*Timers_T1b_OVfPtr)(void) ;
extern void (*Timers_T2__OVfPtr)(void) ;

void (*Timers_T0__OCfPtr)(void) ;
void (*Timers_T1a_OCfPtr)(void) ;
void (*Timers_T1b_OCfPtr)(void) ;
void (*Timers_T2__OCfPtr)(void) ;
void (*Timers_T0__OVfPtr)(void) ;
void (*Timers_T1a_OVfPtr)(void) ;
void (*Timers_T1b_OVfPtr)(void) ;
void (*Timers_T2__OVfPtr)(void) ;






// TCNT		Timer/Counter        Reg
// TCCR 	Timer/Counter Ctrl   Reg
// OCR		Output Compare       Reg
// TIMSK	Timer Interrupt Mask Reg
// TIFR		Timer Interrupt Flag Reg
// 

//for millis (prevents OC0 (B3 pin) from being used as a timer output pin):
// set prescaler to 64 - normal mode 
// set OCR to 250 (249?)
// compare match interrupt: 
//      ++milliSecs;
//      if(milliSecs==(4e9-1)){milliSecs =0;} 
//      if(!(milliSecs%1000)){++Secs;} 
//      if(!(Secs%60)){++minutes;}
// 


// correction: 16384 tick/ms
// 16384/64 = 256
// 
// 
// 


// for secs:
// 16 000 000 /1024 = 15'625 ticks/sec
// 15625 /256 = (61 overFlow + 9 ticks) (sec)

// for millis:
// 16'000 /64 = 249 ticks/ms
// 250 

// for micros:
// 16 000 000 / 1 = 16 ticks / us
//  = (61 overFlow + 9 ticks) (sec)


// Normal:			
// CTC: 			fOCnCTC   = fclk_I/O / ( 2 * N * (1 + OCRn)    )
// fast_PWM:		fOCnPWM   = fclk_I/O / ( N * 256 )
// PhCorrect_PWM:	fOCnPCPWM = fclk_I/O / ( N * 510 )

extern volatile u64	milliSecs,
					Secs 	 ,
					minutes	 ,
                    hours    ,
                    days     ;

volatile u64  		milliSecs ,
					Secs      ,
					minutes	  ,
                    hours     ,
                    days      ;

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



// extern void (*Timers_T0__OCfPtr)(void);
// extern void (*Timers_T1a_OCfPtr)(void);
// extern void (*Timers_T1b_OCfPtr)(void);
// extern void (*Timers_T2__OCfPtr)(void);

// extern void (*Timers_T0__OVfPtr)(void);
// extern void (*Timers_T1a_OVfPtr)(void);
// extern void (*Timers_T1b_OVfPtr)(void);
// extern void (*Timers_T2__OVfPtr)(void);



void Timers_T0_SetClkSrcandPreScaler(u8 ps);
void Timers_T0_SetMode              (u8 mode);
void Timers_T0_CompareVal           (u8 OC);
void Timers_T0_setCompareOutputMode	(u8 outputCompareMode);

void Timers_T0_Init					(u8 ps, u8 mode, u8 outputCompareMode, u8 OutputCompareVal);
void Timers_T0_Disable				();

void Timers_T0_WG__PWM_B3			(u8 outCompVal);
void Timers_T0_IntCompMtchEnable	();
void Timers_T0_IntOverFlowEnable	();
void Timers_T0_IntCompMtchDisable	();
void Timers_T0_IntOverFlowDisable	();
u8   Timers_T0_ReturnCounter    	();
void Timers_T0_ForceOutputCompare	();

void Timers_T0_IntOverFlowSetCallBack (void (*ptr)(void));
void Timers_T0_IntCompMtchSetCallBack (void (*ptr)(void));

void TIMER0_OVF_vect (void) __attribute__ ((used)) __attribute__ ((signal));

void TIMER0_COMP_vect (void) __attribute__ ((used)) __attribute__ ((signal));



void Timers_T0_WatchInit();

u64  Timers_T0_milliSecs			();
u64  Timers_T0_secs					();
u64  Timers_T0_minutes				();
u64  Timers_T0_hours				();
u64  Timers_T0_days 				();

// void (*Timers_T0__OCfPtr)(void) ;               

#define TIMERS_ENABLE_T0_WATCH                  \
void WatchUpdate(){                             \
    ++milliSecs;                                \
    if(milliSecs==((u64)4e9))   {milliSecs =0;} \
    Secs    =milliSecs/1000;                    \
    minutes =Secs     /60  ;                    \
    hours   =minutes  /60  ;                    \
    days    =hours    /24  ;                    \
}                                               \
void(*Timers_T0__OCfPtr)() = WatchUpdate;






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


// in TCCR2: [ CS22:0 ] Clock select & prescalers
#define TIMERS_T2_CLK_DISABLE	0
#define TIMERS_T2_CLK_PS_1		1
#define TIMERS_T2_CLK_PS_8		2
#define TIMERS_T2_CLK_PS_32		3
#define TIMERS_T2_CLK_PS_64		4
#define TIMERS_T2_CLK_PS_128	5
#define TIMERS_T2_CLK_PS_256	6
#define TIMERS_T2_CLK_PS_1024	7

// in TCCR2: [ WGM00 - WGM01 ]
#define TIMERS_T2_MODE_NORMAL	0
#define TIMERS_T2_MODE_PCPWM	1
#define TIMERS_T2_MODE_CTC		2	//clear timer on compare match (for wave generation)
#define TIMERS_T2_MODE_FASTPWM	3

// in TCCR2: [ COM00:1 ] Compare output modes
#define TIMERS_T2_OCPIN_DISCONNECT 			 0
#define TIMERS_T2_OCPIN_TOGGLE_ON_COMP_MTCH  1 	//doesnt work while PWM Modes
#define TIMERS_T2_OCPIN_NON_INVERTING_MODE	 2	
#define TIMERS_T2_OCPIN_INVERTING_MODE 		 3




void Timers_T2_SetPreScaler         (u8 ps);
void Timers_T2_SetMode              (u8 mode);
void Timers_T2_CompareVal           (u8 OC);
void Timers_T2_setCompareOutputMode	(u8 outputCompareMode);

void Timers_T2_Init					(u8 ps, u8 mode, u8 outputCompareMode, u8 OutputCompareVal);
void Timers_T2_Disable				();

void Timers_T2_WG__PWM_D7			(u8 outCompVal);
void Timers_T2_IntCompMtchEnable	();
void Timers_T2_IntOverFlowEnable	();
void Timers_T2_IntCompMtchDisable	();
void Timers_T2_IntOverFlowDisable	();
u8   Timers_T2_ReturnCounter    	();
void Timers_T2_ForceOutputCompare	();


void Timers_T2_IntOverFlowSetCallBack (void (*ptr)(void));
void Timers_T2_IntCompMtchSetCallBack (void (*ptr)(void));

void TIMER2_OVF_vect(void) __attribute__ ((used)) __attribute__ ((signal));
void TIMER2_COMP_vect(void) __attribute__ ((used)) __attribute__ ((signal));

// Servo: 
/*
volatile u8 OVFcntr = 0;
volatile float64 angl = 90;

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


    }
}
void OV2IntFn(void)
{
    if (OVFcntr == 0)
    {
        // OCR2 = 0;
        OVFcntr = 1;
        TCNT2 = 0x00;
    }
    else if (OVFcntr == 1)
    {
        TCNT2 = 200;
        OVFcntr = 0;
        // OCR2 = MAP(angl, 0, 180, 200, 231.25);
    }
}

int main()
{
    
    DIO_PinMode (DIO_D7,OUTPUT);
    
    Timer_2_INIT_With_OCV(FAST,OCV_2_Clear,MAP(angl,    0, 180,    200, 231.25));

    // TCNT2 = 200;     //Not affecting


    // SET_BIT(TCCR2,CS20);
    // SET_BIT(TCCR2,CS21);
    // SET_BIT(TCCR2,CS22);
    
    Timer_2_OverFlow_Int_Enable();
    Timer_2_Output_Compare_Int_Enable();

    Timer_2_OverFlow_CallBack(OV2IntFn);
    Timer_2_Output_Compare_CallBack(OC2IntFn);
    while (1)
    {
        // angl = 0; _delay_ms(1000);
        // angl = 60; _delay_ms(1000);
        // angl = 120; _delay_ms(1000);
        // angl = 180; _delay_ms(1000);
    }
    


}
*/



#endif 		//TIMER_H_INCLUDED























