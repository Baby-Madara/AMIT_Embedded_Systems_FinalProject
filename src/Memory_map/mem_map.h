#ifndef MEMORY_MAP_H_INCLUDED
#define MEMORY_MAP_H_INCLUDED
#include "../UTILS/STD_Types.h"


#define Bit7	7
#define Bit6	6
#define Bit5	5
#define Bit4	4
#define Bit3	3
#define Bit2	2
#define Bit1	1
#define Bit0	0

#define PIN_0	0
#define PIN_1	1
#define PIN_2	2
#define PIN_3	3
#define PIN_4	4
#define PIN_5	5
#define PIN_6	6
#define PIN_7	7


#define SREG	(*(volatile u8*)0x5F) 	 			// page 10
#define SREG_I	7	 	
#define SREG_T	6 		
#define SREG_H	5 		
#define SREG_S	4 		
#define SREG_V	3 		
#define SREG_N	2 		
#define SREG_Z	1 		
#define SREG_C	0 			

#define SPH		(*(volatile u8*)0x5E) 		 		// page 12
#define SP11	3
#define SP10	2
#define SP9		1
#define SP8		0


#define SPL		(*(volatile u8*)0x5D) 				//12 	
#define SP7		7
#define SP6		6
#define SP5		5
#define SP4		4
#define SP3		3
#define SP2		2
#define SP1		1
#define SP0		0


#define OCR0	(*(volatile u8*)0x5C) 	 			//	Timer/Counter0 Output Compare Register 					82

#define GICR	(*(volatile u8*)0x5B) 	 			//47, 67 
#define INT1	7
#define INT0	6
#define INT2	5
#define IVSEL	1
#define IVCE	0

#define GIFR	(*(volatile u8*)0x5A) 	 			//68
#define INTF1	7	
#define INTF0	6 	
#define INTF2	5 	

#define TIMSK	(*(volatile u8*)0x59) 	 			//82, 112, 130
#define OCIE2	7	
#define TOIE2	6 	
#define TICIE1	5 	
#define OCIE1A	4 	
#define OCIE1B	3 	
#define TOIE1	2 	
#define OCIE0	1 	
#define TOIE0	0 		

#define TIFR	(*(volatile u8*)0x58) 	 			//83, 112, 130
#define OCF2	7	
#define TOV2	6 	
#define ICF1	5 	
#define OCF1A	4 	
#define OCF1B	3 	
#define TOV1	2 	
#define OCF0	1 	
#define TOV0	0 		

#define SPMCR	(*(volatile u8*)0x57) 	 			//248
#define SPMIE	7	
#define RWWSB	6 	
#define RWWSRE	4 	
#define BLBSET	3 	
#define PGWRT	2 	
#define PGERS	1 	
#define SPMEN	0 		

#define TWCR	(*(volatile u8*)0x56) 	 			//177
#define TWINT	7	
#define TWEA	6 	
#define TWSTA	5 	
#define TWSTO	4 	
#define TWWC	3 	
#define TWEN	2 	
#define TWIE	0 		

#define MCUCR	(*(volatile u8*)0x55) 	 			//32, 66
#define SE		7	 	
#define SM2		6 	
#define SM1		5 	
#define SM0		4 	
#define ISC11	3 	
#define ISC10	2 	
#define ISC01	1 	
#define ISC00	0 		

#define MCUCSR	(*(volatile u8*)0x54) 	 			//40, 67, 228
#define JTD		7	 	
#define ISC2	6 	
#define JTRF	4 	
#define WDRF	3 	
#define BORF	2 	
#define EXTRF	1 	
#define PORF	0 		

#define TCCR0	(*(volatile u8*)0x53) 	 			//80
#define FOC0	7	
#define WGM00	6 	
#define COM01	5 	
#define COM00	4 	
#define WGM01	3 	
#define CS02	2 	
#define CS01	1 	
#define CS00	0 		

#define TCNT0	(*(volatile u8*)0x52) 	 			//  Timer/Counter0 	(8 Bits)	 									82

#define OSCCAL	(*(volatile u8*)0x51)	 			//  Oscillator Calibration Register 								30
//  OCDR 										//  On-Chip Debug Register 											224


#define SFIOR 	(*(volatile u8*)0x50) 	 			//56,85,131,198,218
#define ADTS2	7 	
#define ADTS1	6 	
#define ADTS0	5 	
#define ACME	3 	
#define PUD		2 	
#define PSR2	1 	
#define PSR10	0 		

#define TCCR1A 	(*(volatile u8*)0x4F) 	 			//107
#define COM1A1	7 	
#define COM1A0	6 	
#define COM1B1	5 	
#define COM1B0	4 	
#define FOC1A	3 	
#define FOC1B	2 	
#define WGM11	1 	
#define WGM10	0 		

#define TCCR1B 	(*(volatile u8*)0x4E) 	 			//110
#define ICNC1	7 	
#define ICES1	6 	
#define WGM13	4 	
#define WGM12	3 	
#define CS12	2 	
#define CS11	1 	
#define CS10	0 		

