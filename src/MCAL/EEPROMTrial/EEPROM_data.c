#include "EEPROM.h"
#include "../../Services/Users/Users.h"




/*
Read Operation :
1. WAit for completion of previous Write operation.
2. EEWE will be cleared once EEPROM write is completed.
3. Load the EEPROM address into EEAR from where the data needs to be read.
4. Trigger the EEPROM read operation by setting EERE (EEPROM Read Enable).
5. Wait for some time (about 1ms) and collect the read data from EEDR.*/
/*To read the data from the EEPROM given the Address*/
 u8 EEPROM_read(short address){
	//Setup Address Register
	EEARL = (u8)address; //LOW Address
	EEARH = (u8)(address>>8); //High Address
	u8 *pointer_return= EEDR;
	// Start Reading and Return Data
	SET_BIT(EECR,EERE);
	return (*pointer_return);
}

/* write data in the EEPROM given the address and the data.*/


void EEPROM_write(short address,  u8 data)
{/*write Operation :
1. Wait till previous write operation is completed(i.e. wait till EEWE becomes zero).
2. Load the EEPROM address into EEAR at which the data has to be stored.
3. Load the data into EEDR which has to be stored in EEPROM.
4. Set the EEMWE (EEPROM Master Write Enable).
5. Within four clock cycles after 4th step, set EEWE(Eeprom Write Enable) to trigger the EEPROM Write Opeartion
*/
	u8 INT_EN=0;
		
	// Setup Address Register
	EEARL = (u8)address;
	EEARH = (u8)(address>>8);
	
	// Put Data in Data Register
	EEDR = data;
	
	// Disable Interrupts 
	if((GET_BIT(SREG,7)==1)) //SREG:status register
	{
		INT_EN = 1;
		CLR_BIT(SREG,7);
	}
	
	// Start Writing
	SET_BIT(EECR,EEMWE);
	SET_BIT(EECR,EEWE);

	while((GET_BIT(EECR,EEWE)==1));//wait till operation is done
	
	// Back
	if (INT_EN==1)
	{
		SET_BIT(SREG,7);
	}
}
/*
EEDR (EEPROM Data Register)
This register contains data to be written to the EEPROM in write operation
and for read operation, it has data read out from EEPROM.
EECR (EEPROM Control Register)
This registers controls all EEPROM operations.
• Bits 7 to 4 – Reserved Bits
These bits are reserved bits and will always read as zero.
• Bit 3 – EERIE: EEPROM Ready Interrupt Enable
To enable the EEPROM Ready Interrupt write one to EERIE ( first set the I bit in SREG )and zero to disable it. The EEPROM Ready interrupt generates a constant interrupt when EEWE is cleared.
• Bit 0 – EERE: EEPROM Read Enable
It is the read strobe to the EEPROM. Write one to the EERE after setting up the correct address in the EEAR Register to trigger the EEPROM read.
You should poll the EEWE bit before starting the read operation. If a write operation is in progress, it is neither possible to read the EEPROM, nor to change the EEAR Register.
EEAR (EEPROM Address Register)
• Bits 15..10 – Reserved Bits
These bits are reserved bits and will always read as zero.
• Bits 9..0 – EEAR9..0: EEPROM Address
*/














void Write_list_struct(Users_usersList* Pointer_User_List){
EEPROM_write(0x00, (*Pointer_User_List).length);
EEPROM_write(0x01, (*Pointer_User_List).maxLength);
EEPROM_write(0x02, (*Pointer_User_List).headPtr);
}







void Write_Struct_EEPROM(Users_userNode *Pointer_struct,u8 User_Number_in_array)
{
EEPROM_write(0xFF, 146);
u8 Size_Struct=sizeof(Users_userNode);
u8 Counter_Two=0;// counter 1 for counting user
u8* Poitr_eeprom=NULL;
Poitr_eeprom=Pointer_struct;
for(;Counter_Two < Size_Struct;)// looop for taking all data for one struct
{
EEPROM_write((0x03)+(Counter_Two)+(User_Number_in_array*Size_Struct),*Poitr_eeprom);
Poitr_eeprom++;
Counter_Two++;
}
}



void Read_all_Struct_EEPROM(Users_userNode*pointer_struct)
{
u8 Counter_One=0;// counter 1 for counting user
u8 Number_of_User = EEPROM_read(0x00);     //get the number of users to read
u8 Size_Struct= sizeof(Users_userNode);   // get size of the struct
for(;Counter_One<Number_of_User;){// loop 1 as the action will be done /user  although nested loop is bad it cant be avoided here
u8 temp_Ddress=(*pointer_struct).next;
u8* Poitr_eeprom=NULL;
Poitr_eeprom=pointer_struct;
u8 Counter_Two=0;// counter 2 for bumber of bytes per user
for(;Counter_Two < Size_Struct;)// looop for taking all data for one struct
{
*Poitr_eeprom=EEPROM_read((0x03)+(Counter_Two)+(Counter_One*Size_Struct));
Poitr_eeprom++;
Counter_Two++;
}
(*pointer_struct).next=temp_Ddress;
pointer_struct=(*pointer_struct).next;																									//            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ neeed help here#####################################
Counter_One++;
}
}






bool Error_in_EEPROM()
{
if (EEPROM_read(0xFF)==146)// check for value of 0xAA if value == 146 every thing is fine
	{return 0;}// return 0 if no proplem
	return 1;// return 1 if not equal
	}