#pragma once
#include "coordinates.h"

class Player {
public:
	SDL_Rect shell;
	coords position;
	int speed, rotation;
	SDL_Point centre;


	/* Initializes this player
	\param x, y - coordinates of the player
	\param w, h - width and height of the player
	\param path - path to the picture
	*/
	Player(float x, float y, int w, int h);
};