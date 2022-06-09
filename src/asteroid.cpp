#include "engine.h"
#include "asteroid.h"
#include "SDL_image.h"
#include <stdlib.h>
#include <stdio.h>


//=============================================================================
asteroid::asteroid(float x, float y, int w, int h, char* material) {
	shell = { SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h};
	position = { x, y };
	resource = material;
}