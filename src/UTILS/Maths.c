#include "Maths.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Reverses a string 'str' of length 'len'
void reverse(u8 *str, s32 len){
	s32 i = 0, j = len - 1, temp;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
s64 intToStr(s32 x, u8 str[], s32 d){

	s64 i = 0;

	//the number will be saved inverted, then will be reversed
	while (x){
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}

	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d){
		str[i++] = '0';
	}

	reverse(str, i);
	if(0 ==i){
		str[i++]='0';
	}
	str[i] = '\0';
	return i;
}

// Converts a floating-point/double number to a string.
void ftoa(float64 n, u8 *res, s32 afterpoint)
{
	u8 negFlag=0;
	if(n<0){	n=-n;			res[0]='-';		negFlag=1;	}
	
	// Extract integer part
	s64 ipart = (s64)n;
	
	// Extract floating part
	float64 fpart = n - (float64)ipart;

	// convert integer part to string
	s32 i;
	if(TRUE == negFlag) 	{	i = intToStr(ipart, res+1, 0)+1;		}
	else			        {	i = intToStr(ipart, res, 0);			}

	// check for display option after point
	if (afterpoint != 0)
	{
		res[i] = '.'; // add dot

		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter
		// is needed to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);

		intToStr((s32)fpart, res + i + 1, afterpoint);
	}
}

