#ifndef UART_TRIAL_H
#define UART_TRIAL_H

#include "../../UTILS/BitMath.h"
#include "../../UTILS/Maths.h"
#include "../../UTILS/STD_Types.h"
#include "../../Memory_map/mem_map.h"
#include "../DIO/DIO.h"


#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)	


void UART_Init();
bool UART_IsAvailable();
u8   UART_RxChar();
void UART_TxChar(char ch);





#endif