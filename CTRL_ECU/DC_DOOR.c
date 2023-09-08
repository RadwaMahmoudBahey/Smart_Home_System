#include "STD_TYPES.h"
#include "BIT_MATH.h"
//2-mcal
#include "DIO.h"
//3-AVR
#include "avr/io.h"
#include "util/delay.h"
#include "DC_DOOR.h"
// clockwise
void DOOR_CwMotion(void){
	//setting IN1 to 1 and IN2 to 0
	DIO_SetPinValue(DOOR_PORT, DOOR_IN2,DIO_LOW);
	DIO_SetPinValue(DOOR_PORT, DOOR_IN1,DIO_HIGH);
}

//anticlockwise
void DOOR_CCwMotion(void){
	//setting IN1 to 0 and IN2 to 1
	DIO_SetPinValue(DOOR_PORT, DOOR_IN1,DIO_LOW);
	DIO_SetPinValue(DOOR_PORT, DOOR_IN2,DIO_HIGH);
}

// DOOR init
void DOOR_Init(void){
	//directions as output
	DIO_SetPinDirection(DIO_PORTD, DOOR_ENA,DIO_OUTPUT);
	DIO_SetPinDirection(DOOR_PORT, DOOR_IN1,DIO_OUTPUT);
	DIO_SetPinDirection(DOOR_PORT, DOOR_IN2,DIO_OUTPUT);

	//setting IN1 to 0 and IN2 to 0
	DIO_SetPinValue(DOOR_PORT, DOOR_IN1,DIO_LOW);
	DIO_SetPinValue(DOOR_PORT, DOOR_IN2,DIO_LOW);

}
//DOOR stop
void DOOR_Stop(void){

	//setting IN1 to 0 and IN2 to 0
	DIO_SetPinValue(DOOR_PORT, DOOR_IN1,DIO_LOW);
	DIO_SetPinValue(DOOR_PORT, DOOR_IN2,DIO_LOW);

}


