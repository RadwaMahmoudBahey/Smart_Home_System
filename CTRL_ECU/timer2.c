/*
 * timer2.c
 *
 *  Created on: Sep 7, 2023
 *      Author: Dell
 */


/*
 * Timer.c

 *
 *  Created on: Aug 20, 2023
 *      Author: Menna
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "avr/io.h"
#include "timer2.h"
#include "stdio.h"


void (*TIMER0_pvCallBackFunc)(void) =NULL;

void TIMER0_Init(void){
	// wave generation : CTC mode
	SET_BIT(TCCR0 , TCCR0_WGM00);
	SET_BIT(TCCR0 , TCCR0_WGM01);

	SET_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(SREG,7);
	//Enable PIE of Compare Match intrrupt
	SET_BIT(TIMSK , TIMSK_OCIE);
	//Set compare match value
	OCR0=50;

	// prescaler
	CLR_BIT(TCCR0 , TCCR0_CS00);
	SET_BIT(TCCR0 , TCCR0_CS01);
	CLR_BIT(TCCR0 , TCCR0_CS02);




}
u8   TIMER0_u8SetCallBack(void ( *Copy_pvCallBackFunc)(void)){

	u8 u8ErrorStatus_Local = OK;
	if(Copy_pvCallBackFunc != NULL){
		TIMER0_pvCallBackFunc = Copy_pvCallBackFunc;
	}
	else{
		u8ErrorStatus_Local = NULL;
	}
	return u8ErrorStatus_Local;
}


/* Actual ISR */
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void){
	if(TIMER0_pvCallBackFunc != NULL){
		TIMER0_pvCallBackFunc();
	}
}


/* Actual ISR */

