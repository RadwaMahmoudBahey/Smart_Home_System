/*
 * ADC.h
 *
 *  Created on: Sep 4, 2023
 *      Author: Menna
 */

#ifndef ADC_H_
#define ADC_H_

/*ADMUX*/
#define REFS1 7
#define REFS0 6
#define ADLAR 5
#define MUX4  4
#define MUX3  3
#define MUX2  2
#define MUX1  1
#define MUX0  0

/*ADCSRA*/
#define ADEN 7
#define ADSC 6
#define ADATE 5
#define ADIF 4
#define ADIE 3
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0

#define OK 1

void ADC_Init(void);
u16 ADC_Read(void);
u8 ADC_u8IntSetCallBack (void (*PvIntFunc_Copy) (void));

#endif /* ADC_H_ */
