/// \file main.с  
/// ESTC 3-th laboratory work.
#include "main.h"

/// \brief bit offset
	u16 offset;
/// \brief blinking order
	u16 blink_type;
/// \brief blink switch
	u16 light_or_dark;
/// \brief debounce params
u32 systime, timeout;

/// \brief Entry point
int main(void)
{
	offset = blink_type = light_or_dark = 0;
	
	AllInit();

	DebounceLaunch();

	while(1);
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{	
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		

		!(light_or_dark = (light_or_dark + 1) % 2) ? 
		GPIO_ResetBits(GPIOA, GPIO_Pin_8 << (offset = (!blink_type) ? ((offset + 1) % 3) : ((offset + 2) % 3))) : 
		GPIO_SetBits(GPIOA, GPIO_Pin_8 << offset);		
	}
}

void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line0);

		if (timeout) return;

		blink_type = (blink_type + 1) % 2;

		timeout = systime;
	}
}

void DebounceLaunch(void)
{
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);

    systime = 0;
    timeout = 0;

    (void)SysTick_Config(RCC_Clocks.HCLK_Frequency / 10000);
}

void SysTick_Handler(void)
{
    systime++;

    if (timeout && systime - timeout > 100) timeout = 0;
}