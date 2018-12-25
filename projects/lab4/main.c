/// \file main.с  
/// ESTC 3-th laboratory work.
#include "main.h"

/// \brief pulse delta
const int delta = 5;
/// \brief pulse width
int PULSE;
/// \brief blink switch
int flag;

/// \brief Entry point
int main(void)
{
	PULSE = 5;
	flag = 1;	

	AllInit();	
	while(1);
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		

		if (PULSE >= PERIOD) flag = 0;
		if (PULSE <= 0) flag = 1;

		PULSE = flag ? PULSE + delta : PULSE - delta; 

		TIM_SetCompare1(TIM1, PULSE);
		TIM_SetCompare2(TIM1, PULSE);
		TIM_SetCompare3(TIM1, PULSE);
    }
}