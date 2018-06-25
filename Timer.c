
#include "timer.h"
#include "ExtInt.h"  
#include "task.h"  



volatile u32 g_ulSysTicks = 0;      //系统时间


/**
  * @brief  TM0_Init
  * @param  
  * @retval 
  */
u32 *TM0_Init(void)		//1ms@11.0592MHz
{
	AUXR |= 0x80;		//?????1T??
	TMOD |= 0x01;
	TL0	= SYS_TICKS_CLK;                     //initial timer0 low byte
	TH0	= SYS_TICKS_CLK >> 8;                //initial timer0 high byte
	TF0	= 0;						//clr TF0 flag
	TR0 = 1;                        //timer0 start running
	ET0 = 1;                        //enable timer0 interrupt
	
	return &g_ulSysTicks;
}

/**
  * @brief  TM0_Init
  * @param  
  * @retval 
  */
void TM1_Init(void)  //5ms??@11.0592MHz
{	
	//AUXR |= 0x40;		//?????1T??
	TMOD &= 0x0F;		//???????
	TMOD |= 0x10;		//???????
	TL1	= SYS_TICKS_CLK;                     //initial timer0 low byte
	TH1	= SYS_TICKS_CLK >> 8;                //initial timer0 high byte
	TF1 = 0;		//??TF1??
	TR1 = 1;		//???1????
	ET1 = 1;
}


/**
  * @brief  Delay_Ms
  * @param  nms
  * @retval none
  */
void Delay_Ms(int nms)
{
	u32 old_ticks = g_ulSysTicks;
	while((g_ulSysTicks-old_ticks) <= nms);
}

/**
  * @brief  TM0_ISR
  * @param  
  * @retval 
  */
void TM0_ISR(void)  interrupt 1 
{
	TL0	= SYS_TICKS_CLK;                     //initial timer0 low byte
	TH0	= SYS_TICKS_CLK >> 8;                //initial timer0 high byte
	g_ulSysTicks++;	
	TaskTickHandler();
}

/**
  * @brief  TM1_ISR
  * @param  
  * @retval 
  */
void TM1_ISR(void) interrupt 3 using 3           //(location at 001BH)
{

	SWM = 0;    //调试引脚 用于观察定时器中断使用的时间

	SWM = 1;  //调试引脚 用于观察定时器中断使用的时间
}


