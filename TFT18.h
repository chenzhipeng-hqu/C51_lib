
#ifndef __TFT18_H_
#define __TFT18_H_		

#include "Common.h"	//通用头文件

//#define delayms Delay_Ms

/* 
//程序默认IO连接方式：
sbit LCD_CS     =P0^0;     //片选	
sbit LCD_AO     =P0^2;	  //数据/命令切换
sbit LCD_SDA    =P1^5;	  //数据
sbit LCD_SCK    =P1^7;	  //时钟
sbit LCD_REST   =P0^1;	  //复位  
*/ 
 //定义LCD的尺寸	
#define LCD_W 128
#define LCD_H 160


//IO连接  
#define LCD_CS     P01     //片选	
#define LCD_AO     P03	  //数据/命令切换
#define LCD_SDA    P04	  //数据
#define LCD_SCK    P05	  //时钟
#define LCD_REST   P02	  //复位  


extern  u16 BACK_COLOR, POINT_COLOR;   //背景色，画笔色


extern void Lcd_Init(void); 
extern void LCD_Clear(u16 Color);
extern void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
extern void LCD_WR_DATA8(char da);
extern void LCD_WR_DATA(int da);
extern void LCD_WR_REG(char da);

extern void LCD_DrawPoint(u16 x,u16 y);//画点
extern void LCD_DrawPoint_big(u16 x,u16 y);//画一个大点
u16  LCD_ReadPoint(u16 x,u16 y); //读点
extern void Draw_Circle(u16 x0,u16 y0,u8 r);
extern void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
extern void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
extern void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
extern void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode);//显示一个字符
extern void LCD_ShowCH(unsigned int x,unsigned int y,unsigned char index)	;
extern void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len);//显示数字
extern void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len);//显示2个数字
extern void LCD_ShowString(u16 x,u16 y,const u8 *p);		 //显示一个字符串,16字体
 
extern void showhanzi(unsigned int x,unsigned int y,unsigned char index);



//画笔颜色
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
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)


					  		 
#endif  
	 
	 



