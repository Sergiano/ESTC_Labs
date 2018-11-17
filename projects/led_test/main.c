#include "main.h"

#define SWITCH_DELAY 250000

void AllInit(void);

int main(void)
{
	AllInit();	

	while (1)
	{
		int i;

		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		for (i = 0; i < SWITCH_DELAY; i++);
		GPIO_SetBits(GPIOD, GPIO_Pin_12);

		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		for (i = 0; i < SWITCH_DELAY; i++);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);

		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		for (i = 0; i < SWITCH_DELAY; i++);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);

		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		for (i = 0; i < SWITCH_DELAY; i++);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
	}
}

void AllInit(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}
