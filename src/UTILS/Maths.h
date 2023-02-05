#ifndef MATHS_H_INCLUDED
#define MATHS_H_INCLUDED


#include "BitMath.h"
#include "STD_Types.h"
#include <math.h>



#define MAP(_val, _oldL, _oldH, _newL, _newH)	( ((float64)_newH - _newL)*((float64)_val - _oldL)/( (float64)_oldH - _oldL) + _newL )



void reverse(u8 *str, s32 len);
s64  intToStr(s32 x, u8 str[], s32 d);
void ftoa(float64 n, u8 *res, s32 afterpoint);



#endif //MATHS_H_INCLUDED