#include "Shell.h"


volatile u8 available_login_trials 	= 3,
			userCmd					= 0;

volatile Users_user loggedUser;

volatile bool Shell_loginTool= SHELL_KEYPAD_LOGIN;

void Shell_firstLogin()
{
    
}




void Shell_login(Users_usersList *usersList)
{
    LCD_WriteString("login... use # to enter"); 
	Shell_Pause();
	LCD_Clear();

	LCD_WriteString("user: ");
	
	volatile u8 tempCharUser            = 0,
				tempStrUser[20]         = {0},
				tempIndexUser           = 0,
	
				tempCharPass            = 0,
				tempStrPass[20]         = "",
				tempIndexPass           = 0,
				
				tempStrPasswordComp[20] = {0}	;

	volatile u8 cmdKP = 0,
				cmdBT = 0;

	volatile bool tempIsAdmin = 0;
	available_login_trials = 3;

	while (tempCharUser != '#' )
	{
		cmdKP = KeyPad_GetRead_click();
		cmdBT = Bluetooth_RxChar();
		if		(cmdKP) {tempCharUser = cmdKP; Shell_loginTool = SHELL_KEYPAD_LOGIN;		}
		else if	(cmdBT) {tempCharUser = cmdBT; Shell_loginTool = SHELL_BLUETOOTH_LOGIN; 	}
		else			{tempCharUser = 0;		}

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
					cmdKP = KeyPad_GetRead_click();
					cmdBT = Bluetooth_RxChar();
					if		(cmdKP) {tempCharPass = cmdKP; Shell_loginTool = SHELL_KEYPAD_LOGIN;		}
					else if	(cmdBT) {tempCharPass = cmdBT; Shell_loginTool = SHELL_BLUETOOTH_LOGIN; 	}
					else			{tempCharPass = 0;		}

					if((tempCharPass != '#') && (tempCharPass != 0))
					{
						LCD_WriteData('*');
						tempStrPass[tempIndexPass] = tempCharPass;
						++tempIndexPass;
					}
					else if(tempCharPass == '#')
					{
						tempStrPass[tempIndexPass] = '\0';
						LCD_Clear();
						
						// if password true, login, break, 
						// else if password false --> Shell_wrongUser();
						Users_ReadEntry(usersList, tempStrUser, tempStrPasswordComp, &tempIsAdmin);
						if (!strcmp(tempStrPasswordComp, tempStrPass))
						{
							LCD_Clear();

							strcpy(loggedUser.username, tempStrUser); 
							strcpy(loggedUser.password, tempStrPass);
							loggedUser.isAdmin = tempIsAdmin;
							available_login_trials = 3;
							
							if((loggedUser.isAdmin == FALSE) && (Shell_loginTool == SHELL_BLUETOOTH_LOGIN))
							{
								LCD_Clear();
								LCD_WriteString("only admins can use bluetooth!");
								_delay_ms(2000);
								LCD_Clear();

								Shell_login(usersList); //recursion
								return;
							}
							else
							{	
								LCD_WriteString((u8*)"Welcome home ^_^");
								Shell_Pause();
								LCD_Clear();
								break;
							}
						}
						else
						{
							Shell_wrongUser();
							tempCharPass =	tempIndexPass = 0;
							tempIndexPass =	tempIndexUser = 0;
							
							LCD_WriteString((u8*)"pswd: ");
						}
					}
				}
				break;
			}
			else
			{
				tempCharPass  =	tempCharUser  = 0;
				tempIndexPass =	tempIndexUser = 0;
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


void Shell_cmdChecker()
{
	volatile u8 chBT = KeyPad_GetRead_click(),
				chKP = Bluetooth_RxChar()    ;

	if 		    (chKP)
	{
		Shell_loginTool = SHELL_KEYPAD_LOGIN;			userCmd = chKP;
	}
	else if		(chBT)
	{
		Shell_loginTool = SHELL_BLUETOOTH_LOGIN;		userCmd = chBT;
	}
	else
	{	
		userCmd = 0;
	}
}


void Shell_cmdExecuter(Users_usersList *usersList)
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

			LCD_WriteString("A:usrMn B:logOut");         LCD_WriteString("#:cont.    *:esc");                userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(usersList); break;}
			LCD_WriteString("C:adUsr D:edtUsr");         LCD_WriteString("#:cont.    *:esc");                userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(usersList); break;}
			LCD_WriteString("0:doorTog 1:LED1");         LCD_WriteString("#:cont.    *:esc");                userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(usersList); break;}
			LCD_WriteString("2:LED2    3:LED3");         LCD_WriteString("#:cont.    *:esc");                userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(usersList); break;}
			LCD_WriteString("4:LED4    5:LED5");         LCD_WriteString("#:cont.    *:esc");                userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(usersList); break;}
			LCD_WriteString("6:dimmer on/lvl/off");      LCD_WriteString(" #cont. *:esc");                   userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(usersList); break;}
			LCD_WriteString("7:AC auto/lvl/off");        LCD_WriteString(" #:cont.  *:esc");                 userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(usersList); break;}
			LCD_WriteString("8:AC man/lvl/off");         LCD_WriteString("#:cont.    *:esc");                userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(usersList); break;}
			LCD_WriteString("9:printUsersList");         LCD_WriteString("#:cont.    *:esc");                userCmd = Shell_WaitCmd();                 if(userCmd == '#'){LCD_Clear();}                else if(userCmd == '*') {LCD_Clear(); break;}                else { Shell_cmdExecuter(usersList); break;}
			
			
		}break;
		case SHELL_CMD_LOGOUT:
		{
			LCD_Clear();
			Shell_login(usersList);
			
		}break;
		case SHELL_CMD_ADD_USER:
		{
			LCD_Clear();
			if		(loggedUser.isAdmin == FALSE)
			{
				LCD_WriteString("you cannot, you are not admin!"); Shell_Pause(); LCD_Clear();
			}
			else if	(loggedUser.isAdmin == TRUE)
			{
				volatile u8 tempCharUser            = 0,
							tempStrUser[20]         = {0},
							tempIndexUser           = 0,
				
							tempCharPass            = 0,
							tempStrPass[20]         = {0},
							tempIndexPass           = 0,
							
							tempStrPasswordComp[20] = {0}	;
				
				volatile bool tempIsAdmin = FALSE;

				LCD_WriteString("new user: "); 
				strcpy(tempStrUser, Shell_enterStr(FALSE));
				LCD_Clear();
				
				if(Users_IsUserExist(usersList, tempStrUser))
				{
					LCD_WriteString("user already exists");
					_delay_ms(2000);
					LCD_Clear();
				}
				else
				{

					LCD_WriteString("new pswd: "); 
					strcpy(tempStrPass, Shell_enterStr(TRUE));
					LCD_Clear();

					LCD_WriteString("is Admin? (1 TRUE/0 FALSE): "); 
					(Shell_WaitCmd() == '1')  ?  (tempIsAdmin = 1)  :  (tempIsAdmin = 0);
					LCD_WriteData(tempIsAdmin+48);
					_delay_ms(2000);
					LCD_Clear();


					Users_AddEntry(usersList, tempStrUser, tempStrPass, tempIsAdmin);
					LCD_WriteString("user is added successfully! ");
					_delay_ms(1500);
					LCD_Clear();
				}
			}
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
		}break;
		case SHELL_CMD_EDIT_USER:
		{
			LCD_Clear();
			if		(loggedUser.isAdmin == FALSE)
			{
				LCD_WriteString("you cannot, you are not admin!"); Shell_Pause(); LCD_Clear();
			}
			else if	(loggedUser.isAdmin == TRUE)
			{

			}
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
		}break;
		case SHELL_CMD_DOOR_TOGGLE:
		{
			LCD_Clear();

			if(loggedUser.isAdmin == TRUE)
			{
				static volatile bool doorState = SHELL_DOOR_LOCKED;
				Servo_write(doorState*180);

				switch(doorState)
				{
					case SHELL_DOOR_UNLOCKED: LCD_WriteString("you closed door :("); break;
					case SHELL_DOOR_LOCKED:   LCD_WriteString("you opened door :)"); break;
				}
				doorState = !doorState;

				_delay_ms(1000);
			}
			else
			{
				LCD_WriteString("you aren't admin! press# to cont");
				Shell_Pause();
			}
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
			
		}break;
		case SHELL_CMD_LED1_TOGGLE:
		{
			LCD_Clear();
			static volatile bool LED1State = SHELL_DOOR_LOCKED;
			LED_ToggleLED(LED0);

			switch(LED1State)
			{
				case SHELL_DOOR_UNLOCKED: LCD_WriteString("LED1 turned off :("); break;
				case SHELL_DOOR_LOCKED:   LCD_WriteString("LED1 turned on  :)"); break;
			}
			LED1State = !LED1State;

			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
		}break;
		case SHELL_CMD_LED2_TOGGLE:
		{
			LCD_Clear();
			static volatile bool LED2State = SHELL_DOOR_LOCKED;
			LED_ToggleLED(LED1);

			switch(LED2State)
			{
				case SHELL_DOOR_UNLOCKED: LCD_WriteString("LED2 turned off :("); break;
				case SHELL_DOOR_LOCKED:   LCD_WriteString("LED2 turned on  :)"); break;
			}
			LED2State = !LED2State;

			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
			
		}break;
		case SHELL_CMD_LED3_TOGGLE:
		{
			LCD_Clear();
			static volatile bool LED3State = SHELL_DOOR_LOCKED;
			LED_ToggleLED(LED2);

			switch(LED3State)
			{
				case SHELL_DOOR_UNLOCKED: LCD_WriteString("LED3 turned off :("); break;
				case SHELL_DOOR_LOCKED:   LCD_WriteString("LED3 turned on  :)"); break;
			}
			LED3State = !LED3State;

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
		case SHELL_CMD_PRINT_USERS_LIST:
		{
			LCD_Clear();
			static volatile u8 	strList[][20]={""},
								ct=0;

			strList[0][0] = "";
			ct=0;

			Users_GetUsersList(usersList, &ct, strList);
			for(u8 i=0; i<3; i++)
			{
				LCD_WriteString(strList[i]);
				_delay_ms(1000);
				LCD_Clear();
			}
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("press A for user manual");
			
			
			
		}break;
	}
    
}

