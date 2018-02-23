


#ifndef		_PID_H_   
#define		_PID_H_


#include "common.h"

#define		MOTOR_STOP		0
#define		MOTOR_RUN		1

#define		MAX_SPEED		3000
#define		MIN_SPEED		200

extern s32 NowSpeed;
extern s16 SetSpeed;
extern u16 Speed_Filter[60];//现在的速度 速度5点滤波数组

extern u8 Motor_State;

void PID_Init(void);
void Get_NowSpeed(void);
s16 PID_Cal(void);






#endif //