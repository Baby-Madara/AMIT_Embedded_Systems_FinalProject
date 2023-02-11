#include "Timers.h"









// ***************************  Timer0  *************************** //

void Timers_T0_SetClkSrcandPreScaler(u8 ps){
	// ps (Clk Src):
	if((ps == TIMERS_T0_COUNT_EXT_ON_FALLING_B0) || (ps == TIMERS_T0_COUNT_EXT_ON_RISING_B0)){
		CLEAR_BIT(DDRB, PIN_0);
		CLEAR_BIT(PORTB, PIN_0);
	}
	WRITE_BIT(TCCR0, CS02	,	GET_BIT(ps, 2)	),	
	WRITE_BIT(TCCR0, CS01	,	GET_BIT(ps, 1)	),
	WRITE_BIT(TCCR0, CS00	,	GET_BIT(ps, 0)	);

}
void Timers_T0_SetMode              (u8 mode){
	// Wave Generation mode WGM0n
	WRITE_BIT(TCCR0, WGM01	,	GET_BIT(mode, 1)	),
	WRITE_BIT(TCCR0, WGM00	,	GET_BIT(mode, 0)	);

}
void Timers_T0_CompareVal           (u8 OutputCompareVal){
	OCR0 = OutputCompareVal;

}
void Timers_T0_setCompareOutputMode	(u8 outputCompareMode){
	// Compare Output Mode COM
	if( outputCompareMode != TIMERS_T0_OCPIN_DISCONNECT ){		SET_BIT(DDRB, PIN_3);	}
	WRITE_BIT(TCCR0, COM01	,	GET_BIT(outputCompareMode, 1)	),
	WRITE_BIT(TCCR0, COM00	,	GET_BIT(outputCompareMode, 0)	);

}

void Timers_T0_Init					(u8 ps, u8 mode, u8 outputCompareMode, u8 OutputCompareVal){
	// ps (Clk Src):
	Timers_T0_SetClkSrcandPreScaler(ps);

	// Wave Generation mode WGM0n
	Timers_T0_SetMode(mode);

	// Compare Output Mode COM
	Timers_T0_setCompareOutputMode(outputCompareMode);

	// set CompareVal
	Timers_T0_CompareVal(OutputCompareVal);
}

void Timers_T0_Disable				(){
	CLEAR_BIT(TCCR0, CS02);
	CLEAR_BIT(TCCR0, CS01);
	CLEAR_BIT(TCCR0, CS00);
}

void Timers_T0_WG__PWM_B3			(u8 outCompVal){	OCR0 = outCompVal;	}

// Normal:			
// CTC: 			fOCnCTC   = fclk_I/O / ( 2*N * (1+OCRn) )
// fast_PWM:		fOCnPWM   = fclk_I/O / ( N   * 256      )
// PhCorrect_PWM:	fOCnPCPWM = fclk_I/O / ( N   * 510      )


void Timers_T0_IntCompMtchEnable	(){
	GI_Enable();
	SET_BIT(TIFR, OCF0);  
	SET_BIT(TIMSK, OCIE0);
}

void Timers_T0_IntOverFlowEnable	(){
	GI_Enable();
	SET_BIT(TIFR, TOV0);  
	SET_BIT(TIMSK, TOIE0);
}

void Timers_T0_IntCompMtchDisable	(){	CLEAR_BIT(TIMSK, OCIE0);	}
void Timers_T0_IntOverFlowDisable	(){	CLEAR_BIT(TIMSK, TOIE0);	}
u8   Timers_T0_ReturnCounter		(){	return TCNT0;	}

void Timers_T0_ForceOutputCompare	(){ //doesnt generate interrupt
	//can be used if WG mode is a non-PWM mode
	SET_BIT(TCCR0, FOC0);
}


