#include "USART.h"




////initialize function
void UART_INIT(){




    // buffer empty flag is one to enable storing UDR
    // tranmit complete flag is zero opposite to Buffer Empty
    // transmit complete flag is set when complete frame is sent

    //      *** FORMAT OF DATA***          //
    /***********************************************/
    //access USCRC to edit the format of data transferred
    SET_BIT(UCSRC  , UCSRC_URSEL);
    //mode select >> asyn.
    CLEAR_BIT(UCSRC  , UCSRC_UMSEL);
    //disable parity
    CLEAR_BIT(UCSRC  , UCSRC_UPM0);
    CLEAR_BIT(UCSRC  , UCSRC_UPM1);
    //stop bit
    SET_BIT(UCSRC   , UCSRC_USBS);
    //Bits transmitted
    CLEAR_BIT(UCSRC  , UCSRC_UCSZ0);
    SET_BIT(UCSRC   ,UCSRC_UCSZ1);
    SET_BIT(UCSRB   ,UCSRC_UCSZ2);
    // siince asyn. disable UCPOL by clear
    CLEAR_BIT(UCSRC ,UCSRC_UCPOL);




}






