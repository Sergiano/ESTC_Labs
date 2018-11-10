#include "main.h"

#define SWITCH_DELAY 250000

int main(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable peripheral clock for LEDs port */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /* Init LEDs */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10; 
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);

  while (1)
  {
    int i;

    GPIO_ResetBits(GPIOA, GPIO_Pin_8);
    for (i = 0; i < SWITCH_DELAY; i++);

    GPIO_SetBits(GPIOA, GPIO_Pin_8);
    for (i = 0; i < SWITCH_DELAY; i++);

    GPIO_ResetBits(GPIOA, GPIO_Pin_9);
    for (i = 0; i < SWITCH_DELAY; i++);

    GPIO_SetBits(GPIOA, GPIO_Pin_9);
    for (i = 0; i < SWITCH_DELAY; i++);

    GPIO_ResetBits(GPIOA, GPIO_Pin_10);
    for (i = 0; i < SWITCH_DELAY; i++);

    GPIO_SetBits(GPIOA, GPIO_Pin_10);
    for (i = 0; i < SWITCH_DELAY; i++);
  }
}
