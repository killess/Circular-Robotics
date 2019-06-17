//------------------------------------------------------------------------------
// Description:
//
//   Board Communications
//
//
//   Subroutines:
//     task_Comms
//     init_Comms_Peripherals
//
//   Functions:
//     None
//
//
//------------------------------------------------------------------------------





//------------------------------------------------------------------------------
//  Includes Files
//------------------------------------------------------------------------------
#include "stm32f4xx_hal.h"
#include "rtos.h"
#include "task_communication.h"
#include "wireless_joystick/wireless_joystick.h"




//------------------------------------------------------------------------------
// Private Variables
//------------------------------------------------------------------------------
comms_t comPort={0};





//------------------------------------------------------------------------------
// Task Name      : task_Comms
// Description    : Receive communications task
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void task_Comms(void const * argument)
{
	TickType_t  xLastWakeTime;

	init_Comms_Peripherals();


	xLastWakeTime = osKernelSysTick();
	while(1)
	{
			comPort.dmaIndex = RX_SIZE - comPort.huart.hdmarx->Instance->NDTR;
			while(comPort.parseIndex != comPort.dmaIndex)
			{
				RADIO_PARSER(comPort.rxBuffer[comPort.parseIndex]);
				comPort.parseIndex++;
				if(comPort.parseIndex >= RX_SIZE)
					comPort.parseIndex=0;
			}


		osDelayUntil(&xLastWakeTime,COMMS_PERIOD);
	}
}


//------------------------------------------------------------------------------
// Task Name      : init_Compass_Peripherals
// Description    : Initialize task peripherals
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void init_Comms_Peripherals(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;


	// Clocks
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO
	GPIO_InitStruct.Pin = RADIO_TX_Pin|RADIO_RX_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(RADIO_GPIO_Port, &GPIO_InitStruct);

	// USART
	comPort.huart.Instance = RADIO_INST;
	comPort.huart.Init.BaudRate = RADIO_BAUDRATE;
	comPort.huart.Init.WordLength = UART_WORDLENGTH_8B;
	comPort.huart.Init.StopBits = UART_STOPBITS_1;
	comPort.huart.Init.Parity = UART_PARITY_NONE;
	comPort.huart.Init.Mode = UART_MODE_TX_RX;
	comPort.huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	comPort.huart.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&comPort.huart);

	// DMA RX
	comPort.hdma_usart_rx.Instance = RADIO_DMA_RX_INST;
	comPort.hdma_usart_rx.Init.Channel = RADIO_DMA_RX_CH;
	comPort.hdma_usart_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	comPort.hdma_usart_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	comPort.hdma_usart_rx.Init.MemInc = DMA_MINC_ENABLE;
	comPort.hdma_usart_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	comPort.hdma_usart_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	comPort.hdma_usart_rx.Init.Mode = DMA_CIRCULAR;
	comPort.hdma_usart_rx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
	comPort.hdma_usart_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(&comPort.hdma_usart_rx);

	__HAL_LINKDMA(&comPort.huart,hdmarx,comPort.hdma_usart_rx);

	// DMA TX
	comPort.hdma_usart_tx.Instance = DMA1_Stream6;
	comPort.hdma_usart_tx.Init.Channel = DMA_CHANNEL_4;
	comPort.hdma_usart_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	comPort.hdma_usart_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	comPort.hdma_usart_tx.Init.MemInc = DMA_MINC_ENABLE;
	comPort.hdma_usart_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	comPort.hdma_usart_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	comPort.hdma_usart_tx.Init.Mode = DMA_NORMAL;
	comPort.hdma_usart_tx.Init.Priority = DMA_PRIORITY_HIGH;
	comPort.hdma_usart_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(&comPort.hdma_usart_tx);

	__HAL_LINKDMA(&comPort.huart,hdmatx,comPort.hdma_usart_tx);

	// Interrupts (NVIC)
    HAL_NVIC_SetPriority(USART2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 1, 0); // Tx
	HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
	HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 1, 0); // Rx
	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

	// Start Circular RX
	HAL_UART_Receive_DMA(&comPort.huart,comPort.rxBuffer,RX_SIZE);
}


//------------------------------------------------------------------------------

void USART2_IRQHandler(void)
{
  HAL_UART_IRQHandler(&comPort.huart);
}

void DMA1_Stream5_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&comPort.hdma_usart_rx);
}

void DMA1_Stream6_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&comPort.hdma_usart_tx);
}


//HAL_UART_Transmit_DMA(&huart1,Msg2,12);
//HAL_UART_Transmit(&huart1,"hello",5,0xFFFF);








