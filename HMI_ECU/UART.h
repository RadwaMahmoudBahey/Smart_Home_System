/*
 * USART.h
 *
 *  Created on: Aug 22, 2023
 *      Author: Mariam
 */

#ifndef USART_H_
#define USART_H_


/* USART Control and Status Register B   UCSRB */

#define    RXCIE        7
#define    TXCIE        6
#define    UDRIE        5
#define    RXEN         4
#define    TXEN         3
#define    UCSZ         2
#define    UCSZ2        2
#define    RXB8         1
#define    TXB8         0


/* USART Control and Status Register A UCSRA   */

#define    RXC          7
#define    TXC          6
#define    UDRE         5
#define    FE           4
#define    DOR          3
#define    UPE          2
#define    U2X          1
#define    MPCM         0




/* USART Baud Rate Register Low  UBRRL   */

/* USART I/O Data Register  UDR */

/* USART Baud Rate Register High UBRRH */

//the same address ..
/* USART Control and Status Register C UCSRC  */


/* USART Register C */
#define    URSEL        7
#define    UMSEL        6
#define    UPM1         5
#define    UPM0         4
#define    USBS         3
#define    UCSZ1        2
#define    UCSZ0        1
#define    UCPOL        0



void UART_Init(void);
void USART_SendData(u8 u8data_Copy);
u8   USART_ReceiveData(void);
void USART_voidSendString(u8* Copy_pu8Data);
void USART_voidReceiveString(u8* Copy_pu8Data);


#endif /* USART_H_ */




