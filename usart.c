

#include "usart.h"

bit busy = 0;
u8 g_u8RxCnt = 0;
unsigned char Receive_Buff[DATA_MAX] = 0,Transmit_Buff[DATA_MAX] = 0;

bit Usart_Init(void){
	SCON = 0x50;	//8-bit variable UART
	AUXR |= 0x40;		//set timer1 to 1T
	PCON |= 0x80;		// 0x80=SMOD: set serial baudrate doubler
	TMOD |= 0x20;            //Set Timer1 as 8-bit auto reload mode
	TH1 = TL1 = 256-(FOSC/16/BAUD); //Set auto-reload vaule
	ET1 = 0;
	TR1 = 1;                //Timer1 start run
	ES  = 1;                 //Enable UART interrupt
	return 0;
}
/*----------------------------
Send a byte data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void SendData(unsigned char dat){
    while (busy);           //Wait for the completion of the previous data is sent
    busy = 1;
    SBUF = dat;             //Send data to UART buffer
}
void SendString(char *s){
    while (*s){              //Check the end of the string
		SendData(*s++);     //Send current char and increment string ptr
    }
}
void ReString(void){
	Receive_Buff[g_u8RxCnt] = SBUF;          //P0 show UART data
	g_u8RxCnt = (g_u8RxCnt+1)%DATA_MAX;
}
/*----------------------------
UART interrupt service routine
----------------------------*/
void Uart_Isr(void) interrupt 4 using 1{
	if (RI){
		RI = 0;             //Clear receive interrupt flag
		ReString();
	}else if (TI){
		TI = 0;             //Clear transmit interrupt flag
		busy = 0;           //Clear transmit busy flag
	}
}