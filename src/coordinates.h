#pragma once



struct coords {
	double x, y;
};


/* Basic functiion to give you x and y values relative to the camera
\param Cam - Rectangle of the camera
\param x, y - coordinates of the object
*/
void toCamCords(SDL_Rect Cam, int* x, int* y);


/* Basic functiion to give you x and y values relative to the map
\param Cam - Rectangle of the camera
\param x, y - coordinates of the object
*/
void toMapCords(SDL_Rect Cam, int* x, int* y);