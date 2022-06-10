#pragma once
#include "coordinates.h"

class Player {
public:
	SDL_Rect shell;
	coords position;
	int speed = 2, rotation, speedOfRotating = 2;
	SDL_Point centre;
	SDL_RendererFlip flip = SDL_FLIP_NONE;


	/* Initializes this player
	\param x, y - coordinates of the player
	\param w, h - width and height of the player
	\param path - path to the picture
	*/
	Player(float x, float y, int w, int h);


	/*Moves the player
	\param dir - direction of the move (F = forwards, R = Reverse)
	*/
	void move(const char dir);
};