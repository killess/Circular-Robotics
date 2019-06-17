#ifndef task_communication_h
#define task_communication_h



// Task
#define COMMS_PERIOD           10 // (ms) 100 Hz


// Radio GPIO
#define RADIO_TX_Pin           GPIO_PIN_2
#define RADIO_TX_GPIO_Port     GPIOA
#define RADIO_RX_Pin           GPIO_PIN_3
#define RADIO_RX_GPIO_Port     GPIOA
#define RADIO_GPIO_Port        GPIOA

// Radio Communication
#define RADIO_BAUDRATE      9600
#define RADIO_PARSER        wjoy_Parser
#define RADIO_INST          USART2
#define RADIO_DMA_RX_INST   DMA1_Stream5
#define RADIO_DMA_RX_CH     DMA_CHANNEL_4
#define RADIO_DMA_TX_INST   DMA1_Stream6
#define RADIO_DMA_TX_CH     DMA_CHANNEL_4


#define RX_SIZE    128 // Bytes


typedef struct com_control
{
	UART_HandleTypeDef huart;
	DMA_HandleTypeDef hdma_usart_rx;
	DMA_HandleTypeDef hdma_usart_tx;
	uint16_t dmaIndex;
	uint16_t parseIndex;
	uint8_t rxBuffer[RX_SIZE];
}comms_t;





//#define BYT3( dwIn )            ((uint8_t)((dwIn&0xFF000000)>>24))
//#define BYT2( dwIn )            ((uint8_t)((dwIn&0x00FF0000)>>16))
//#define BYT1( dwIn )            ((uint8_t)((dwIn&0x0000FF00)>>8))
//#define BYT0( dwIn )            ((uint8_t)(dwIn&0x000000FF))






//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------
void task_Comms(void const * argument);
void init_Comms_Peripherals(void);

void USART2_IRQHandler(void);
void DMA1_Stream5_IRQHandler(void);
void DMA1_Stream6_IRQHandler(void);

#endif // task_communication_h



