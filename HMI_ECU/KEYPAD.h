/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: KEYPAD.h
 *
 * Description: Header file for the KEYPAD driver
 *
 * Author: Mohamed Khaled
 *
 *******************************************************************************/


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT                DIO_PORTB
#define KEYPAD_R0_PIN                  DIO_PIN0
#define KEYPAD_R1_PIN                  DIO_PIN1
#define KEYPAD_R2_PIN                  DIO_PIN2
#define KEYPAD_R3_PIN                  DIO_PIN3

#define KEYPAD_COL_PORT                DIO_PORTC
#define KEYPAD_C0_PIN                  DIO_PIN0
#define KEYPAD_C1_PIN                  DIO_PIN1
#define KEYPAD_C2_PIN                  DIO_PIN2
#define KEYPAD_C3_PIN                  DIO_PIN3

/*Define the keypad values*/
#define KPD_VALUES     {{'7','8','9','/'},\
	                    {'4','5','6','*'},\
						{'1','2','3','-'},\
						{'c','0','=','+'}}


/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the Keypad Driver (it's pins and ports)
 */
void KEYPAD_voidInit(void);

/*
 * Description :
 * Get the Keypad pressed button
 */
u8 KEYPAD_u8GetPressedKey(void);



#endif /* KEYPAD_H_ */
