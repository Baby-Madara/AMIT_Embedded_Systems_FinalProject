#ifndef BITMATH_H_INCLUDED
#define BITMATH_H_INCLUDED

#include "STD_Types.h"

#define SET_REG(reg)							(reg =  0xFF)
#define CLEAR_REG(reg)							(reg =  0x00)
#define TOGGLE_REG(reg)							(reg = ~reg )


#define SET_BIT(	_reg, _bit)					(_reg |= (1<<_bit))
#define CLEAR_BIT(	_reg, _bit)					(_reg &=~(1<<_bit))
#define TOGGLE_BIT(	_reg, _bit)					(_reg ^= (1<<_bit))
#define GET_BIT(	_reg, _bit)					(1   &(_reg>>_bit))

#define WRITE_BIT(REG,PIN,DATA)					( (REG) = ( REG & (~(1<<PIN)) ) | (DATA<<PIN) )

#define WRITE_BITS(Reg, Bits, Data)				( (Reg) = ((Bits) & (Data)) | ((~(Bits)) & (Reg))  )		 	//experimantal :)


#endif //BITMATH_H_INCLUDED

