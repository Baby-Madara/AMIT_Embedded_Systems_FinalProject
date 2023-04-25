#ifndef I2C_H_
#define I2C_H_

#include "../../UTILS/BitMath.h"
#include "../../Memory_map/mem_map.h"
#include "../General_Interrupts/General_Interrupts.h"


// registers:
// TWBR bit rate
// TWSR status reg
//     [TWS7: TWS3] 
//     
//          
// TWCR ctrl reg  [ TWINT TWEA TWSTA TWSTO TWWC TWEN __ TWIE ]
//     TWINT  interrupt flag
//     TWEA   Enable Acknowledge Bit
//     TWSTA  start condition
//     TWSTO  stop
//     TWWC   write
//     TWEN   enable
//     TWIE   interrupt enable
// TWAR adress reg
// TWDR data register

// #define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))



#define I2C_PRESCALER_1   0
#define I2C_PRESCALER_4   1
#define I2C_PRESCALER_16  2
#define I2C_PRESCALER_64  3


#define I2C_WRITE 0
#define I2C_READ  1

#define I2C_ALL_SLAVES 0

typedef enum{
    I2C_status_Bus_Err                       = 0x00,
    I2C_status_StartCond_Transmitted         = 0x08,
    I2C_status_RepeatedStartCond_Transmitted = 0x10,
    I2C_status_SLA_W_sent_AckReceived        = 0x18,
    I2C_status_SLA_W_sent_NoAckReceived      = 0x20,
    I2C_status_Data_sent_AckReceived         = 0x28,
    I2C_status_Data_sent_NoAckReceived       = 0x30,
    I2C_status_LostArbitration               = 0x38,

    // I2C_status_Data_sent_NoAckReceived       = 0x40,
    // I2C_status_LostArbitration               = 0x48,
    // I2C_status_Data_sent_NoAckReceived       = 0x50,
    // I2C_status_LostArbitration               = 0x58,
}I2C_Status;




void I2C_init(u8 address, bool enableGeneralCall, u8 ps, u8 bitRate);
u8 I2C_Start(u8 write_address, bool rw);
u8 I2C_Write(u8 data);
void I2C_Stop();



u8 I2C_Read_Ack();
u8 I2C_Read_NoAck();



void I2C_onRequestSetCallBack(void (*ptr)(void));
void TWI_vect(void) __attribute__ ((used)) __attribute__ ((signal));






























/*
#define I2C_PRESCALER_1   0
#define I2C_PRESCALER_4   1
#define I2C_PRESCALER_16  2
#define I2C_PRESCALER_64  3


#define I2C_WRITE 0
#define I2C_READ  1

#define I2C_ALL_SLAVES 0


typedef enum{
    I2C_status_Bus_Err                       = 0x00,
    I2C_status_StartCond_Transmitted         = 0x08,
    I2C_status_RepeatedStartCond_Transmitted = 0x10,
    I2C_status_SLA_W_sent_AckReceived        = 0x18,
    I2C_status_SLA_W_sent_NoAckReceived      = 0x20,
    I2C_status_Data_sent_AckReceived         = 0x28,
    I2C_status_Data_sent_NoAckReceived       = 0x30,
    I2C_status_LostArbitration               = 0x38,

    I2C_status_Data_sent_NoAckReceived       = 0x40,
    I2C_status_LostArbitration               = 0x48,
    I2C_status_Data_sent_NoAckReceived       = 0x50,
    I2C_status_LostArbitration               = 0x58,
}I2C_Status;

// I2C_Status | ((GET_BIT(TWSR, TWPS1)<<1) | (GET_BIT(TWSR, TWPS0)))


//SCL frequency =    CPU Clock frequency / (16 + (2*(TWBR)*4^TWPS))
void I2C_init(u8 address, bool enableGeneralCall, u8 ps, u8 bitRate);
void I2C_sendByte(u8 data);
u8   I2C_read();

void I2C_connectTo_SelectRW(u8 slave, bool RWVal);
void I2C_connectAgain();
void I2C_stopConnection();

void I2C_onRequestSetCallBack(void (*ptr)(void));

void TWI_vect(void) __attribute__ ((used)) __attribute__ ((signal));

void I2C_interruptEnable();
void I2C_interruptDisable();
bool I2C_writingCollisionVal();

void I2C_temporalDisconnect();
void I2C_rejoinBus();

*/




/*
#define I2C_BITRATE ((F_CPU / F_I2C) - 16) / (2 * 4^I2C_PRESCALER
#define F_I2C 100000UL


void I2C_setBitRateAndPrescaler(u8 br, u8 ps);
void I2C_setSelfAddress(u8 address, bool callRecogEn);
void I2C_init(u8 address, bool callRecogEn, u8 br,u8 ps);

void I2C_interruptEnable();
void I2C_interruptDisable();
void I2C_clearInterruptFlag();

void I2C_disconnectTemporarly();

void I2C_start(void);
void I2C_connectTo(u8 slave);
void I2C_stop(void);

void I2C_sendData(u8 data);
u8 I2C_receive(u8 ack);

void I2C_onRequestSetCallback(void (*ptr)(void));
void TWI_vect(void) __attribute__((signal, used));
*/






/////////////////////////////////////// chatGPT /////////////////////////////////////

/*

// I2C clock frequency
#define F_I2C 100000UL

// I2C bit rate
#define I2C_BITRATE ((F_CPU / F_I2C) - 16) / 2

// initialize I2C communication
void I2C_init(void);

// start I2C communication
void I2C_start(void);

// stop I2C communication
void I2C_stop(void);

// send a byte to the I2C bus
void I2C_send(u8 data);

// receive a byte from the I2C bus
u8 I2C_receive(u8 ack);
*/

/*
I2C (Inter-Integrated Circuit) is a serial communication protocol that is used to communicate with a variety of different devices. It is a half-duplex protocol, which means that data is transferred in only one direction at a time. I2C is often used to communicate with sensors, memory chips, and other devices that have a limited number of input/output pins.

In the I2C communication, there is a master device and one or more slave devices. The master device controls the communication and initiates the data transfer, while the slave devices respond to the requests from the master device. The master device generates the clock signal (SCL) and the slave devices sample the data (SDA) on the rising edge of the clock signal.

In the I2C protocol, each device has a unique address, and the master device communicates with a specific slave device by sending its address to the bus. The slave device with the matching address responds to the request, and the master and slave devices can then exchange data.
*/


#endif // I2C_H_