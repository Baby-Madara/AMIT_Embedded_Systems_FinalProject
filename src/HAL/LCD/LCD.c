#include "LCD.h"

u8 LCD_cursorTracer =0;

void LCD_Cycle(){
	DIO_DigitalWritePin(LCD_En, HIGH);		_delay_ms(1);
	DIO_DigitalWritePin(LCD_En, LOW);		_delay_ms(1);
}


void LCD_Init(){

	DIO_PinMode(LCD_RS, OUTPUT);
	#ifdef AMIT_KIT
	DIO_PinMode(LCD_RW, OUTPUT);
	#endif
	DIO_PinMode(LCD_En, OUTPUT);

	DIO_PinMode(LCD_D4, OUTPUT);
	DIO_PinMode(LCD_D5, OUTPUT);
	DIO_PinMode(LCD_D6, OUTPUT);
	DIO_PinMode(LCD_D7, OUTPUT);
	_delay_ms(100);

	//personal touch
	DIO_DigitalWritePin(LCD_D7, 0 ),	DIO_DigitalWritePin(LCD_D6, 0 ),	DIO_DigitalWritePin(LCD_D5, 0 ),	DIO_DigitalWritePin(LCD_D4, 0 );	LCD_Cycle();
	DIO_DigitalWritePin(LCD_D7, 0 ),	DIO_DigitalWritePin(LCD_D6, 0 ),	DIO_DigitalWritePin(LCD_D5, 0 ),	DIO_DigitalWritePin(LCD_D4, 0 );	LCD_Cycle();
	DIO_DigitalWritePin(LCD_D7, 0 ),	DIO_DigitalWritePin(LCD_D6, 0 ),	DIO_DigitalWritePin(LCD_D5, 0 ),	DIO_DigitalWritePin(LCD_D4, 0 );	LCD_Cycle();
	_delay_ms(100);

	// func set
	LCD_WriteCMD(LCD_4bit_mode);
	DIO_DigitalWritePin(LCD_D7, 	1	); 	//N 0 1 line 
	DIO_DigitalWritePin(LCD_D6, 	0	);	//F 0 5*7 dot character font
	LCD_Cycle();
	_delay_us(100);

	//disp on
	LCD_WriteCMD(0x0F);
	_delay_us(100);

	//disp clear
	LCD_WriteCMD(0x01);
	_delay_ms(2);

	// entry mode set
	LCD_WriteCMD(0x06);





	
}

void LCD_WriteData(u8 data){

	DIO_DigitalWritePin(LCD_RS, HIGH);
	#ifdef AMIT_KIT
	DIO_DigitalWritePin(LCD_RW, LOW);
	#endif

	DIO_DigitalWritePin(LCD_D7, 	GET_BIT(data,7)	);
	DIO_DigitalWritePin(LCD_D6, 	GET_BIT(data,6)	);
	DIO_DigitalWritePin(LCD_D5, 	GET_BIT(data,5)	);
	DIO_DigitalWritePin(LCD_D4, 	GET_BIT(data,4)	);
	LCD_Cycle();

	DIO_DigitalWritePin(LCD_D7, 	GET_BIT(data,3)	);
	DIO_DigitalWritePin(LCD_D6, 	GET_BIT(data,2)	);
	DIO_DigitalWritePin(LCD_D5, 	GET_BIT(data,1)	);
	DIO_DigitalWritePin(LCD_D4, 	GET_BIT(data,0)	);
	LCD_Cycle();

	++LCD_cursorTracer;
	
	#ifdef AMIT_KIT
	if(LCD_cursorTracer== 16){
		LCD_GoTo(1,0);
	}
	else if(LCD_cursorTracer==32){
		LCD_GoTo(0,0);
		LCD_cursorTracer=0;
	}
	#endif
	
	#ifdef FARES_KIT
	if(LCD_cursorTracer== 20){
		LCD_GoTo(1,0);
	}
	else if(LCD_cursorTracer==40){
		LCD_GoTo(2,0);
	}
	else if(LCD_cursorTracer==60){
		LCD_GoTo(3,0);
	}
	else if(LCD_cursorTracer==80){
		LCD_GoTo(0,0);
		LCD_cursorTracer=0;
	}
	#endif


	_delay_ms(1);



}


void LCD_WriteCMD(u8 cmd){


	
	DIO_DigitalWritePin(LCD_RS, 	LOW);
	#ifdef AMIT_KIT
	DIO_DigitalWritePin(LCD_RW, 	LOW);
	#endif

	DIO_DigitalWritePin(LCD_D7, 	GET_BIT( cmd,7)	);
	DIO_DigitalWritePin(LCD_D6, 	GET_BIT( cmd,6)	);
	DIO_DigitalWritePin(LCD_D5, 	GET_BIT( cmd,5)	);
	DIO_DigitalWritePin(LCD_D4, 	GET_BIT( cmd,4)	);
	LCD_Cycle();

	DIO_DigitalWritePin(LCD_D7, 	GET_BIT( cmd,3)	);
	DIO_DigitalWritePin(LCD_D6, 	GET_BIT( cmd,2)	);
	DIO_DigitalWritePin(LCD_D5, 	GET_BIT( cmd,1)	);
	DIO_DigitalWritePin(LCD_D4, 	GET_BIT( cmd,0)	);
	LCD_Cycle();

	_delay_ms(2);
}






void LCD_WriteString(u8* str){
	while (*str != '\0'){
		LCD_WriteData(*str);
		++str;
	}
}


void LCD_WriteStringWithLength(u8* str, s8 len){
	while ((*str != '\0') && (len>0) ){
		LCD_WriteData(*str);
		++str;
		--len;
	}
	while(len >0){
		LCD_WriteData(' ');
		--len;
	}
}



void LCD_Clear(){
	LCD_WriteCMD(LCD_clr);
	LCD_cursorTracer=0;
}


#ifdef AMIT_KIT
void LCD_GoTo(u8 line, u8 col){
	LCD_WriteCMD(LCD_DDRAM_addr + (line*64 + col));
	LCD_cursorTracer = line*16 + col;
}
#endif

#ifdef FARES_KIT

void LCD_GoTo(u8 line, u8 col){
	switch (line)
	{
	case 0:		LCD_WriteCMD(LCD_DDRAM_addr + (          col));		break;
	case 1:		LCD_WriteCMD(LCD_DDRAM_addr + (     64 + col));		break;
	case 2:		LCD_WriteCMD(LCD_DDRAM_addr + (     20 + col));		break;
	case 3:		LCD_WriteCMD(LCD_DDRAM_addr + (     84 + col));		break;
	}
	LCD_cursorTracer = line*20 + col;
}
#endif



void LCD_WriteInt(s64 num){
	u8 num_str[10]={0};
	sprintf((char*)num_str, 	"%d", 	(int)num);
	LCD_WriteString(num_str);
}



void LCD_WriteFloat(float64 num, u8 digits){
	u8 res[20] = {0};
	ftoa(num, res, digits);
	LCD_WriteString(res);
}



void LCD_WriteNumWithLength(float64 num, u8 len){
	u8 res[len];
	ftoa(num, res, 5);
	LCD_WriteStringWithLength(res, len);
}




