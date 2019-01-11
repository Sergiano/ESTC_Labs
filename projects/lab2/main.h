/// \file main.h  
/// ESTC 2-nd laboratory work.
#ifndef LEDS_AND_BUTTON_H
#define LEDS_AND_BUTTON_H

#include <stm32f4xx.h>
#include <math.h>

/// \brief
/// Timer prescaler (configured by 1 sec blink period).
#define PRESCALER 42000
/// \brief
/// Timer period (configured by 1 sec blink period).
#define PERIOD 1000

/// \brief STM32F4XX configure.
/// Initialization buttons, LEDs and timer
void AllInit(void);

#endif