#include "main.h"

void AllInit(void);
void LightSwitch(void);

int ledstatus = 0;

int main(void)
{
	AllInit();

	int btnstatus, previous = 1, counter = 0;

	while (1)
	{
		for(;;)
		{
			btnstatus = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0);
			if (btnstatus != previous)
			{
				counter++;
				previous = btnstatus;
			}
			if (counter == 2) 
			{
				counter = 0;
				break;
			}
		}
		LightSwitch();
	}
}

void LightSwitch(void)
{
	if (ledstatus == 1)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
		ledstatus = 0;
	}
	else
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
		ledstatus = 1;
	}
}

void AllInit(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef LED;
	LED.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10; 
	LED.GPIO_Mode  = GPIO_Mode_OUT;
	LED.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_Speed = GPIO_Speed_100MHz;
	LED.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &LED);

	GPIO_InitTypeDef BTN;
	BTN.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	BTN.GPIO_Mode  = GPIO_Mode_IN;
	BTN.GPIO_OType = GPIO_OType_PP;
	BTN.GPIO_Speed = GPIO_Speed_2MHz;
	BTN.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &BTN);

	GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
}