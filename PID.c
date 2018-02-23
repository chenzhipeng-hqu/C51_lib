
#include "PID.h"
#include "ExtInt.h"
#include "LCD5110.h"
							 //tab	10			//20			//30
#define 	PID_P		0.048//0.038		//0.02			//0.045
#define 	PID_I		0.00029//0.0003		//0.0023 		// 0.001
#define 	PID_D		0.0099 //0.0005		//0.001 		//0.05

u8 Motor_State = MOTOR_STOP;
s32 NowSpeed = 0;
s16 SetSpeed = 2225;
u16 Speed_Filter[60];//现在的速度 速度5点滤波数组
					 //300  500	 700  900  1100 1300 1500 1700 1900	2100 2300 2500 2700 2900
u8 code PWM_Tab[15] = {0x1E,0x23,0x29,0x33,0x35,0x40,0x46,0x4E,0x58,0x5E,0x61,0x67,0x6A,0x6C};

void PID_Init(void)
{
	
}

void Get_NowSpeed(void)
{
	NowSpeed = Speed_Pulse * 3;
	Speed_Pulse = 0;
}


s16 PID_Cal(void)
{
	static s32 Prev_Error = 0, Integral_I = 0;
	s32 Now_Error = 0,tempErr;
	float PWM_Temp;
	s16 PWM_Out;
	u8 Array[15];
	
	Now_Error = SetSpeed - NowSpeed;  //实际速度与预设速度的偏差
	
	//if( (Integral_I > -2000000) & (Integral_I < 2000000) )
	{
		Integral_I += Now_Error;  	//计算偏差的积分
	}
	
 //	PWM_Temp = PWM_Tab[((SetSpeed - MIN_SPEED)/200)] + (PID_I * Integral_I) + (PID_D * (Prev_Error-Now_Error));
	
    PWM_Temp = (PID_P * Now_Error) + (PID_I * Integral_I) + (PID_D * (Prev_Error-Now_Error));
	
	Prev_Error = Now_Error;    //保存本次误差
	
	PWM_Out = PWM_Temp * 1;
	
//	PWM_Out = 0x61;  //2500
	
	sprintf(Array,"PWM:  %02x %02x",(u16)PWM_Out,(s16)PWM_Tab[((SetSpeed - MIN_SPEED)/200)]);		
	LCD_printsl(0, 3, Array);
	
	sprintf(Array,"I:%6ld",Integral_I);		
	LCD_printsl(0, 4, Array);
	
	if( ((Now_Error > 10) & (Now_Error < 18) & (Now_Error != 15)) )
	{
		tempErr = Now_Error - 10;
	}
	else if( (Now_Error > -18) & (Now_Error < -10) & (Now_Error != -15))
	{
		tempErr = Now_Error + 10;
	}
	else 
	{
		tempErr = Now_Error;
	}
/**/	
	sprintf(Array,"NowERR:%6ld",Abs_e(tempErr));		
	LCD_printsl(0, 5, Array);
	
	return (s16)PWM_Out;/**/
}


