

#ifndef		__INFRA_RED_NEC_H__   
#define		__INFRA_RED_NEC_H__ 

#include "common.h"

typedef struct
{
	u8 Pin_State;
	u16 Time;
}Nec;

int InfraRed_RX_NEC_Init(void);




#endif /* __INFRA_RED_NEC_H__ */