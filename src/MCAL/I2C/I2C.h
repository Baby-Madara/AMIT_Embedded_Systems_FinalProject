#ifndef I2C_H_
#define I2C_H_

#include "../../UTILS/BitMath.h"
#include "../../Memory_map/mem_map.h"

// I2C clock frequency
#define F_I2C 100000UL

// I2C bit rate
#define I2C_BITRATE ((F_CPU / F_I2C) - 16) / 2

// initialize I2C communication
void i2c_init(void);

// start I2C communication
void i2c_start(void);

// stop I2C communication
void i2c_stop(void);

// send a byte to the I2C bus
void i2c_send(u8 data);

// receive a byte from the I2C bus
u8 i2c_receive(u8 ack);

/*
I2C (Inter-Integrated Circuit) is a serial communication protocol that is used to communicate with a variety of different devices. It is a half-duplex protocol, which means that data is transferred in only one direction at a time. I2C is often used to communicate with sensors, memory chips, and other devices that have a limited number of input/output pins.

In the I2C communication, there is a master device and one or more slave devices. The master device controls the communication and initiates the data transfer, while the slave devices respond to the requests from the master device. The master device generates the clock signal (SCL) and the slave devices sample the data (SDA) on the rising edge of the clock signal.

In the I2C protocol, each device has a unique address, and the master device communicates with a specific slave device by sending its address to the bus. The slave device with the matching address responds to the request, and the master and slave devices can then exchange data.
*/


#endif // I2C_H_