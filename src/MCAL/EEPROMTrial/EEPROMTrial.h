#ifndef EEPROM_TRIAL_H
#define EEPROM_TRIAL_H



#include <string.h>
#include <stdlib.h>

#include "../../Memory_map/mem_map.h"
#include "../../UTILS/BitMath.h"
#include "../../UTILS/STD_Types.h"
#include "../../MCAL/General_Interrupts/General_Interrupts.h"



u8   EEPROM_readChar (u16 addr);
void EEPROM_readStr  (u16 addr, u8* buffer);
void EEPROM_writeStr (u8* str,  u16 addr);
void EEPROM_writeChar(u8  data, u16 addr);







#endif