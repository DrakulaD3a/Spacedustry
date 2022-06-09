#pragma once
#include "coordinates.h"

class Player {
public:
	SDL_Rect shell;
	coords position;
	int speed, rotation;
	float x, y;


	/* Initializes this player
	\param x, y - coordinates of the player
	\param w, h - width and height of the player
	*/
	Player(float x, float y, int w, int h);
};