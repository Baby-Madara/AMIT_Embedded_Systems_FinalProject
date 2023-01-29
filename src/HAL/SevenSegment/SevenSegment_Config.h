#ifndef SEVENSEGMENT_H_CONFIG_INCLUDED
#define SEVENSEGMENT_H_CONFIG_INCLUDED

#include "../Kit_config.h"

#ifdef AMIT_KIT

#define SEG_A	DIO_A4
#define SEG_B	DIO_A5
#define SEG_C	DIO_A6
#define SEG_D	DIO_A7

#define SEG_DOT	DIO_B3

#define SEG_En1	DIO_B2
#define SEG_En2	DIO_B1

#endif

#ifdef FARES_KIT

#define SEG_A	DIO_B0
#define SEG_B	DIO_B1
#define SEG_C	DIO_B2
#define SEG_D	DIO_B4


#define SEG_En1	DIO_A3
#define SEG_En2	DIO_A2
#define SEG_En3	DIO_B5
#define SEG_En4	DIO_B6

#endif




#endif//SEVENSEGMENT_H_CONFIG_INCLUDED






