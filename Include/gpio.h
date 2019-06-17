#ifndef __gpio_H
#define __gpio_H

#include "stm32f4xx.h"



#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA




#define LD2  LD2_GPIO_Port,LD2_Pin
#define B1   B1_GPIO_Port,B1_Pin





//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------
void gpio_init(void);


#endif /*__ pinoutConfig_H */


