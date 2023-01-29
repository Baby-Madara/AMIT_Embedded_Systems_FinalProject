#include "SevenSegment.h"


#ifdef AMIT_KIT

void SEG_Init(){
	DIO_PinMode	(SEG_A,		OUTPUT);
	DIO_PinMode	(SEG_B,		OUTPUT);
	DIO_PinMode	(SEG_C,		OUTPUT);
	DIO_PinMode	(SEG_D,		OUTPUT);

	DIO_PinMode	(SEG_DOT,	OUTPUT);
	DIO_PinMode	(SEG_En1,	OUTPUT);
	DIO_PinMode	(SEG_En2,	OUTPUT);

}


void SEG_Display(u16 num){
	volatile u8 units = num%10,
				tens  = (u8)num/(u8)10;

	if((num>=0) && (num <100)){
		//En1 is for tens
		DIO_DigitalWritePin(SEG_A,			(GET_BIT(tens, 0))	 );
		DIO_DigitalWritePin(SEG_B,			(GET_BIT(tens, 1))	 );
		DIO_DigitalWritePin(SEG_C,			(GET_BIT(tens, 2))	 );
		DIO_DigitalWritePin(SEG_D,			(GET_BIT(tens, 3))	 );
		DIO_DigitalWritePin(SEG_En1, 	HIGH);	_delay_ms(2);	;
		DIO_DigitalWritePin(SEG_En1, 	LOW);

		//En2 is for units
		DIO_DigitalWritePin(SEG_A,			(GET_BIT(units, 0))	 );
		DIO_DigitalWritePin(SEG_B,			(GET_BIT(units, 1))	 );
		DIO_DigitalWritePin(SEG_C,			(GET_BIT(units, 2))	 );
		DIO_DigitalWritePin(SEG_D,			(GET_BIT(units, 3))	 );
		DIO_DigitalWritePin(SEG_En2, 	HIGH);	_delay_ms(2);	;
		DIO_DigitalWritePin(SEG_En2, 	LOW);
	}
}

#endif




#ifdef FARES_KIT

void SEG_Init(){
	DIO_PinMode	(SEG_A,		OUTPUT);
	DIO_PinMode	(SEG_B,		OUTPUT);
	DIO_PinMode	(SEG_C,		OUTPUT);
	DIO_PinMode	(SEG_D,		OUTPUT);

	DIO_PinMode	(SEG_En1,	OUTPUT);
	DIO_PinMode	(SEG_En2,	OUTPUT);
	DIO_PinMode	(SEG_En3,	OUTPUT);
	DIO_PinMode	(SEG_En4,	OUTPUT);

}


void SEG_Display(u16 num){
	volatile u16 	units       = num         % 10,
					tens        = (num / 10)   %10,
					hundreds    = (num / 100)  %10,
					thousands   = (num / 1000) %10
					;

	if((num>=0) && (num <10000)){
		//En3 is for tens
		DIO_DigitalWritePin(SEG_A,			(!GET_BIT(thousands, 	0))	 );
		DIO_DigitalWritePin(SEG_B,			(!GET_BIT(thousands, 	1))	 );
		DIO_DigitalWritePin(SEG_C,			(!GET_BIT(thousands, 	2))	 );
		DIO_DigitalWritePin(SEG_D,			(!GET_BIT(thousands, 	3))	 );
		DIO_DigitalWritePin(SEG_En1, 	!HIGH);	_delay_ms(2);
		DIO_DigitalWritePin(SEG_En1, 	!LOW);
		//En2 is for tens
		DIO_DigitalWritePin(SEG_A,			(!GET_BIT(hundreds, 	0))	 	);
		DIO_DigitalWritePin(SEG_B,			(!GET_BIT(hundreds, 	1))	 	);
		DIO_DigitalWritePin(SEG_C,			(!GET_BIT(hundreds, 	2))	 	);
		DIO_DigitalWritePin(SEG_D,			(!GET_BIT(hundreds, 	3))	 	);
		DIO_DigitalWritePin(SEG_En2, 	!HIGH);	_delay_ms(2);
		DIO_DigitalWritePin(SEG_En2, 	!LOW);
		//En1 is for tens
		DIO_DigitalWritePin(SEG_A,			(!GET_BIT(tens, 		0))	 		);
		DIO_DigitalWritePin(SEG_B,			(!GET_BIT(tens, 		1))	 		);
		DIO_DigitalWritePin(SEG_C,			(!GET_BIT(tens, 		2))	 		);
		DIO_DigitalWritePin(SEG_D,			(!GET_BIT(tens, 		3))	 		);
		DIO_DigitalWritePin(SEG_En3, 	!HIGH);	_delay_ms(2);
		DIO_DigitalWritePin(SEG_En3, 	!LOW);

		//En0 is for units
		DIO_DigitalWritePin(SEG_A,			(!GET_BIT(units, 		0))	 	);
		DIO_DigitalWritePin(SEG_B,			(!GET_BIT(units, 		1))	 	);
		DIO_DigitalWritePin(SEG_C,			(!GET_BIT(units, 		2))	 	);
		DIO_DigitalWritePin(SEG_D,			(!GET_BIT(units, 		3))	 	);
		DIO_DigitalWritePin(SEG_En4, 	!HIGH);	_delay_ms(2);
		DIO_DigitalWritePin(SEG_En4, 	!LOW);
	}
}

#endif





