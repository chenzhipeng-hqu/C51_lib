
#ifndef __TFT18_H_
#define __TFT18_H_		

#include "Common.h"	//ͨ��ͷ�ļ�

//#define delayms Delay_Ms

/* 
//����Ĭ��IO���ӷ�ʽ��
sbit LCD_CS     =P0^0;     //Ƭѡ	
sbit LCD_AO     =P0^2;	  //����/�����л�
sbit LCD_SDA    =P1^5;	  //����
sbit LCD_SCK    =P1^7;	  //ʱ��
sbit LCD_REST   =P0^1;	  //��λ  
*/ 
 //����LCD�ĳߴ�	
#define LCD_W 128
#define LCD_H 160


//IO����  
#define LCD_CS     P01     //Ƭѡ	
#define LCD_AO     P03	  //����/�����л�
#define LCD_SDA    P04	  //����
#define LCD_SCK    P05	  //ʱ��
#define LCD_REST   P02	  //��λ  


extern  u16 BACK_COLOR, POINT_COLOR;   //����ɫ������ɫ


extern void Lcd_Init(void); 
extern void LCD_Clear(u16 Color);
extern void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
extern void LCD_WR_DATA8(char da);
extern void LCD_WR_DATA(int da);
extern void LCD_WR_REG(char da);

extern void LCD_DrawPoint(u16 x,u16 y);//����
extern void LCD_DrawPoint_big(u16 x,u16 y);//��һ�����
u16  LCD_ReadPoint(u16 x,u16 y); //����
extern void Draw_Circle(u16 x0,u16 y0,u8 r);
extern void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
extern void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
extern void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
extern void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode);//��ʾһ���ַ�
extern void LCD_ShowCH(unsigned int x,unsigned int y,unsigned char index)	;
extern void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len);//��ʾ����
extern void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len);//��ʾ2������
extern void LCD_ShowString(u16 x,u16 y,const u8 *p);		 //��ʾһ���ַ���,16����
 
extern void showhanzi(unsigned int x,unsigned int y,unsigned char index);



//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


					  		 
#endif  
	 
	 



