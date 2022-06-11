#include "engine.h"
#include "coordinates.h"
#include <stdlib.h>
#include <stdio.h>


//=============================================================================
void toCamCords(SDL_Rect Cam, double* x, double* y) {
	*x -= Cam.x;
	*y -= Cam.y;
}


//=============================================================================
void toMapCords(SDL_Rect Cam, double* x, double* y) {
	*x += Cam.x;
	*y += Cam.y;
}