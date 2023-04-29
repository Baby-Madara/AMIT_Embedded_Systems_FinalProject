#include "Shell.h"



volatile u8 available_login_trials 	= 3,
			userCmd					= 0;


void Shell_firstLogin()
{
    
}




void Shell_login(Users_usersList *usersList)
{
    LCD_WriteString("login... use # to enter"); 
	Shell_Pause();
	LCD_Clear();

	LCD_WriteString("user: ");
	
	volatile u8 tempCharUser=0,
				tempStrUser[20]={0},
				tempIndexUser = 0,
	
				tempCharPass=0,
				tempStrPass[20]={0},
				tempIndexPass = 0,
				
				tempStrPasswordComp[20]={0}	;
				
	volatile bool tempIsAdmin = 0;

	available_login_trials = 3;

	while (tempCharUser != '#' )
	{
		tempCharUser = KeyPad_GetRead_click();
		if((tempCharUser != '#') && (tempCharUser != 0))
		{
			LCD_WriteData(tempCharUser);
			tempStrUser[tempIndexUser] = tempCharUser;
			++tempIndexUser;
		}
		else if(tempCharUser == '#')
		{
			tempStrUser[tempIndexUser]='\0';
			
			if( Users_IsUserExist(usersList, tempStrUser)  )
			{
				LCD_Clear();
				LCD_WriteString((u8*)"pswd: ");
				tempCharPass =	tempIndexPass = 0;
				
				while (tempCharPass != '#' )
				{
					tempCharPass = KeyPad_GetRead_click();
					if((tempCharPass != '#') && (tempCharPass != 0))
					{
						LCD_WriteData('*');
						tempStrPass[tempIndexPass] = tempCharPass;
						++tempIndexPass;
					}
					else if(tempCharPass == '#')
					{
						tempStrPass[tempIndexPass]='\0';
						LCD_Clear();
						
						// if password true, login, break, 
						// else if password false --> Shell_wrongUser();
						Users_ReadEntry(usersList, tempStrUser, tempStrPasswordComp, &tempIsAdmin);
						if (!strcmp(tempStrPasswordComp, tempStrPass))
						{
							LCD_Clear();
							LCD_WriteString((u8*)"Welcum ho_e nig");
							Shell_Pause();
							LCD_Clear();
							available_login_trials = 3;
							break;
						}
						else
						{
							Shell_wrongUser();
							tempCharPass =	tempIndexPass = 0;
							LCD_WriteString((u8*)"pswd: ");
						}
					}
				}
				break;
			}
			else
			{
				tempCharPass =	tempCharUser = 0;
				Shell_wrongUser();
				LCD_WriteString((u8*)"user: ");
			}

		}
	}

	LCD_Clear();
	LCD_WriteString((u8*)"Welcome user... ");
	LCD_WriteString((u8*)"press # to cont");
	Shell_Pause();
	LCD_Clear();
	LCD_WriteString("press A for user manual");
    
}

void Shell_systemInit()
{
	LCD_Init();
	KeyPad_Init();
	Bluetooth_Init();

	LED_InitLED(LED0);
	LED_InitLED(LED1);
	LED_InitLED(LED2);
    
    
}


void Shell_cmdChecker(){
	userCmd = KeyPad_GetRead_click();
}


