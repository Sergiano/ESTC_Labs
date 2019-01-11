/// \file main.h  
/// ESTC 3-th laboratory work.
#ifndef LEDS_AND_BUTTON_H
#define LEDS_AND_BUTTON_H

#include <stm32f4xx.h>
#include <math.h>

/// \brief
/// Timer prescaler (configured by 1 sec blink period).
#define PRESCALER 42001
/// \brief
/// Timer period (configured by 1 sec blink period).
#define PERIOD 1001

/// \brief STM32F4XX configure.
/// Initialization buttons, LEDs, timer and interrupts
void AllInit(void);
/// \brief Timer interrupts handler.
/// Switching the LED to the next one after the time expires
void TIM2_IRQHandler(void);
/// \brief Button interrupts handler.
/// LED flashing order switching
void EXTI0_IRQHandler(void);
/// \brief Button debounce.
/// Debounce handler
void DebounceLaunch(void);
/// \brief Systick handler.
/// for debounce
void SysTick_Handler(void);

#endif