#ifndef INCLUDE_TASK_DEBUF_H_
#define INCLUDE_TASK_DEBUF_H_


#define FORMAT       "M %d dY %d dDpth %d dTh %d : Y %d P %d R %d Dpth %d Th %d Rpm %d\n\r"
#define FORMATDATA   debugData.Mode,debugData.desireHeading,debugData.desireDepth,debugData.desireThrottle,debugData.Yaw,debugData.Pitch,debugData.Roll,debugData.Depth,debugData.Throttle,debugData.RPM

#define DEBUGSIZE     80


#define STLINK_TX_Pin GPIO_PIN_10
#define STLINK_TX_GPIO_Port GPIOC
#define STLINK_RX_Pin GPIO_PIN_11
#define STLINK_RX_GPIO_Port GPIOC
#define STLINK_Port GPIOC
#define STLINK_AF GPIO_AF7_USART3

#define STLINK_UART_INST  USART3
#define STLINK_UART_BAUDRATE 115200

#define STLINK_DMA_RX_INST  DMA1_Stream1
#define STLINK_DMA_RX_CH    DMA_CHANNEL_4
#define STLINK_DMA_TX_INST  DMA1_Stream3
#define STLINK_DMA_TX_CH    DMA_CHANNEL_4

#define STLINK_UART_IRQ    USART3_IRQn
#define STLINK_DMA_RX_IRQ  DMA1_Stream1_IRQn
#define STLINK_DMA_TX_IRQ  DMA1_Stream3_IRQn


typedef struct debug_stlink
{
	UART_HandleTypeDef huart;
	DMA_HandleTypeDef hdma_usart_rx;
	DMA_HandleTypeDef hdma_usart_tx;
	uint16_t dmaIndex;
	uint16_t parseIndex;
	uint8_t rxBuffer[DEBUGSIZE];
}dbg_stlink_t;





//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------
void task_debug(void const * argument);
void init_debug_Peripherals(void);



#endif
