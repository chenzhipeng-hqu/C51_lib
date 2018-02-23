#include "NRF24L01.h"

/*****************************************
时间：2010.6.12
功能：NRF24L01射频模块C文件(节点发射部分)
*****************************************/
u8 code TxAddr[TX_ADDR_WITDH]={0x34,0x43,0x10,0x10,0x01};//发送地址
u8 g_ucNRF_Send_Busy = 0;
extern u8 g_ucRevFlag;
/*****************状态标志*****************************************/
u8 bdata sta;   //状态标志 
sbit RX_DR=sta^6;
sbit TX_DS=sta^5;	//数据发送完成中断
sbit MAX_RT=sta^4;  //重发次数溢出中断
//

void Delay(s16 nus)
{
	int i,j;
        for(i=0;i<nus;i++);
}

/*****************SPI时序函数******************************************/
u8 NRFSPI(u8 date)
{
    u8 i;
   	for(i=0;i<8;i++)          // 循环8次
   	{
			if(date&0x80)
				MOSI=1;
			else
				MOSI=0;   // byte最高位输出到MOSI
			date<<=1;             // 低一位移位到最高位
			SCLK=1; 
			if(MISO)               // 拉高SCK，nRF24L01从MOSI读入1位数据，同时从MISO输出1位数据
					date|=0x01;       	// 读MISO到byte最低位
			SCLK=0;            	// SCK置低
   	}
    return(date);           	// 返回读出的一字节
}
/**********************NRF24L01初始化函数*******************************/
void NRF24L01Int()
{
	Delay(2);//让系统什么都不干
	CE=0; //待机模式1   
	CSN=1;  
	SCLK=0;
	IRQ=1;	 
}
/*****************SPI读寄存器一字节函数*********************************/
u8 NRFReadReg(u8 RegAddr)
{
   u8 BackDate;
   CSN=0;//启动时序
   NRFSPI(RegAddr);//写寄存器地址
   BackDate=NRFSPI(0x00);//写入读寄存器指令  
   CSN=1;
   return(BackDate); //返回状态
}
/*****************SPI写寄存器一字节函数*********************************/
u8 NRFWriteReg(u8 RegAddr,u8 date)
{
   u8 BackDate;
   CSN=0;//启动时序
   BackDate=NRFSPI(RegAddr);//写入地址
   NRFSPI(date);//写入值
   CSN=1;
   return(BackDate);
}
/*****************SPI读取RXFIFO寄存器的值********************************/
u8 NRFReadRxDate(u8 RegAddr,u8 *RxDate,u8 DateLen)
{  //寄存器地址//读取数据存放变量//读取数据长度//用于接收
    u8 BackDate,i;
	CSN=0;//启动时序
	BackDate=NRFSPI(RegAddr);//写入要读取的寄存器地址
	for(i=0;i<DateLen;i++) //读取数据
	  {
	     RxDate[i]=NRFSPI(0);
	  } 
    CSN=1;
   return(BackDate); 
}
/*****************SPI写入TXFIFO寄存器的值**********************************/
u8 NRFWriteTxDate(u8 RegAddr,u8 *TxDate,u8 DateLen)
{ //寄存器地址//写入数据存放变量//读取数据长度//用于发送
   u8 BackDate,i;
   CSN=0;
   BackDate=NRFSPI(RegAddr);//写入要写入寄存器的地址
   for(i=0;i<DateLen;i++)//写入数据
     {
	    NRFSPI(TxDate[i]);
	 }   
   CSN=1;
   return(BackDate);
}
/*****************NRF设置为发送模式并发送数据******************************/
void NRFSetTxMode(u8 *TxDate)
{//发送模式
	clear_fifo();
    CE=0; 
   	NRFWriteTxDate(W_REGISTER+TX_ADDR,TxAddr,TX_ADDR_WITDH);//写寄存器指令+接收地址使能指令+接收地址+地址宽度
	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);//为了应答接收设备，接收通道0地址和发送地址相同
	NRFWriteTxDate(W_TX_PAYLOAD,TxDate,TX_DATA_WITDH);//写入数据 
	/******下面有关寄存器配置**************/
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);       // 使能接收通道0自动应答
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);   // 使能接收通道0
  	NRFWriteReg(W_REGISTER+SETUP_RETR,0x03);  // 自动重发延时等待250us+86us，自动重发10次
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);         // 选择射频通道0x40
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);    // 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益
	NRFWriteReg(W_REGISTER+CONFIG,0x0e);      // CRC使能，16位CRC校验，上电  
	CE=1;
	Delay(5);//保持10us秒以上
}
/*****************NRF设置为接收模式并接收数据******************************/
//主要接收模式
void NRFSetRXMode()
{
	clear_fifo();
	CE=0;  
  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);  // 接收设备接收通道0使用和发送设备相同的发送地址
