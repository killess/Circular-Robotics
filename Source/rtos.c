//------------------------------------------------------------------------------
// Description:
//   
//   Real Time Operating System (RTOS)
//
//
//   Subroutines: 
//     Initialize
//     startup
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
#include "cmsis_os.h"
#include "rtos.h"
#include "task_led.h"
#include "task_navigation.h"
#include "task_communication.h"
//#include "task_sensors.h"
#include "task_debug.h"

#include "wireless_joystick/wireless_joystick.h"



// Task Handles
osThreadId LedHandle;
osThreadId NavHandle;
osThreadId CommsHandle;
//osThreadId SensorsHandle;
osThreadId DebugHandle;


// Queue Handles
osMessageQId queueJoystickHandle;
//osMessageQId queueCompassDataHandle;
//osMessageQId queueCompassCmdHandle;
//osMessageQId queueCommandHandle;
//osMessageQId queueSensorHandle;
//osMessageQId queueDebugHandle;
//osMessageQId queueStreamHandle;


// Watchdog
//IWDG_HandleTypeDef hiwdg;




// OpenOCD's threads awareness
//   Add " --undefined=uxTopUsedPriority " in LINKER flags in project options
//   Add " $_TARGETNAME configure -rtos auto " in openOCD.cfg file
//   Copy " cmsis_os.c and cmsis_os.h "  from the cube/FreeRTOS to Libraries/CMSIS/RTOS
//const int USED uxTopUsedPriority = configMAX_PRIORITIES - 1;





//------------------------------------------------------------------------------
// Function Name  : rtos_start
// Description    : Real Time Operating System (RTOS)
//                  Create Tasks, Queues, Semaphores, Mutexes
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void rtos_start(void)
{

	// Create Tasks
	osThreadDef(Led, task_led, osPriorityBelowNormal, 0, 128);
	LedHandle = osThreadCreate(osThread(Led), NULL);

	osThreadDef(Nav, task_nav, osPriorityHigh, 0, 128);
	NavHandle = osThreadCreate(osThread(Nav), NULL);

	osThreadDef(Comms, task_Comms, osPriorityNormal, 0, 256);
	CommsHandle = osThreadCreate(osThread(Comms), NULL);

	osThreadDef(Debug, task_debug, osPriorityBelowNormal, 0, 256);
	DebugHandle = osThreadCreate(osThread(Debug), NULL);

	//osThreadDef(Watchdog, task_watchdog, osPriorityLow, 0, 128);
	//WatchdogHandle = osThreadCreate(osThread(Watchdog), NULL);






	// Create Queues
	osMessageQDef(queueJoystickData, 3, wjoy_t);
	queueJoystickHandle = osMessageCreate(osMessageQ(queueJoystickData), NULL);
	vQueueAddToRegistry(queueJoystickHandle, "Joystick");
//
//	osMessageQDef(queueCompassCmd, 3, osvr_cmd_t);
//	queueCompassCmdHandle = osMessageCreate(osMessageQ(queueCompassCmd), NULL);
//	vQueueAddToRegistry(queueCompassCmdHandle, "CompassTx");
//
//	osMessageQDef(queueCommand, 3, command_t);
//	queueCommandHandle = osMessageCreate(osMessageQ(queueCommand), NULL);
//	vQueueAddToRegistry(queueCommandHandle, "Command");
//
//	osMessageQDef(queueStream, 3, comStm_t);
//	queueStreamHandle = osMessageCreate(osMessageQ(queueStream), NULL);
//	vQueueAddToRegistry(queueStreamHandle, "Stream");
//
//	osMessageQDef(queueSensor, 3, sendata_t);
//	queueSensorHandle = osMessageCreate(osMessageQ(queueSensor), NULL);
//	vQueueAddToRegistry(queueCommandHandle, "Sensor");
//
//	osMessageQDef(queueDebug, 3, debugData_t);
//	queueDebugHandle = osMessageCreate(osMessageQ(queueDebug), NULL);
//	vQueueAddToRegistry(queueCommandHandle, "Debug");



	// Create Binary Semaphores (Synchronization) task/task, task/interrupt


	// Create Counting Semaphores


	// Create Mutexes  (Mutual Exclusion)


	// Create Recursive Mutexes


	// Create Software Timers


	// Start the scheduler.
	osKernelStart();


	// RTOS should not reach here

}

/*
//------------------------------------------------------------------------------
// Task Name      : vApplicationIdleHook
// Description    : Idle Hook
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void vApplicationIdleHook(void)
{
//	 vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
//   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
//   task. It is essential that code added to this hook function never attempts
//   to block in any way (for example, call xQueueReceive() with a block time
//   specified, or call vTaskDelay()). If the application makes use of the
//   vTaskDelete() API function (as this demo application does) then it is also
//   important that vApplicationIdleHook() is permitted to return to its calling
//   function, because it is the responsibility of the idle task to clean up
//   memory allocated by the kernel to any task that has since been deleted.
}
 */

//------------------------------------------------------------------------------
// Task Name      : vApplicationStackOverflowHook
// Description    : Stack over flow hook
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void vApplicationStackOverflowHook( TaskHandle_t xTask, signed char *pcTaskName )
{
	//bad_task_handle = xTask;     // this seems to give me the crashed task handle
	//bad_task_name = pcTaskName;     // this seems to give me a pointer to the name of the crashed task
	//mLED_3_On();   // a LED is lit when the task has crashed

	//while(1);
}

/*
//------------------------------------------------------------------------------
// Task Name      : task_watchdog
// Description    : Watchdog
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void task_watchdog(void * pvParameters)
{
	TickType_t xLastWakeTime;

	hiwdg.Instance = IWDG;
	hiwdg.Init.Prescaler = IWDG_PRESCALER_4;
	hiwdg.Init.Reload = 4095;
	HAL_IWDG_Init(&hiwdg);

	xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		// Feed the dog
		HAL_IWDG_Refresh(&hiwdg);

		osDelayUntil(&xLastWakeTime,200); // 5 Hz
	}
}
*/






