#ifndef JOYSTICK_WIRELESS_JOYSTICK_H_
#define JOYSTICK_WIRELESS_JOYSTICK_H_



typedef enum wjoy_state
{
	START=0,
	SYNC0,
	SYNC1,
	JOYX,
	JOYY,
	BUTTONS,
}wjoy_state_t;


typedef struct wj_data
{
	uint16_t xaxis;
	uint16_t yaxis;
	uint8_t buttons;
}wjoy_t;


//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------
void wjoy_Parser(uint8_t data);




#endif /* JOYSTICK_WIRELESS_JOYSTICK_H_ */
