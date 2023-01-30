#include "Ex_Interrupts.h"


void (*EXT0ptr) (void) =NULLptr;
void (*EXT1ptr) (void) =NULLptr;
void (*EXT2ptr) (void) =NULLptr;


// **********************		EX_Int0 		********************** //

//setting interrupt sensing pin (D2) as input
void EX_Int0_D2_Init		(u8 signalMode){
	CLEAR_BIT(DDRD,  PIND2);
	CLEAR_BIT(PORTD, PIND2);

	CLEAR_BIT(GICR, INT0);
	EX_Int0_D2_SignalMode(signalMode);

	SET_BIT(GIFR, INTF0);			//clearing flag by writing 1 in it
	EX_Int0_D2_Enable();

}

void EX_Int0_D2_Enable		(void){
	GI_Enable();
	SET_BIT(GICR, INT0);
}

void EX_Int0_D2_Disable	(void){		CLEAR_BIT(GICR, INT0);	}

void EX_Int0_D2_ClearFlag	(void){	//cleared by 1, it is automatically cleared after ISR is finished but making functions anyway
	SET_BIT(GIFR, INTF0);		//cleared by 1, it is automatically cleared after ISR is finished but making functions anyway
}

void EX_Int0_D2_SignalMode	(u8 signalMode){
	if ((signalMode>=0) && (signalMode <4)){		
		WRITE_BIT(MCUCR, ISC01, GET_BIT(signalMode, 1));
		WRITE_BIT(MCUCR, ISC00, GET_BIT(signalMode, 0));
	}
}

void EX_Int0_D2_SetCallBack( void(*ptrFn)(void) ){
	if(ptrFn != NULLptr){		EXT0ptr = ptrFn;		}
}

void INT0_vect			(void){
	CLEAR_BIT(GICR, INT0);
	EXT0ptr();
	EX_Int0_D2_Enable();

}	












// **********************		EX_Int1 		********************** //

//setting interrupt sensing pin (D3) as input
void EX_Int1_D3_Init		(u8 signalMode){
	CLEAR_BIT(DDRD,  PIND3);
	CLEAR_BIT(PORTD, PIND3);

	CLEAR_BIT(GICR, INT1);
	EX_Int1_D3_SignalMode(signalMode);

	SET_BIT(GIFR, INTF1);			//clearing flag by writing 1 in it
	EX_Int1_D3_Enable();

}

void EX_Int1_D3_Enable		(void){
	GI_Enable();
	SET_BIT(GICR, INT1);
}

void EX_Int1_D3_Disable	(void){
	CLEAR_BIT(GICR, INT1);
}

void EX_Int1_D3_ClearFlag	(void){	//cleared by 1, it is automatically cleared after ISR is finished but making functions anyway
	SET_BIT(GIFR, INTF1);		//cleared by 1, it is automatically cleared after ISR is finished but making functions anyway
}

void EX_Int1_D3_SignalMode	(u8 signalMode){
	if ((signalMode>=0) && (signalMode <4)){		
		WRITE_BIT(MCUCR, ISC11, GET_BIT(signalMode, 1));
		WRITE_BIT(MCUCR, ISC10, GET_BIT(signalMode, 0));
	}
}


void EX_Int1_D3_SetCallBack( void(*ptrFn)(void) ){
	if(ptrFn != NULLptr){		EXT1ptr = ptrFn;		}
}

void INT1_vect			(void){
	CLEAR_BIT(GICR, INT1);
	EXT1ptr();
	SET_BIT(GICR, INT1);
}	









// **********************		EX_Int2 		********************** //

//setting interrupt sensing pin (B2) as input
void EX_Int2_B2_Init		(u8 signalMode){
	CLEAR_BIT(DDRB,  PIND2);
	CLEAR_BIT(PORTB, PIND2);

	CLEAR_BIT(GICR, INT2);
	EX_Int2_B2_SignalMode(signalMode);

	SET_BIT(GIFR, INTF2);			//clearing flag by writing 1 in it
	EX_Int2_B2_Enable();

}

void EX_Int2_B2_Enable		(void){
	GI_Enable();
	SET_BIT(GICR, INT2);
}

void EX_Int2_B2_Disable	(void){
	CLEAR_BIT(GICR, INT2);
}

void EX_Int2_B2_ClearFlag	(void){	//cleared by 1, it is automatically cleared after ISR is finished but making functions anyway
	SET_BIT(GIFR, INTF2);		//cleared by 1, it is automatically cleared after ISR is finished but making functions anyway
}

void EX_Int2_B2_SignalMode	(u8 signalMode){
	if ((signalMode>=0) && (signalMode <2)){		
		WRITE_BIT(MCUCSR, ISC2, GET_BIT(signalMode, 0));
	}
}



void EX_Int2_B2_SetCallBack( void(*ptrFn)(void) ){
	if(ptrFn != NULLptr){		EXT2ptr = ptrFn;		}
}

void INT2_vect			(void){
	CLEAR_BIT(GICR, INT2);
	EXT1ptr();
	SET_BIT(GICR, INT2);
}	










