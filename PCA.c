
#include "PCA.h"


u16		CCAP1_tmp;
bit		B_Capture1;
sbit LED7 = P1^7;

extern void CaptureCallback(void);

void PCA_Init(void)
{
	CCON = 0;                       //Initial PCA control register
                                    //PCA timer stop running
                                    //Clear CF flag
                                    //Clear all module interrupt flag
    CL = 0;                         //Reset PCA base timer
    CH = 0;
    CMOD |= 0x00;                    //Set PCA timer clock source as Fosc/12
                                    //Disable PCA timer overflow interrupt
//    CCAPM1 = 0x11;                  //PCA module-0 capture by a negative tigger on CEX0(P1.3) and enable PCA interrupt
//  CCAPM1 = 0x21;                  //PCA module-0 capture by a rising edge on CEX0(P1.3) and enable PCA interrupt
	CCAPM1 = 0x31;                  //PCA module-0 capture by a transition (falling/rising edge) on CEX0(P1.3) and enable PCA interrupt

    CR = 1;                         //PCA timer start run
}

void PCA1_ISR() interrupt 7 using 1
{
	if(0x01 == CCF1)
	{
    CCF1 = 0;                       //Clear interrupt flag
		//CCAP1_tmp = CCAP1H;	//读CCAP1H
		//CCAP1_tmp = (CCAP1H << 8) | CCAP1L;
		//B_Capture1 = 1;
		//CCAP1H = CCAP1L = 0;
		CaptureCallback();
	}
	
	if(0x01 == CF)	//PCA溢出中断
	{
		CF = 0;			//清PCA溢出中断标志
	}
}
