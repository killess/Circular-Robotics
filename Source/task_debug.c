//------------------------------------------------------------------------------
// Description:
//
//   Debug
//
//
//   Subroutines:
//     task_debug
//     init_debug_Peripherals
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
#include "task_debug.h"
#include <stdio.h>





//------------------------------------------------------------------------------
// Private Variables
//------------------------------------------------------------------------------
dbg_stlink_t dbg;



//uint8_t format[] = FORMAT;

//HAL_UART_Transmit_DMA(&huart1,Msg2,12);
//HAL_UART_Transmit(&huart1,"hello",5,0xFFFF);


//------------------------------------------------------------------------------
// Task Name      : task_debug
// Description    : Gatekeeper task to the debug uart tx
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void task_debug(void const * argument)
{
	//int16_t size=0;
	TickType_t  xLastWakeTime;

	init_debug_Peripherals();



	xLastWakeTime = osKernelSysTick();
	while(1)
	{

		//HAL_UART_Transmit_DMA(&dbg.huart,"Greg\n\r",6);

//		xQueueReceive(queueDebugHandle,&debugData,portMAX_DELAY);
//
//		size = snprintf(debugString,DEBUGSIZE,format,FORMATDATA);
//		if(size>0)
//			HAL_UART_Transmit_DMA(&huart5,debugString,size);
//		else
//			HAL_UART_Transmit_DMA(&huart5,"BadString\n\r",11);


		osDelayUntil(&xLastWakeTime,100);
	}
}


//------------------------------------------------------------------------------
// Task Name      : init_mission_Peripherals
// Description    : Initialize task peripherals
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void init_debug_Peripherals(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;


	// Clock
	__HAL_RCC_USART3_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// GPIO
	GPIO_InitStruct.Pin = STLINK_TX_Pin|STLINK_RX_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = STLINK_AF;
	HAL_GPIO_Init(STLINK_Port, &GPIO_InitStruct);

	// UART
	dbg.huart.Instance = STLINK_UART_INST;
	dbg.huart.Init.BaudRate = STLINK_UART_BAUDRATE;
	dbg.huart.Init.WordLength = UART_WORDLENGTH_8B;
	dbg.huart.Init.StopBits = UART_STOPBITS_1;
	dbg.huart.Init.Parity = UART_PARITY_NONE;
	dbg.huart.Init.Mode = UART_MODE_TX_RX;
	dbg.huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	dbg.huart.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&dbg.huart);

	// DMA
	dbg.hdma_usart_rx.Instance = STLINK_DMA_RX_INST;
	dbg.hdma_usart_rx.Init.Channel = STLINK_DMA_RX_CH;
	dbg.hdma_usart_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	dbg.hdma_usart_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	dbg.hdma_usart_rx.Init.MemInc = DMA_MINC_ENABLE;
	dbg.hdma_usart_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	dbg.hdma_usart_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	dbg.hdma_usart_rx.Init.Mode = DMA_CIRCULAR;
	dbg.hdma_usart_rx.Init.Priority = DMA_PRIORITY_LOW;
	dbg.hdma_usart_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(&dbg.hdma_usart_rx);

	__HAL_LINKDMA(&dbg.huart,hdmarx,dbg.hdma_usart_rx);

	dbg.hdma_usart_tx.Instance = STLINK_DMA_TX_INST;
	dbg.hdma_usart_tx.Init.Channel = STLINK_DMA_TX_CH;
	dbg.hdma_usart_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	dbg.hdma_usart_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	dbg.hdma_usart_tx.Init.MemInc = DMA_MINC_ENABLE;
	dbg.hdma_usart_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	dbg.hdma_usart_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	dbg.hdma_usart_tx.Init.Mode = DMA_NORMAL;
	dbg.hdma_usart_tx.Init.Priority = DMA_PRIORITY_LOW;
	dbg.hdma_usart_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(&dbg.hdma_usart_tx);

	__HAL_LINKDMA(&dbg.huart,hdmatx,dbg.hdma_usart_tx);

	// NVIC
	HAL_NVIC_SetPriority(STLINK_UART_IRQ, 5, 0);
	HAL_NVIC_EnableIRQ(STLINK_UART_IRQ);
	HAL_NVIC_SetPriority(STLINK_DMA_RX_IRQ, 5, 0);
	HAL_NVIC_EnableIRQ(STLINK_DMA_RX_IRQ);
	HAL_NVIC_SetPriority(STLINK_DMA_TX_IRQ, 5, 0);
	HAL_NVIC_EnableIRQ(STLINK_DMA_TX_IRQ);

	// Start Circular RX
	HAL_UART_Receive_DMA(&dbg.huart,dbg.rxBuffer,DEBUGSIZE);
}


//------------------------------------------------------------------------------
void USART3_IRQHandler(void)
{
  HAL_UART_IRQHandler(&dbg.huart);
}
void DMA1_Stream1_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&dbg.hdma_usart_rx);
}
void DMA1_Stream3_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&dbg.hdma_usart_tx);
}






