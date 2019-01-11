/// \file main.с  
/// ESTC 2-nd laboratory work.
#include "main.h"

/// \brief Entry point
int main(void)
{
	AllInit();	

/// \brief bit offset
	u16 offset = 0;
/// \brief blinking order
	u16 blink_type = 0;
/// \brief push checker
	u16 is_earlier_pushed = 0;
/// \brief blink switch
	u16 light_or_dark = 0;

	while(1)
	{			
		if (!(is_earlier_pushed || GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)))
		{
			blink_type = (blink_type + 1) % 2;
			is_earlier_pushed = 1;
		}
		
		if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)) is_earlier_pushed = 0;
	
		if (!TIM_GetCounter(TIM2))
		{			
			if (!(light_or_dark = (light_or_dark + 1) % 2))
			{ 
				GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
				offset = (!blink_type) ? ((offset + 1) % 3) : ((offset + 2) % 3);			
			}
			else GPIO_ResetBits(GPIOA, GPIO_Pin_8 << offset);	
		}
	}
}