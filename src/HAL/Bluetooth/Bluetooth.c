#include "Bluetooth.h"


void Bluetooth_Init()
{    UART_Init();           }

bool Bluetooth_IsAvailable()
{    return UART_IsAvailable();    }

u8   Bluetooth_RxChar()
{    return UART_RxChar();         }

void Bluetooth_TxChar(char ch)
{    UART_TxChar(ch);       }





