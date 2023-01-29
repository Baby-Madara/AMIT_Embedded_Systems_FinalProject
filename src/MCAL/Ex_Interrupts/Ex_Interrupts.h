#ifndef EX_INTERRUPTS_H_INCLUDED
#define EX_INTERRUPTS_H_INCLUDED

#include "../General_Interrupts/General_Interrupts.h"

#include "../../UTILS/BitMath.h"
#include "../../UTILS/STD_Types.h"
#include "../../Memory_map/mem_map.h"


#define EX_INT0_LOW		0
#define EX_INT0_LOGICAL	1
#define EX_INT0_FALLING	2
#define EX_INT0_RISING	3

#define EX_INT1_LOW		0
#define EX_INT1_LOGICAL	1
#define EX_INT1_FALLING	2
#define EX_INT1_RISING	3

#define EX_INT2_FALLING	0
#define EX_INT2_RISING	1


#define EX_INT0 	__vector_1
#define EX_INT1 	__vector_2
#define EX_INT2 	__vector_3


// **********************		EX_Int0 		********************** //

void EX_Int0_Init		(	u8 signalMode);
void EX_Int0_Enable		(	void);
void EX_Int0_Disable	(	void);

void EX_Int0_SignalMode	(	u8 signalMode);
void EX_Int0_SetCallBack( 	void(*ptrFn)(void) );
void EX_Int0_ClearFlag	(	void);

void __vector_1(void) __attribute__((used)); 			//__attribute((signal)) for preventing optimization - but __attribute((signal)) in PlatformIO



// **********************		EX_Int1 		********************** //


void EX_Int1_Init		(	u8 signalMode);
void EX_Int1_Enable		(	void);
void EX_Int1_Disable	(	void);

void EX_Int1_SignalMode	(	u8 signalMode);
void EX_Int1_SetCallBack( 	void(*ptrFn)(void) );
void EX_Int1_ClearFlag	(	void);

void __vector_2(void) __attribute__((used)); 			//__attribute((signal)) for preventing optimization - but __attribute((signal)) in PlatformIO



// **********************		EX_Int2 		********************** //


void EX_Int2_Init		(	u8 signalMode);
void EX_Int2_Enable		(	void);
void EX_Int2_Disable	(	void);

void EX_Int2_SignalMode	(	u8 signalMode);
void EX_Int2_SetCallBack( 	void(*ptrFn)(void) );
void EX_Int2_ClearFlag	(	void);

void __vector_3(void) __attribute__((used)); 			//__attribute((signal)) for preventing optimization - but __attribute((signal)) in PlatformIO









#endif // EX_INTERRUPTS_H_INCLUDED
