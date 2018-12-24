#include "main.h"

#define SWITCH_DELAY 1000000
#define PRESCALER 42000
#define PERIOD 2000

void AllInit(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

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

	TIM_TimeBaseInitTypeDef Tim_InitStructure;

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		
	Tim_InitStructure.TIM_Period = PERIOD - 1;
	Tim_InitStructure.TIM_Prescaler = PRESCALER - 1;
	Tim_InitStructure.TIM_ClockDivision = 0;
	Tim_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &Tim_InitStructure);

	GPIO_SetBits(GPIOD, 0xF000);
	GPIO_ResetBits(GPIOD, 0xF000);

	TIM_Cmd(TIM2, ENABLE);
}

int main(void)
{
	AllInit();	

	u16 offset = 0, blink_type = 0, is_earlier_pushed = 0;

	int ticks;

	while(1)
	{			
		if (!(is_earlier_pushed || GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)))
		{
			blink_type = (blink_type + 1) % 2;
			is_earlier_pushed = 1;
		}
		
		if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)) is_earlier_pushed = 0;
	
		ticks = TIM_GetCounter(TIM2);

		if(ticks > PERIOD / 2 &&  ticks < PERIOD) GPIO_SetBits(GPIOD, 0x1000 << offset);
		if(ticks > 0 && ticks < PERIOD / 2) GPIO_ResetBits(GPIOD, 0x1000 << (offset = (!blink_type) ? (offset + 1) % 4 : (offset + 3) % 4));


	}
}