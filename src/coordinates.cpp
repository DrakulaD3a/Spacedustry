#include "engine.h"
#include "coordinates.h"
#include <stdlib.h>
#include <stdio.h>


//=============================================================================
void toCamCords(SDL_Rect Cam, coords map, int* x, int* y) {
	*x = map.x - Cam.x;
	*y = map.y - Cam.y;
}