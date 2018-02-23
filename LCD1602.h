
#ifndef _LCD1602_H_
#define _LCD1602_H_

#include "common.h"



#define LCD_DATA  P0

//#define uchar  unsigned char
//#define uint  unsigned int


sbit LCD_RS = P2^0;
sbit LCD_RW = P2^1;
sbit LCD_E  = P2^2;

void LCD_Init(void);
void LCD_Com(uchar com);
void LCD_Data(uchar dat);
void LCD_Write_String(uchar xpos,uchar ypos,uchar *s);
void delay(uint z); 






#endif

