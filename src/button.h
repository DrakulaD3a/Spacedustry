#pragma once
#include "SDL.h"
#include <stdbool.h>

struct Button {
	SDL_Rect shell;
	bool shown = false;
};