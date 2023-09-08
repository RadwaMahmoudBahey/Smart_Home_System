#ifndef TIMER_H_
#define TIMER_H_
//TCCR2
#define		TCCR2_FOC2	7
#define		TCCR2_WGM20	6
#define		TCCR2_COM21	5
#define		TCCR2_COM20	4
#define		TCCR2_WGM21 3
#define		TCCR2_CS22	2
#define		TCCR2_CS21	1
#define		TCCR2_CS20	0


//TIMSK
#define		TIMSK_TOIE2	6
#define		TIMSK_OCIE2	7




void TIMER2_Init(void);
u8 CallBack_func(void (*local_pointer)(void));

void TIMER2_SetCompareValue(u8 u8_TicksNumber);
void TIMER2_OC2_ON(void);
void TIMER2_OC2_OFF(void);





#endif