// timer0 application (watch)
void Timers_T0_WatchInit(){
	Timers_T0_Init(TIMERS_T0_CLK_PS_64,TIMERS_T0_MODE_CTC, TIMERS_T0_OCPIN_DISCONNECT, 249);
	Timers_T0_IntCompMtchEnable();
}


u64  Timers_T0_milliSecs	(){	return milliSecs;	}
u64  Timers_T0_secs			(){	return Secs;		}
u64  Timers_T0_minutes		(){	return minutes;		}
u64  Timers_T0_hours		(){ return hours;		}
u64  Timers_T0_days 		(){ return days;		}

void TIMER0_OVF_vect(){
    Timers_T0__OVfPtr();
}

void TIMER0_COMP_vect(){
	Timers_T0__OCfPtr();

}


// ***************************  Timer1  *************************** //

// ***************************  Timer2  *************************** //


// timer2 application (servo)

void Timers_T2_SetPreScaler(u8 ps){
	WRITE_BIT(TCCR2, CS22	,	GET_BIT(ps, 2)	),	
	WRITE_BIT(TCCR2, CS21	,	GET_BIT(ps, 1)	),
	WRITE_BIT(TCCR2, CS20	,	GET_BIT(ps, 0)	);
}
void Timers_T2_SetMode              (u8 mode){
	// Wave Generation mode WGM0n
	WRITE_BIT(TCCR2, WGM21	,	GET_BIT(mode, 1)	),
	WRITE_BIT(TCCR2, WGM20	,	GET_BIT(mode, 0)	);
}
void Timers_T2_CompareVal           (u8 OC){
	OCR2 = OC;

}
void Timers_T2_setCompareOutputMode	(u8 outputCompareMode){
	// Compare Output Mode COM
	if( outputCompareMode != TIMERS_T2_OCPIN_DISCONNECT ){		SET_BIT(DDRD, PIN_7);	}
	WRITE_BIT(TCCR2, COM21	,	GET_BIT(outputCompareMode, 1)	),
	WRITE_BIT(TCCR2, COM20	,	GET_BIT(outputCompareMode, 0)	);

}

void Timers_T2_Init					(u8 ps, u8 mode, u8 outputCompareMode, u8 OutputCompareVal){
	Timers_T2_SetPreScaler(ps);
	Timers_T2_SetMode(mode);
	Timers_T2_setCompareOutputMode(outputCompareMode);
	Timers_T2_CompareVal(OutputCompareVal);

}

void Timers_T2_Disable				(){
	Timers_T2_SetPreScaler(TIMERS_T2_CLK_DISABLE);
}

void Timers_T2_WG__PWM_D7			(u8 outCompVal){
	OCR2 = outCompVal;
}

void Timers_T2_IntCompMtchEnable	(){
	GI_Enable();
	SET_BIT(TIFR, OCF2);
	SET_BIT(TIMSK,OCIE2);
	
}

void Timers_T2_IntOverFlowEnable	(){
	GI_Enable();
	SET_BIT(TIFR, TOV2);
	SET_BIT(TIMSK,TOIE2);
	
}

void Timers_T2_IntCompMtchDisable	(){
	CLEAR_BIT(TIMSK,OCIE2);
	
}

void Timers_T2_IntOverFlowDisable	(){
	CLEAR_BIT(TIMSK,TOIE2);
	
}

u8   Timers_T2_ReturnCounter    	(){
	return TCNT2;
}

void Timers_T2_ForceOutputCompare	(){
	SET_BIT(TCCR2, FOC2);

}





void Timers_T2_IntOverFlowSetCallBack (void (*ptr)(void)){
	Timers_T2__OVfPtr = ptr;
}
void Timers_T2_IntCompMtchSetCallBack (void (*ptr)(void)){
	Timers_T2__OCfPtr = ptr;
}





void TIMER2_OVF_vect(){
    Timers_T2__OVfPtr();
}

void TIMER2_COMP_vect(){
	Timers_T2__OCfPtr();

}




