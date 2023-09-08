/*
 * I2C.c
 *
 *  Created on: Aug 28, 2023
 *      Author: Dell
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
//2 HAL
//3 MCAL
#include "DIO.h"
#include "I2C.h"
//4
#include "avr/io.h"
#include "util/delay.h"
void I2C_Init(u32 SCL_Clock){
	//setting the TWBR value
	TWBR = (u8)(((F_CPU / SCL_Clock) -16) /(2*Prescaler));
	//setting prescalar in TWSR
	if(Prescaler ==1){
		CLR_BIT(TWSR ,TWPS0);
		CLR_BIT(TWSR ,TWPS1);
	}
	else if(Prescaler == 4 ){
		SET_BIT(TWSR ,TWPS0);
		CLR_BIT(TWSR ,TWPS1);
	}
	else if(Prescaler == 16){
		CLR_BIT(TWSR ,TWPS0);
		SET_BIT(TWSR ,TWPS1);
	}
	else if(Prescaler == 64){
		SET_BIT(TWSR ,TWPS0);
		SET_BIT(TWSR ,TWPS1);
	}
}


void I2C_Start(void){
	//CLRing interrupt flag , setting start bit and twi enable
	TWCR = (1<< TWINT) | ( 1<< TWSTA) | ( 1<< TWEN);
	//to check if start bit is transmitted , flag should be set if transmission done.
	while((TWCR & (1<< TWINT))==0);
	//check statusto check start ack
	//while(TWSR != I2C_START_ACK);
}

void I2C_Stop(void){
	//CLRing interrupt flag , setting stop bit and twi enable
	TWCR = (1<< TWINT) | ( 1<< TWSTO) | ( 1<< TWEN);
}



void I2C_SetAddress(u8 u8AddressCopy){
	//setting 7 MSB of address register
	TWAR = u8AddressCopy;

}



u8 I2C_Read(u8 u8read){
	TWCR = (1<< TWINT) | ( 1<< TWEA) | ( 1<< TWEN);
	while(!(TWCR & (1<< TWINT)));

	return TWDR;
}


u8 I2C_ReadSlave(u8 u8read){

	TWCR = (1<< TWINT) | ( 1<< TWEA) | ( 1<< TWEN);
	while(!(TWCR & (1<< TWINT)));
	while(TWSR != I2C_ADDRESS_ACK);

	if(u8read ==1){
		TWCR = (1<< TWINT) | ( 1<< TWEA) | ( 1<< TWEN);
		while(!(TWCR & (1<< TWINT)));
		while(TWSR != I2C_DATA_ACK);
		return TWDR;
	}

}


void I2C_Write(u8 u8write){
	TWDR =u8write;
	// CLR TWINT bit in TWCR to start transmission
	TWCR = (1<< TWINT)  | ( 1<< TWEN);
	while(!(TWCR & (1<< TWINT)));
}




void EEPROM_WriteByte(u8 address, u8 data) {
    I2C_Start();
    I2C_Write(EEPROM_ADDRESS | ((address) & 0x0E));
    I2C_Write(address & 0xFF);
    I2C_Write(data);
    I2C_Stop();
    _delay_ms(10);  // Delay for EEPROM write cycle completion
}

u8 EEPROM_ReadByte(u8 address) {
    u8 data;
    I2C_Start();
    I2C_Write(EEPROM_ADDRESS | ((address) & 0x0E));
    I2C_Write(address & 0xFF);
    I2C_Start();
    I2C_Write(EEPROM_ADDRESS | 1);
    data = I2C_Read(0);
    I2C_Stop();
    return data;
}

