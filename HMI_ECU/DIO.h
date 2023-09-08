/******************************************************************************
 *
 * Module: DIO
 *
 * File Name: DIO.h
 *
 * Description: Header file for the AVR GPIO driver
 *
 * Author: Mohamed Khaled
 *
 *******************************************************************************/


#ifndef DIO_H_
#define DIO_H_
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define DIO_PORTA              0
#define DIO_PORTB              1
#define DIO_PORTC              2
#define DIO_PORTD              3

#define DIO_PIN0               0
#define DIO_PIN1               1
#define DIO_PIN2               2
#define DIO_PIN3               3
#define DIO_PIN4               4
#define DIO_PIN5               5
#define DIO_PIN6               6
#define DIO_PIN7               7

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void DIO_SetPinDirection(u8 u8PortIdCopy, u8 u8PinIdCopy, GPIO_PinDirectionType direction);

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void DIO_SetPinValue(u8 u8PortIdCopy,u8 u8PinIdCopy, u8 u8value);

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
u8 DIO_GetPinValue(u8 u8PortIdCopy,u8 u8PinIdCopy);

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void DIO_SetPortDirection(u8 u8PortIdCopy, GPIO_PortDirectionType direction);

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void DIO_SetPortValue(u8 u8PortIdCopy, u8 u8value);

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
u8 GPIO_readPort(u8 u8PortIdCopy);



#endif /* DIO_H_ */
