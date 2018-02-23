
#ifndef		_EasyKey_H_   
#define		_EasyKey_H_

#include "Common.h"

//按键位定义
sbit S0=P3^2;
sbit S1=P3^3;
sbit S2=P3^4;
sbit S3=P3^6;
sbit S4=P3^7;

//按键数量为3
#define key_num 5
#define Default_Voltage	1	//按键未按下的电压
#define continue_T 100	//连续高电平确认时间
#define ctn_tri_T  10	//连续高电平触发时间

#define LOW_Level  0	//低电平
#define HIGH_Level 1	//高电平
#define Rising		 2	//上升沿
#define Falling		 3	//下降沿
#define continue_L 4	//连续低电平
#define continue_H 5	//连续高电平
#define ctn_tri_L  6	//连续低电平触发
#define ctn_tri_H	 7	//连续高电平触发

extern unsigned char KEY_Prev[key_num];	//上一次的按键值
extern unsigned char KEY_Now[key_num];		//当前读的按键值
extern unsigned char KEY_State[key_num];	//按键状态
extern unsigned int  KEY_Time[key_num];	//按键状态持续的时间

void Read_Key(void);//读取按键
#endif //_EasyKey_H