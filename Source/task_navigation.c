//------------------------------------------------------------------------------
// Description:
//		Vehicle Navigation
//
//
//
//   Subroutines:
//
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
#include "stm32f4xx_hal.h"
#include "rtos.h"
#include "task_navigation.h"

//#include "task_sensors.h"
//#include "task_debug.h"
//#include "task_communication.h"
#include "Motor-TB6612FNG/TB6612FNG.h"

//------------------------------------------------------------------------------
// Private Variables
//------------------------------------------------------------------------------


//static void init_task_peripherals(void);


//------------------------------------------------------------------------------
// Task Name      : task_Nav
// Description    : Navigation
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void task_nav(void const * argument)
{
	TickType_t xLastWakeTime;

	uint8_t test1=0,test2=0;
	tb66_init(); // Motor Driver IC

	tb66_control(TB66_CW,TB66_CW);


	xLastWakeTime = osKernelSysTick();
	while(1)
	{

		tb66_speed(test1,test2);

		test1++;
		if(test1>100)test1=0;
		test2++;
		if(test2>100)test2=0;

		// Read data queues
//		xQueueReceive(queueCompassDataHandle,&Compass,NAV_TIMEOUT);
//		xQueueReceive(queueCommandHandle,&Command,0);
//		xQueueReceive(queueSensorHandle,&Sensors,0);

/*
		// Vehicle Modes
		switch(Command.Mode)
		{

		case MANUAL:

			break;



		case AUTO:


			break;


		case IDLE:
		default:

			break;
		}

*/






		// Set PWM values
//		htim3.Instance->CCR2 = (uint16_t)pwm.ch2;
//		htim3.Instance->CCR3 = (uint16_t)pwm.ch3;



		osDelayUntil(&xLastWakeTime, NAV_PERIOD);
	}// End main loop
}// End Task

/*
//------------------------------------------------------------------------------
// Task Name      : init_task_peripherals
// Description    : Initialize task peripherals
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void init_task_peripherals(void)
{




}










//------------------------------------------------------------------------------
// Task Name      : PID_Control
// Description    : Calculate one iteration of the PID control loop
// Input          : pid_t      (Private Variables)
// Output         : output
// Return         : output
//------------------------------------------------------------------------------
int32_t PID_Control(pidparm_t* parm)
{
	int32_t pid_P=0,pid_I=0,pid_D=0;

	// Calculate Proportional
	if(parm->Kp==0)
		parm->P_term=0;
	else
	{
		pid_P  = parm->Error;
		parm->P_term = (parm->Kp*pid_P)/1000;
		if(parm->P_term > parm->Pmax) parm->P_term = parm->Pmax;
		if(parm->P_term < parm->Pmin) parm->P_term = parm->Pmin;
	}

	// Calculate Integral
	if(parm->Ki==0)
		parm->I_term=0;
	else
	{
		pid_I = (parm->Error*parm->dT);
		parm->I_term += (parm->Ki*pid_I)/100000;
		if(parm->I_term > parm->Imax) parm->I_term = parm->Imax;
		if(parm->I_term < parm->Imin) parm->I_term = parm->Imin;
	}

	// Calculate Derivative
	if(parm->Kd==0)
		parm->D_term=0;
	else
	{
		pid_D  = (parm->Error - parm->preError);
		pid_D *= 10;
		pid_D /= parm->dT;
		parm->D_term = (parm->Kd*pid_D);
		if(parm->D_term > parm->Dmax) parm->D_term = parm->Dmax;
		if(parm->D_term < parm->Dmin) parm->D_term = parm->Dmin;
	}

	// Save Error
	parm->preError = parm->Error;

	// Calculate Output
	parm->Output = parm->P_term + parm->I_term + parm->D_term;
	return parm->Output;
}


//------------------------------------------------------------------------------
// Task Name      : dT
// Description    : Calculate dT from RTOS ticker, in (ms)
// Input          : last time
// Output         : change in time
// Return         : None
//------------------------------------------------------------------------------
uint32_t dT(uint32_t *lastTime)
{
	uint32_t time, dT;

	time = osKernelSysTick(); // Current tick
	time *= portTICK_PERIOD_MS;   // Tick to ms

	if(time > *lastTime) // check rollover tick counter
		dT = (time - *lastTime);
	else
		dT = ((0xFFFFFFFF - *lastTime) + time);
	if(dT==0)
		dT = 1; // Protect divide by zero

	*lastTime = time;
	return dT;
}


//------------------------------------------------------------------------------
// Task Name      : Error
// Description    : Calculate error for PID controller
// Input          :
// Output         :
// Return         : None
//------------------------------------------------------------------------------
int32_t Error(uint8_t wrap, int32_t num1, int32_t num2)
{
	int32_t error;

	// Calculate Error
	error = num1 - num2;

	// Yaw Wrap around correction
	if(wrap)
	{
		if(error > 18000)
		{
			error -= 36000;
		}
		else if(error < -18000)
		{
			error += 36000;
		}
	}
	return error;
}

*/


