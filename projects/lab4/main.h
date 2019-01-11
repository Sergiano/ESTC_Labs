/// \file main.h  
/// ESTC 4-th laboratory work.
#ifndef LEDS_AND_BUTTON_H
#define LEDS_AND_BUTTON_H

#include <stm32f4xx.h>
#include <math.h>

/// \brief
/// Timer prescaler
#define PRESCALER 500
/// \brief
/// Timer period
#define PERIOD 1024

/// \brief STM32F4XX configure.
/// Initialization LEDs, timer and interrupts
void AllInit(void);
/// \brief Timer interrupts handler.
/// Switching pulse length of PWM
void TIM2_IRQHandler(void);

#endif