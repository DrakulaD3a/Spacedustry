#pragma once
#include "coordinates.h"
#include "SDL.h"

struct asteroid {
	SDL_Rect shell;
	coords position;
	char resource[16];
	char building[16];
};