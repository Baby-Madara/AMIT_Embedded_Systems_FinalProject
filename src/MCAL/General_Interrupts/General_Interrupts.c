#include "General_Interrupts.h"

void GI_Enable() {		SET_BIT(SREG, SREG_I);		}
void GI_Disable(){		CLEAR_BIT(SREG, SREG_I);	}







