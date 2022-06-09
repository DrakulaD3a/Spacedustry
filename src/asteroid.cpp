#include "engine.h"
#include "asteroid.h"
#include "SDL_image.h"
#include <stdlib.h>
#include <stdio.h>


//=============================================================================
asteroid::asteroid(float x, float y, int w, int h, char* material, const char* path) {
	shell = { SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h};
	position = { x, y };
	resource = material;

	if(path != NULL)
		texture = IMG_LoadTexture(gRenderer, path);

	
	
}