u8 Shell_WaitCmd()
{
	volatile u8 cmdKP = 0,
				cmdBT = 0;

	while(1){
		cmdKP = KeyPad_GetRead_click();
		cmdBT = Bluetooth_RxChar();

		if		(cmdKP) {Shell_loginTool = SHELL_KEYPAD_LOGIN; 		return cmdKP;}
		else if	(cmdBT) {Shell_loginTool = SHELL_BLUETOOTH_LOGIN; 	return cmdBT;}
	}
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
	while(1)
	{
		if 		    (KeyPad_GetRead_click() == '#')
		{
			Shell_loginTool = SHELL_KEYPAD_LOGIN;			return;
		}
		else if		(Bluetooth_RxChar()     == '#')
		{
			Shell_loginTool = SHELL_BLUETOOTH_LOGIN;		return;
		}
	}
}


u8* Shell_enterStr(bool isHidden)
{
	static volatile u8 	str[20]="",
						ch=0,
						indx=0,
						chBT=0,
						chKP=0;
	
	str[0]="";
	ch=0,
	indx=0;

	while (ch != '#' )
	{
		chBT = Bluetooth_RxChar();
		chKP = KeyPad_GetRead_click();
		if		(chBT)	{ch =chBT; 	Shell_loginTool = SHELL_BLUETOOTH_LOGIN;}
		else if	(chKP)	{ch =chKP; 	Shell_loginTool = SHELL_KEYPAD_LOGIN;	}
		else 			{ch =0;		}

		if((ch != '#') && (ch != 0))
		{
			switch(isHidden){case FALSE: LCD_WriteData(ch); break; 		case TRUE: LCD_WriteData('*'); break;}
			str[indx] = ch;
			++indx;
		}
		else if(ch == '#')
		{
			str[indx]='\0';
			return str;
		}
	}
}

