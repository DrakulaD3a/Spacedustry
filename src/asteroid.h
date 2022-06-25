#pragma once
#include "coordinates.h"
#include "SDL.h"

class asteroid {
public:
	static enum building : short {
		None = 0, Miner
	};
	SDL_Rect shell;
	coords position;
	char resource[16];
	bool clicked;
	building build;

	void setBuild(building b) {
		build = b;
	}
};