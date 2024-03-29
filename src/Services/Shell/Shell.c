#include "Shell.h"


volatile u8 available_login_trials 	= 3;
volatile u8 userCmd					= 0;
volatile u8 currentTemperature      = 0;

volatile Users_user loggedUser;

volatile bool Shell_loginTool= SHELL_KEYPAD_LOGIN;


volatile u16 firstNodeAddr = 0x0005;


void Shell_firstLogin()
{
    
}


void Shell_login(Users_usersList *usersList)
{
	volatile u8	tempStrPasswordComp[20] = {0}   ;
	volatile u8	tempStrUser[20]         = {0}   ;
	volatile u8	tempStrPass[20]         = {0}   ;
	volatile bool tempIsAdmin = 0;


	available_login_trials = 3;
	
    LCD_WriteString("login... use # to enter"); 
	Shell_Pause();
	LCD_Clear();

	LCD_WriteString("user: ");
	strcpy(tempStrUser, Shell_enterStr(FALSE));
	LCD_Clear();
	
	while(1)
	{
		// if user is right, 	check password
		// else, 				wrongUser(), insert user again
		if( Users_IsUserExist(usersList, tempStrUser)  )
		{
			
			LCD_Clear();
			LCD_WriteString((u8*)"pswd: ");
			strcpy(tempStrPass, Shell_enterStr(TRUE));
			LCD_Clear();

			Users_ReadEntry(usersList, tempStrUser, tempStrPasswordComp, &tempIsAdmin);
			
			// 		// if password true, login, break, 
			// 		// else if password false --> Shell_wrongUser();
			if (!strcmp(tempStrPasswordComp, tempStrPass) )
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
					
					Shell_login(usersList); 			//recursion
					return;
				}
				else
				{	
					LCD_WriteString((u8*)"Welcome home ^_^");
					LCD_WriteString((u8*)"press # to cont");
					Shell_Pause();
					LCD_Clear();
					LCD_WriteString((u8*)"A:menu");
					return;
				}
			}
			else
			{
				Shell_wrongUser();
				// LCD_WriteString((u8*)"pswd: ");
			}
		}
		else
		{
			Shell_wrongUser();
			LCD_WriteString((u8*)"user: ");
			strcpy(tempStrUser, Shell_enterStr(FALSE));
			LCD_Clear();
		}
	}
}


void Shell_systemInit()
{
	LCD_Init();
	KeyPad_Init();
	Bluetooth_Init();

	LED_InitLED(LED0);
	LED_InitLED(LED1);
	LED_InitLED(LED2);

	ADC_DisableAutoTrigger();
	ADC_Init(ADC_CLK_PS_128);
	Stepper_init();
	// ADC_IntEnable();
	
	LED_DimmerInit();

}


