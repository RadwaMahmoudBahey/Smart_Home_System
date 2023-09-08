/*
 * Buzzer.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Dell
 */


#include "Buzzer.h"


void Buzzer_Init() {
	// Set BUZZER_PIN as output
	DIO_SetPinDirection(BUZZER_PORT , BUZZER_PIN , DIO_OUTPUT);
}

void Buzzer_On() {
	// Set BUZZER_PIN high to turn on the buzzer
	DIO_SetPinValue(BUZZER_PORT , BUZZER_PIN , DIO_HIGH);
}

void Buzzer_Off() {
	// Set BUZZER_PIN low to turn off the buzzer
	DIO_SetPinValue(BUZZER_PORT , BUZZER_PIN , DIO_LOW);

}
