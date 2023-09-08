#define F_CPU 8000000UL
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "ADC.h"
#include "DC_MOTOR.h"
#include <avr/io.h>
#include "Timer.h"
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "I2C.h"
#include "UART.h"
#include "Buzzer.h"
#include "DC_DOOR.h"
#include "Timer2.h"

#define STOP 3
#define MATCHED_PASS 0x55
#define UNMATCHED_PASS 0x33
#define ERASE_EEPROM 0x66
#define ACTIVATE_BUZZER 0x11
#define ACTIVATE_MOTOR 0x22
#define AVAILABLE 0x01
#define N_AVAILABLE 0xFF
#define DOOR_DONE 0x50
#define MC2_READY 0x10

 u8 setPassFlag = 0;


void TIMER2_ISR(void);
void passwordSet(u8 * recieve);
u8 passwordComp(u8 *recieveSec);
u8 passConfirm(u8 *recieveSec);
void delaySec(u8 sec);
void convertnsend(u8 val);
void Buzzer(void);
int main()
{

	DIO_SetPinDirection(DIO_PORTA,DIO_PIN0,DIO_INPUT);
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN3,DIO_OUTPUT);
	DIO_SetPinValue(DIO_PORTA,DIO_PIN3,DIO_LOW);

	ADC_Init();
    MOTOR_Init();
    TIMER0_Init();
    UART_Init();
    while(USART_ReceiveData() != MC2_READY){}
    I2C_Init(8000000);

    u8 recieve[6];
    u8 recieveSec[6];
    u8 options = 0;
    u8 temp;

    while(1)
    {

    	passwordSet(recieve);
		temp = ADC_Read();
		while(USART_ReceiveData() != MC2_READY){}
		USART_SendData(temp);
		if(temp >= 30 && temp <=50)
		{
			MOTOR_CWMotion();

				OCR0 = 150;
				DIO_SetPinValue(DIO_PORTA,DIO_PIN3,DIO_HIGH);


		}else if(temp > 50){
			OCR0 = 250;
			DIO_SetPinValue(DIO_PORTA,DIO_PIN3,DIO_HIGH);

		}
		else
		{
			MOTOR_StopMotion();
			DIO_SetPinValue(DIO_PORTA,DIO_PIN3,DIO_LOW);

		}
    	while(passConfirm(recieveSec)==UNMATCHED_PASS);
    	 USART_SendData(MC2_READY);
    	while((options != ACTIVATE_MOTOR) && (options != ERASE_EEPROM))
    	{
    		options = USART_ReceiveData();
    	}



    	if(options == ACTIVATE_MOTOR)
    	{  TIMER2_Init();
    		CallBack_func(&TIMER2_ISR);
    		DOOR_Init();
    		TIMER2_ISR();
    	}
    	else if(options == ERASE_EEPROM)
    	{
    		setPassFlag= 1;
    		 passwordSet(recieve);

    	}





}
}


//for 15 seconds , 256 prescalars , ocr2 =250 , counts 1875
//for 3 seconds , 256 prescalars , ocr2 =250 , counts 375
void TIMER2_ISR(void){
	static u16 count=0;
	static u8 flag =0;
	count++;
	if(flag ==0){
		TIMER2_OC2_ON();
		DOOR_CwMotion();
		TIMER2_SetCompareValue(250);
	}
	if((count==800) && (flag ==0)){
		DOOR_Stop();
		TIMER2_SetCompareValue(250);
		count=0;
		flag++;
	}

	if((count==150) && (flag ==1)){
		DOOR_CCwMotion();
		count=0;
		flag++;
	}

	if((count==800) && (flag ==2)){
		DOOR_Stop();
		TIMER2_OC2_OFF();
		count=0;
		flag=0;
		CLR_BIT(TIMSK ,TIMSK_OCIE2);
		//while(USART_ReceiveData() != MC2_READY){}
		USART_SendData(DOOR_DONE);
	}
}



void passwordSet(u8 *recieve)
{
	u8 setOrNot= EEPROM_ReadByte(0x28);
	u8 recieveSec[6];

	if(setPassFlag  == 0)
	{
		while(USART_ReceiveData() != MC2_READY){}
			USART_SendData(setOrNot);
if(setOrNot == N_AVAILABLE)
{
	       USART_SendData(MC2_READY);
	       USART_voidReceiveString(recieve);

	    	u8 i =0;

	        while(recieve[i] != '\0')
	       {
		   EEPROM_WriteByte(i*8, recieve[i]);
	       i++;
	       }
	       while( passwordComp(recieveSec) == UNMATCHED_PASS);
	       EEPROM_WriteByte(0x28,AVAILABLE);
}
	}else
	{
		USART_SendData(MC2_READY);

		            USART_voidReceiveString(recieve);

			    	u8 i =0;

			        while(recieve[i] != '\0')
			       {
				   EEPROM_WriteByte(i*8, recieve[i]);
			       i++;
			       }


	}
}
u8 passwordComp(u8 *recieveSec)
{
	u8 confirm = MATCHED_PASS;
	USART_SendData(MC2_READY);
	USART_voidReceiveString(recieveSec);
for(u8 j =0;j <5; j++ )
{

	if( EEPROM_ReadByte(j*8) != recieveSec[j])
	{

		confirm = UNMATCHED_PASS;
	}


}
while(USART_ReceiveData() != MC2_READY){}
USART_SendData(confirm);
return confirm;

}
u8 passConfirm(u8 *recieveSec)
{
	 u8 number = 0;
	while( passwordComp(recieveSec) == UNMATCHED_PASS )
	{
		number++;
		if(number == STOP)
		{
			Buzzer();
			return UNMATCHED_PASS;

		}
	}
	return MATCHED_PASS;


}
void Buzzer(void)
{

	 Buzzer_Init(); // Initialize the buzzer pin
	 Buzzer_On();
	 //Turn on the buzzer
	 delaySec(60);
	 Buzzer_Off();// Turn off the buzzer
}
void delaySec(u8 sec)
{
	for(int i =0; i <sec; i++)
		 {
	_delay_ms(1000); // Delay for 1 minute
		 }

}
