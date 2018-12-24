#include "main.h"

#define SWITCH_DELAY 1000000

void AllInit(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin   = 0xF000; 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = 0x0001;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;

	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_SetBits(GPIOD, 0xF000);
	GPIO_ResetBits(GPIOD, 0xF000);
}

int main(void)
{
	AllInit();	

	u16 offset = 0, blink_type = 0, is_earlier_pushed = 0;

	while(1)
	{	
		if (!(is_earlier_pushed || GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)))
		{
			blink_type = (blink_type + 1) % 2;
			is_earlier_pushed = 1;
		}
		
		if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)) is_earlier_pushed = 0;
	
		GPIO_SetBits(GPIOD, 0x1000 << (offset = (!blink_type) ? (offset + 1) % 4 : (offset + 3) % 4));

		int dt;
		for (dt = 0; dt < SWITCH_DELAY; dt++);

		GPIO_ResetBits(GPIOD, 0x1000 << offset);
	}
}