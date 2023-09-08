/*
 * HMI ECU application program.c
 *
 * Created: 9/4/2023 11:47:17 PM
 * Author : Radwa
 */
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "DIO.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "uart.h"
#include "common_macros.h"
#include "util/delay.h"

#define MATCHED_PASS 0x55
#define UNMATCHED_PASS 0x33
#define ERASE_EEPROM 0x66
#define ACTIVATE_BUZZER 0x11
#define ACTIVATE_MOTOR 0x22
#define AVAILABLE 0x01
#define N_AVAILABLE 0xFF
#define DOOR_DONE 0x50
#define MC2_READY 0x10

u8  error_flag=0, confirm = 0 , pass_flag =0 ;



void System_voidInit(void);
void welcome_voidInit(void);
void second_voidInit(void);
void Positive_voidInit(void);
void Negative_voidInit(void);
void Mainopt_voidInit(void);
void error_voidInit(void);
void DOOR_INIT(void);

int main(void)
{
	System_voidInit();
	while (1)
	{
		USART_SendData(MC2_READY);
		pass_flag = USART_ReceiveData();
		if (pass_flag == N_AVAILABLE)/* if there is no password saved in memory*/
		{
			welcome_voidInit();
		}
	    else if (pass_flag == AVAILABLE)/* if there is password saved in memory*/
		{
			Mainopt_voidInit();
		}
		else
		{
            // do nothing
			LCD_voidClearScreen();
			LCD_voidSendString("ERROR");
		}
	}
}





void System_voidInit(void)
{
	LCD_voidInit();
	KEYPAD_voidInit();
	UART_Init();
	USART_SendData(MC2_READY);
	SREG |= (1<<7); /* Enable global interrupts in MC */

}

void welcome_voidInit(void)
{
	u8  i=0, key=0 ;
	LCD_voidClearScreen();
	LCD_voidSendString("plz enter pass:");
	LCD_moveCursor(1,0);
	while(USART_ReceiveData() != MC2_READY);
//	LCD_voidSendString("terminate while");

	for (i=0;i<5;i++)
	{
		if (KEYPAD_u8GetPressedKey() != KEYPAD_BUTTON_RELEASED)/* if button pressed */
		{
			key = KEYPAD_u8GetPressedKey();
			USART_SendData(key);
			LCD_voidSendData('*');
		}
		else
		{
			--i;/* if the KEYPAD_BUTTON_RELEASED */
		}
	}
	USART_SendData('.');
	while (KEYPAD_u8GetPressedKey() != '=')
	{}
	second_voidInit();
}

void second_voidInit(void)
{
	u8 i2=0, key2=0 ;
	LCD_voidClearScreen();
	LCD_voidSendString("plz re-enter pass : ");
	LCD_moveCursor(1,0);
	while(USART_ReceiveData() != MC2_READY);
	for (i2=0;i2<5;i2++)
	{
		if (KEYPAD_u8GetPressedKey() != KEYPAD_BUTTON_RELEASED)/* if button pressed */
		{
			key2 = KEYPAD_u8GetPressedKey();
			USART_SendData(key2);
			LCD_voidSendData('*');
		}
		else
		{
			--i2;/* if the KEYPAD_BUTTON_RELEASED */
		}

	}
	USART_SendData('.');
	while (KEYPAD_u8GetPressedKey() != '=')
	{}
	USART_SendData(MC2_READY);
	confirm = USART_ReceiveData();
	if(confirm == MATCHED_PASS)
	{
		Mainopt_voidInit();
	}
	else if (confirm == UNMATCHED_PASS)
	{
		second_voidInit();
	}
}

