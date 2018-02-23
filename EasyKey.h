
#ifndef		_EasyKey_H_   
#define		_EasyKey_H_

#include "Common.h"

//����λ����
sbit S0=P3^2;
sbit S1=P3^3;
sbit S2=P3^4;
sbit S3=P3^6;
sbit S4=P3^7;

//��������Ϊ3
#define key_num 5
#define Default_Voltage	1	//����δ���µĵ�ѹ
#define continue_T 100	//�����ߵ�ƽȷ��ʱ��
#define ctn_tri_T  10	//�����ߵ�ƽ����ʱ��

#define LOW_Level  0	//�͵�ƽ
#define HIGH_Level 1	//�ߵ�ƽ
#define Rising		 2	//������
#define Falling		 3	//�½���
#define continue_L 4	//�����͵�ƽ
#define continue_H 5	//�����ߵ�ƽ
#define ctn_tri_L  6	//�����͵�ƽ����
#define ctn_tri_H	 7	//�����ߵ�ƽ����

extern unsigned char KEY_Prev[key_num];	//��һ�εİ���ֵ
extern unsigned char KEY_Now[key_num];		//��ǰ���İ���ֵ
extern unsigned char KEY_State[key_num];	//����״̬
extern unsigned int  KEY_Time[key_num];	//����״̬������ʱ��

void Read_Key(void);//��ȡ����
#endif //_EasyKey_H