#include "ADC.h"


void (*ADC_Int_fptr)(void) = NULLptr;


void ADC_Init(u8 ps){
	ADC_Enable();
	
	// CLEAR_BIT(SFIOR, 4);		//WUUUTS THAT?!
	
	// setting prescalar to 128:
	ADC_SetPreScaler(ps);
	
	ADC_SetReference(ADC_REF_AVCC);




}

u16 ADC_Read(u8 chanel){
	static volatile u8 prevChanel = 0;
	volatile u16 read =0;

	CLEAR_BIT(DDRA,  chanel);
	CLEAR_BIT(PORTA, chanel);
	
	
	// choosing channel
	WRITE_BIT(ADMUX, MUX0, 		GET_BIT(chanel, 0)	);
	WRITE_BIT(ADMUX, MUX1, 		GET_BIT(chanel, 1)	);
	WRITE_BIT(ADMUX, MUX2, 		GET_BIT(chanel, 2)	);
	WRITE_BIT(ADMUX, MUX3, 		GET_BIT(chanel, 3)	);
	WRITE_BIT(ADMUX, MUX4, 		GET_BIT(chanel, 4)	);

	// if ADC was running on a previously selected chanel, wait till it it finishes (ADIF=1), clear ADIF, and set the prevChanel to the current one, then you can continue normally
	if( (GET_BIT(ADCSRA,ADSC) == HIGH) && (prevChanel != chanel)){
		prevChanel=chanel;
		if(	!GET_BIT(ADCSRA, ADIE) ){
			while(!GET_BIT(ADCSRA, ADIF))	;		//wait
			SET_BIT(ADCSRA, ADIF);					//clear Interrupt flag by writing 1}
		}
	}

	SET_BIT(ADCSRA,ADSC);   				//Start Conversion
	if(	!GET_BIT(ADCSRA, ADIE) ){
		while(!GET_BIT(ADCSRA, ADIF))	;		//wait
		SET_BIT(ADCSRA, ADIF);					//clear Interrupt flag by writing 1
	}

	// reading value
	read 	= ((ADCL) | ((u16)ADCH <<8));
	// read	= (((u16)ADCH <<8) | (ADCL));	//YOU CANT DO THAT BECAUSE DATA WILL NOT BE UPDATED AGAIN!!!

	return read;

}







void ADC_SetReference	(	u8 ref){
	WRITE_BIT(ADMUX, REFS0, GET_BIT(ref,0));
	WRITE_BIT(ADMUX, REFS1, GET_BIT(ref,1));

}

void ADC_SetPreScaler	(	u8 ps){
	WRITE_BIT(ADCSRA, ADPS0, GET_BIT(ps, 0) );
	WRITE_BIT(ADCSRA, ADPS1, GET_BIT(ps, 1) );
	WRITE_BIT(ADCSRA, ADPS2, GET_BIT(ps, 2) );

}


void ADC_Enable			(	void){
	SET_BIT(ADCSRA, ADEN);

}

void ADC_Disable		(	void){
	CLEAR_BIT(ADCSRA, ADEN);		//if ADEN is cleared, ADC will ot consume power

}




void ADC_setValueLeftAdj(void){
	SET_BIT(ADMUX, ADLAR);
}

void ADC_setValueRightAdj(void){
	CLEAR_BIT(ADMUX, ADLAR);
}

void ADC_EnableAutoTrigger(){
	SET_BIT(ADCSRA, ADATE);
}

void ADC_DisableAutoTrigger(){
	CLEAR_BIT(ADCSRA, ADATE);
}

void ADC_IntEnable		(	void	){
	GI_Enable();
	SET_BIT(ADCSRA, ADIE);
}

void ADC_IntDisable		(	void	){
	CLEAR_BIT(ADCSRA, ADIE);
}

void ADC_IntSetCallBack	(	void(*IntPtr)(void)	){
	ADC_Int_fptr = IntPtr;
}


ISR(ADC_vect){
	CLEAR_BIT(ADCSRA, ADIE);
	SET_BIT(ADCSRA, ADIF);
	ADC_Int_fptr();
	ADC_IntEnable();
}

