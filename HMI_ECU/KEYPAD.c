/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: KEYPAD.c
 *
 * Description: Source file for the KEYPAD driver
 *
 * Author: Mohamed Khaled
 *
 *******************************************************************************/
#define F_CPU 8000000UL
#include "std_types.h"
#include "common_macros.h"
#include "DIO.h"
#include "avr/io.h"
#include "util/delay.h"
#include "KEYPAD.h"
/*
 * Description :
 * Initialize the Keypad Driver (it's pins and ports)
 */
void KEYPAD_voidInit(void)
{
	/*Set the Raw port as input with PORT=1 to activate the internal pull up */
	DIO_SetPortDirection(KEYPAD_ROW_PORT,PORT_INPUT);
	DIO_SetPortValue(KEYPAD_ROW_PORT,0x0F);
	/*Set the COL port as output with Initial value =LOGIC HIGH*/
    DIO_SetPortDirection(KEYPAD_COL_PORT,PORT_OUTPUT);
    DIO_SetPortValue(KEYPAD_COL_PORT,0xFF);
}

/*
 * Description :
 * Get the Keypad pressed button
 */
u8 KEYPAD_u8GetPressedKey(void)
{
	/*Define the row and col variables that will check which button pressed*/
	u8 u8RowLocal=0,u8ColLocal=0;
	/*Define the row and col arrays that will include the keypad pins */
	u8 KPD_u8RwoPinArr[KEYPAD_NUM_ROWS] = {KEYPAD_R0_PIN,KEYPAD_R1_PIN,KEYPAD_R2_PIN,KEYPAD_R3_PIN};
	u8 KPD_u8ColPinArr[KEYPAD_NUM_COLS] = {KEYPAD_C0_PIN,KEYPAD_C1_PIN,KEYPAD_C2_PIN,KEYPAD_C3_PIN};
	for(u8ColLocal=0;u8ColLocal<KEYPAD_NUM_COLS;u8ColLocal++)
	{
		/*To activate one column at a time -> col_pin =0*/
		DIO_SetPinValue(KEYPAD_COL_PORT,KPD_u8ColPinArr[u8ColLocal],LOGIC_LOW);
		for(u8RowLocal=0;u8RowLocal<KEYPAD_NUM_ROWS;u8RowLocal++)
		{
			u8 u8Value=DIO_GetPinValue(KEYPAD_ROW_PORT,KPD_u8RwoPinArr[u8RowLocal]);
			if (u8Value == KEYPAD_BUTTON_PRESSED)
			{
				/*delay and second check for switch debouncing*/
				_delay_ms(30);
				if (u8Value == KEYPAD_BUTTON_PRESSED)
				{
					while(u8Value == KEYPAD_BUTTON_PRESSED)
					{
						u8Value=DIO_GetPinValue(KEYPAD_ROW_PORT,KPD_u8RwoPinArr[u8RowLocal]);
					}
					u8 KPD_u8Value[KEYPAD_NUM_ROWS][KEYPAD_NUM_COLS]= KPD_VALUES;
					return KPD_u8Value[u8RowLocal][u8ColLocal];
				}
			}
		}
		/*there is no button pressed*/
		DIO_SetPinValue(KEYPAD_COL_PORT,KPD_u8ColPinArr[u8ColLocal],LOGIC_HIGH);
	}
	return KEYPAD_BUTTON_RELEASED;
}
