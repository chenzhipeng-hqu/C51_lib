
#include "KEY.h"
#include "string.h"
#include "timer.h"
#include "LCD5110.h"
#include "PID.h"


/**
 *@brief:	paraments of key port
 *@{
 */
/* key opration paraments */
#define		KEY_REPEAT_RATE				300
#define		LONG_PREESS_EFFECTIVE_TIME	1000

/* key state */
#define		KEY_IDL_STAT			0x00
#define		KEY_TRIG_STAT			0x01
#define		KEY_FRESSED_STAT		0x02
#define		KEY_LONG_PRESS_STAT		0x03
/*
 *@}
 */ /* end of paraments of key port */

 /**
 *@{addtogroup key coding
 */
#define		KEY0		0x77
#define		KEY1		0xb7
#define		KEY2		0xd7
#define		KEY3		0xe7
#define		KEY4		0x7b
#define		KEY5		0xbb
#define		KEY6		0xdb
#define		KEY7		0xeb
#define		KEY8		0x7d
#define		KEY9		0xbd
#define		KEY10		0xdd
#define		KEY11		0xed
#define		KEY12		0x7e
#define		KEY13		0xbe
#define		KEY14		0xde
#define		KEY15		0xee
/**
 *@}
 */ /* end of key coding */


void Key_Init(void)
{
	P2 = 0xFF;
}

s16 Key_Scan(void)
{
	s16 Key_Val = 0;
	static u32 old_ticks;
	static u8   keyLast = KEY_IDL_STAT, keyStat = KEY_IDL_STAT;
	
	P2  = 0x00;   //低四位置零；
	P2 |= 0xf0;
	
	_nop_();_nop_();_nop_();_nop_();
	
	Key_Val |= (P2&0xf0);
	
	P2  = 0x00;   //高四位置零；
	P2 |= 0x0f;
	
	_nop_();_nop_();_nop_();_nop_();
	
	Key_Val |= (P2&0x0f);
	
	switch(Key_Val)
	{
		case KEY0:
				Key_Val = 0;
			break;
		case KEY1:
				Key_Val = 1;
			break;
		case KEY2:
				Key_Val = 2;
			break;
		case KEY3:
				Key_Val = 3;
			break;
		case KEY4:
				Key_Val = 4;
			break;
		case KEY5:
				Key_Val = 5;
			break;
		case KEY6:
				Key_Val = 6;
			break;
		case KEY7:
				Key_Val = 7;
			break;
		case KEY8:
				Key_Val = 8;
			break;
		case KEY9:
				Key_Val = 9;
			break;
		case KEY10:
				Key_Val = 10;
			break;
		case KEY11:
				Key_Val = 11;
			break;
		case KEY12:
				Key_Val = KEY_RUN;
			break;
		case KEY13:
				Key_Val = 13;
			break;
		case KEY14:
				Key_Val = KEY_DEL;
			break;
		case KEY15:
				Key_Val = KEY_ENTER;
			break;
		default:
				Key_Val = KEY_NONE;
			break;
	}
	
	if(keyStat == KEY_IDL_STAT) //按键空状态
	{
		keyLast = Key_Val;     //储存按键当前的值
		
		if(Key_Val != KEY_NONE)  //如果键值不为空
		{
			keyStat = KEY_TRIG_STAT;   //按键状态为触发态
		}
			
	}
	else if(keyStat == KEY_TRIG_STAT)   //按键状态为触发态
	{
		if(keyLast == Key_Val)       //这次的键值和上次相等
		{
			old_ticks = SysTicks;     //记录此刻的时间
			keyStat = KEY_FRESSED_STAT;   //按键状态为按下。
		}
		else                      //如果这次的键值和上次的键值不相等，
		{
			keyStat = KEY_IDL_STAT;     //按键状态设置为空闲
			keyLast = KEY_NONE;			//键值储存设置为空 。
		}
	}
	else if(keyStat == KEY_FRESSED_STAT)   //如果按键状态为按下
	{
		if(Key_Val == KEY_NONE)       //如果键值为空，说明已经弹起按键
		{
			keyStat = KEY_IDL_STAT;		//按键状态设置为空闲
			return keyLast;			//返回上一次的有效按键值
		}
		else						//如果键值不为空
		{
			if(SysTicks - old_ticks > LONG_PREESS_EFFECTIVE_TIME)     //如果时间超过长按检测时间
			{
				keyStat = KEY_LONG_PRESS_STAT;			//按键状态设置为长按
				old_ticks = SysTicks;					//记录此时的时间。
			}
		}
	}
	else if(keyStat == KEY_LONG_PRESS_STAT)    		//如果为长按状态
	{
		if(Key_Val != KEY_NONE)					//如果键值不为空
		{
			if(SysTicks - old_ticks > KEY_REPEAT_RATE)   //如果时间超过长按循环检测时间
			{
                old_ticks = SysTicks;				//记录此时的时间。
				return keyLast;					//返回上一次的有效按键值
			}
			else           						//如果时间小于长按循环检测时间		
			{
				return KEY_NONE;				//返回键值为空
			}
				
		}
		keyStat = KEY_IDL_STAT;	
	}
	else
	{
		old_ticks = SysTicks;
		keyStat = KEY_IDL_STAT;
	}
	return KEY_NONE;
	
}





