#ifndef INCLUDE_TASK_NAVIGATION_H_
#define INCLUDE_TASK_NAVIGATION_H_




// Task
#define NAV_TIME        20 // Hz
#define NAV_PERIOD      (NAV_TIME/portTICK_PERIOD_MS)
#define NAV_TIMEOUT     NAV_PERIOD


// TIM
#define PWM_PRESCALAR    89    // (90-1, Internal +1)
#define PWM_PERIOD       19999 // (20000-1, Internal +1)

// Scalar for PWM
#define CNT2DEG          1200
#define CNT2DEG_MUL      1000
#define DEG2CNT          833
#define DEG2CNT_MUL      1000
#define TH2CNT           117
#define TH2CNT_MUL       100

// Reverse Direction
#define NEG              (-1)

// Wrap around
#define WRAP             1
#define NOWRAP           0

// LED
#define LED_DEADBAND     1000




// Modes
enum navModes
{
	IDLE   = 0,
	MANUAL = 1,
	AUTO   = 2,
};




























//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------
void task_nav(void const * argument);






#endif /* INCLUDE_TASK_NAVIGATION_H_ */
