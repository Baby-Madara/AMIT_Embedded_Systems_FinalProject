#include "EEPROMTrial.h"

// static volatile u16 EEPROM_currentAddress = 0x0005;






u8 EEPROM_readChar(u16 addr)
{
    while(EECR & (1<<EEWE)) ;

    EEARH = (addr>>8);
    EEARL = (u8)(addr & 0xFF);
    EECR |= (1<<EERE);
    return EEDR;
}

void EEPROM_readStr(u16 addr, u8* buffer)
{
    volatile u8 i=0;
    while(1)
    {
        buffer[i] = EEPROM_readChar(addr+i);
        if(buffer[i] == '\0'){break;}
        ++i;
    }
}

void EEPROM_writeChar(u8 data, u16 addr)
{
    while(EECR & (1 << EEWE))   ;

    EEARH = (addr>>8);
    EEARL = (u8)(addr & 0xFF);
    EEDR = data;
    EECR |= (1 << EEMWE);
    EECR |= (1 << EEWE);
}

void EEPROM_writeStr (u8*str, u16 addr)
{
    volatile u8 i=0;
    while(str[i] != '\0')
    {
        EEPROM_writeChar(str[i], addr+i);
        i++;
    }
    EEPROM_writeChar(0, addr+i);
}





// u16 EEPROM_malloc   (u8 allocSize)
// {
//     EEPROM_currentAddress += allocSize;
//     return (EEPROM_currentAddress - allocSize);
// }






