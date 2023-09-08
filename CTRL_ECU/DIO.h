#ifndef DIO_H_
#define DIO_H_


#include "STD_TYPES.h"
//port macros
#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 3
#define DIO_PORTD 4

//pins macros
#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

//directions macros
#define DIO_INPUT 0
#define DIO_OUTPUT 1

//values macros
#define DIO_LOW 0
#define DIO_HIGH 1

//function for setting and clearing pin value
void DIO_SetPinValue(u8 u8PortIdCopy ,u8 u8PinIdCopy , u8 u8PinValCopy);
void DIO_SetPinDirection(u8 u8PortIdCopy ,u8 u8PinIdCopy , u8 u8PinDirCopy);
u8 DIO_GetPinValue (u8 u8PortIdCopy ,u8 u8PinIdCopy);

//functions for ports
void DIO_SetPortValue(u8 u8PortIdCopy , u8 u8PortValCopy);
void DIO_SetPortDirection(u8 u8PortIdCopy , u8 u8PortDirCopy);


#endif
