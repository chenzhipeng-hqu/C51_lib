
#include "InfraRed.h"

//static IR_TypeDef IR_Obj = {0};

const IR_BufTypeDef IR_NEC_head[] = {
	{9000, HIGH},
	{4500, LOW},
};

const IR_BufTypeDef IR_NEC_one[] = {
	{560,	 HIGH},
	{1685, LOW},
};

const IR_BufTypeDef IR_NEC_zero[] = {
	{560, HIGH},
	{560, LOW},
};

int InfraRed_RX_NEC_Init(void)
{
	
	return 0;
}

int InfraRed_RX_NEC_Calculate(IR_TypeDef *pIR_Obj)
{
	u8 idx = 0, byte = 0, _bit = 0x01;
	u16 min0, max0, min1, max1;
	u8 val[4] = {0};
	
	min0 = IR_NEC_zero[0].timer - IR_NEC_zero[0].timer/10;
	max0 = IR_NEC_zero[0].timer + IR_NEC_zero[0].timer/10;
	min1 = IR_NEC_one[0].timer - IR_NEC_one[0].timer/10;
	max1 = IR_NEC_one[0].timer + IR_NEC_one[0].timer/10;
	
	if(pIR_Obj->len != 0)
	{
		for(idx=sizeof(IR_NEC_head)/sizeof(IR_NEC_head[0]); idx<pIR_Obj->len; idx+=2)
		{
			if((pIR_Obj->rx_buf[idx].timer >= min0) && (pIR_Obj->rx_buf[idx].timer <= max0))
			{
				
			}
			else if((pIR_Obj->rx_buf[idx].timer >= min1) && (pIR_Obj->rx_buf[idx].timer <= max1))
			{
				val[byte] |= _bit; 
			}
			else
			{
				return ERROR;
			}
			
			_bit <<= 1;
			
			if(_bit == 0)
			{
				_bit = 0x01;
				byte++;
			}
		}
		
		if(idx >= pIR_Obj->len)
		{
			pIR_Obj->value.address = val[0]<<8 | val[1];
			pIR_Obj->value.command = val[2];
			pIR_Obj->value.command_check = val[3];
		}
		
		pIR_Obj->len = 0;
	}	
	
	return OK;
}

