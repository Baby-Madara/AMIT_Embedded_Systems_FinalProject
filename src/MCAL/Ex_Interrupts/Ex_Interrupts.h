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



// **********************		EX_Int0 		********************** //

void EX_Int0_D2_Init		(	u8 signalMode);                         // start intialise external intterupt (0) sequance that will be on pin d2
void EX_Int0_D2_Enable		(	void);                                  //enable the intterupt 0 and allow it to start aactivate
void EX_Int0_D2_Disable	    (	void);                                  // disablle and prevent interupt (0)

void EX_Int0_D2_SignalMode	(	u8 signalMode);                         //used to receive signals
void EX_Int0_D2_SetCallBack ( 	void(*ptrFn)(void) );                   // set the function to be called in intrupt(0)
void EX_Int0_D2_ClearFlag	(	void);                                  //clear intterupt flag

void INT0_vect(void) __attribute__ ((used)) __attribute__ ((signal)); 		//(signal,__INTR_ATTRS)



// **********************		EX_Int1 		********************** //


void EX_Int1_D3_Init		(	u8 signalMode);                         // start intialise external intterupt (1) sequance  that will be on pin d3
void EX_Int1_D3_Enable		(	void);                                  //enable the intterupt and allow it to activate
void EX_Int1_D3_Disable	(	void);                                      // disablle and prevent interupt (1)

void EX_Int1_D3_SignalMode	(	u8 signalMode);                         //used to receive signals
void EX_Int1_D3_SetCallBack( 	void(*ptrFn)(void) );                   // set the function to be called in intrupt (1)
void EX_Int1_D3_ClearFlag	(	void);                                  //clear intterupt flag

void INT1_vect (void) __attribute__ ((used)) __attribute__ ((signal)); 		//(signal,__INTR_ATTRS)



// **********************		EX_Int2 		********************** //


void EX_Int2_B2_Init		(	u8 signalMode);                             // start intialise external intterupt (3)  sequance that will be on pin b2
void EX_Int2_B2_Enable		(	void);                                      //enable the intterupt and allow it to start activate
void EX_Int2_B2_Disable	(	void);                                          // disablle and prevent interupt (1)

void EX_Int2_B2_SignalMode	(	u8 signalMode);                             //used to receive signals
void EX_Int2_B2_SetCallBack( 	void(*ptrFn)(void) );                       // set the function to be called in intrupt(2)
void EX_Int2_B2_ClearFlag	(	void);                                      //clear intterupt flag

void INT2_vect (void) __attribute__ ((used)) __attribute__ ((signal)); 		//(signal,__INTR_ATTRS)









#endif // EX_INTERRUPTS_H_INCLUDED
