#ifndef LIBRARIES_TB6612FNG_MOTOR_H_
#define LIBRARIES_TB6612FNG_MOTOR_H_


#define TB66_PWM_FREQ  1000 // Hz  (100KHz Max)

#define D4_AIN1_Pin GPIO_PIN_5
#define D4_AIN1_GPIO_Port GPIOB
#define D5_AIN2_Pin GPIO_PIN_4
#define D5_AIN2_GPIO_Port GPIOB
#define D4_AIN1 D4_AIN1_GPIO_Port,D4_AIN1_Pin
#define D5_AIN2 D5_AIN2_GPIO_Port,D5_AIN2_Pin

#define D3_PWMA_Pin GPIO_PIN_3
#define D3_PWMA_GPIO_Port GPIOB

#define D7_BIN1_Pin GPIO_PIN_8
#define D7_BIN1_GPIO_Port GPIOA
#define D8_BIN2_Pin GPIO_PIN_9
#define D8_BIN2_GPIO_Port GPIOA
#define D7_BIN1 D7_BIN1_GPIO_Port,D7_BIN1_Pin
#define D8_BIN2 D8_BIN2_GPIO_Port,D8_BIN2_Pin

#define D6_PWMB_Pin GPIO_PIN_10
#define D6_PWMB_GPIO_Port GPIOB

#define PWM_port GPIOB

#define TB66_TIM_INST       TIM2



typedef enum tb66_control
{
	TB66_SHORT_BRAKE = 1,
	TB66_CW = 2,
	TB66_CCW = 3,
	TB66_STOP = 4,
	TB66_STANDBY = 5,
	TB66_OFF = 6,
}tb66_cmd_t;

typedef struct tb66_tim
{
	uint32_t clock;
	uint32_t prescaler;
	uint32_t period;
	float fperiod;

	uint32_t scalar;
}tb66_tim_h;

//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------
void tb66_init(void);
void tb66_control(tb66_cmd_t cmda, tb66_cmd_t cmdb);
void tb66_speed(uint8_t speeda, uint8_t speedb);



#endif /* LIBRARIES_TB6612FNG_MOTOR_H_ */
