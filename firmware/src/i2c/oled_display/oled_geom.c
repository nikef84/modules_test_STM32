#include "oled_geom.h"
#include "terminal_write.h"

/* @brief 	The coordinates of the second point to be found using the angle and distance.
 *
 * @note	oledCountCoordLineAngle();
 */
static coordParams drawLineAngleParam = {
    .x = 0,
	.y = 0
};



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
void oledDrawLineCoord(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    int8_t dx = x2 - x1;
    int8_t dy = y2 - y1;

    if (abs(dx) > abs(dy)) {
        if (x1 < x2) {
            for (int16_t x = x1; x <= x2; x++) {
            	oledDrawPixel(x, (uint8_t)((x - x1) * dy / dx + y1));

            }
        } else {
            for (int16_t x = x1; x >= x2; x--) {
            	oledDrawPixel(x, (uint8_t)((x - x1) * dy / dx + y1));
            }
        }
    } else {
        if (y1 < y2) {
            for (int16_t y = y1; y <= y2; y++) {
            	oledDrawPixel((uint8_t)((y - y1) * dx / dy + x1), y);
            }
        } else {
            for (int16_t y = y1; y >= y2; y--) {
            	oledDrawPixel((uint8_t)((y - y1) * dx / dy + x1), y);
            }
        }
    }
}


/*
 * @brief	Sets start point to fill the rectangle.
 *
 * @notapi
 */
void oled_change_rect_fill_param(uint8_t *x1, uint8_t *x2){
	uint8_t temp;
	if (*x1 < *x2) {
		*x1 = *x1 + 1;
		*x2 = *x2 - 1;
	}
	else {
		temp = *x1;
		*x1 = *x2 + 1;
		*x2 = temp - 1;
	}
}


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
void oledDrawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill){

	oledDrawLineCoord(x1, y1, x1, y2);
	oledDrawLineCoord(x2, y1, x2, y2);
	oledDrawLineCoord(x1, y1, x2, y1);
	oledDrawLineCoord(x1, y2, x2, y2);

	// Fill or hollow.
	if (fill == true && (x1 != x2 && y1 != y2)){

		oled_change_rect_fill_param(&x1, &x2);
		oled_change_rect_fill_param(&y1, &y2);
		while (y1 <= y2){
			oledDrawLineCoord(x1, y1, x2, y1);
			y1++;
		}
	}
}


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
void oledDrawCircle(uint8_t x, uint8_t y, uint8_t R, bool fill){
	uint8_t x_circle, y_circle; // Coord of circle.
	int16_t delta, error;
	x_circle = 0;
	y_circle = R;
	delta = 1 - 2 * R;
	error = 0;
	while (y_circle >= x_circle){
		oledDrawPixel(x + x_circle, y + y_circle);
		oledDrawPixel(x + x_circle, y - y_circle);
		oledDrawPixel(x - x_circle, y + y_circle);
		oledDrawPixel(x - x_circle, y - y_circle);
		oledDrawPixel(x + y_circle, y + x_circle);
		oledDrawPixel(x + y_circle, y - x_circle);
		oledDrawPixel(x - y_circle, y + x_circle);
		oledDrawPixel(x - y_circle, y - x_circle);
		error = 2 * (delta + y_circle) - 1;
		if ((delta < 0) && (error <= 0)){
			delta += 2 * ++x_circle + 1;
			continue;
		}
		if ((delta > 0) && (error > 0)){
			delta -= 2 * --y_circle + 1;
			continue;
		}
		delta += 2 * (++x_circle - --y_circle);
	}
	if (fill == true){
		oledFillSpace(x, y);
	}
}


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
void oledDrawTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, bool fill){
	oledDrawLineCoord(x1, y1, x2, y2);
	oledDrawLineCoord(x2, y2, x3, y3);
	oledDrawLineCoord(x3, y3, x1, y1);

	if (fill == true){
		oledFillSpace((x1 + x2 + x3) / 3, (y1 + y2 + y3) / 3);
	}

}


/*
 * @breif	Converts degrees to radians.
 *
 * @param_in	angle	Angle in degrees.
 *
 * @not_api
 */
