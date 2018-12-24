#include "main.h"

u16 offset = 0, blink_type = 0, light_or_dark = 0;

int main(void)
{
	AllInit();
	while(1);
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{	
		!(++light_or_dark%2) ? 	GPIO_ResetBits(GPIOD, 0x1000 << offset) : 
		GPIO_SetBits(GPIOD, 0x1000 << (offset = (!blink_type) ? (offset + 1) % 4 : (offset + 3) % 4));

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void EXTI0_IRQHandler(void)
{
   if (EXTI_GetITStatus(EXTI_Line0) != RESET)
   {
      EXTI_ClearITPendingBit(EXTI_Line0);

      blink_type = (blink_type + 1) % 2;
   }
}
