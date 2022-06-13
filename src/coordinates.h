#pragma once



struct coords {
	double x, y;
};


/* Basic function that returns x coordination relative to the camera
\param Cam - Rectangle of the camera
\param map - coordinates of the object
*/
void toCamCords(SDL_Rect Cam, coords map, int *x, int *y);