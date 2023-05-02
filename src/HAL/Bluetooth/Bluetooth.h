#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "../../UTILS/BitMath.h"
#include "../../UTILS/Maths.h"
#include "../../UTILS/STD_Types.h"
#include "../../Memory_map/mem_map.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/UART_Trial/UART_Trial.h"

// intialise bluetooth and enable cumminication through it
void Bluetooth_Init();

// check if there is data unread in register waiting to be read
bool Bluetooth_IsAvailable();

// read data and return it 
u8   Bluetooth_RxChar();

// send data
void Bluetooth_TxChar(char ch);



#endif