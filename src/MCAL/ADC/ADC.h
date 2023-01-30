#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

/**
 * ADCSRA : ADC Control and Status Register A
 *   ADSC   : ADC Start Conversion
 *   ADATE  : ADC Auto Trigger Enable
 *   ADIF   : ADC Interrupt Flag
 *   ADIE   : ADC Interrupt Enable
 *   ADPS2:0: ADC Prescaler Select Bits
 * 
 * 
 * 
 * 
*/








#include "../General_Interrupts/General_Interrupts.h"

#include "../../UTILS/BitMath.h"
#include "../../UTILS/STD_Types.h"
#include "../../Memory_map/mem_map.h"


#define ADC_CH0 		0
#define ADC_CH1 		1
#define ADC_CH2 		2
#define ADC_CH3 		3
#define ADC_CH4 		4
#define ADC_CH5 		5
#define ADC_CH6 		6
#define ADC_CH7 		7

#define ADC_CHGAIN_P0N0G10  	8
#define ADC_CHGAIN_P1N0G10  	9
#define ADC_CHGAIN_P0N0G200 	10
#define ADC_CHGAIN_P1N0G200 	11
#define ADC_CHGAIN_P2N2G10  	12
#define ADC_CHGAIN_P3N2G10  	13
#define ADC_CHGAIN_P2N2G200 	14
#define ADC_CHGAIN_P3N2G200 	15
#define ADC_CHGAIN_P0N1G1   	16
#define ADC_CHGAIN_P1N1G1   	17
#define ADC_CHGAIN_P2N1G1   	18
#define ADC_CHGAIN_P3N1G1   	19
#define ADC_CHGAIN_P4N1G1   	20
#define ADC_CHGAIN_P5N1G1   	21
#define ADC_CHGAIN_P6N1G1   	22
#define ADC_CHGAIN_P7N1G1   	23
#define ADC_CHGAIN_P0N2G1   	24
#define ADC_CHGAIN_P1N2G1   	25
#define ADC_CHGAIN_P2N2G1   	26
#define ADC_CHGAIN_P3N2G1   	27
#define ADC_CHGAIN_P4N2G1   	28
#define ADC_CHGAIN_P5N2G1   	29
#define ADC_VBANDGAP_1_22  	30
#define ADC_GND   			31

#define ADC_CLK_PS_2_0 	0
#define ADC_CLK_PS_2_1 	1
#define ADC_CLK_PS_4 	2
#define ADC_CLK_PS_8 	3
#define ADC_CLK_PS_16 	4
#define ADC_CLK_PS_32 	5
#define ADC_CLK_PS_64 	6
#define ADC_CLK_PS_128 	7

#define ADC_REF_AREF 			0 	//AREF pin
#define ADC_REF_AVCC 			1 	//AVCC           with external capacitor at AREF pin
#define ADC_REF_2_56_INTERNAL 	3 	//internal 2.56V with external capacitor at AREF pin

#define ADC_AUTO_TRIG_SRC_FREERUN                0
#define ADC_AUTO_TRIG_SRC_ANALOGCOMP             1
#define ADC_AUTO_TRIG_SRC_EX_INT0                2
#define ADC_AUTO_TRIG_SRC_TIMER0_COMP_MATCH      3
#define ADC_AUTO_TRIG_SRC_TIMER0_OVERFLOW        4
#define ADC_AUTO_TRIG_SRC_TIMER_COMP_MATCH_B     5
#define ADC_AUTO_TRIG_SRC_TIMER1_OVERFLOW        6
#define ADC_AUTO_TRIG_SRC_TIMER1_COMP_MATCH      7



void ADC_Init			(	u8 ps);
void ADC_SetReference	(	u8 ref);
void ADC_SetPreScaler	(	u8 ps);

void ADC_Enable			(	void);
void ADC_Disable		(	void);


u16  ADC_Read			(	u8 chanel);

void ADC_IntEnable		(	void);
void ADC_IntDisable		(	void);
void ADC_IntSetCallBack	(	void(*IntPtr)(void));


void ADC_setValueLeftAdj(void);
void ADC_setValueRightAdj(void);

// ADC Auto trigger doesn't work properly when reading from different chanels!
void ADC_EnableAutoTrigger();
void ADC_DisableAutoTrigger();
void ADC_TriggeringSource(u8 src);

void ADC_IntEnable		(	void	);
void ADC_IntDisable		(	void	);
void ADC_IntSetCallBack	(	void(*IntPtr)(void)	);

#endif // ADC_H_INCLUDED