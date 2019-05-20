//------------------------------------------------------------------------------
// Description:
//   
//   LEDs Control
//  
//
//   Subroutines: 
//     task_led
//     init_LED_Peripherals
//
//   Functions:
//     None
//
//   Interrupts:
//     None
//     
//
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
//  Includes Files
//------------------------------------------------------------------------------
#include "stm32f4xx.h"
#include "cmsis_os.h"
#include "task_led.h"



//------------------------------------------------------------------------------
//  Private
//------------------------------------------------------------------------------
static void init_task_peripherals(void);


//------------------------------------------------------------------------------
// Task Name      : task_led
// Description    : LED Controller
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void task_led(void const * argument)
{
	TickType_t xLastWakeTime;

	init_task_peripherals();


	xLastWakeTime = osKernelSysTick();
	while(1)
	{

		HAL_GPIO_TogglePin(D13_LD2);

		osDelayUntil(&xLastWakeTime, LED_PERIOD);
	}
}


//------------------------------------------------------------------------------
// Task Name      : init_Peripherals
// Description    : Initialize task peripherals
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void init_task_peripherals(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	uint8_t i;

	// Clocks
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO
	GPIO_InitStruct.Pin = D13_LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(D13_LD2_GPIO_Port, &GPIO_InitStruct);

	// Flash all LEDs on startup
	for(i = 0; i < 16; i++)
	{
		HAL_GPIO_TogglePin(LED_ALL);
		HAL_Delay(30);
	}
	HAL_GPIO_WritePin(LED_ALL, GPIO_PIN_RESET);

}