void Mainopt_voidInit(void)
{
	u8 option=0,temp=0;
	LCD_voidClearScreen();
	LCD_voidSendString("+ : Open door");
	LCD_moveCursor(1,0);
	LCD_voidSendString("- : Change pass");
	LCD_moveCursor(2,0);

	USART_SendData(MC2_READY);
	temp=USART_ReceiveData();

	LCD_moveCursor(2,3);/* to display the string from the third row*/
	/* Display this string "Temp =   C" only once on LCD at the third raw row */
	LCD_voidSendString(" Temp =    C");
	LCD_moveCursor(2,10);
	LCD_voidIntgerToString((temp-22)+0x30);
	LCD_voidSendData(' ');
	//

	option = KEYPAD_u8GetPressedKey();
	while ( option != '+' &&  option != '-')
	{
		option = KEYPAD_u8GetPressedKey();
	}


	if (option == '+')
	{
		Positive_voidInit();
	}
	else if (option == '-')
	{
		Negative_voidInit();
	}
	else
	{

	}
}


void Positive_voidInit(void)
{
	u8 i3=0, key3=0,confirm=0;
	LCD_voidClearScreen();
	LCD_voidSendString("plz enter pass2:");
	LCD_moveCursor(1,0);

	while(USART_ReceiveData() != MC2_READY);
	for (i3=0;i3<5;i3++)
	{

		if (KEYPAD_u8GetPressedKey() != KEYPAD_BUTTON_RELEASED)/* if button pressed */
		{
			key3 = KEYPAD_u8GetPressedKey();
			USART_SendData(key3);
			LCD_voidSendData('*');
		}
		else
		{
			--i3;/* if the KEYPAD_BUTTON_RELEASED */
		}
	}
	USART_SendData('.');
	while (KEYPAD_u8GetPressedKey() != '=')
	{}
	USART_SendData(MC2_READY);
	confirm = USART_ReceiveData();
	if(confirm == MATCHED_PASS)
	{
		while(USART_ReceiveData() != MC2_READY);
		USART_SendData(ACTIVATE_MOTOR);
		DOOR_INIT();


	}
	else if (confirm == UNMATCHED_PASS)
	{
		error_flag++;
		if (error_flag == 3)
		{
			error_voidInit();
			error_flag=0;
		}
		else
		{
			Positive_voidInit();
		}

	}

}




void Negative_voidInit(void)
{

	u8 i3=0, key3=0,confirm=MATCHED_PASS;
	LCD_voidClearScreen();
	LCD_voidSendString("plz enter pass2:");
	LCD_moveCursor(1,0);

	while(USART_ReceiveData() != MC2_READY);
	for (i3=0;i3<5;i3++)
	{
		if (KEYPAD_u8GetPressedKey() != KEYPAD_BUTTON_RELEASED)/* if button pressed */
		{
			key3 = KEYPAD_u8GetPressedKey();
			USART_SendData(key3);
			LCD_voidSendData('*');
		}
		else
		{
			--i3;/* if the KEYPAD_BUTTON_RELEASED */
		}
	}
	USART_SendData('.');
	while (KEYPAD_u8GetPressedKey() != '=')
	{}
	USART_SendData(MC2_READY);
	confirm = USART_ReceiveData();
	if(confirm == MATCHED_PASS)
	{
		while(USART_ReceiveData() != MC2_READY);
		USART_SendData(ERASE_EEPROM);
		welcome_voidInit();
	}
	else if (confirm == UNMATCHED_PASS)
	{
		error_flag++;
		if (error_flag == 3)
		{
			error_voidInit();
			error_flag=0;
		}
		else
		{
			Negative_voidInit();
		}

	}
}

void error_voidInit(void)
{

	LCD_voidClearScreen();
	LCD_voidSendString("Error?!");
	_delay_ms(60000);
	Mainopt_voidInit();

}

void DOOR_INIT(void){
    u8 done =0;
	LCD_voidClearScreen();
	LCD_voidSendString("The Door is Opening");
	//USART_SendData(MC2_READY);
	while (done != DOOR_DONE)
	{
		done = USART_ReceiveData();
	}
	Mainopt_voidInit();



}
