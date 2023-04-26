#include "Shell.h"


volatile u8 loggedUser[20]   = "",
            cmdBufferLCD[20] = "",
            
            available_login_trials = 3
                                ;








void Shell_firstLogin()
{

}

void Shell_login()
{

}

void Shell_systemInit()
{
    LCD_Init();
    KeyPad_Init();
    
}


void Shell_cmdChecker()
{

    
    
    if      (!strcmp(cmdBufferLCD, "login"))
    {

    }
    else if (!strcmp(cmdBufferLCD, "remove-user"))
    {

    }
    
    else if (!strcmp(cmdBufferLCD, "add-user"))
    {

    }
    
    else if (!strcmp(cmdBufferLCD, "add-user"))
    {

    }
    
    else if (!strcmp(cmdBufferLCD, "add-user"))
    {

    }
    
    else if (!strcmp(cmdBufferLCD, "add-user"))
    {

    }
    

}