//  	NRFWriteTxDate(W_REGISTER+TX_ADDR,TxAddr,TX_ADDR_WITDH); 		//写TX节点地址  
	NRFWriteReg(W_REGISTER+EN_AA,0x01);               // 使能接收通道0自动应答
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);           // 使能接收通道0
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);                 // 选择射频通道0x40
  	NRFWriteReg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);  // 接收通道0选择和发送通道相同有效数据宽度
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);            // 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益*/
  	NRFWriteReg(W_REGISTER+CONFIG,0x0f);              // CRC使能，16位CRC校验，上电，接收模式
  	CE = 1;
	Delay(5);//保持10us秒以上     
}
/****************************检测应答信号******************************/
u8 CheckACK()
{  //用于发射
	sta=NRFReadReg(R_REGISTER+STATUS);                    // 返回状态寄存器
	if(TX_DS||MAX_RT) //发送完毕中断
	{
	   NRFWriteReg(W_REGISTER+STATUS,sta);  // 清除TX_DS或MAX_RT中断标志
	   CSN=0;
	   NRFSPI(FLUSH_TX);//用于清空FIFO ！！关键！！不然会出现意想不到的后果！！！大家记住！！  
       CSN=1; 
	   return(0);
	}
	else
	   return(1);
}
/******************判断是否接收收到数据，接到就从RX取出*********************/
//用于接收模式
u8 NRFRevDate(u8 *RevDate)
{
	u8 RevFlags=0;
	sta=NRFReadReg(R_REGISTER+STATUS);//发送数据后读取状态寄存器
	if(RX_DR)				// 判断是否接收到数据
	{
		CE=0; 			//SPI使能
		NRFReadRxDate(R_RX_PAYLOAD,RevDate,RX_DATA_WITDH);// 从RXFIFO读取数据
		NRFWriteReg(W_REGISTER+STATUS,0xff); //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标	   
			CSN=0;
	   NRFSPI(FLUSH_RX);//用于清空FIFO ！！关键！！不然会出现意想不到的后果！！！大家记住！！ 
	   CSN=1;		 
		RevFlags=1;	   //读取数据完成标志
	}
	return(RevFlags);
}

void clear_fifo(void){
	CE=0; 			//SPI使能
	NRFWriteReg(W_REGISTER+STATUS,0xff); //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标	   
	CSN=0;
	NRFSPI(FLUSH_RX);//用于清空FIFO ！！关键！！不然会出现意想不到的后果！！！大家记住！！ 
	NRFSPI(FLUSH_TX);//用于清空FIFO ！！关键！！不然会出现意想不到的后果！！！大家记住！！ 
	CSN=1;		 
}

u8 Nrf24l01_Check(void)
{ 
	u8 buf1[5]; 
	u8 i; 
	/*写入5个字节的地址. */ 
//	NRF_Write_Buf(NRF_WRITE_REG+TX_ADDR,TX_ADDRESS,5); 
	NRFWriteTxDate(W_REGISTER+TX_ADDR,TxAddr, 5);
	/*读出写入的地址 */ 
//	NRF_Read_Buf(TX_ADDR,buf1,5); 
	NRFReadRxDate(TX_ADDR,buf1,5);
	/*比较*/ 
	for(i=0;i<5;i++) 
	{ 
		if(buf1[i]!=TxAddr[i]) 
			break; 
	} 
	if(i==5)
		return SUCCESS ; //MCU与NRF成功连接 
	else
		return ERROR ; //MCU与NRF不正常连接 
}

u8 NRF_ISR_Callback(void)
{
	sta=NRFReadReg(R_REGISTER+STATUS);                    // 返回状态寄存器
	if( RX_DR == 0x01 )
	{
//		P34 = ~P34;	
//		CE=0; 			//SPI使能
//		NRFReadRxDate(R_RX_PAYLOAD,RevDate,RX_DATA_WITDH);// 从RXFIFO读取数据		 
		g_ucRevFlag = SUCCESS;	   //读取数据完成标志
		CE=0;
		NRFWriteReg(W_REGISTER+STATUS,0xff);  // RX_DR,TX_DS,MAX_RT都置高为1，通过写1来清楚中断标
		P34 = !P34;	
	}
	else if( TX_DS == 0x01 ) //发送完毕中断
	{		
		g_ucNRF_Send_Busy = 0;
		CE=0;
		NRFWriteReg(W_REGISTER+STATUS,0xff);  // RX_DR,TX_DS,MAX_RT都置高为1，通过写1来清楚中断标
		
	}
	else if( MAX_RT == 0x01 )
	{
		CSN=0;
		NRFSPI(FLUSH_RX);//用于清空FIFO ！！关键！！不然会出现意想不到的后果！！！大家记住！！ 
		NRFSPI(FLUSH_TX);//用于清空FIFO ！！关键！！不然会出现意想不到的后果！！！大家记住！！ 
		CSN=1; 
		CE=0;
		NRFWriteReg(W_REGISTER+STATUS,0xff);  // RX_DR,TX_DS,MAX_RT都置高为1，通过写1来清楚中断标
	}  
	
	
	
}
