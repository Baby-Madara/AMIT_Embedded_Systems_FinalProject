## MCU
	UART - LCD - KeyPad - tempSen  - Lamps[5] - dimmer    - ACmotor   - alarm                                  - servoDoor 
	UART - LCD - KeyPad - easy ADC - easy     - easy(pwm) - easy(PWM) - easy (buzzer for emergency not alarm) 





## objects
	users[20]

	 IUOI
	 0

| cmd                                                           |done/notDone 	|
|---------------------------------------------------------------|---------------|
|if (isAdmin == TRUE)    {use keyPad or BLUETOOTH    }	        |	__x__		|
|if (isAdmin == FALSE)   {use keyPad only            }	        |	__x__		|
|if (isAdmin ==FALSE)     {"cannot control door"   }	        |	__x__		|
|if (isAdmin ==TRUE)      {--"add/remove any user" }	        |	_x_ __		|
|userAvailableTrials = 3 , if 3 trials fail, alarm till reset	|	__x__	    |


userList is saved in EEPROM









