
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
	
	P2  = 0x00;   //����λ���㣻
	P2 |= 0xf0;
	
	_nop_();_nop_();_nop_();_nop_();
	
	Key_Val |= (P2&0xf0);
	
	P2  = 0x00;   //����λ���㣻
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
	
	if(keyStat == KEY_IDL_STAT) //������״̬
	{
		keyLast = Key_Val;     //���水����ǰ��ֵ
		
		if(Key_Val != KEY_NONE)  //�����ֵ��Ϊ��
		{
			keyStat = KEY_TRIG_STAT;   //����״̬Ϊ����̬
		}
			
	}
	else if(keyStat == KEY_TRIG_STAT)   //����״̬Ϊ����̬
	{
		if(keyLast == Key_Val)       //��εļ�ֵ���ϴ����
		{
			old_ticks = SysTicks;     //��¼�˿̵�ʱ��
			keyStat = KEY_FRESSED_STAT;   //����״̬Ϊ���¡�
		}
		else                      //�����εļ�ֵ���ϴεļ�ֵ����ȣ�
		{
			keyStat = KEY_IDL_STAT;     //����״̬����Ϊ����
			keyLast = KEY_NONE;			//��ֵ��������Ϊ�� ��
		}
	}
	else if(keyStat == KEY_FRESSED_STAT)   //�������״̬Ϊ����
	{
		if(Key_Val == KEY_NONE)       //�����ֵΪ�գ�˵���Ѿ����𰴼�
		{
			keyStat = KEY_IDL_STAT;		//����״̬����Ϊ����
			return keyLast;			//������һ�ε���Ч����ֵ
		}
		else						//�����ֵ��Ϊ��
		{
			if(SysTicks - old_ticks > LONG_PREESS_EFFECTIVE_TIME)     //���ʱ�䳬���������ʱ��
			{
				keyStat = KEY_LONG_PRESS_STAT;			//����״̬����Ϊ����
				old_ticks = SysTicks;					//��¼��ʱ��ʱ�䡣
			}
		}
	}
	else if(keyStat == KEY_LONG_PRESS_STAT)    		//���Ϊ����״̬
	{
		if(Key_Val != KEY_NONE)					//�����ֵ��Ϊ��
		{
			if(SysTicks - old_ticks > KEY_REPEAT_RATE)   //���ʱ�䳬������ѭ�����ʱ��
			{
                old_ticks = SysTicks;				//��¼��ʱ��ʱ�䡣
				return keyLast;					//������һ�ε���Ч����ֵ
			}
			else           						//���ʱ��С�ڳ���ѭ�����ʱ��		
			{
				return KEY_NONE;				//���ؼ�ֵΪ��
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





