//------------------------------------------------------------------------------
// Program Name:    Circular Robotics
// Program Number:
// Program Date:    5/19/19
// Project:
// Board:           Nucleo-STM32F446RE
// Author:          Greg Hughes
// IDE:             TrueStudio v9.3
// Microcontroller: STMicroelectronics
//                  STM32F446RE
//
// Description:     Sparkfun Circular Robot
//
//
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
//  Include Files
//------------------------------------------------------------------------------
#include "stm32f4xx.h"
#include "system.h"
#include "rtos.h"



int main(void)
{
	system_init();
	rtos_start();

  while(1)
  {}
}


