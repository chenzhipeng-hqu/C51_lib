
#ifndef		_LED_H_   
#define		_LED_H_

#include "common.h"

sbit LED0 = P1^0;

//#define	LED0_PORT		P1
//#define LED0_PIN		0
//#define	LED0_ON()		CLRB(LED0_PORT,LED0_PIN)
//#define	LED0_OFF()		SETB(LED0_PORT,LED0_PIN)
//#define	LED_FLASH()		NORB(LED0_PORT,LED0_PIN)

void LED_Init(void);




#endif //