#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED

#include "../../Memory_map/mem_map.h"

#include "../../UTILS/STD_Types.h"
#include "../../UTILS/BitMath.h"




//Init function 
void UART_INIT();

// transmit function
void UART_TX(u8 data);

// recieve function
u8 UART_RX();

void status_check();




#endif //USART_H_INCLUDED