/// \file main.h  
/// ESTC 5-th laboratory work (example).
#include "main.h"

/// \brief onboard help LEDs
u16 onboard_leds[3];
/// \brief current color
u8 color;
/// \brief colors
u8 red, green, blue;
/// \brief debounce params
u32 systime, timeout_color, timeout_brightness;

/// \brief Entry point
int main(void)
{
    AllInit();

	color = 0;
	red = 0;
	green = 0;
	blue = 0;

	onboard_leds[0] = 0x1000;
	onboard_leds[1] = 0x4000;
	onboard_leds[2] = 0x8000;

	DebounceLaunch();

	ESTC_InitExBoardAndRunPWM();

    GPIO_SetBits(GPIOD, onboard_leds[color]);
	ESTC_ExBoardLedsSetColorHEX(0x4B0082);

    while (1);
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line0);		
        
		if (timeout_brightness) return;

		GPIO_ResetBits(GPIOD, onboard_leds[color]);
		color = (color + 1) % 3;
		GPIO_SetBits(GPIOD, onboard_leds[color]);

 		timeout_brightness = systime;
	}
}

void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line1);

        if (timeout_color) return;
	
		if (color == 0) red = (red + 16) % 256;
		else if (color == 1) green = (green + 16) % 256;
		else if (color == 2) blue = (blue + 16) % 256;

		ESTC_ExBoardLedsSetColorRGB(red,green,blue);

 		timeout_color = systime;
	}
}

void DebounceLaunch(void)
{
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);

	systime = 0;
	timeout_color = 0;
	timeout_brightness = 0;

	(void)SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
}

void SysTick_Handler(void)
{
	systime++;

	if (timeout_color && systime - timeout_color > 100) timeout_color = 0;
	if (timeout_brightness && systime - timeout_brightness > 100) timeout_brightness = 0;
}
