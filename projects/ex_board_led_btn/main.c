#include "main.h"

#define SWITCH_DELAY 250000

void IOInit(GPIO_InitTypeDef *LED, GPIO_InitTypeDef *BTN);

int main(void)
{
  GPIO_InitTypeDef GPIO_ISLed;
  GPIO_InitTypeDef GPIO_ISBtn;

	IOInit(&GPIO_ISLed, &GPIO_ISBtn);
  
  GPIO_Init(GPIOA, &GPIO_ISLed);
  GPIO_Init(GPIOE, &GPIO_ISBtn);

  GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
  
  int btnstatus, ledstatus = 0, prev = 1, counter = 0;

  while (1)
  {
		while(1)
		{
			btnstatus = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0);
			if (btnstatus != prev)
			{
				counter++;
				prev = btnstatus;
			}
			if (counter == 2) 
			{
				counter = 0;
				break;
			}
		}
		if (ledstatus == 1)
    {
	    GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
  	  ledstatus = 0;
    }
    else
    {
    	GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
    	ledstatus = 1;
    }
  }
}

void IOInit(GPIO_InitTypeDef *LED, GPIO_InitTypeDef *BTN)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	//LEDs structure init
  LED->GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10; 
  LED->GPIO_Mode  = GPIO_Mode_OUT;
  LED->GPIO_OType = GPIO_OType_PP;
  LED->GPIO_Speed = GPIO_Speed_100MHz;
  LED->GPIO_PuPd  = GPIO_PuPd_NOPULL;

	//Buttons structure init
  BTN->GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  BTN->GPIO_Mode  = GPIO_Mode_IN;
  BTN->GPIO_OType = GPIO_OType_PP;
  BTN->GPIO_Speed = GPIO_Speed_2MHz;
  BTN->GPIO_PuPd  = GPIO_PuPd_UP;
}
