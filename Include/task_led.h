#ifndef task_led_h
#define task_led_h
#include "stm32f4xx_hal.h"

#define LED_PERIOD             250  // ms (4 Hz)

// From Cube
#define D13_LD2_Pin GPIO_PIN_5
#define D13_LD2_GPIO_Port GPIOA

// LEDs Macros
#define D13_LD2 D13_LD2_GPIO_Port,D13_LD2_Pin



#define LED_ALL_Pin            D13_LD2_Pin
#define LED_ALL_Port           D13_LD2_GPIO_Port
#define LED_ALL                LED_ALL_Port,LED_ALL_Pin


//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------
void task_led(void const * argument);




#endif // task_led_h


