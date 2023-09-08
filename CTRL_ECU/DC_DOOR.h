/*
 * DC_DOOR.h
 *
 *  Created on: Sep 6, 2023
 *      Author: Dell
 */

#ifndef DC_DOOR_H_
#define DC_DOOR_H_

//"using H BRIDGE"
#define DOOR_PORT		DIO_PORTA
#define DOOR_ENA		DIO_PIN7
#define DOOR_IN1		DIO_PIN1
#define DOOR_IN2		DIO_PIN2

// clockwise
void DOOR_CwMotion(void);

//anticlockwise
void DOOR_CCwMotion(void);

// DOOR init
void DOOR_Init(void);
//DOOR stop
void DOOR_Stop(void);



#endif /* DC_DOOR_H_ */
