#ifndef INCLUDE_I2C_OLED_DISPLAY_OLED_GEOM_H_
#define INCLUDE_I2C_OLED_DISPLAY_OLED_GEOM_H_

#include "oled_basic.h"
#include "math.h"


typedef struct{
    int16_t x;
    int16_t y;
} coordParams;


/*
 * @brief	Draws a line at coordinates.
 *
 * @param_in	x1	Horizontal coordinate of the first point.
 * 				y1 	Vertical coordinate of the first point.
 * 				x2	Horizontal coordinate of the second point.
 * 				y2 	Vertical coordinate of the second point.
 *
 * @note	Draws a line according to the equation: (y-y1)/(y2-y1) = (x-x1)/(x2-x1).
 *
 * @note	(x, y) = (0, 0) - Upper left coner.
 */
void oledDrawLineCoord(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);


/*
 * @brief	Draws a rectangle at coordinates of two opposite corners.
 *
 * @note	May be hollow or filled.
 *
 * @param_in	x1		Horizontal coordinate of the first point.
 * 				y1 		Vertical coordinate of the first point.
 * 				x2		Horizontal coordinate of the second point.
 * 				y2 		Vertical coordinate of the second point.
 * 				fill	Fill or hollow.
 *
 * @note	(x, y) = (0, 0) - Upper left coner.
 */
void oledDrawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill);


/*
 * @brief	Draws a circle at center coordinates and the radios.
 *
 * @note	May be hollow or filled.
 *
 * @param_in	x		Horizontal coordinate of the center.
 * 				y 		Vertical coordinate of the center.
 * 				R		Radios.
 * 				fill	Fill or hollow.
 *
 * @note	(x, y) = (0, 0) - Upper left coner.
 */
void oledDrawCircle(uint8_t X1, uint8_t Y1, uint8_t R, bool fill);


/*
 * @brief	Fill the space in which (x,y) is located.
 *
 * @note	Can not to work correctly!!!
 *
 * @param_in	x		Horizontal coordinate inside the space we want to fill.
 * 				y 		Vertical coordinate inside the space we want to fill.
 */
void oledFillSpace(uint8_t x, uint8_t y);


/*
 * @brief	Draws a triangle at 3 coordinates.
 *
 * @note	May be hollow or filled.
 *
 * @param_in	x1		Horizontal coordinate of the first point.
 * 				y1 		Vertical coordinate of the first point.
 * 				x2		Horizontal coordinate of the second point.
 * 				y2 		Vertical coordinate of the second point.
 * 				x3		Horizontal coordinate of the third point.
 * 				y3 		Vertical coordinate of the third point.
 * 				fill	Fill or hollow.
 *
 * @note	(x, y) = (0, 0) - Upper left coner.
 */
void oledDrawTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, bool fill);


/*
 * @brief	Counts the coordinates of the second point to be found using the angle and distance.
 *
 * @pram_in		x		Horizontal coordinate of the first point.
 * 				y		Vertical coordinate of the first point.
 * 				angle	The angle of inclination of a straight line relative to the X axis.
 * 				lenght	The length of the line.
 *
 * @param_out	drawLineAngleParam	Contains coordinates of the second point.
 */
coordParams* oledCountCoordLineAngle(uint8_t x, uint8_t y, uint16_t angle, uint8_t lenght);


/*
 * @brief	Draws a line at coordinates, angle and lenght.
 *
 * @pram_in		x		Horizontal coordinate of the first point.
 * 				y		Vertical coordinate of the first point.
 * 				angle	The angle of inclination of a straight line relative to the X axis.
 * 				lenght	The length of the line.
 *
 * @param_out	drawLineAngleParam	Contains coordinates of the second point.
 */
coordParams* oledDrawLineAngle(uint8_t x, uint8_t y, uint16_t angle, uint8_t lenght);


/*
 * @brief	Gets the coordinates of the second point to be found using the angle and distance.
 *
 * @param_out	drawLineAngleParam	Contains coordinates of the second point.
 */
coordParams* oledGetLineAngleParam(void);

#endif /* INCLUDE_I2C_OLED_DISPLAY_OLED_GEOM_H_ */
