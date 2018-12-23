#include "main.h"

#define PRESCALER 42000
#define PERIOD 1000

void AllInit(void);
void TIM2_IRQHandler(void);

int flag = 0;

int main(void)
{
	AllInit();
	while(1);
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		if (flag == 0)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 );
			flag = 1;
		}
		else
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 );
			flag = 0;
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
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

	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
	TIM_TimeBaseInit(TIM2, &Tim_InitStructure);
	TIM_Cmd(TIM2, ENABLE);
	NVIC_Init(&NVIC_InitStructure);	
}