#define TCNT1H 	(*(volatile u8*)0x4D) 				//  Timer/Counter1 - Counter Register High Byte 					111
#define TCNT1L 	(*(volatile u8*)0x4C) 				//  Timer/Counter1 - Counter Register Low Byte 						111
#define OCR1AH 	(*(volatile u8*)0x4B) 				//  Timer/Counter1 - Output Compare Register A High Byte 			111
#define OCR1AL 	(*(volatile u8*)0x4A) 				//  Timer/Counter1 - Output Compare Register A Low Byte 			111
#define OCR1BH 	(*(volatile u8*)0x49) 				//  Timer/Counter1 - Output Compare Register B High Byte 			111
#define OCR1BL 	(*(volatile u8*)0x48) 				//  Timer/Counter1 - Output Compare Register B Low Byte 			111
#define ICR1H 	(*(volatile u8*)0x47) 				//  Timer/Counter1 - Input Capture Register High Byte 				111
#define ICR1L 	(*(volatile u8*)0x46) 				//  Timer/Counter1 - Input Capture Register Low Byte 				111

#define	TCCR2 	(*(volatile u8*)0x45) 				//125
#define FOC2	7 	
#define WGM20	6 	
#define COM21	5 	
#define COM20	4 	
#define WGM21	3 	
#define CS22	2 	
#define CS21	1 	
#define CS20	0 		

#define	TCNT2 	(*(volatile u8*)0x44) 				//	Timer/Counter2 (8 Bits)											127
#define	OCR2 	(*(volatile u8*)0x43) 				//	Timer/Counter2 Output Compare Register 							127

#define	ASSR 	(*(volatile u8*)0x42) 				//128
#define AS2		3 	
#define TCN2UB	2 	
#define OCR2UB	1 	
#define TCR2UB	0 		

#define	WDTCR 	(*(volatile u8*)0x41) 				//42
#define WDTOE	4 	
#define WDE		3 	
#define WDP2	2 	
#define WDP1	1 	
#define WDP0	0 		

#define	UBRRH 	(*(volatile u16*)0x40) 				//164
#define UBRRH_URSEL		15 		
#define UBRRH_UBRR11	11
#define UBRRH_UBRR10	10
#define UBRRH_UBRR9		9 
#define UBRRH_UBRR8		8 

#define	UCSRC 	(*(volatile u16*)0x40) 				//162
#define UCSRC_URSEL		7
#define UCSRC_UMSEL		6
#define UCSRC_UPM1		5
#define UCSRC_UPM0		4
#define UCSRC_USBS		3
#define UCSRC_UCSZ1		2
#define UCSRC_UCSZ0		1
#define UCSRC_UCPOL		0


#define EEARH 	(*(volatile u8*)0x3F) 	 	//19
#define EEAR9	1 	
#define EEAR8	0 		

#define EEARL 	(*(volatile u8*)0x3E) 	 	// EEPROM Address Register Low Byte 								19
#define EEDR 	(*(volatile u8*)0x3D) 	 	// EEPROM Data Register 											19

#define EECR 	(*(volatile u8*)0x3C) 	 	//19
#define EERIE	3 	
#define EEMWE	2 	
#define EEWE	1 	
#define EERE	0 		


#define PORTA 	(*(volatile u8*)0x3B) 	 	//64
#define PORTA7	7 	
#define PORTA6	6 	
#define PORTA5	5 	
#define PORTA4	4 	
#define PORTA3	3 	
#define PORTA2	2 	
#define PORTA1	1 	
#define PORTA0	0 		

#define DDRA 	(*(volatile u8*)0x3A) 	 	//64
#define DDA7	7 	
#define DDA6	6 	
#define DDA5	5 	
#define DDA4	4 	
#define DDA3	3 	
#define DDA2	2 	
#define DDA1	1 	
#define DDA0	0 		

#define PINA 	(*(volatile u8*)0x39) 	 	//64
#define PINA7	7 	
#define PINA6	6 	
#define PINA5	5 	
#define PINA4	4 	
#define PINA3	3 	
#define PINA2	2 	
#define PINA1	1 	
#define PINA0	0 		

#define PORTB 	(*(volatile u8*)0x38) 	 	//64
#define PORTB7	7 	
#define PORTB6	6 	
#define PORTB5	5 	
#define PORTB4	4 	
#define PORTB3	3 	
#define PORTB2	2 	
#define PORTB1	1 	
#define PORTB0	0 		

#define DDRB 	(*(volatile u8*)0x37) 	 	//64
#define DDB7	7 	
#define DDB6	6 	
#define DDB5	5 	
#define DDB4	4 	
#define DDB3	3 	
#define DDB2	2 	
#define DDB1	1 	
#define DDB0	0 		

#define PINB 	(*(volatile u8*)0x36) 	 	//65
#define PINB7	7 	
#define PINB6	6 	
#define PINB5	5 	
#define PINB4	4 	
#define PINB3	3 	
#define PINB2	2 	
#define PINB1	1 	
#define PINB0	0 		

#define PORTC 	(*(volatile u8*)0x35) 	 	//65
#define PORTC7	7 	
#define PORTC6	6 	
#define PORTC5	5 	
#define PORTC4	4 	
#define PORTC3	3 	
#define PORTC2	2 	
#define PORTC1	1 	
#define PORTC0	0 		

