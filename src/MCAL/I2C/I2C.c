#include "I2C.h"


void (*I2C_callBackFn)(void) =NULLptr;




// void I2C_Init()
// {
//     TWBR = BITRATE(TWSR=0x00);	// Get bit rate register value by formula 
// }

void I2C_init(u8 address, bool enableGeneralCall, u8 ps, u8 bitRate)
{
    // TWAR = (address << 1) |  enableGeneralCall;
    TWAR = (address << 1);
    
    TWBR = bitRate;
    WRITE_BIT(TWSR, TWPS1,  GET_BIT(ps,1) );
    WRITE_BIT(TWSR, TWPS0,  GET_BIT(ps,0) );

    SET_BIT(TWCR, TWEN);
    SET_BIT(TWCR,TWINT);

    // I2C_interruptEnable();
    // SET_BIT(TWCR, TWEA);

}


u8 I2C_Start(u8 write_address, bool rw)
{
    volatile u8 status;
    
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); // Enable TWI, generate START 
    
    while(!(TWCR&(1<<TWINT)))
    ;	            // Wait until TWI finish its current job 
    
    // status=TWSR&0xF8;		                // Read TWI status register 
    
    // if(status!=0x08)		                // Check if START transmitted or not
    // {return 0;}			                    // Return 0 to indicate start condition fail 
    
    TWDR = ((write_address<<1) | rw);		            // Write SLA+W in TWI data register 
    // TWCR = (1<<TWEN)|(1<<TWINT);	        // Enable TWI & clear interrupt flag 
    
    // while(!(TWCR&(1<<TWINT)))
    // ;	            // Wait until TWI finish its current job 
    
    // status=TWSR&0xF8;		                // Read TWI status register 
    
    // if(status==0x18)		                // Check for SLA+W transmitted &ack received 
    // {return 1;}			                    // Return 1 to indicate ack received 
    
    // if(status==0x20)		                // Check for SLA+W transmitted &nack received 
    // {return 2;}			                    // Return 2 to indicate nack received 
    // else    {return 3;}			            // Else return 3 to indicate SLA+W failed 
}


u8 I2C_Write(u8 data)
{
    // volatile u8 status;		        // Declare variable 
    TWDR = data;			        // Copy data in TWI data register 
    TWCR = (1<<TWEN)|(1<<TWINT);	// Enable TWI and clear interrupt flag 
    while(!GET_BIT(TWCR,TWINT))
    ;	            // Wait until TWI finish its current job 
    SET_BIT(TWCR,TWINT);
    // status = TWSR & 0xF8;		    // Read TWI status register 
    
    // if(status==0x28)		        // Check for data transmitted &ack received 
    // {return 0;}			            // Return 0 to indicate ack received 
    
    // if(status==0x30)		        // Check for data transmitted &nack received 
    // {return 1;}			            // Return 1 to indicate nack received 
    // else
    // {return 2;}		                // Else return 2 for data transmission failure 
}


void I2C_Stop()			
{
    TWCR=(1<<TWSTO)|(1<<TWEN)|(1<<TWINT);  // Enable TWI, generate stop
    // while(GET_BIT(TWCR,TWINT))
    ;	               // i think wrong, ..Wait until stop condition execution
}



u8 I2C_Read_Ack()		// I2C read ack function 
{
    TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA); // Enable TWI, generation of ack 
    while(!GET_BIT(TWCR,TWINT))
    ;	// Wait until TWI finish its current job 
    
    return TWDR;			// Return received data 
}


u8 I2C_Read_NoAck()		// I2C read nack function 
{
    TWCR = (1<<TWINT)|(1<<TWEN);	// Enable TWI and clear interrupt flag 
    while(!GET_BIT(TWCR,TWINT))
    ;	// Wait until TWI finish its current job 
    
    return TWDR;		// Return received data 
}











void I2C_onRequestSetCallBack(void (*ptr)(void)){
    I2C_callBackFn = ptr;
}


void TWI_vect(void){
    I2C_callBackFn();
    SET_BIT(TWCR,TWINT);
}






























