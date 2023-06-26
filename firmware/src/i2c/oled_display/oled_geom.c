#include "oled_geom.h"

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
 * @brief	Fill the space in which (x,y) is located.
 *
 * @note	Can not to work correctly!!!
 *
 * @param_in	x		Horizontal coordinate inside the space we want to fill.
 * 				y 		Vertical coordinate inside the space we want to fill.
 */
void oledFillSpace(uint8_t x, uint8_t y){
	if (oledGetPixel(x, y) != oledGetColorDraw()){
		// Goes up and down from a given point.
		int8_t vert_dir = -1;
		int8_t vert_step = 0;
		// To save first x coor.
		uint8_t x_temp = x;
		// Goes left and right from a point.
		int8_t hor_dir, hor_step;
		// Coords of the leftmost and rightmost points of space at Y.
		uint8_t x1, x2;
		// Horizontal direction if we need to move x coord.
		int8_t temp_dir;
		while (vert_dir != 0){
			if (oledGetPixel(x, y + vert_step) != oledGetColorDraw()){
				hor_dir = 1;
				hor_step = 0;

				while (hor_dir != 0){ // Find coords the leftmost and rightmost points of space at Y.
					hor_step += hor_dir;
					if (oledGetPixel(x + hor_step, y + vert_step) == oledGetColorDraw()){
						// Change horizontal direction of filling.
						if (hor_dir == 1) {
							hor_dir = -1;
							x2 = x + hor_step;
						}
						else {
							hor_dir = 0;
							x1 = x + hor_step;
						}
						hor_step = 0;
					}


				}
				oledDrawLineCoord(x1, y + vert_step, x2, y + vert_step); // Drwa line.
				vert_step += vert_dir;
			}
			else{ // We need to move x to find more space which we need to fill.
				if (abs(x-x1) < abs(x2 - x)) {
					temp_dir = 1;
					x = x1 + temp_dir;
				}
				else {
					temp_dir = -1;
					x = x2 + temp_dir;
				}
				bool flag = false;
				// Try to find more space to fill.
				while (x != x2 && x != x1){
					if (oledGetPixel(x, y + vert_step) == oledGetColorDraw()) flag = true;
					else if(flag == true) break;
					x += temp_dir;
				}
				// Change vertical direction of filling.
				if (x == x2 || x == x1){
					if (vert_dir == -1){
						vert_dir = 1;
						vert_step = 1;
						x = x_temp;
					}
					else { // Stops filling.
						vert_dir = 0;
					}
				}
			}
		}
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

void oledFillV2(uint8_t x, uint8_t y){
	if (oledGetPixel(x, y) != oledGetColorDraw()){
		// Goes up and down from a given point.
		int8_t vert_dir = -1;
		int8_t vert_step = 0;
		// To save first x coor.
		uint8_t x_temp = x;
		// Goes left and right from a point.
		int8_t hor_dir, hor_step;
		// Coords of the leftmost and rightmost points of space at Y.
		uint8_t x1, x2;
		// Horizontal direction if we need to move x coord.
		int8_t temp_dir;
		while (vert_dir != 0){
			if (oledGetPixel(x, y + vert_step) != oledGetColorDraw()){
				hor_dir = 1;
				hor_step = 0;
			}
		}
	}

}
