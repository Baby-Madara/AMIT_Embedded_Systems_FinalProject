#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "../../UTILS/BitMath.h"
#include "../../UTILS/Maths.h"
#include "../../UTILS/STD_Types.h"
#include "../../Memory_map/mem_map.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/UART_Trial/UART_Trial.h"


void Bluetooth_Init();
bool Bluetooth_IsAvailable();
u8   Bluetooth_RxChar();
void Bluetooth_TxChar(char ch);





#endif