#include "USART.h"




////initialize function
void UART_INIT(){


    // buffer empty flag is one to enable storing UDR
    // tranmit complete flag is zero opposite to Buffer Empty
    // transmit complete flag is set when complete frame is sent


    //***   ENABLE RX AND TX     ***///
    /*************************************************/
    SET_BIT(UCSRB , RXEN);
    SET_BIT(UCSRB , TXEN);


    //***     BAUD RATE        ***//
    /*************************************************/
    //to access register UBRRH
    SET_BIT(UBRRH, UBRRH_URSEL);
    //for U2X normal speed  >>UBRRL = 51 ;
    UBRRL = 103;  //because U2X is set
    
    //***    Interrupts         **//
    /*************************************************/
    //disable all no need

    //recieve interrupt
    CLEAR_BIT(UCSRB, RXCIE);
    //transmit interrupt
    CLEAR_BIT(UCSRB, TXCIE);
    //data register empty interrupt
    CLEAR_BIT(UCSRB, UDRIE);

       //***     OPTIONS    ***//
    /*************************************************/
    //USART transmission speed  when set >> double speed
    SET_BIT(UCSRA   , U2X);
    //Multi processor communication Mode     
    CLEAR_BIT(UCSRA , MPCM); 


    //      *** DATA FORMAT***          //
    /***********************************************/
    //to access USCRC only because it shares with UBRRH 
    SET_BIT(UCSRC  , UCSRC_URSEL);
    //mode select >> asyn.
    CLEAR_BIT(UCSRC  , UCSRC_UMSEL);
    //disable parity
    CLEAR_BIT(UCSRC  , UCSRC_UPM0);
    CLEAR_BIT(UCSRC  , UCSRC_UPM1);
    //stop bit
    SET_BIT(UCSRC   , UCSRC_USBS);
    //Bits transmitted 0->7 by default this is already done but for sure
    CLEAR_BIT(UCSRC  , UCSZ2);
    SET_BIT(UCSRC   ,UCSRC_UCSZ1);
    SET_BIT(UCSRB   ,UCSRC_UCSZ0);
    // siince asyn. disable UCPOL by clear
    CLEAR_BIT(UCSRC ,UCSRC_UCPOL);



    

}


// transmit function
void UART_TX(u8 data){
    while ( GET_BIT(UCSRA , UDRE) == 1 ) //read UDRE and if one then the buffer is ready to store then transmit data
    {
        UDR = data;
    }
    
}

// recieve function
u8 UART_RX(){

}


void status_check(){

}





