#include "I2C.h"

// initialize I2C communication
void i2c_init(void)
{
    // set I2C bit rate
    TWBR = I2C_BITRATE;
}

// start I2C communication
void i2c_start(void)
{
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ;
}

// stop I2C communication
void i2c_stop(void)
{
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

// send a byte to the I2C bus
void i2c_send(u8 data)
{
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ;
}

// receive a byte from the I2C bus
u8 i2c_receive(u8 ack)
{
    TWCR = (1 << TWEN) | (ack << TWEA) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ;
    return TWDR;
}
