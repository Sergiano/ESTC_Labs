#include "main.h"

#define PRESCALER 65356
#define PERIOD 50

int flag = 0;

void AllInit(void);

int main(void)
{
	AllInit();

	while (1)
	{
		TIM_GetCounter(TIM2) == 0 ? 
			GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 ) : 
			GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 );
	}
}

void AllInit(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;

	TIM_TimeBaseInitTypeDef Tim_InitStructure;

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		
	Tim_InitStructure.TIM_Period = PERIOD - 1;
	Tim_InitStructure.TIM_Prescaler = PRESCALER - 1;
	Tim_InitStructure.TIM_ClockDivision = 0;
	Tim_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
	TIM_TimeBaseInit(TIM2, &Tim_InitStructure);
	TIM_Cmd(TIM2, ENABLE);
}