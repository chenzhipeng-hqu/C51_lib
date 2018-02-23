#include "NRF24L01.h"

/*****************************************
ʱ�䣺2010.6.12
���ܣ�NRF24L01��Ƶģ��C�ļ�(�ڵ㷢�䲿��)
*****************************************/
u8 code TxAddr[TX_ADDR_WITDH]={0x34,0x43,0x10,0x10,0x01};//���͵�ַ
u8 g_ucNRF_Send_Busy = 0;
extern u8 g_ucRevFlag;
/*****************״̬��־*****************************************/
u8 bdata sta;   //״̬��־ 
sbit RX_DR=sta^6;
sbit TX_DS=sta^5;	//���ݷ�������ж�
sbit MAX_RT=sta^4;  //�ط���������ж�
//

void Delay(s16 nus)
{
	int i,j;
        for(i=0;i<nus;i++);
}

/*****************SPIʱ����******************************************/
u8 NRFSPI(u8 date)
{
    u8 i;
   	for(i=0;i<8;i++)          // ѭ��8��
   	{
			if(date&0x80)
				MOSI=1;
			else
				MOSI=0;   // byte���λ�����MOSI
			date<<=1;             // ��һλ��λ�����λ
			SCLK=1; 
			if(MISO)               // ����SCK��nRF24L01��MOSI����1λ���ݣ�ͬʱ��MISO���1λ����
					date|=0x01;       	// ��MISO��byte���λ
			SCLK=0;            	// SCK�õ�
   	}
    return(date);           	// ���ض�����һ�ֽ�
}
/**********************NRF24L01��ʼ������*******************************/
void NRF24L01Int()
{
	Delay(2);//��ϵͳʲô������
	CE=0; //����ģʽ1   
	CSN=1;  
	SCLK=0;
	IRQ=1;	 
}
/*****************SPI���Ĵ���һ�ֽں���*********************************/
u8 NRFReadReg(u8 RegAddr)
{
   u8 BackDate;
   CSN=0;//����ʱ��
   NRFSPI(RegAddr);//д�Ĵ�����ַ
   BackDate=NRFSPI(0x00);//д����Ĵ���ָ��  
   CSN=1;
   return(BackDate); //����״̬
}
/*****************SPIд�Ĵ���һ�ֽں���*********************************/
u8 NRFWriteReg(u8 RegAddr,u8 date)
{
   u8 BackDate;
   CSN=0;//����ʱ��
   BackDate=NRFSPI(RegAddr);//д���ַ
   NRFSPI(date);//д��ֵ
   CSN=1;
   return(BackDate);
}
/*****************SPI��ȡRXFIFO�Ĵ�����ֵ********************************/
u8 NRFReadRxDate(u8 RegAddr,u8 *RxDate,u8 DateLen)
{  //�Ĵ�����ַ//��ȡ���ݴ�ű���//��ȡ���ݳ���//���ڽ���
    u8 BackDate,i;
	CSN=0;//����ʱ��
	BackDate=NRFSPI(RegAddr);//д��Ҫ��ȡ�ļĴ�����ַ
	for(i=0;i<DateLen;i++) //��ȡ����
	  {
	     RxDate[i]=NRFSPI(0);
	  } 
    CSN=1;
   return(BackDate); 
}
/*****************SPIд��TXFIFO�Ĵ�����ֵ**********************************/
u8 NRFWriteTxDate(u8 RegAddr,u8 *TxDate,u8 DateLen)
{ //�Ĵ�����ַ//д�����ݴ�ű���//��ȡ���ݳ���//���ڷ���
   u8 BackDate,i;
   CSN=0;
   BackDate=NRFSPI(RegAddr);//д��Ҫд��Ĵ����ĵ�ַ
   for(i=0;i<DateLen;i++)//д������
     {
	    NRFSPI(TxDate[i]);
	 }   
   CSN=1;
   return(BackDate);
}
/*****************NRF����Ϊ����ģʽ����������******************************/
void NRFSetTxMode(u8 *TxDate)
{//����ģʽ
	clear_fifo();
    CE=0; 
   	NRFWriteTxDate(W_REGISTER+TX_ADDR,TxAddr,TX_ADDR_WITDH);//д�Ĵ���ָ��+���յ�ַʹ��ָ��+���յ�ַ+��ַ���
	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);//Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ
	NRFWriteTxDate(W_TX_PAYLOAD,TxDate,TX_DATA_WITDH);//д������ 
	/******�����йؼĴ�������**************/
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);       // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);   // ʹ�ܽ���ͨ��0
  	NRFWriteReg(W_REGISTER+SETUP_RETR,0x03);  // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);         // ѡ����Ƶͨ��0x40
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);    // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
	NRFWriteReg(W_REGISTER+CONFIG,0x0e);      // CRCʹ�ܣ�16λCRCУ�飬�ϵ�  
	CE=1;
	Delay(5);//����10us������
}
/*****************NRF����Ϊ����ģʽ����������******************************/
//��Ҫ����ģʽ
void NRFSetRXMode()
{
	clear_fifo();
	CE=0;  
  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);  // �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
