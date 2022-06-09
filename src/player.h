#pragma once
#include "SDL.H"

class Player {
public:
	SDL_Rect shell;
	int speed;
	double x, y;
};