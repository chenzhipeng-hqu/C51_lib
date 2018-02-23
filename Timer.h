

#ifndef		_TIMER_H_   
#define		_TIMER_H_


#include "common.h"


extern u32 g_ulSysTicks;      //系统时间

u32 *TM0_Init(void);

void TM1_Init(void);  //5ms??@11.0592MHz

void Delay_Ms(int nms);




#endif //