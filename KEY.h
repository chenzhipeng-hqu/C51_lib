

#ifndef		_KEY_H_   
#define		_KEY_H_


#include "common.h"


#define  ROW  		(P2&0x0f)    //ÐÐ
#define  COLUMN  	(P2&0xf0)  //ÁÐ

/*--------------------------------------------
 --				DEFIEN_IO_PORT
 --------------------------------------------*/

/**
 *@{addtougroup oder coding
 */
#define		KEY_RUN		0x0c
#define		KEY_DEL		0x0e
#define		KEY_ENTER	0x0f
#define		KEY_NONE	0xff
/*
 *@}
 */ /* end of key coding */
 
 
void Key_Init(void);

s16 Key_Scan(void);

u8 Input_SetSpeed(s16 key_val);



#endif //