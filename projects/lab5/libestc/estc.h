/// \file estc.h  
/// ESTC library.
#ifndef ESTC_H_
#define ESTC_H

#include <stdint.h>
#include <stm32f4xx.h>
#include <math.h>

/// \brief Extention board LED configure.
/// Initialization of PWM LEDs
void ESTC_InitExBoardLeds(void);
/// \brief PWM Timer configure.
/// Initialization of PWM Timer
void ESTC_InitExBoardLedsTimer(void);
/// \brief PWM configure.
/// Initialization of PWM
void ESTC_InitExBoardLedsPWM(void);
/// \brief PWM configuration aggregator.
/// Aggregator of initializations functions
void ESTC_InitExBoardAndRunPWM(void);
/// \brief PWM timer launch.
/// Finally Initialization and launch
void ESTC_PWMTimerStart(void);
/// \brief LEDs color configuration (RGB).
/// Color management RGB
/// \param red brightness of red: 0..255
/// \param green brightness of green: 0..255
/// \param blue brightness of blue: 0..255
void ESTC_ExBoardLedsSetColorRGB(u8 red, u8 green, u8 blue);
/// \brief LEDs color configuration (RGB).
/// Color management RGB
/// \param red brightness of red: 0..255
void ESTC_ExBoardLedsSetColorRed(u8 red);
/// \brief LEDs color configuration (RGB).
/// Color management RGB
/// \param red brightness of green: 0..255
void ESTC_ExBoardLedsSetColorGreen(u8 green);
/// \brief LEDs color configuration (RGB).
/// Color management RGB
/// \param red brightness of blue: 0..255
void ESTC_ExBoardLedsSetColorBlue(u8 blue);
/// \brief LEDs color configuration (HEX).
/// Color management HEX
/// \param hexcolor HEX color format as uint32
void ESTC_ExBoardLedsSetColorHEX(uint32_t hexcolor);

#endif