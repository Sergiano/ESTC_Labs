/// \file main.h  
/// ESTC 5-th laboratory work (example).
#ifndef LEDS_AND_BUTTON_H
#define LEDS_AND_BUTTON_H

#include <stm32f4xx.h>
#include <math.h>
#include <estc.h>

/// \brief STM32F4XX configure.
/// Initialization another LEDs, timer, buttons and interrupts
void AllInit(void);
/// \brief button0 interrupts handler.
/// Сolor changing options
void EXTI0_IRQHandler(void);
/// \brief button1 interrupts handler.
/// Сolor brightnes options
void EXTI1_IRQHandler(void);
/// \brief Debounce initialization.
/// (using RCC_Clocks)
void DebounceLaunch(void);
/// \brief clocks interrupts handler.
/// Debounce options
void SysTick_Handler(void);

#endif