#include "../DIO/DIO.h"
#include "../../Memory_Map/MEM_MAP.h"
#include "../../UTILS/BitMath.h"
#include "../../UTILS/STD_Types.h"
#include "../../Services/Users/Users.h"
#ifndef EEPROM_H
#define EEPROM_H


u8 EEPROM_read(short address);//read data from eeprom
void EEPROM_write(short address,  u8 data);// write data to eeprom
void Write_list_struct(Users_usersList* Pointer_User_List);
void Write_Struct_EEPROM(Users_userNode*Pointer_struct,u8 User_Number_in_array);// write all data to struct
void Read_all_Struct_EEPROM(Users_userNode*pointer_struct);//read from eeprom all data data and send it to struct
bool Error_in_EEPROM();//check for a certain value you already know at the eeprom if eeprom is ramged and value is not equal then return 1

#endif
