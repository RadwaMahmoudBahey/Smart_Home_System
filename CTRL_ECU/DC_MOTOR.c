/*
 * DC_MOTOR.c
 *
 *  Created on: Sep 4, 2023
 *      Author: Menna
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "DC_MOTOR.h"

void MOTOR_Init(void)
{
	DIO_SetPinDirection(MOTOR_PORT, MOTOR_ENA, DIO_OUTPUT);
	DIO_SetPinDirection(MOTOR_PORT, MOTOR_IN1, DIO_OUTPUT);
	DIO_SetPinDirection(MOTOR_PORT, MOTOR_IN2, DIO_OUTPUT);
	DIO_SetPinValue(MOTOR_PORT, MOTOR_ENA, DIO_HIGH);
	DIO_SetPinValue(MOTOR_PORT, MOTOR_IN1, DIO_LOW);
	DIO_SetPinValue(MOTOR_PORT, MOTOR_IN2, DIO_LOW);
}

void MOTOR_CWMotion(void)
{
	DIO_SetPinValue(MOTOR_PORT, MOTOR_IN2, DIO_LOW);
	DIO_SetPinValue(MOTOR_PORT, MOTOR_IN1, DIO_HIGH);
}

void MOTOR_CCWMotion(void)
{
	DIO_SetPinValue(MOTOR_PORT, MOTOR_IN1, DIO_LOW);
	DIO_SetPinValue(MOTOR_PORT, MOTOR_IN2, DIO_HIGH);
}

void MOTOR_StopMotion(void)
{
	DIO_SetPinValue(MOTOR_PORT, MOTOR_IN1, DIO_LOW);
	DIO_SetPinValue(MOTOR_PORT, MOTOR_IN2, DIO_LOW);
}
