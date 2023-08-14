#ifndef INCLUDE_BUTTONS_H_
#define INCLUDE_BUTTONS_H_

#include "common.h"

// Pins for buttons. Do not change, it can lead to the thread freezing!
#define LINE_CENTER_BUT		PAL_LINE(GPIOC, 6)
#define LINE_RIGHT_BUT		PAL_LINE(GPIOB, 15)
#define LINE_BOTTOM_BUT		PAL_LINE(GPIOB, 13)
#define LINE_LEFT_BUT		PAL_LINE(GPIOB, 12)
#define LINE_TOP_BUT		PAL_LINE(GPIOC, 7)


// Possible buttons.
typedef  enum
{
  VOID   = 0, // Inital value
  CENTER = 1,
  RIGHT  = 2,
  BOTTOM = 3,
  LEFT   = 4,
  TOP    = 5
}buttons_t;


/*
 *  @brief  Initializes the thread to to check buttons state.
 *
 *  @note	Interrupts occur and it determines which button is pressed.
 *
 *  @note	Do not change the pins, it can lead to the thread freezing!
 */
void buttonsInit(void);

/*
 * @brief	Returns the status of a new button press.
 *
 * @note	Resets the status.
 *
 * @param_out	flag	The status of a new button press
 */
bool buttonsGetFlagNewVal(void);

/*
 * @brief	Returns which button was pressed.
 *
 * @param_out	current_button	The last button that was pressed.
 */
buttons_t buttonsGetCurrentBut(void);

#endif /* INCLUDE_BUTTONS_H_ */
