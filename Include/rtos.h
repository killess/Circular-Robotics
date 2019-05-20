//------------------------------------------------------------------------------
// RTOS Header
//------------------------------------------------------------------------------
#ifndef rtos_h
#define rtos_h
#include "cmsis_os.h"


// Task Handles
extern osThreadId LedHandle;
extern osThreadId NavHandle;

//extern osThreadId CompassHandle;
//extern osThreadId CommsHandle;
//extern osThreadId StoreHandle;
//extern osThreadId SensorHandle;
//extern osThreadId MissionHandle;
//extern osThreadId WatchdogHandle;
//extern osThreadId DebugHandle;


// Queue Handles
//extern osMessageQId queueCompassDataHandle;
//extern osMessageQId queueCompassCmdHandle;
//extern osMessageQId queueCommandHandle;
//extern osMessageQId queueSensorHandle;
//extern osMessageQId queueDebugHandle;
//extern osMessageQId queueStreamHandle;



// Debugging for openOCD
#ifdef __GNUC__
#define USED __attribute__((used))
#else
#define USED
#endif




//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------
void rtos_start(void);



#endif //rtos_h
