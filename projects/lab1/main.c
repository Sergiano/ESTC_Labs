#include "main.h"

int main(void)
{
	AllInit();	

	u16 offset = 0, blink_type = 0, is_earlier_pushed = 0;

	while(1)
	{	
		if (!(is_earlier_pushed || GPIO_ReadInputDataBit(GPIOE, 0x0001)))
		{
			blink_type = (blink_type + 1) % 2;
			is_earlier_pushed = 1;
		}
		
		if (GPIO_ReadInputDataBit(GPIOE, 0x0001)) is_earlier_pushed = 0;
	
		GPIO_SetBits(GPIOD, 0x1000 << (offset = (!blink_type) ? (offset + 1) % 4 : (offset + 3) % 4));

		int dt;
		for (dt = 0; dt < SWITCH_DELAY; dt++);

		GPIO_ResetBits(GPIOD, 0x1000 << offset);
	}
}