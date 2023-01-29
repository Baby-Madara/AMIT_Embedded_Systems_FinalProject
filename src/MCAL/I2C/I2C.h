#ifndef I2C_H_INCLUDED
#define I2C_H_INCLUDED

#include "../../Memory_map/mem_map.h"
#include "../../UTILS/STD_Types.h"
#include "../../UTILS/BitMath.h"



void I2C_Init();
void I2C_Send();
u8 I2C_Receive();












#endif //I2C_H_INCLUDED