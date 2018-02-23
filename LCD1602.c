
#include "LCD1602.h"


void delay(uint z)  
{  
    uint x,y;  
    for(x=z;x>0;x--)  
    for(y=110;y>0;y--);  
}

 bit LCD_Check_Busy(void) 
 { 
	 LCD_DATA= 0xFF; 
	 LCD_RS = 0; 
	 LCD_RW = 1; 
	 LCD_E  = 0;
	 _nop_(); 
	 LCD_E  = 1; 
	 return (bit)(LCD_DATA & 0x80);
 }

void LCD_Com(uchar com){
	LCD_Check_Busy();
	LCD_RS = 0;  
	LCD_RW = 0;
	LCD_E  = 0;
	LCD_DATA = com;
	delay(1);  
	LCD_E  = 1; 
	delay(5);  
	LCD_E  = 0; 
}

void LCD_Data(uchar dat){
	LCD_Check_Busy();
	LCD_RS = 1;  
	LCD_RW = 0;
	LCD_E  = 0;
	LCD_DATA = dat;
	delay(1);  
	LCD_E  = 1; 
	delay(5);  
	LCD_E  = 0; 
}

void LCD_Init(void){
	//LCD_E = 0;
	LCD_Com(0X38);//初始化液晶为8为总线，显示两行，5*7点阵每字符
	LCD_Com(0X0e);//开显示，有光标，光标不闪烁
	LCD_Com(0X06);//写入新数据后光标右移，屏幕不移动
	LCD_Com(0X01);//清屏指令
	LCD_Com(0X80);//AC指针移动到左上角，
}

void LCD_Write_String(uchar xpos,uchar ypos,uchar *s){
	if(ypos)	LCD_Com(0XC0+xpos);
	else      LCD_Com(0X80+xpos);
	while(*s){
		LCD_Data(*s);
		s++;
	}	
}





