
#ifndef _USART_H_
#define _USART_H_
#include "Common.h"

#define BAUD 		9600           //UART baudrate
#define DATA_MAX 	16     //接收和发送的最大数据个数

extern unsigned char Receive_Buff[DATA_MAX],Transmit_Buff[DATA_MAX];  

extern u8 g_u8RxCnt;


bit  Usart_Init(void);
void SendData(unsigned char dat);
void SendString(char *s);


#endif



