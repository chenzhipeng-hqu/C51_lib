
#include "NixieTube.h"
						//   0    1    2    3    4	  5	   6	 7	  8    9   A   b   C   d   E   F   L   H   18
u8 code NixieTubeTable[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xC7,0x89,0xff};//共阳数码管段码表

void NixieTube_Init(void)
{
	
//	Nixie_Tube_0 = 0;
//	Nixie_Tube_1 = 0;
	NIXIE_TUBE_PORT = NixieTubeTable[0];
	
}

/**
  * @brief  NixieTube_Disp
  * @param  
  * @retval 
  */
void NixieTube_Disp(u8 ucNixie_Val_0, u8 ucNixie_Val_1){
	static u8 ucNixieTube_Num = 0;
			
	switch(ucNixieTube_Num){
		case 0:		
//			Nixie_Tube_0 = 0;
//			Nixie_Tube_1 = 0;
//			NIXIE_TUBE_PORT = NixieTubeTable[18];
//			Nixie_Tube_0 = 0;
//			Nixie_Tube_1 = 1;	
			NIXIE_TUBE_PORT = 	NixieTubeTable[ucNixie_Val_0];
				
			break;			
		case 1:
				
			break;					
		default:
			
			break;
	}
	
	ucNixieTube_Num = (ucNixieTube_Num+1)%NIXIE_NUM_MAX;
	
}