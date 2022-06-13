#pragma once



struct coords {
	double x, y;
};


/* Basic function that returns x coordination relative to the camera
\param Cam - Rectangle of the camera
\param map - coordinates of the object
*/
int toCamCordX(SDL_Rect Cam, coords map);


/* Basic function that returns y coordination relative to the camera
\param Cam - Rectangle of the camera
\param map - coordinates of the object
*/
int toCamCordY(SDL_Rect Cam, coords map);