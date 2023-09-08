/*
 * I2C.h
 *
 *  Created on: Aug 28, 2023
 *      Author: Dell
 */

#ifndef I2C_H_
#define I2C_H_

//mode
#define MASTER_TRANSMITTER_EEPROM_RECIEVER
//#define MASTER_TRANSMITTER_SLAVE_RECIEVER
//#define MASTER_RECIEVER_SLAVE_TRANSMITTER

#define EEPROM_ADDRESS 0xA0
//prescalar
#define Prescaler			1
// ack
#define I2C_ADDRESS_ACK   		0x60
#define I2C_DATA_ACK   			0x80
#define I2C_START_ACK   		0x08
//TWCR

#define TWINT				7
#define TWEA				6
#define TWSTA				5
#define TWSTO				4
#define TWEN				2



//TWSR
#define TWPS1				0
#define TWPS0				1


//APIS

void I2C_Init(u32 SCL_Clock);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SetAddress(u8 u8AddressCopy);
u8 I2C_Read(u8 u8read);
u8 I2C_ReadSlave(u8 u8read);
void I2C_Write(u8 u8write);
//FOR EEPROM
u8 EEPROM_ReadByte(u8 address);
void EEPROM_WriteByte(u8 address, u8 data);


#endif /* I2C_H_ */
