#ifndef LEDS_AND_BUTTON_H
#define LEDS_AND_BUTTON_H

#include <stm32f4xx.h>
#include <math.h>

#define PRESCALER 42000
#define PERIOD 1000

void AllInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef Tim_InitStructure;	

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = 0xF000; 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD, 0xF000);
	GPIO_ResetBits(GPIOD, 0xF000);

	GPIO_InitStructure.GPIO_Pin = 0x0001;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		
	Tim_InitStructure.TIM_Period = PERIOD - 1;
	Tim_InitStructure.TIM_Prescaler = PRESCALER - 1;
	Tim_InitStructure.TIM_ClockDivision = 0;
	Tim_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &Tim_InitStructure);
	TIM_Cmd(TIM2, ENABLE);
}

#endif
