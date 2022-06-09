#pragma once
#include "coordinates.h"
#include "SDL.h"

class asteroid {
public:
	SDL_Rect shell;
	coords position;
	char* resource;
	SDL_Texture* texture = NULL;

	/* Initializes this object
	\param rect - rectangle of this object
	\param x, y - coordinations of this obj relative to the map
	\param material - Material on this asteroid, NULL for no material
	\param path - Path to the sprite
	*/
	asteroid(float x, float y, int w, int h, char* material);



};