void Shell_cmdChecker()
{
	volatile u8 chBT = KeyPad_GetRead_click();
	volatile u8 chKP = Bluetooth_RxChar()    ;

	if 		(chKP)
	{
		Shell_loginTool = SHELL_KEYPAD_LOGIN;			userCmd = chKP;
	}
	else if	(chBT)
	
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
			// SHELL_CMD_PRINT_USERS_LIST     '9'


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
				volatile u8 tempStrUser[20]         = {0};
				volatile u8 tempStrPass[20]         = {0};
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

					LCD_WriteString("is Admin? (1:TRUE/0:FALSE): "); 
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
			LCD_WriteString("A:menu");
			
			
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
				volatile u8 tempStrNewUser[20]      = {0};
				volatile u8 tempStrPass[20]         = {0};
				volatile u8 tempStrOldUser[20]      = {0};
				volatile u8 tempCmd 				= 0  ;
				volatile bool tempIsAdmin = FALSE;

				LCD_Clear();
				LCD_WriteString("#:edit *:del ");
				tempCmd = Shell_WaitCmd();
				LCD_Clear();
				if (tempCmd == '#')
				{
					LCD_Clear();
					LCD_WriteString("old user: ");
					strcpy(tempStrOldUser, Shell_enterStr(FALSE));
					LCD_Clear();
					if(Users_IsUserExist(usersList, tempStrOldUser))
					{
						LCD_Clear();
						LCD_WriteString("new user: ");
						strcpy(tempStrNewUser, Shell_enterStr(FALSE));
						LCD_Clear();
						LCD_WriteString("new password: ");
						strcpy(tempStrPass, Shell_enterStr(TRUE));
						LCD_Clear();
						LCD_WriteString("make admin? 1:yes 0:no ");
						tempIsAdmin = (Shell_WaitCmd()-48);
						LCD_Clear();
						Users_EditEntry(usersList, tempStrOldUser, tempStrNewUser, tempStrPass, tempIsAdmin);
						
					}
					else
					{
						LCD_Clear();
						LCD_WriteString("user does not exist!");
						_delay_ms(2000);
						LCD_Clear();
					}
				}
				else if (tempCmd == '*')
				{
					LCD_Clear();
					LCD_WriteString("user: ");
					strcpy(tempStrOldUser, Shell_enterStr(FALSE));
					LCD_Clear();
					if(Users_IsUserExist(usersList, tempStrOldUser))
					{
						Users_DeleteEntry(usersList, tempStrOldUser);
						LCD_Clear();
						LCD_WriteString("user is deleted successfully");
						_delay_ms(2000);
						LCD_Clear();
						
					}
					else
					{
						LCD_Clear();
						LCD_WriteString("user does not exist!");
						_delay_ms(2000);
						LCD_Clear();
					}
				}
				
				
				///////////////////////
			}
				
			
			LCD_Clear();
			LCD_WriteString("A:menu");
			
		}break;
		case SHELL_CMD_DOOR_TOGGLE:
		{
			LCD_Clear();
			if(loggedUser.isAdmin == TRUE)
			{
				static volatile bool doorState = SHELL_DOOR_LOCKED;
				// Servo_write(doorState*180);
				switch(doorState)
				{
					case SHELL_DOOR_UNLOCKED: Stepper_open();  LCD_WriteString("you closed door :("); break;
					case SHELL_DOOR_LOCKED:   Stepper_close(); LCD_WriteString("you opened door :)"); break;
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
			LCD_WriteString("A:menu");
			
			
			
		}break;
		case SHELL_CMD_LED1_TOGGLE:
		{
			LCD_Clear();
			static volatile bool LED1State = SHELL_DOOR_LOCKED;
			LED_ToggleLED(LED0);
			switch(LED1State)
			{
				case SHELL_LED_OFF: LCD_WriteString("LED1 turned off :("); break;
				case SHELL_LED_ON:   LCD_WriteString("LED1 turned on  :)"); break;
			}
			LED1State = !LED1State;
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("A:menu");
			
			
		}break;
		case SHELL_CMD_LED2_TOGGLE:
		{
			LCD_Clear();
			static volatile bool LED2State = SHELL_DOOR_LOCKED;
			LED_ToggleLED(LED1);
			switch(LED2State)
			{
				case SHELL_LED_OFF: LCD_WriteString("LED2 turned off :("); break;
				case SHELL_LED_ON:   LCD_WriteString("LED2 turned on  :)"); break;
			}
			LED2State = !LED2State;
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("A:menu");
			
			
			
		}break;
		case SHELL_CMD_LED3_TOGGLE:
		{
			LCD_Clear();
			static volatile bool LED3State = SHELL_DOOR_LOCKED;
			LED_ToggleLED(LED2);
			switch(LED3State)
			{
				case SHELL_LED_OFF: LCD_WriteString("LED3 turned off :("); break;
				case SHELL_LED_ON:   LCD_WriteString("LED3 turned on  :)"); break;
			}
			LED3State = !LED3State;
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("A:menu");
			
		}break;
		case SHELL_CMD_LED4_TOGGLE:
		{
			LCD_Clear();
			static volatile bool LED4State = SHELL_DOOR_LOCKED;
			LED_ToggleLED(LED3);
			switch(LED4State)
			{
				case SHELL_LED_OFF: LCD_WriteString("LED4 turned off :("); break;
				case SHELL_LED_ON:   LCD_WriteString("LED4 turned on  :)"); break;
			}
			LED4State = !LED4State;
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("A:menu");
			
			
		}break;
		case SHELL_CMD_LED5_TOGGLE:
		{
			
			LCD_Clear();
			static volatile bool LED5State = SHELL_DOOR_LOCKED;
			LED_ToggleLED(LED4);
			switch(LED5State)
			{
				case SHELL_LED_OFF: LCD_WriteString("LED5 turned off :("); break;
				case SHELL_LED_ON:   LCD_WriteString("LED5 turned on  :)"); break;
			}
			LED5State = !LED5State;
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("A:menu");
			
			
			
		}break;
		case SHELL_CMD_LED_DIMMER_LEVEL:
		{
			volatile u8 lvl=0;
			LCD_Clear();
			LCD_WriteString("Dimmer level (0:5): ");
			lvl = Shell_WaitCmd();
			LCD_WriteData(lvl);

			// LED_DimmerVal(0);
			LED_DimmerVal(((lvl-48) % 6)*51);

			_delay_ms(1500);
			LCD_Clear();
			LCD_WriteString("A:menu");
			_delay_ms(1500);
			
			
			
			
		}break;
		case SHELL_CMD_AC_AUTO:
		{
			LCD_Clear();
			LCD_WriteString("you chose AC Auto");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("A:menu");
			
			
		}break;
		case SHELL_CMD_AC_MANUAL:
		{
			volatile u8 lvl=0;
			LCD_Clear();
			LCD_WriteString("Dimmer level (0:5): ");
			lvl = Shell_WaitCmd();
			LCD_WriteData(lvl);
			
			switch (lvl)
			{
				case '0':
				{
					AC_manualLvl(0);
				}break;
				case '1':
				{
					AC_manualLvl(1*200);
				}break;
				case '2':
				{
					AC_manualLvl(2*200);
				}break;
				case '3':
				{
					AC_manualLvl(3*200);
				}break;
				case '4':
				{
					AC_manualLvl(4*200);
				}break;
				case '5':
				{
					AC_manualLvl(5*200);
				}break;
			}
			_delay_ms(1500);
			LCD_Clear();
			LCD_WriteString("A:menu");
			
			
		}break;
		case SHELL_CMD_PRINT_USERS_LIST:
		{
			LCD_Clear();
			volatile u8 strList[10][20]={""};
			volatile u8 ct=0;

			strList[0][0] = "";
			ct=5;

			Users_GetUsersList(usersList, &ct, strList);

			for(u8 i=0; i<ct; i++)
			{
				LCD_WriteString(strList[i]);
				_delay_ms(1000);
				LCD_Clear();
			}
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("A:menu");
			
			
			
		}break;
	}
    
}


u8 Shell_WaitCmd()
{
	volatile u8 cmdKP = 0;
	volatile u8 cmdBT = 0;

	while(1)
	{
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
	static volatile u8 	str[20]="";
	static volatile u8 	ch=0;
	static volatile u8 	indx=0;
	static volatile u8 	chBT=0;
	static volatile u8 	chKP=0;
	
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


void Shell_devicesUpdate()
{
	currentTemperature = AC_currentTemperature(); 	//assume 0-> 10deg    1023->70deg Celcuis
	
}


void Shell_ScreenUpdate()
{
	LCD_GoTo(1, 6);
	LCD_WriteString("temp ");
	LCD_WriteInt(AC_currentTemperature());
	LCD_WriteString(" C");
}


