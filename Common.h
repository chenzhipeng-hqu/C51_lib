
/**
  ******************************************************************************
  * @file    common.h
  * @author  CZP
  * @version V1.0.0
  * @date    13-January-2016
  * @brief   common.h
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
#ifndef		_COMMON_H_   
#define		_COMMON_H_
/*************************************
              include
*************************************/
#include "STC12C5A60S2.H"
//#include <STC15F2K60S2.H>
#include <stdio.h>
#include <stdlib.h>
#include <intrins.h>
#include <string.h>

/*************************************
              define
*************************************/

#define 	FOSC      		12000000L// 24000000L//	11059200UL//		  

//#define 	T1MS 		(65536-FOSC/12/1000)   //1ms timer calculation method in 12T mode

#define		SYS_TICKS_CLK	(65536-FOSC/1000)   //1ms timer calculation method in 1T mode  1000HZ


#define 	SETB(x,y) 		( x |= 1<< y )
#define 	CLRB(x,y) 		( x &= ~(1<< y) )
#define 	NORB(x,y)		( x ^= 1<< y )
#define 	CHEB(x,y) 		(!(!(x & 1<< y)))  //¼ì²âxµÄµÚyÎ»ÊÇ·ñÎª1£»

#define 	Abs_e(x)   		((x)>0?(x):(0-x))
#define 	GetSign(x) 		((x)>=0?(1):0)  //¶ÁÈ¡·ûºÅ
#define 	Swap(x, y)		do{x = x + y; y = x - y; x = x - y;}while(0)
#define		IS2*N(x)  		((x & (x - 1))? 0 : 1)    //ÊÇ·ñÎª2µÄÈô¸É´ÎÃÝ
#define		Limit(x,x_min,x_max)	((x>x_max)?(x = x_max):((x<x_min)?(x = x_min):x))

#define 	GetTh(x)		((x/1000)		)	//¶ÁÈ¡Ç§Î»Êý×Ö
#define 	GetHu(x)		((x/100	)%10	)	//¶ÁÈ¡°ÙÎ»Êý×Ö
#define 	GetTe(x)		((x/10	)%10	)	//¶ÁÈ¡Ê®Î»Êý×Ö
#define 	GetSi(x)		((x		)%10	)	//¶ÁÈ¡¸öÎ»Êý×Ö

/**************************************
               typedef
**************************************/
typedef		volatile 				__IO;
typedef		bit 					bool;
typedef 	char  					s8,int8,int8_t;
typedef 	int  					s16,int16,int16_t;
typedef 	long int  				lint,s32,lint32,lint32_t;
typedef 	unsigned char  			uchar,u8,uint8,uint8_t;
typedef 	unsigned int  			uint,u16,uint16,uint16_t;
typedef 	unsigned long int		ulint,u32,ulint32,ulint32_t;

typedef enum{
	DISABLE = 0,ERROR = 0,fault 	= 0,FALSE = 0,false	= 0,OFF = 0,LOW = 0,
	ENABLE  = 1,OK 	  = 1,SUCCESS = 1,TRUE  = 1,true	= 1,ON = 1,	HIGH = 1
}eR_STATE;

/*************************************
              variable
*************************************/
sbit SWM = P3^3;//µ÷ÊÔÒý½Å¶¨Òå


/*************************************
              function
*************************************/
extern void Delay_Ms(int nms);



#endif //_COMMON_H
