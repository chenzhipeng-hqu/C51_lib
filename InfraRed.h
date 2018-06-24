

#ifndef		__INFRA_RED_H__   
#define		__INFRA_RED_H__ 

#include "common.h"

sbit IR_RX_PIN = P1^4;

typedef enum
{
	IRType_NONE = 0,
	IRType_NEC,
	IRType_RCA,
	IRType_RC5,
	IRType_RC6,
	
	IRType_MAX,
}IRType_e;

#define	IR_RX_PORT			P1
#define IR_RX_PIN				4
#define	IR_RX_GET_PIN()	IR_RX_PIN
//#define	IR_RX_OFF()			SETB(LED0_PORT,LED0_PIN)
//#define	IR_RX_GET_PIN()	CLRB(LED0_PORT,LED0_PIN)
//#define	IR_RX_OFF()			SETB(LED0_PORT,LED0_PIN)

int InfraRed_RX_Init(void);




#endif /* __INFRA_RED_H__ */