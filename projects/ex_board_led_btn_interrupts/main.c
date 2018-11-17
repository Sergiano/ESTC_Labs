#include "main.h"

void AllInit(void);
void EXTI0_IRQHandler(void);

int flag = 0;

int main(void)
{
	AllInit();
	while(1);
}

void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0)!= RESET)
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
		EXTI_ClearITPendingBit(EXTI_Line0);
	}	
}

void AllInit(void)
{	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);

	GPIO_InitTypeDef LED;

	LED.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10; 
	LED.GPIO_Mode  = GPIO_Mode_OUT;
	LED.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_Speed = GPIO_Speed_100MHz;
	LED.GPIO_PuPd  = GPIO_PuPd_NOPULL;

	GPIO_InitTypeDef BTN;

	BTN.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	BTN.GPIO_Mode  = GPIO_Mode_IN;
	BTN.GPIO_OType = GPIO_OType_PP;
	BTN.GPIO_Speed = GPIO_Speed_2MHz;
	BTN.GPIO_PuPd  = GPIO_PuPd_UP;

	EXTI_InitTypeDef EXTI_InitStruct;

	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;

	NVIC_InitTypeDef NVIC_InitStruct;

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

	GPIO_Init(GPIOA, &LED);
	GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
	GPIO_Init(GPIOE, &BTN);
	EXTI_Init(&EXTI_InitStruct);	
	NVIC_Init(&NVIC_InitStruct);
}