#ifndef SEVENSEGMENT_H_INCLUDED
#define SEVENSEGMENT_H_INCLUDED

#include "../../MCAL/DIO/DIO.h"

#include <util/delay.h>

#include "SevenSegment_Config.h"



void SEG_Init();

void SEG_Display(u16 num);



#endif //SEVENSEGMENT_H_INCLUDED