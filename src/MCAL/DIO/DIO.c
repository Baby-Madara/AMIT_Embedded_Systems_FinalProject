#include "DIO.h"

void DIO_PinMode			(u8 port, u8 pin, u8 mode	){
	if(port <4){
		if(pin <8){
			switch(mode){
				case INPUT:{
					switch(port){
						case DIO_A:{	CLEAR_BIT(DDRA, pin);	CLEAR_BIT(PORTA, pin);}break;
						case DIO_B:{	CLEAR_BIT(DDRB, pin);	CLEAR_BIT(PORTB, pin);}break;
						case DIO_C:{	CLEAR_BIT(DDRC, pin);	CLEAR_BIT(PORTC, pin);}break;
						case DIO_D:{	CLEAR_BIT(DDRD, pin);	CLEAR_BIT(PORTD, pin);}break;
					}
				}break;
				case OUTPUT:{
					switch(port){
						case DIO_A:{	SET_BIT(DDRA, pin);	}break;
						case DIO_B:{	SET_BIT(DDRB, pin);	}break;
						case DIO_C:{	SET_BIT(DDRC, pin);	}break;
						case DIO_D:{	SET_BIT(DDRD, pin);	}break;
					}
				}break;
				case INPUT_PULLUP:{
					DIO_EnablePullUp();
					switch(port){
						case DIO_A:{	CLEAR_BIT(DDRA, pin);	SET_BIT(PORTA, pin);}break;
						case DIO_B:{	CLEAR_BIT(DDRB, pin);	SET_BIT(PORTB, pin);}break;
						case DIO_C:{	CLEAR_BIT(DDRC, pin);	SET_BIT(PORTC, pin);}break;
						case DIO_D:{	CLEAR_BIT(DDRD, pin);	SET_BIT(PORTD, pin);}break;
					}
				}break;
			}

		}
	}
}


void DIO_DigitalWritePin	(u8 port, u8 pin, u8 val	){
	

	switch(val){
		case LOW:{
			switch(port){
				case DIO_A:{	CLEAR_BIT(PORTA, pin);	}break;
				case DIO_B:{	CLEAR_BIT(PORTB, pin);	}break;
				case DIO_C:{	CLEAR_BIT(PORTC, pin);	}break;
				case DIO_D:{	CLEAR_BIT(PORTD, pin);	}break;

				default: break;
			}

		}break;

		case HIGH:{
			switch(port){
				case DIO_A:{	SET_BIT(PORTA, pin);	}break;
				case DIO_B:{	SET_BIT(PORTB, pin);	}break;
				case DIO_C:{	SET_BIT(PORTC, pin);	}break;
				case DIO_D:{	SET_BIT(PORTD, pin);	}break;

				default: break;
			}
		}break;

		default: break;
	}
		
}


void DIO_DigitalTogglePin	(u8 port, u8 pin			){
	if(port<4){
		if(pin<8){

			switch(port){
				case DIO_A:{	TOGGLE_BIT(PORTA, pin);	}break;
				case DIO_B:{	TOGGLE_BIT(PORTB, pin);	}break;
				case DIO_C:{	TOGGLE_BIT(PORTC, pin);	}break;
				case DIO_D:{	TOGGLE_BIT(PORTD, pin);	}break;
				default: return;
			}

		}
	}
}



u8   DIO_DigitalReadPin		(u8 port, u8 pin		){
	volatile bool val=0;
	switch(port){
		case DIO_A:{	val=	GET_BIT(PINA, pin);	}break;
		case DIO_B:{	val=	GET_BIT(PINB, pin);	}break;
		case DIO_C:{	val=	GET_BIT(PINC, pin);	}break;
		case DIO_D:{	val=	GET_BIT(PIND, pin);	}break;
		default: break;
	}

	
	
	return val;
}



u8   DIO_ReturnOutputValue	(u8 port, u8 pin		){
	volatile u8 val;
	switch (port){
		case DIO_A: {	val= 	GET_BIT(PORTA, pin); }break;
		case DIO_B: {	val= 	GET_BIT(PORTB, pin); }break;
		case DIO_C: {	val= 	GET_BIT(PORTC, pin); }break;
		case DIO_D: {	val= 	GET_BIT(PORTD, pin); }break;
	}
	return val;

}



// ************************************************************************ //



void DIO_PortMode			(u8 port, u8 mode		){
	switch (mode)
	{
		case OUTPUT:	switch (port)
		{
			case DIO_A:		DDRA = 0xFF;	break;
			case DIO_B:		DDRB = 0xFF;	break;
			case DIO_C:		DDRC = 0xFF;	break;
			case DIO_D:		DDRD = 0xFF;	break;
			default:	break;

		} break;

		case  INPUT:	switch (port)
		{
			case DIO_A:		DDRA = 0x00;	break;
			case DIO_B:		DDRB = 0x00;	break;
			case DIO_C:		DDRC = 0x00;	break;
			case DIO_D:		DDRD = 0x00;	break;
			default:	break;

		} break;

		default:		break;
	}

}

void DIO_DigitalWritePort	(u8 port, u8 val		){
	switch (port)
	{
		case DIO_A:		PORTA = val;	break;
		case DIO_B:		PORTB = val;	break;
		case DIO_C:		PORTC = val;	break;
		case DIO_D:		PORTD = val;	break;
		
		default:		break;
	}


}

void DIO_DigitalTogglePort	(u8 port				){
	switch (port)
	{
		case DIO_A:		TOGGLE_REG(PORTA);	break;
		case DIO_B:		TOGGLE_REG(PORTB);	break;
		case DIO_C:		TOGGLE_REG(PORTC);	break;
		case DIO_D:		TOGGLE_REG(PORTD);	break;
		
		default:		break;
	}
}

u8   DIO_DigitalReadPort		(u8 port			){
	volatile u8 val;

	switch (port)
	{
		case DIO_A:		val = PINA;	break;
		case DIO_B:		val = PINB;	break;
		case DIO_C:		val = PINC;	break;
		case DIO_D:		val = PIND;	break;
		
		default:		break;
	}
	return val;

}


void DIO_DisablePullUp		(void){
	SET_BIT(SFIOR, PUD);
}

void DIO_EnablePullUp		(void){
	CLEAR_BIT(SFIOR, PUD);
}



