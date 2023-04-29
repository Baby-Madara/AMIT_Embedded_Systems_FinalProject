


#include "UART_Trial.h"








void UART_Init()
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);	    // Turn on transmission and reception 
	UCSRC |= (1 << UBRRH_URSEL) | (1 << UCSRC_UCSZ0) | (1 << UCSRC_UCSZ1);// Use 8-bit char size 
	UBRRL = 103;			        // Load lower 8-bits of the baud rate 
	UBRRH = 0;		                // Load upper 8-bits
	
    
}



void UART_TxChar(char ch)
{
	while (! (UCSRA & (1<<UDRE)));          // Wait for empty transmit buffer 
	UDR = ch ;
}

bool UART_IsAvailable()
{
    if((UCSRA & (1 << RXC)) == 0)
    {   
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}


u8 UART_RxChar()
{
	// while ((UCSRA & (1 << RXC)) == 0);      // Wait till data is received 
	// if       ((UCSRA & (1 << RXC)) == 0){
	    return UDR;		                    // Return the byte 
    // }
}