//  	NRFWriteTxDate(W_REGISTER+TX_ADDR,TxAddr,TX_ADDR_WITDH); 		//дTX�ڵ��ַ  
	NRFWriteReg(W_REGISTER+EN_AA,0x01);               // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);           // ʹ�ܽ���ͨ��0
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);                 // ѡ����Ƶͨ��0x40
  	NRFWriteReg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);  // ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);            // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������*/
  	NRFWriteReg(W_REGISTER+CONFIG,0x0f);              // CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ
  	CE = 1;
	Delay(5);//����10us������     
}
/****************************���Ӧ���ź�******************************/
u8 CheckACK()
{  //���ڷ���
	sta=NRFReadReg(R_REGISTER+STATUS);                    // ����״̬�Ĵ���
	if(TX_DS||MAX_RT) //��������ж�
	{
	   NRFWriteReg(W_REGISTER+STATUS,sta);  // ���TX_DS��MAX_RT�жϱ�־
	   CSN=0;
	   NRFSPI(FLUSH_TX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס����  
       CSN=1; 
	   return(0);
	}
	else
	   return(1);
}
/******************�ж��Ƿ�����յ����ݣ��ӵ��ʹ�RXȡ��*********************/
//���ڽ���ģʽ
u8 NRFRevDate(u8 *RevDate)
{
	u8 RevFlags=0;
	sta=NRFReadReg(R_REGISTER+STATUS);//�������ݺ��ȡ״̬�Ĵ���
	if(RX_DR)				// �ж��Ƿ���յ�����
	{
		CE=0; 			//SPIʹ��
		NRFReadRxDate(R_RX_PAYLOAD,RevDate,RX_DATA_WITDH);// ��RXFIFO��ȡ����
		NRFWriteReg(W_REGISTER+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�	   
			CSN=0;
	   NRFSPI(FLUSH_RX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס���� 
	   CSN=1;		 
		RevFlags=1;	   //��ȡ������ɱ�־
	}
	return(RevFlags);
}

void clear_fifo(void){
	CE=0; 			//SPIʹ��
	NRFWriteReg(W_REGISTER+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�	   
	CSN=0;
	NRFSPI(FLUSH_RX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס���� 
	NRFSPI(FLUSH_TX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס���� 
	CSN=1;		 
}

u8 Nrf24l01_Check(void)
{ 
	u8 buf1[5]; 
	u8 i; 
	/*д��5���ֽڵĵ�ַ. */ 
//	NRF_Write_Buf(NRF_WRITE_REG+TX_ADDR,TX_ADDRESS,5); 
	NRFWriteTxDate(W_REGISTER+TX_ADDR,TxAddr, 5);
	/*����д��ĵ�ַ */ 
//	NRF_Read_Buf(TX_ADDR,buf1,5); 
	NRFReadRxDate(TX_ADDR,buf1,5);
	/*�Ƚ�*/ 
	for(i=0;i<5;i++) 
	{ 
		if(buf1[i]!=TxAddr[i]) 
			break; 
	} 
	if(i==5)
		return SUCCESS ; //MCU��NRF�ɹ����� 
	else
		return ERROR ; //MCU��NRF���������� 
}

u8 NRF_ISR_Callback(void)
{
	sta=NRFReadReg(R_REGISTER+STATUS);                    // ����״̬�Ĵ���
	if( RX_DR == 0x01 )
	{
//		P34 = ~P34;	
//		CE=0; 			//SPIʹ��
//		NRFReadRxDate(R_RX_PAYLOAD,RevDate,RX_DATA_WITDH);// ��RXFIFO��ȡ����		 
		g_ucRevFlag = SUCCESS;	   //��ȡ������ɱ�־
		CE=0;
		NRFWriteReg(W_REGISTER+STATUS,0xff);  // RX_DR,TX_DS,MAX_RT���ø�Ϊ1��ͨ��д1������жϱ�
		P34 = !P34;	
	}
	else if( TX_DS == 0x01 ) //��������ж�
	{		
		g_ucNRF_Send_Busy = 0;
		CE=0;
		NRFWriteReg(W_REGISTER+STATUS,0xff);  // RX_DR,TX_DS,MAX_RT���ø�Ϊ1��ͨ��д1������жϱ�
		
	}
	else if( MAX_RT == 0x01 )
	{
		CSN=0;
		NRFSPI(FLUSH_RX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס���� 
		NRFSPI(FLUSH_TX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס���� 
		CSN=1; 
		CE=0;
		NRFWriteReg(W_REGISTER+STATUS,0xff);  // RX_DR,TX_DS,MAX_RT���ø�Ϊ1��ͨ��д1������жϱ�
	}  
	
	
	
}
