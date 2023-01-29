#ifndef WATCHDOG_TIMER_H_INCLUDED
#define WATCHDOG_TIMER_H_INCLUDED

#include "../General_Interrupts/General_Interrupts.h"

#include "../../UTILS/BitMath.h"
#include "../../UTILS/STD_Types.h"
#include "../../Memory_map/mem_map.h"


#define WatchDog_PS_16K			0
#define WatchDog_PS_32K			1
#define WatchDog_PS_64K			2
#define WatchDog_PS_128K		3
#define WatchDog_PS_256K		4
#define WatchDog_PS_512K		5
#define WatchDog_PS_1024K		6
#define WatchDog_PS_2048K		7


// WDTCR 
// WDTOE WDE WDP2 WDP1 WDP0


void WatchDog_SetPreScaler(	u8 ps);

void WatchDog_On(			u8 ps);
void WatchDog_Disable(		void );






#endif 		// WATCHDOG_TIMER_H_INCLUDED