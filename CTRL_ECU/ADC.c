/*
 * ADC.c
 *
 *  Created on: Sep 4, 2023
 *      Author: Menna
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "ADC.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
void (*ADC_pvIntfunc)(void)=NULL;

void ADC_Init()
{
	    SET_BIT(ADCSRA , ADEN);
	    //SET_BIT(ADCSRA,ADIE);
		// Prescaler Configuration as 128
		SET_BIT(ADCSRA , ADPS2);
		SET_BIT(ADCSRA , ADPS1);
		SET_BIT(ADCSRA , ADPS0);

		SET_BIT(ADCSRA , ADSC);
		// Referance Voltage as AVCC with external capacitor
		CLR_BIT (ADMUX  , REFS1);
		SET_BIT (ADMUX  , REFS0);

		/*ADC Data Rgith Adjustment 10 bits
		CLR_BIT(ADMUX , ADMUX_ADLAR);*/

		/*Activate Left adjustment result 8 bits */
		SET_BIT(ADMUX ,  ADLAR);
		sei();


}

u16 ADC_Read(void)
{

		//step 1 : Clear MUX bits in ADMUX
	ADMUX   = 0b11100000;


		//Step 2 : Set the required  ADC Channel Selection into the MUX bits

		// Step 3 : Start Single Converstion
		SET_BIT(ADCSRA , ADSC);


		// Step 4 :  Polling (busy wait ) until the conversion complete flag is set
		while((GET_BIT(ADCSRA , ADIF)) == 0);


		// Step 5 :  Clear Conversion Complete Flag
		SET_BIT(ADCSRA,ADIF);

		// Step 7 :   return value in ADCH (Left adjustment result 8 bits)

		return ADCH;

}
u8 ADC_u8IntSetCallBack (void (*PvIntFunc_Copy) (void)){

	u8 u8ErrorStatusLocal = OK;
	if( PvIntFunc_Copy != NULL ){
		//global ptr = local variable
		ADC_pvIntfunc = PvIntFunc_Copy;
	}
	else{
		u8ErrorStatusLocal = NULL;
	}
	return u8ErrorStatusLocal ;
}



void __vector_16 (void) __attribute__ ((signal));
void __vector_16 (void){
	if(ADC_pvIntfunc != NULL){
		//global ptr
		ADC_pvIntfunc();
	}
	else{
		/* DO NOTHING */
	}

}



