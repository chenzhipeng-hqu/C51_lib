
#include "PWM.h"

#define		PWM_MAX		0xfe
#define		PWM_MIN		0x01

void PWM_Init(void)
{
	CCON = 0;                       //Initial PCA control register
									//PCA timer stop running
									//Clear CF flag
									//Clear all module interrupt flag
	CL = 0;                         //Reset PCA base timer
	CH = 0;
	CMOD = 0x02;                    //Set PCA timer clock source as Fosc/2
																	//Disable PCA timer overflow interrupt
	CCAP0H = CCAP0L = 0x02;         //PWM0 port output 50% duty cycle square wave
	CCAPM0 = 0x42;                  //PCA module-0 work in 8-bit PWM mode and no PCA interrupt

	CCAP1H = CCAP1L = 0x02;         //PWM1 port output 0% duty cycle square wave
	CCAPM1 = 0x42;                  //PCA module-1 work in 8-bit PWM mode and no PCA interrupt

	CR = 1;                         //PCA timer start run
}

void PWM_Set(u8 lhs,u8 rhs)
{		
	lhs = Limit(lhs,PWM_MIN,PWM_MAX);
	rhs = Limit(rhs,PWM_MIN,PWM_MAX);
	
	CCAP0H = CCAP0L = lhs;
	CCAP1H = CCAP1L = rhs;
}


void PWM_Cal(s16 pwm_val)
{
	s16 lhs,rhs;
	
	lhs = 0x80 - pwm_val;
	rhs = 0x80 + pwm_val;
	
	lhs = Limit(lhs,PWM_MIN,PWM_MAX);
	rhs = Limit(rhs,PWM_MIN,PWM_MAX);
	
	PWM_Set(lhs,rhs);
}

