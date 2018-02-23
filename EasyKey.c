#include "EasyKey.h"
unsigned char KEY_Prev[key_num];	//��һ�εİ���ֵ
unsigned char KEY_Now[key_num];		//��ǰ���İ���ֵ
unsigned char KEY_State[key_num];	//����״̬
unsigned int  KEY_Time[key_num];	//����״̬������ʱ��
//��ȡ����
void Read_Key(void)
{
	unsigned char i;
	//�ȰѰ�����ѹ����Ϊ�ް��µĵ�ѹ ���δ���� ���ѹ����
	S0 = Default_Voltage;
	S1 = Default_Voltage;
	S2 = Default_Voltage;
	S3 = Default_Voltage;
	//Ȼ���ȡ
	KEY_Now[0] = S0;
	KEY_Now[1] = S1;
	KEY_Now[2] = S2;
	KEY_Now[3] = S3;
	KEY_Now[4] = S4;	
	for(i=0;i<key_num;i++){//
		if(KEY_Now[i] !=KEY_Prev[i]){//��ֵ����һ�β�ͬ�� Ϊ����
				KEY_Time[i] = 0;//��հ�������ʱ��
			if(KEY_Now[i] == 0){//���ݰ�����ֵ �ж����������½���
				KEY_State[i] = Falling;//�½���
			}else{
				KEY_State[i] = Rising;	//������
			}
		}else{//��ֵ����һ����ͬ�� Ϊһֱ����
				KEY_Time[i] ++;	//����ʱ���һ
			if(KEY_Now[i] == 0){	//�ж��Ǹߵ�ƽ���ǵ͵�ƽ				
				if((KEY_State[i] == continue_L)|(KEY_State[i] == ctn_tri_L)){			//�����Ƿ����������µ�״̬��
					if(KEY_Time[i]>=ctn_tri_T) {KEY_State[i] = ctn_tri_L;KEY_Time[i] = 0;}	//����������� ���ڴ���
					else												KEY_State[i] = continue_L;					//����ʱ�䲻���ڴ���״̬
				}else{
					if(KEY_Time[i]>continue_T)	KEY_State[i] = continue_L;					//�����������ʱ�䳬��һ��ʱ�� ������������״̬
					else												KEY_State[i] = LOW_Level;						//�����Ϊ����״̬
				}
			}else{//�����͵�ƽ
				if((KEY_State[i] == continue_H)|(KEY_State[i] == ctn_tri_H)){			//�����Ƿ����������µ�״̬��
					if(KEY_Time[i]>=ctn_tri_T) {KEY_State[i] = ctn_tri_H;KEY_Time[i] = 0;}	//����������� ���ڴ���
					else												KEY_State[i] = continue_H;					//����ʱ�䲻���ڴ���״̬
				}else{
					if(KEY_Time[i]>continue_T)	KEY_State[i] = continue_H;					//�����������ʱ�䳬��һ��ʱ�� ������������״̬
					else												KEY_State[i] = HIGH_Level;						//�����Ϊ����״̬
				}
			}
		}
	}
	for(i=0;i<key_num;i++){
		KEY_Prev[i] = KEY_Now[i];//��¼��һ�εİ�����ֵ
	}
}
