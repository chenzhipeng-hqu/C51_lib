
#ifndef		_LCD5110_H_   
#define		_LCD5110_H_


#include "common.h"

#define X_Col_Addr     0x80		//????0???(?????)(0 - 83)
#define Y_Page_Addr    0x40		//????0???(?????)(0 - 5)


/*--------------------------------------------------------------*/
//?????
//????
#define LCD_reset_hard	LCD_RST = 0; LCD_RST = 1	//????
#define LCD_reset_soft	LCD_reset_5510()			//????
//??????(???DDRAM)
#define LCD_show_blank		LCD_write_cmd(0x08)		//????
#define LCD_show_normal		LCD_write_cmd(0x0c)		//????
#define LCD_show_black		LCD_write_cmd(0x09)		//????
#define LCD_show_inverse 	LCD_write_cmd(0x0d)		//????
//????
#define LCD_write_cmd(cmd)	LCD_write_byte(cmd, 0)	//????
#define LCD_write_dat(dat)	LCD_write_byte(dat, 1)	//????
  
sbit LCD_CLK = P1^5;     //����ʱ��         //������д������  
sbit LCD_DIN = P1^6;     //������������       //�ȸߺ��  
sbit LCD_DC  = P1^7;     //����ָ����ƶ�  //�ߵ�ƽ���ݣ��͵�ƽָ��  
sbit LCD_CS  = P1^1;     //Ƭѡʹ��         //�͵�ƽ��Ч  
sbit LCD_RST = P1^0;     //LCD��λ��       //�͵�ƽ��λ  
sbit LCD_LED = P0^2;    //����ƿ��ƶ�      //�ߵ�ƽ��LED  
  
/*--------------------------------------------------------------*/
//????(??)
extern void LCD_write_byte(unsigned char wbyte, unsigned char dat_cmd);//????
extern void LCD_reset_5510(void);										//??LCD5510


/*--------------------------------------------------------------*/
//????(??)
/*--------------------------------------------------------------*/
//????(?DDRAM)
extern void LCD_clr_scr(void);


/*--------------------------------------------------------------*/
//??????(1*1)
//????:
//x: 0 - 83
//y: 0 - 5
extern void LCD_pos_byte(unsigned char x, unsigned char y);


/*--------------------------------------------------------------*/
//????
//num:	0 - 5
extern void LCD_clr_row(unsigned char num);


/*--------------------------------------------------------------*/
//??????(6*8??)
//x: 0 - 13
//y: 0 - 5
extern void LCD_printc(unsigned char x, unsigned char y, unsigned char c_dat);


/*--------------------------------------------------------------*/
//???????(6*8??)
//x: 0 - 13
//y: 0 - 5
extern void LCD_prints(unsigned char x, unsigned char y, unsigned char *s_dat);


/*--------------------------------------------------------------*/
//???????,????(6*8??)
//x: 0 - 13
//y: 0 - 5
extern void LCD_printsl(unsigned char x, unsigned char y, unsigned char *s_dat);


/*--------------------------------------------------------------*/
//???LCD5510
extern void LCD5110_Init(void);				



#endif