float grad_to_rad(uint16_t angle){
	return (angle * M_PI) / 180;
}


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
coordParams* oledCountCoordLineAngle(uint8_t x, uint8_t y, uint16_t angle, uint8_t lenght){
	drawLineAngleParam.x = x + lenght * cos(grad_to_rad(angle));
	drawLineAngleParam.y = y - lenght * sin(grad_to_rad(angle));
	return &drawLineAngleParam;
}

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
coordParams* oledDrawLineAngle(uint8_t x, uint8_t y, uint16_t angle, uint8_t lenght){
	oledCountCoordLineAngle(x, y, angle, lenght);
	if (drawLineAngleParam.x > 0 && drawLineAngleParam.x < 255 &&
		drawLineAngleParam.y > 0 && drawLineAngleParam.y < 255){
		oledDrawLineCoord(x, y, drawLineAngleParam.x, drawLineAngleParam.y);
	}
	return &drawLineAngleParam;
}

/*
 * @brief	Gets the coordinates of the second point to be found using the angle and distance.
 *
 * @param_out	drawLineAngleParam	Contains coordinates of the second point.
 */
coordParams* oledGetLineAngleParam(void){
	return &drawLineAngleParam;
}


/*
 * @brief	Checks and paints a pixel in an area.
 *
 * param_in		space_x			An array that contains the horizontal coordinates of
 * 								all coords in the space to be filled.
 * 				space_y			An array that contains the vertical coordinates of
 * 								all coords in the space to be filled.
 * 				space_size		The maximum number of pixels that the region contains.
 * 				space_index		The index of the investigated pixel.
 * 				dx				Horizontal change of coordinate relative to the pixel under study.
 * 				dy				Vertical change of coordinate relative to the pixel under study.
 *
 * @notapi
 */
void fill_pixel(uint8_t *space_x, uint8_t *space_y, uint16_t *space_size, uint16_t *space_index, int8_t dx, int8_t dy){
	if (space_x[*space_index] + dx <= (OLED_LENGHT - 1) && space_x[*space_index] + dx >= 0 &&
		space_y[*space_index] + dy <= (OLED_HEIGHT - 1) && space_y[*space_index] + dy >= 0){
		if (oledGetPixel(space_x[*space_index] + dx, space_y[*space_index] + dy) != oledGetColorDraw()){
			space_x[*space_size] = space_x[*space_index] + dx;
			space_y[*space_size] = space_y[*space_index] + dy;
			oledDrawPixel(space_x[*space_size], space_y[*space_size]);
			*space_size = *space_size + 1;
		}
	}
}


// Arrays that contain the coordinates of all coords in the space to be filled.
static uint8_t space_x[OLED_NUM_OF_PIXELS] = {0};
static uint8_t space_y[OLED_NUM_OF_PIXELS] = {0};


/*
 * @brief	Fill the space in which (x,y) is located.
 *
 * @note	Can take some time.
 *
 * @param_in	x		Horizontal coordinate inside the space we want to fill.
 * 				y 		Vertical coordinate inside the space we want to fill.
 */
void oledFillSpace(uint8_t x, uint8_t y){
	if (oledGetPixel(x, y) != oledGetColorDraw()){
		uint16_t space_size = 0; // The maximum number of pixels that the region contains.
		uint16_t space_index = 0; // The index of the investigated pixel.
		// Clean the buf.
		for (uint16_t i = 0; i != OLED_NUM_OF_PIXELS; i++){
			space_x[i] = 0;
			space_y[i] = 0;
		}
		// Fills the first point of the space.
		space_x[space_size] = x;
		space_y[space_size] = y;
		oledDrawPixel(space_x[space_size], space_y[space_size]);
		space_size = space_size + 1;

		while (space_size != space_index){ // Untill we find all pixel, that we need to fill.
			fill_pixel(space_x, space_y, &space_size, &space_index, 0, -1); // Step to the top.
			fill_pixel(space_x, space_y, &space_size, &space_index, 1, 0); // Step to the right
			fill_pixel(space_x, space_y, &space_size, &space_index, 0, 1); // Step to the bottom.
			fill_pixel(space_x, space_y, &space_size, &space_index, -1, 0); // Step to the left.
			space_index = space_index + 1;
		}
	}
}
