#include "WatchDog_Timer.h"

void WatchDog_SetPreScaler(u8 ps){
	WRITE_BIT(WDTCR, WDP2, 	GET_BIT(ps, 2) );	WRITE_BIT(WDTCR, WDP1, 	GET_BIT(ps, 1) );	WRITE_BIT(WDTCR, WDP0, 	GET_BIT(ps, 0) );
}



void WatchDog_On(u8 ps){
	WatchDog_SetPreScaler(ps);
	SET_BIT(  WDTCR, WDE  );
	SET_BIT(  WDTCR, WDTOE  );

}



void WatchDog_Disable(){
	CLEAR_BIT(  WDTCR, WDE  );

}














