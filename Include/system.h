#ifndef SYSTEM_H_
#define SYSTEM_H_










#define MCO2_Pin GPIO_PIN_9
#define MCO2_GPIO_Port GPIOC











//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------
void system_init(void);
void SystemClock_Config(void);
void assert_failed(uint8_t* file, uint32_t line);

#endif /* SYSTEM_H_ */
