

#ifndef		__INFRA_RED_H__   
#define		__INFRA_RED_H__ 

#include "common.h"

sbit IR_RX_PIN = P1^4;

typedef enum _IRType_e
{
	IRType_NONE = 0,
	IRType_NEC,
	IRType_RC5,// PHILIPS
	IRType_RC6,
  IRType_RCA,// THOMSON
  IRType_JVC,
  IRType_TRC,
  IRType_SONY,
  IRType_SHARP,
	IRType_MIT,
	IRType_KONK,
	IRType_MI,
	IRType_NEC_WB,
	IRType_TOP,

	IRType_MAX,
}IRType_e;

typedef struct _IR_DataTypeDef
{
	u16 address;
	u8 command;
	u8 command_check;
}IR_DataTypeDef;

typedef struct _IR_BufTypeDef
{
	u16 timer;
	u8 pin_state;
}IR_BufTypeDef;

typedef struct _IR_InitTypeDef
{
	IR_BufTypeDef rx_buf[60];
	u8 len;
	IR_DataTypeDef value;
	u16 carry_freq;
}IR_TypeDef;

#define	IR_RX_PORT			P1
#define IR_RX_PIN				4
#define	IR_RX_GET_PIN()	IR_RX_PIN
//#define	IR_RX_OFF()			SETB(LED0_PORT,LED0_PIN)
//#define	IR_RX_GET_PIN()	CLRB(LED0_PORT,LED0_PIN)
//#define	IR_RX_OFF()			SETB(LED0_PORT,LED0_PIN)

int InfraRed_RX_Init(void);




#endif /* __INFRA_RED_H__ */