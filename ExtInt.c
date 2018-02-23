
#include "ExtInt.h"
#include "PID.h"


void ExtInt0_Init(void)
{
	IT0 = 1;                        //set INT0 int type (1:Falling 0:Low level)
    EX0 = 1;                        //enable INT0 interrupt
	PX0 = 1;						//外部中断优先级设置为最高
}

//External interrupt0 service routine
void ExtInt0_ISR(void) interrupt 0           //(location at 0003H)
{
	
}