#include "main.h"

#define PRESCALER 168 //65356
#define PERIOD 1000

int PULSE = 10;
int flag = 1;
const int delta = 5;

void AllInit(void);
void TIM2_IRQHandler(void);

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		if (PULSE >= PERIOD)
			flag = -1;
		if (PULSE <= 0)
			flag = 1;

		if (flag == 1)
			PULSE += delta;
		if (flag == -1)
			PULSE -= delta;

		TIM_SetCompare1(TIM1, PULSE);
		TIM_SetCompare2(TIM1, PULSE);
		TIM_SetCompare3(TIM1, PULSE);
    }
}

int main(void)
{
	AllInit();	
	while(1);
}

void AllInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	

	TIM_TimeBaseInitTypeDef tim_init;
	tim_init.TIM_Period = PERIOD - 1;
	tim_init.TIM_Prescaler = PRESCALER - 1;
	tim_init.TIM_ClockDivision = 0;
	tim_init.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM1, &tim_init);

    tim_init.TIM_Prescaler = 84;
    tim_init.TIM_Period = 999;
    tim_init.TIM_ClockDivision = TIM_CKD_DIV1;
    tim_init.TIM_RepetitionCounter = 0;
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    TIM_TimeBaseInit(TIM2, &tim_init);

    NVIC_InitTypeDef timer_nvic_init_structure;

    timer_nvic_init_structure.NVIC_IRQChannel = TIM2_IRQn;
    timer_nvic_init_structure.NVIC_IRQChannelPreemptionPriority = 0;
    timer_nvic_init_structure.NVIC_IRQChannelSubPriority = 1;
    timer_nvic_init_structure.NVIC_IRQChannelCmd = ENABLE;
    
	NVIC_Init(&timer_nvic_init_structure);

    TIM_OCInitTypeDef tim_oc_init;

    TIM_OCStructInit(&tim_oc_init);

    tim_oc_init.TIM_OCMode = TIM_OCMode_PWM1;
    tim_oc_init.TIM_Pulse = PULSE;
    tim_oc_init.TIM_OutputState = TIM_OutputState_Enable;
    tim_oc_init.TIM_OCPolarity = TIM_OCPolarity_Low;

    TIM_OC1Init(TIM1, &tim_oc_init);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC2Init(TIM1, &tim_oc_init);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC3Init(TIM1, &tim_oc_init);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    GPIO_InitTypeDef gpio_init;
    GPIO_StructInit(&gpio_init);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);

    gpio_init.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &gpio_init);

    TIM_Cmd(TIM1, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}
