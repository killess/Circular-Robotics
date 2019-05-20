//------------------------------------------------------------------------------
// Description:
//   Dual Motor Driver
//     Part# TB6612FNG
//
//   Subrountines:
//     gpio_init
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
#include "TB6612FNG.h"



//------------------------------------------------------------------------------
//  Private
//------------------------------------------------------------------------------
static TIM_HandleTypeDef htim;
static __IO tb66_tim_h clk;

static void tb66_gpio_init(void);
static void tb66_tim_init(void);
static void Error_Handler(char *file, int line);


//------------------------------------------------------------------------------
// Function Name  : tb66_motor_init
// Description    : Initializes
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void tb66_init(void)
{

	tb66_gpio_init();
	tb66_tim_init();

}

//------------------------------------------------------------------------------
// Function Name  : tb66_gpio_init
// Description    : Initializes
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void tb66_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Pin = D7_BIN1_Pin|D8_BIN2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = D5_AIN2_Pin|D4_AIN1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = D6_PWMB_Pin|D3_PWMA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(PWM_port, &GPIO_InitStruct);
}


//------------------------------------------------------------------------------
// Function Name  : tb66_tim_init
// Description    : Initializes
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void tb66_tim_init(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	clk.clock = HAL_RCC_GetPCLK1Freq()*2; // APB1
	clk.prescaler = clk.clock/1000000; // 1MHz clock
	clk.fperiod = 1.0f/(float)TB66_PWM_FREQ;
	clk.period = (uint32_t)(clk.fperiod*1000000.0f);
	clk.scalar = clk.period/100;

	__HAL_RCC_TIM2_CLK_ENABLE();

	htim.Instance = TB66_TIM_INST;
	htim.Init.Prescaler = clk.prescaler-1;
	htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim.Init.Period = clk.period-1;
	htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim) != HAL_OK)
	{
		Error_Handler(__FILE__, __LINE__);
	}


	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler(__FILE__, __LINE__);
	}


	if (HAL_TIM_PWM_Init(&htim) != HAL_OK)
	{
		Error_Handler(__FILE__, __LINE__);
	}


	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim, &sMasterConfig) != HAL_OK)
	{
		Error_Handler(__FILE__, __LINE__);
	}


	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler(__FILE__, __LINE__);
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler(__FILE__, __LINE__);
	}

	HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_3);
}

//------------------------------------------------------------------------------
// Task Name      : Error_Handler
// Description    : report the HAL error return state
// Input          : char *file,  Source file pointer
//                  int line,    Line number
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void Error_Handler(char *file, int line)
{

	while(1)
	{
	}

}


//------------------------------------------------------------------------------
// Function Name  : tb66_control
// Description    : Control function, modes
// Input          : tb66_cmd_t, tb66_cmd_t
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void tb66_control(tb66_cmd_t cmda, tb66_cmd_t cmdb)
{

	switch(cmda)
	{
	case TB66_SHORT_BRAKE:
		HAL_GPIO_WritePin(D4_AIN1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(D5_AIN2, GPIO_PIN_SET);
		break;
	case TB66_CW:
		HAL_GPIO_WritePin(D4_AIN1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(D5_AIN2, GPIO_PIN_RESET);
		break;
	case TB66_CCW:
		HAL_GPIO_WritePin(D4_AIN1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D5_AIN2, GPIO_PIN_SET);
		break;
	case TB66_STOP:
		HAL_GPIO_WritePin(D4_AIN1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D5_AIN2, GPIO_PIN_RESET);
		break;
	case TB66_STANDBY:
		break;
	case TB66_OFF:
		break;
	default:
		break;
	}

	switch(cmda)
	{
	case TB66_SHORT_BRAKE:
		HAL_GPIO_WritePin(D7_BIN1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(D8_BIN2, GPIO_PIN_SET);
		break;
	case TB66_CW:
		HAL_GPIO_WritePin(D7_BIN1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(D8_BIN2, GPIO_PIN_RESET);
		break;
	case TB66_CCW:
		HAL_GPIO_WritePin(D7_BIN1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D8_BIN2, GPIO_PIN_SET);
		break;
	case TB66_STOP:
		HAL_GPIO_WritePin(D7_BIN1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D8_BIN2, GPIO_PIN_RESET);
		//FIXME force PWM HIGH
		break;
	case TB66_STANDBY:
		break;
	case TB66_OFF:
		break;
	default:
		break;
	}
}


//------------------------------------------------------------------------------
// Function Name  : tb66_speed
// Description    : Change motors speed
// Input          : uint8_t [0-100],uint8_t [0-100]
//                  0=Stop, 100=Full
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void tb66_speed(uint8_t speeda, uint8_t speedb)
{
	uint32_t count;

	// Limit checks
	if(speeda>100)
		speeda=100;
	if(speedb>100)
		speedb=100;

	count = speeda * clk.scalar;
	htim.Instance->CCR2 = (uint16_t)count;
	count = speedb * clk.scalar;
	htim.Instance->CCR3 = (uint16_t)count;
}



