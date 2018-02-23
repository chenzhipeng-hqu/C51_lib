#include "EasyKey.h"
unsigned char KEY_Prev[key_num];	//上一次的按键值
unsigned char KEY_Now[key_num];		//当前读的按键值
unsigned char KEY_State[key_num];	//按键状态
unsigned int  KEY_Time[key_num];	//按键状态持续的时间
//读取按键
void Read_Key(void)
{
	unsigned char i;
	//先把按键电压设置为无按下的电压 如果未按下 则电压不变
	S0 = Default_Voltage;
	S1 = Default_Voltage;
	S2 = Default_Voltage;
	S3 = Default_Voltage;
	//然后读取
	KEY_Now[0] = S0;
	KEY_Now[1] = S1;
	KEY_Now[2] = S2;
	KEY_Now[3] = S3;
	KEY_Now[4] = S4;	
	for(i=0;i<key_num;i++){//
		if(KEY_Now[i] !=KEY_Prev[i]){//数值与上一次不同的 为跳变
				KEY_Time[i] = 0;//清空按键按下时间
			if(KEY_Now[i] == 0){//根据按键数值 判断上升沿与下降沿
				KEY_State[i] = Falling;//下降沿
			}else{
				KEY_State[i] = Rising;	//上升沿
			}
		}else{//数值与上一次相同的 为一直按着
				KEY_Time[i] ++;	//按下时间加一
			if(KEY_Now[i] == 0){	//判断是高电平还是低电平				
				if((KEY_State[i] == continue_L)|(KEY_State[i] == ctn_tri_L)){			//根据是否在连续按下的状态中
					if(KEY_Time[i]>=ctn_tri_T) {KEY_State[i] = ctn_tri_L;KEY_Time[i] = 0;}	//如果连续按下 则定期触发
					else												KEY_State[i] = continue_L;					//其余时间不处于触发状态
				}else{
					if(KEY_Time[i]>continue_T)	KEY_State[i] = continue_L;					//如果按键按下时间超过一定时间 进入连续触发状态
					else												KEY_State[i] = LOW_Level;						//否则仅为按下状态
				}
			}else{//按键低电平
				if((KEY_State[i] == continue_H)|(KEY_State[i] == ctn_tri_H)){			//根据是否在连续按下的状态中
					if(KEY_Time[i]>=ctn_tri_T) {KEY_State[i] = ctn_tri_H;KEY_Time[i] = 0;}	//如果连续按下 则定期触发
					else												KEY_State[i] = continue_H;					//其余时间不处于触发状态
				}else{
					if(KEY_Time[i]>continue_T)	KEY_State[i] = continue_H;					//如果按键按下时间超过一定时间 进入连续触发状态
					else												KEY_State[i] = HIGH_Level;						//否则仅为按下状态
				}
			}
		}
	}
	for(i=0;i<key_num;i++){
		KEY_Prev[i] = KEY_Now[i];//记录上一次的按键数值
	}
}
