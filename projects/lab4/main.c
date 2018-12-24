#include "main.h"

int PULSE = 5;
int flag = 1;
const int delta = 5;

void AllInit(void);
void TIM2_IRQHandler(void);

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
		if (PULSE >= PERIOD) flag = 0;
		if (PULSE <= 0) flag = 1;

		PULSE = flag ? PULSE + delta : PULSE - delta; 

		TIM_SetCompare1(TIM1, PULSE);
		TIM_SetCompare2(TIM1, PULSE);
		TIM_SetCompare3(TIM1, PULSE);

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

int main(void)
{
	AllInit();	
	while(1);
}