#define DDRC 	(*(volatile u8*)0x34) 	 	//65
#define DDC7	7 	
#define DDC6	6 	
#define DDC5	5 	
#define DDC4	4 	
#define DDC3	3 	
#define DDC2	2 	
#define DDC1	1 	
#define DDC0	0 		

#define PINC 	(*(volatile u8*)0x33) 	 	//65
#define PINC7	7 	
#define PINC6	6 	
#define PINC5	5 	
#define PINC4	4 	
#define PINC3	3 	
#define PINC2	2 	
#define PINC1	1 	
#define PINC0	0 		

#define PORTD 	(*(volatile u8*)0x32) 	 	//65
#define PORTD7	7 	
#define PORTD6	6 	
#define PORTD5	5 	
#define PORTD4	4 	
#define PORTD3	3 	
#define PORTD2	2 	
#define PORTD1	1 	
#define PORTD0	0 		

#define DDRD 	(*(volatile u8*)0x31) 	 	//65
#define DDD7	7 	
#define DDD6	6 	
#define DDD5	5 	
#define DDD4	4 	
#define DDD3	3 	
#define DDD2	2 	
#define DDD1	1 	
#define DDD0	0 		

#define PIND 	(*(volatile u8*)0x30) 	 	//65
#define PIND7	7 	
#define PIND6	6 	
#define PIND5	5 	
#define PIND4	4 	
#define PIND3	3 	
#define PIND2	2 	
#define PIND1	1 	
#define PIND0	0 		

#define SPDR 	(*(volatile u8*)0x2F) 	 	//SPI Data Register 												138

#define SPSR 	(*(volatile u8*)0x2E) 	 	//138
#define SPIF	7 	
#define WCOL	6 	
#define SPI2X	0 		

#define SPCR 	(*(volatile u8*)0x2D) 	 	//136
#define SPIE	7 	
#define SPE		6 	
#define DORD	5 	
#define MSTR	4 	
#define CPOL	3 	
#define CPHA	2 	
#define SPR1	1 	
#define SPR0	0 		

#define UDR 	(*(volatile u8*)0x2C) 	 	//USART I/O Data Register 										159

#define UCSRA 	(*(volatile u8*)0x2B) 	 	//160
#define RXC		7 	
#define TXC		6 	
#define UDRE	5 	
#define FE		4 		
#define DOR		3 	
#define PE		2 		
#define U2X		1 	
#define MPCM	0 		

#define UCSRB 	(*(volatile u8*)0x2A) 	 	//161
#define RXCIE	7 	
#define TXCIE	6 	
#define UDRIE	5 	
#define RXEN	4 	
#define TXEN	3 	
#define UCSRC_UCSZ2	2 	
#define RXB8	1 	
#define TXB8	0 		

#define UBRRL 	(*(volatile u8*)0x29) 	 	// USART Baud Rate Register Low Byte 								164

#define ACSR 	(*(volatile u8*)0x28) 	 	//199
#define ACD		7 	
#define ACBG	6 	
#define ACO		5 	
#define ACI		4 	
#define ACIE	3 	
#define ACIC	2 	
#define ACIS1	1 	
#define ACIS0	0 		

#define ADMUX 	(*(volatile u8*)0x27) 	 	//214
#define REFS1	7 	
#define REFS0	6 	
#define ADLAR	5 	
#define MUX4	4 	
#define MUX3	3 	
#define MUX2	2 	
#define MUX1	1 	
#define MUX0	0 		

#define ADCSRA 	(*(volatile u8*)0x26) 	 	//216
#define ADEN	7 	//ADC_Enable
#define ADSC	6 	//ADC_StartConversion
#define ADATE	5 	//ADC_AutoTriggerEnable
#define ADIF	4 	//ADC_InterruptFlag
#define ADIE	3 	//ADC_InterruptEnable
#define ADPS2	2 	//ADC_PreScaler
#define ADPS1	1 	//ADC_PreScaler
#define ADPS0	0 	//ADC_PreScaler	

#define ADCH 	(*(volatile u8*)0x25) 	 	// ADC Data Register High Byte 										217
#define ADCL 	(*(volatile u8*)0x24) 	 	// ADC Data Register Low Byte 										217
#define TWDR 	(*(volatile u8*)0x23) 	 	// Two-wire Serial Interface Data Register 							179

#define TWAR 	(*(volatile u8*)0x22) 	 	//179
#define TWA6	7 	
#define TWA5	6 	
#define TWA4	5 	
#define TWA3	4 	
#define TWA2	3 	
#define TWA1	2 	
#define TWA0	1 	
#define TWGCE	0 		

#define TWSR 	(*(volatile u8*)0x21) 	 	//178
#define TWS7	7 	
#define TWS6	6 	
#define TWS5	5 	
#define TWS4	4 	
#define TWS3	3 	
#define TWPS1	1 	
#define TWPS0	0 		

#define TWBR 	(*(volatile u8*)0x20) 	 	// Two-wire Serial Interface Bit Rate Register 					177






#endif 		// MEMORY_MAP_H_INCLUDED
