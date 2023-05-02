#ifndef EEPROM_TRIAL_H
#define EEPROM_TRIAL_H



#include <string.h>
#include <stdlib.h>

#include "../../Memory_map/mem_map.h"
#include "../../UTILS/BitMath.h"
#include "../../UTILS/STD_Types.h"
#include "../../MCAL/General_Interrupts/General_Interrupts.h"



/*
input  : the eeprom address  from 0x00 to 0xff 
output : returns the value stored in said eeprom address
*/
u8   EEPROM_readChar (u16 addr);

/*
input : address in eeprom where the string is start being stored
        an array pointer to pass result by refrence
output : none
result: if there was string stored in eeprom starting at said address it will be saved in array
*/
void EEPROM_readStr  (u16 addr, u8* buffer);

/*
input : array where string is being stored
        address in eeprom where you want to store array
output : none
result : the string stored in array  will be stored in eeprom 
*/
void EEPROM_writeStr (u8* str,  u16 addr);

/*
input : 8 bit data
        address where data should be stored in eeprom
result : data will be stored at specified address in eeprom
*/
void EEPROM_writeChar(u8  data, u16 addr);







#endif