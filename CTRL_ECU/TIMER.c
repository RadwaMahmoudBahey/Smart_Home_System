#define F_CPU 8000000ul
#include "STD_TYPES.h"
#include "BIT_MATH.h"
//2-mcal
#include "DIO.h"
//3-AVR
#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "TIMER.h"
void (*Global_pointer)(void)=NULL;
void TIMER2_Init(void){
	//for ctc mode
	CLR_BIT(TCCR2 ,TCCR2_WGM20);
	SET_BIT(TCCR2 ,TCCR2_WGM21);
//enabling timer2
	SET_BIT(TIMSK ,TIMSK_OCIE2);





//prescalar :256
	CLR_BIT(TCCR2 ,TCCR2_CS20);
	SET_BIT(TCCR2 ,TCCR2_CS21);
	SET_BIT(TCCR2 ,TCCR2_CS22);


}


void TIMER2_OC2_ON(void){
	//OC2 enabling
	SET_BIT(TCCR2 ,COM20);
	CLR_BIT(TCCR2 ,COM21);

}
void TIMER2_OC2_OFF(void){
	//OC2 DISABLE
	CLR_BIT(TCCR2 ,COM20);
	CLR_BIT(TCCR2 ,COM21);

}

void TIMER2_SetCompareValue(u8 u8_TicksNumber){
	OCR2 = u8_TicksNumber;
}

u8 CallBack_func(void (*local_pointer)(void)){
	u8 error_state = OK;
	if(local_pointer !=NULL){
		Global_pointer =local_pointer;
	}
	else{
		error_state = NOK;
	}
	return error_state;
}

void __vector_4 (void) __attribute__((signal));
void __vector_4 (void){
	if(Global_pointer !=NULL){
	Global_pointer();
	}
}