void Shell_cmdExecuter()
{

				
			// SHELL_CMD_USERMANUAL             'A'
			// SHELL_CMD_LOGOUT                 'B'
			// SHELL_CMD_ADD_USER               'C'
			// SHELL_CMD_EDIT_USER              'D'
			// SHELL_CMD_CONTINUE               '#'
			// SHELL_CMD_ESCAPE                 '*'

			// SHELL_CMD_DOOR_TOGGLE           '0'
			// SHELL_CMD_LED1_TOGGLE           '1'
			// SHELL_CMD_LED2_TOGGLE           '2'
			// SHELL_CMD_LED3_TOGGLE           '3'
			// SHELL_CMD_LED4_TOGGLE           '4'
			// SHELL_CMD_LED5_TOGGLE           '5'
			// SHELL_CMD_LED_DIMMER_LEVEL      '6'
			// SHELL_CMD_AC_AUTO               '7'
			// SHELL_CMD_AC_MANUAL             '8'
			// //  #define SHEL_CMD___                     '9'

    switch(userCmd){
		case SHELL_CMD_USERMANUAL: 			// user manual
		{
			LCD_Clear();

			// EACH ROW DO THE FOLLOWING:
			//       print manual (2 rows)          wait user command and save it in userCmd variable              then... 
			//       if      (userCmd is '#')   -->  claerLCD and pass (go to next page)
			//       else if (userCmd is '*')   -->  clearLCD and exit
			//       else                       -->  recurse commandExecuter (execute the command equivalent to userCmd)

			LCD_WriteString("A:usrMn B:logOut");         LCD_WriteString("#:cont.    *:esc");                userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(); break;}
			LCD_WriteString("C:adUsr D:edtUsr");         LCD_WriteString("#:cont.    *:esc");                userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(); break;}
			LCD_WriteString("0:doorTog 1:LED1");         LCD_WriteString("#:cont.    *:esc");                userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(); break;}
			LCD_WriteString("2:LED2    3:LED3");         LCD_WriteString("#:cont.    *:esc");                userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(); break;}
			LCD_WriteString("4:LED4    5:LED5");         LCD_WriteString("#:cont.    *:esc");                userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(); break;}
			LCD_WriteString("6:dimmer on/lvl/off");      LCD_WriteString(" #cont. *:esc");                   userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(); break;}
			LCD_WriteString("7:AC auto/lvl/off");        LCD_WriteString(" #:cont.  *:esc");                 userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(); break;}
			LCD_WriteString("8:AC man/lvl/off");         LCD_WriteString("#:cont.    *:esc");                userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(); break;}

			
			
			
		}break;
		case SHELL_CMD_DOOR_TOGGLE:
		{
			LCD_Clear();
			LCD_WriteString("you chose A");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
			
		}break;
		case SHELL_CMD_LED1_TOGGLE:
		{
			LCD_Clear();
			LCD_WriteString("you chose 1");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
		}break;
		case SHELL_CMD_LED2_TOGGLE:
			LCD_Clear();
			LCD_WriteString("you chose 2");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
		{
			
			
			
		}break;
		case SHELL_CMD_LED3_TOGGLE:
		{
			LCD_Clear();
			LCD_WriteString("you chose 3");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
			
		}break;
		case SHELL_CMD_LED4_TOGGLE:
		{
			LCD_Clear();
			LCD_WriteString("you chose 4");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
			
		}break;
		case SHELL_CMD_LED5_TOGGLE:
		{
			LCD_Clear();
			LCD_WriteString("you chose 5");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
			
		}break;
		case SHELL_CMD_LED_DIMMER_LEVEL:
		{
			LCD_Clear();
			LCD_WriteString("you chose 6");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
			
		}break;
		case SHELL_CMD_AC_AUTO:
		{
			LCD_Clear();
			LCD_WriteString("you chose 7");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
			
		}break;
		case SHELL_CMD_AC_MANUAL:
		{
			LCD_Clear();
			LCD_WriteString("you chose 8");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
			
		}break;
		case '9':
		{
			LCD_Clear();
			LCD_WriteString("you chose 9");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
			
		}break;
		case SHELL_CMD_LOGOUT:
		{
			LCD_Clear();
			LCD_WriteString("you chose B");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
			
		}break;
		case SHELL_CMD_ADD_USER:
		{
			LCD_Clear();
			LCD_WriteString("you chose C");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
			
		}break;
		case SHELL_CMD_EDIT_USER:
		{
			LCD_Clear();
			LCD_WriteString("you chose D");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
			
		}break;
	}
    
}

u8 Shell_WaitCmd()
{
	volatile u8 cmd = 0;

	while(!cmd){
		cmd = KeyPad_GetRead_click();
	}
	return cmd;
}

void Shell_wrongUser()
{
    LCD_Clear();
    --available_login_trials;
    if(available_login_trials != 0 )
    {	
        LCD_WriteString("wrong! ");
        LCD_WriteInt(available_login_trials);
        LCD_WriteString(" left");
        _delay_ms(3000);

        LCD_Clear();
        
    }
    else
    {
        LCD_Clear();
        LCD_WriteString("WRONG! reset to stop buzzer");
        
        LED_InitLED(BUZZER);
        LED_SetLED(BUZZER);
        while (1)     ;
    }
}

void Shell_Pause()
{
	while(KeyPad_GetRead_click() != '#');
}

