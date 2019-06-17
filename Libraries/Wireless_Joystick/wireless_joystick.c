//------------------------------------------------------------------------------
// Description:
//   Wireless Joystick
//
//
//   Subrountines:
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
#include "stm32f4xx.h"
#include "rtos.h"
#include "wireless_joystick.h"

//------------------------------------------------------------------------------
//  Private
//------------------------------------------------------------------------------
wjoy_state_t wjState=0;
wjoy_t  wjData;
uint8_t wjHi=1;

//------------------------------------------------------------------------------
// Function Name  : wjoy_parser
// Description    : Parse out the bytes
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void wjoy_Parser(uint8_t data)
{

	switch(wjState)
	{
	case START:
		wjHi=1;
		wjState++;
	case SYNC0:
		if(data==0xA9)
			wjState++;
		else
			wjState=START;
		break;

	case SYNC1:
		if(data==0x65)
			wjState++;
		else
			wjState=START;
		break;

	case JOYX:
		if(wjHi)
		{
			wjData.xaxis = (data<<8);
			wjHi=0;
		}
		else
		{
			wjData.xaxis += data;
			wjHi=1;
			wjState++;
		}
		break;

	case JOYY:
		if(wjHi)
		{
			wjData.yaxis = (data<<8);
			wjHi=0;
		}
		else
		{
			wjData.yaxis += data;
			wjHi=1;
			wjState++;
		}
		break;

	case BUTTONS:
		wjData.buttons = data^0xFF;
		wjState=START;
		xQueueSend(queueJoystickHandle,&wjData,0);
		break;
	}


}





