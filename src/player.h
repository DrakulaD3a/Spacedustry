#pragma once
#include "SDL.H"

struct Player {
	SDL_Rect shell;
	int speed;
	double x, y;
};