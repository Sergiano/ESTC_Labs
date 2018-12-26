/// \file estc.c  
/// ESTC library.
#include "estc.h"

void ESTC_InitExBoardLeds(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void ESTC_InitExBoardLedsPWM(void)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
}

void ESTC_InitExBoardLedsTimer(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_Prescaler = 150;
	TIM_InitStructure.TIM_Period = 20000;
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_InitStructure);
}

void ESTC_PWMTimerStart(void)
{
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
}

void ESTC_InitExBoardAndRunPWM(void)
{
	ESTC_InitExBoardLedsTimer();    
	ESTC_InitExBoardLedsPWM();
	ESTC_InitExBoardLeds();
	ESTC_PWMTimerStart();
}

void ESTC_ExBoardLedsSetColorRGB(u8 red, u8 green, u8 blue)
{
    TIM_SetCompare1(TIM1, 65 * red );
    TIM_SetCompare2(TIM1, 65 * green );
    TIM_SetCompare3(TIM1, 65 * blue );
}

void ESTC_ExBoardLedsSetColorRed(u8 red)
{
    TIM_SetCompare1(TIM1, 65 * red );
}

void ESTC_ExBoardLedsSetColorGreen(u8 green)
{
    TIM_SetCompare2(TIM1, 65 * green );
}

void ESTC_ExBoardLedsSetColorBlue(u8 blue)
{
    TIM_SetCompare3(TIM1, 65 * blue );
}

void ESTC_ExBoardLedsSetColorHEX(uint32_t hexcolor)
{
	TIM_SetCompare1(TIM1, 65 * (u8)(hexcolor >> 16));
	TIM_SetCompare2(TIM1, 65 * (u8)(hexcolor >> 8));
	TIM_SetCompare3(TIM1, 65 * (u8)hexcolor);
}