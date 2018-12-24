#include "main.h"

int main(void)
{
	AllInit();	

	u16 offset = 0, blink_type = 0, is_earlier_pushed = 0, light_or_dark = 0;

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
			!(++light_or_dark%2) ? GPIO_ResetBits(GPIOD, 0x1000 << offset) : 
			GPIO_SetBits(GPIOD, 0x1000 << (offset = (!blink_type) ? (offset + 1) % 4 : (offset + 3) % 4));
		}
	}
}