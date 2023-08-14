#include "buttons.h"
#include "terminal_write.h"

// New button press. It is reset when you take the flag value [buttonsGetFlagNewVal()].
static bool flag_new_val = false;

// The last button that was pressed.
static buttons_t current_button = VOID;


/*
 * @brief	Button interrupt (Left).
 *
 * @note	Contact bounce is possible. Should not affect performance.
 *
 * @notapi
 */
void left_but(void* args){
    args = args;
    current_button = LEFT;
    flag_new_val = true;
}

/*
 * @brief	Button interrupt (Right).
 *
 * @note	Contact bounce is possible. Should not affect performance.
 *
 * @notapi
 */
void right_but(void* args){
    args = args;
    current_button = RIGHT;
    flag_new_val = true;
}

/*
 * @brief	Button interrupt (Center).
 *
 * @note	Contact bounce is possible. Should not affect performance.
 *
 * @notapi
 */
void center_but(void* args){
    args = args;
    current_button = CENTER;
    flag_new_val = true;
}

/*
 * @brief	Button interrupt (Top).
 *
 * @note	Contact bounce is possible. Should not affect performance.
 *
 * @notapi
 */
void top_but(void* args){
    args = args;
    current_button = TOP;
    flag_new_val = true;
}

/*
 * @brief	Button interrupt (Bottom).
 *
 * @note	Contact bounce is possible. Should not affect performance.
 *
 * @notapi
 */
void bottom_but(void* args){
    args = args;
    current_button = BOTTOM;
    flag_new_val = true;
}


/*
 *  @brief  Starts another thread to check buttons state.
 *
 *  @note	Interrupts occur and it determines which button is pressed.
 *
 *  @note	Do not change the pins, it can lead to the thread freezing!
 *
 *  @notapi
 */
static thread_t *tp_buttons;
static THD_WORKING_AREA(waButtons, 256);// 256 - stack size

static THD_FUNCTION(buttonsThread, arg)
{
    (void)arg; // just to avoid warnings
    chRegSetThreadName("Buttons thread");


    // Sets pins for buttons.
    // Center button.
    palSetLineMode(LINE_CENTER_BUT, PAL_MODE_INPUT_PULLDOWN);
	palEnableLineEvent(LINE_CENTER_BUT, PAL_EVENT_MODE_RISING_EDGE);
	palSetLineCallback(LINE_CENTER_BUT, center_but, NULL);

	// Right button.
	palSetLineMode(LINE_RIGHT_BUT, PAL_MODE_INPUT_PULLDOWN);
	palEnableLineEvent(LINE_RIGHT_BUT, PAL_EVENT_MODE_RISING_EDGE);
	palSetLineCallback(LINE_RIGHT_BUT, right_but, NULL);

	// Bottom button.
	palSetLineMode(LINE_BOTTOM_BUT, PAL_MODE_INPUT_PULLDOWN);
	palEnableLineEvent(LINE_BOTTOM_BUT, PAL_EVENT_MODE_RISING_EDGE);
	palSetLineCallback(LINE_BOTTOM_BUT, bottom_but, NULL);

	// Left button.
	palSetLineMode(LINE_LEFT_BUT, PAL_MODE_INPUT_PULLDOWN);
	palEnableLineEvent(LINE_LEFT_BUT, PAL_EVENT_MODE_RISING_EDGE);
	palSetLineCallback(LINE_LEFT_BUT, left_but, NULL);

	// Top button.
	palSetLineMode(LINE_TOP_BUT, PAL_MODE_INPUT_PULLDOWN);
	palEnableLineEvent(LINE_TOP_BUT, PAL_EVENT_MODE_RISING_EDGE);
	palSetLineCallback(LINE_TOP_BUT, top_but, NULL);

    systime_t time = chVTGetSystemTime();
    while( !chThdShouldTerminateX() ){
		time = chThdSleepUntilWindowed( time, time + TIME_MS2I( 20 ) );
    }
    chThdExit(MSG_OK);
}


/*
 *  @brief  Initializes the thread to to check buttons state.
 *
 *  @note	Interrupts occur and it determines which button is pressed.
 *
 *  @note	Do not change the pins, it can lead to the thread freezing!
 */
void buttonsInit(void){
	flag_new_val = false;
	current_button = VOID;
	tp_buttons = chThdCreateStatic(waButtons, sizeof(waButtons), NORMALPRIO, buttonsThread, NULL);
}



/*
 * @brief	Returns the status of a new button press.
 *
 * @note	Resets the status.
 *
 * @param_out	flag	The status of a new button press
 */
bool buttonsGetFlagNewVal(void){
	bool flag_temp = flag_new_val;
	flag_new_val = false;
	return flag_temp;
}

/*
 * @brief	Returns which button was pressed.
 *
 * @param_out	current_button	The last button that was pressed.
 */
buttons_t buttonsGetCurrentBut(void){
	return current_button;
}
