/******************************************************************************
 *
 * Module: DIO
 *
 * File Name: DIO.c
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: Mohamed Khaled
 *
 *******************************************************************************/
#include "std_types.h"
#include "DIO.h"
#include "common_macros.h"
#include "avr/io.h"

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void DIO_SetPinDirection(u8 u8PortIdCopy, u8 u8PinIdCopy, GPIO_PinDirectionType direction)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((u8PinIdCopy >= NUM_OF_PINS_PER_PORT) || (u8PortIdCopy >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as required */
		switch(u8PortIdCopy)
		{
		case DIO_PORTA:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRA,u8PinIdCopy);
			}
			else
			{
				CLEAR_BIT(DDRA,u8PinIdCopy);
			}
			break;
		case DIO_PORTB:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRB,u8PinIdCopy);
			}
			else
			{
				CLEAR_BIT(DDRB,u8PinIdCopy);
			}
			break;
		case DIO_PORTC:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRC,u8PinIdCopy);
			}
			else
			{
				CLEAR_BIT(DDRC,u8PinIdCopy);
			}
			break;
		case DIO_PORTD:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRD,u8PinIdCopy);
			}
			else
			{
				CLEAR_BIT(DDRD,u8PinIdCopy);
			}
			break;
		}
	}
}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void DIO_SetPinValue(u8 u8PortIdCopy,u8 u8PinIdCopy, u8 u8value)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((u8PinIdCopy >= NUM_OF_PINS_PER_PORT) || (u8PortIdCopy >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the pin value as required */
		switch(u8PortIdCopy)
		{
		case DIO_PORTA:
			if(u8value == LOGIC_HIGH)
			{
				SET_BIT(PORTA,u8PinIdCopy);
			}
			else
			{
				CLEAR_BIT(PORTA,u8PinIdCopy);
			}
			break;
		case DIO_PORTB:
			if(u8value == LOGIC_HIGH)
			{
				SET_BIT(PORTB,u8PinIdCopy);
			}
			else
			{
				CLEAR_BIT(PORTB,u8PinIdCopy);
			}
			break;
		case DIO_PORTC:
			if(u8value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,u8PinIdCopy);
			}
			else
			{
				CLEAR_BIT(PORTC,u8PinIdCopy);
			}
			break;
		case DIO_PORTD:
			if(u8value == LOGIC_HIGH)
			{
				SET_BIT(PORTD,u8PinIdCopy);
			}
			else
			{
				CLEAR_BIT(PORTD,u8PinIdCopy);
			}
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
u8 DIO_GetPinValue(u8 u8PortIdCopy,u8 u8PinIdCopy)
{
	u8 pin_value = LOGIC_LOW;

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((u8PinIdCopy >= NUM_OF_PINS_PER_PORT) || (u8PortIdCopy >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the pin value as required */
		switch(u8PortIdCopy)
		{
		case DIO_PORTA:
			if(BIT_IS_SET(PINA,u8PinIdCopy))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case DIO_PORTB:
			if(BIT_IS_SET(PINB,u8PinIdCopy))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case DIO_PORTC:
			if(BIT_IS_SET(PINC,u8PinIdCopy))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case DIO_PORTD:
			if(BIT_IS_SET(PIND,u8PinIdCopy))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		}
	}

	return pin_value;
}

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void DIO_SetPortDirection(u8 u8PortIdCopy, GPIO_PortDirectionType direction)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(u8PortIdCopy >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the port direction as required */
		switch(u8PortIdCopy)
		{
		case DIO_PORTA:
			DDRA = direction;
			break;
		case DIO_PORTB:
			DDRB = direction;
			break;
		case DIO_PORTC:
			DDRC = direction;
			break;
		case DIO_PORTD:
			DDRD = direction;
			break;
		}
	}
}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void DIO_SetPortValue(u8 u8PortIdCopy, u8 u8value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(u8PortIdCopy >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the port value as required */
		switch(u8PortIdCopy)
		{
		case DIO_PORTA:
			PORTA = u8value;
			break;
		case DIO_PORTB:
			PORTB = u8value;
			break;
		case DIO_PORTC:
			PORTC = u8value;
			break;
		case DIO_PORTD:
			PORTD = u8value;
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
u8 GPIO_readPort(u8 u8PortIdCopy)
{


	u8 value = LOGIC_LOW;

	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(u8PortIdCopy >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the port value as required */
		switch(u8PortIdCopy)
		{
		case DIO_PORTA:
			value = PINA;
			break;
		case DIO_PORTB:
			value = PINB;
			break;
		case DIO_PORTC:
			value = PINC;
			break;
		case DIO_PORTD:
			value = PIND;
			break;
		}
	}

	return value;

}
