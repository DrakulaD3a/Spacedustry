#include "engine.h"
#include "coordinates.h"
#include <stdlib.h>
#include <stdio.h>


//=============================================================================
int toCamCordX(SDL_Rect Cam, coords map) {
	return map.x - Cam.x;
}


//=============================================================================
int toCamCordY(SDL_Rect Cam, coords map) {
	return map.y - Cam.y;
}