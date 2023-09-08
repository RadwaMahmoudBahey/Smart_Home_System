/*
 * Buzzer.h
 *
 *  Created on: Sep 6, 2023
 *      Author: Menna
 */

#ifndef BUZZER_H_
#define BUZZER_H_




#include "DIO.h"
#define BUZZER_PIN DIO_PIN3
#define BUZZER_PORT DIO_PORTD

void Buzzer_Init();
void Buzzer_On();
void Buzzer_Off();




#endif /* BUZZER_H_ */