/*
void (*I2C_callBackFn)(void) =NULLptr;

//SCL frequency =    CPU Clock frequency / (16 + (2*(TWBR)*4^TWPS))
void I2C_init(u8 address, bool enableGeneralCall, u8 ps, u8 bitRate){
    TWAR = (address << 1) |  enableGeneralCall;
    
    TWBR = bitRate;
    WRITE_BIT(TWSR, TWPS1,  GET_BIT(ps,1) );
    WRITE_BIT(TWSR, TWPS0,  GET_BIT(ps,0) );

    I2C_interruptEnable();
    SET_BIT(TWCR, TWEA);


}


void I2C_temporalDisconnect(){
    CLEAR_BIT(TWCR, TWEA);
}

void I2C_rejoinBus(){
    SET_BIT(TWCR, TWEA);
}

u8   I2C_read(){
    return TWDR;
}

void I2C_connectTo_SelectRW(u8 slave, bool RWVal){
    //  1 X 1 0 X 1 0 X
    // start condition
    WRITE_BITS(TWCR, 0b10110110, 0xA4);
    
    switch ( (TWSR & 0b11111000 ))
    {
    case I2C_status_StartCond_Transmitted:              break;
    case I2C_status_RepeatedStartCond_Transmitted:      break;
    case I2C_status_SLA_W_sent_AckReceived:             break;
    case I2C_status_SLA_W_sent_NoAckReceived:           break;
    case I2C_status_Data_sent_AckReceived:              break;
    case I2C_status_Data_sent_NoAckReceived:            break;
    case I2C_status_LostArbitration:                    break;

    }

    
}
void I2C_sendByte(u8 data);
void I2C_connectAgain();
void I2C_stopConnection(){
    SET_BIT(TWCR, TWSTO);
}

void I2C_interruptEnable(){
    GI_Enable();
    SET_BIT(TWCR,TWINT);
    SET_BIT(TWCR, TWIE);
}

void I2C_interruptDisable(){
    CLEAR_BIT(TWCR, TWIE);
    
}


bool I2C_writingCollisionVal(){
    return GET_BIT(TWCR, TWWC);
}

void I2C_onRequestSetCallBack(void (*ptr)(void)){
    I2C_callBackFn = ptr;
}

void TWI_vect(void){

    I2C_callBackFn();
    
    SET_BIT(TWCR,TWINT);

}

*/









/*
//SCL frequency =    CPU Clock frequency / (16 + (2*(TWBR)*4^TWPS))
void I2C_setSelfAddress(u8 address, bool callRecogEn){
    TWAR = (address<<1) | callRecogEn;
}


//SCL frequency =    CPU Clock frequency / (16 + (2*(TWBR)*4^TWPS))
void I2C_setBitRateAndPrescaler(u8 br, u8 ps){
    TWBR = br;
    WRITE_BITS(TWSR, 0x03, ps);
}

//SCL frequency =    CPU Clock frequency / (16 + (2*(TWBR)*4^TWPS))
void I2C_init(u8 address, bool callRecogEn, u8 br,u8 ps){
    I2C_setSelfAddress(address,callRecogEn);
    I2C_setBitRateAndPrescaler(br, ps);
    SET_BIT(TWCR, TWINT);
    SET_BIT(TWCR, TWEN);

}


// when this bit (TWIE) is written to one, and the I-bit in SREG is set, the TWI interrupt request will be activated for as long as the TWINT Flag is high.
void I2C_interruptEnable(){
    GI_Enable();
    SET_BIT(TWCR, TWIE);
    SET_BIT(TWCR, TWINT);

}
void I2C_interruptDisable(){
    CLEAR_BIT(TWCR, TWIE);
}

//till it is cleared, SCL low bit is stretched, so it must be done after finishing a task
void I2C_clearInterruptFlag(){
    SET_BIT(TWCR, TWINT);
}


void I2C_disconnectTemporarly(){
    CLEAR_BIT(TWCR, TWEN);
}

void I2C_start(void){
    SET_BIT(TWCR, TWSTA);
}

void I2C_connectTo(u8 slave){
    I2C_start();
    TWDR = slave;

}
void I2C_stop(void){
    SET_BIT(TWCR, TWSTO);
    // SET_BIT(TWCR, TWINT);

}


void I2C_sendData(u8 data){

    TWDR = data;
    // SET_BIT(TWCR, TWINT);
}

u8 I2C_receive(u8 ack){

}



void I2C_onRequestSetCallback(void (*ptr)(void)){
    ptr = I2C_callBackFn;
}


void TWI_vect(){
    I2C_callBackFn();

}


*/