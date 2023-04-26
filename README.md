# AMIT Embedded Systems Final Project

This is Embedded Systems Course Final Project

## Documentation

### Authors

| Name          | gitHub username | email address                                          | phone number  |
|---------------|-----------------|--------------------------------------------------------|---------------|
| Ahmed Farahat | @Baby-Madara    | ahmed.farahat1@msa.edu.eg - ahmedfarahat1177@gmail.com | +201119027639 |
| Shehab Ashraf |                 |||
| Yousef Gamal  |                 |||
| Tarek Fouad   |                 |||
| Mohamed Magdy |                 |||







### Details

ATMega32 drivers for AMIT Kit with the following hardware (in the HAL layer). Using PlatformIO as IDE on VS Code

## Date

    start date: 23-01-2023                      -                  completed:     __-__-2023

### Aknowledgement

learned embedded systems interfacing from different instructors but special thanks for Moatasem El-Sayed & Sara Abd Rabbo

### Datasheet

    - ADC                 |201
    - Interrupts          |
    - DIO                 |
    - Registers Page     |||    327

### Pinout
(with HAL connections for the AMIT AVR kit)
```
                                    [PDIP]:
                               __________________
    Btn0         (XCK/T0) PB0 |1       @       40| PA0 (ADC0)       N/C
    LCD_RS           (T1) PB1 |2               39| PA1 (ADC1)       Pot
    LCD_RW    (INT2/AIN0) PB2 |3               38| PA2 (ADC2)       Relay
    LCD_EN     (OC0/AIN1) PB3 |4               37| PA3 (ADC3)       Buzzer
    SS              (_SS) PB4 |5               36| PA4 (ADC4)       LCD_D4
    MOSI           (MOSI) PB5 |6               35| PA5 (ADC5)       LCD_D5
    MISO           (MISO) PB6 |7               34| PA6 (ADC6)       LCD_D6
    SCK             (SCK) PB7 |8               33| PA7 (ADC7)       LCD_D7
                       _RESET |9               32| AREF
                          VCC |10   ATMega32   31| GND
                          GND |11              30| AVCC
                        XTAL2 |12              29| PC7 (TOSC2)      LED1
                        XTAL1 |13              28| PC6 (TOSC1)      H_A4
     RX             (RXD) PD0 |14              27| PC5 (TDI)        H_A3
     TX             (TXD) PD1 |15              26| PC4 (TDO)        H_A2
     Btn2          (INT0) PD2 |16              25| PC3 (TMS)        H_A1
     LED2          (INT1) PD3 |17              24| PC2 (TCK)        LED0
     H_En1         (OC1B) PD4 |18              23| PC1 (SDA)        SDA
     H_En2         (OC1A) PD5 |19              22| PC0 (SCL)        SCL
     Btn1          (ICP1) PD6 |20              21| PD7 (OC2)        Servo
                              |__________________|
                                                                         
                    * (_PIN) means inverted logic pin
```
### SW Archeticture
   
```
    **************************************** Software Architecture *******************************************************************************
    *  [UTILS]   || [main]        |                     main.c                                                                                   *
    *            || [Services]    |     structs - classes - user-defined data types - applications                                               *
    *            || [HAL]         | Lamps[1:5] - Dimmer[L6] - Door ctrlr - AC ctrlr - alarm - LCD - keaypad - tempSensor - EEPROM - Btns         *
    *  STD_Types || [MCAL]        | DIO - General_Interrupts - External_Interrupts - ADC - Timers WDTimer - UART - I2C - SPI                     *
    *  BIT_MATH  || [MEM_MAPPING] |                 MCU registers                                                                                *
    **********************************************************************************************************************************************
```

### Warnings

* LCD and SevenSegments cannot be used together
* sevenSegments must be used with parallel programming (NO SEQUENTIAL DELAY CAN BE USED to work properly)


### main()

IT IS USED FOR TESTING DRIVERS. THE DRIVER YOU WANT TO TEST, UNCOMMENT "#define TESTING_DRIVER_NAME" and type the codes you want in its section, this is for ensuring no loss of old test
