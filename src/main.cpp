#include "engine.h"
#include "asteroid.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// Forward function declarations
void Update(float dt);
void RenderFrame(float dt);
void updatePositions();

#define WW 1920
#define WH 1080

asteroid a1 = { { 0, 0, 64, 64 }, { 30, 30 }, "Fe" };
SDL_Point mouse;
SDL_Rect background = { 0, 0, 7680, 4320 };
SDL_Rect Camera = { background.x / 2, background.y / 2, WW, WH };
SDL_Texture *a1_texture, *Backgroung;


//=============================================================================
int main(int argc, char* argv[])
{
	if (!InitSDL())
	{
		return 1;
	}

	if (!CreateWindow("The Game", WW, WH))
	{
		return 1;
	}


	a1_texture = IMG_LoadTexture(gRenderer, "assets/Meteor1.png");
	Backgroung = IMG_LoadTexture(gRenderer, "assets/Background.png");

	SDL_ShowCursor(SDL_FALSE);

	StartLoop(Update, RenderFrame);

	CleanUp();
	return 0;
}

//=============================================================================
void Update(float dt)
{
	GetMousePosition(&mouse.x, &mouse.y);
	printf("%d %d\n", mouse.x, mouse.y);

	if (IsKeyDown(SDL_SCANCODE_ESCAPE))
		ExitGame();

	if (IsKeyDown(SDL_SCANCODE_W))
		Camera.y--;
	if (IsKeyDown(SDL_SCANCODE_A))
		Camera.x--;
	if (IsKeyDown(SDL_SCANCODE_S))
		Camera.y++;
	if (IsKeyDown(SDL_SCANCODE_D))
		Camera.x++;



	updatePositions();
}

//=============================================================================
void RenderFrame(float interpolation)
{
	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 65, 105, 225, 255);
	SDL_RenderClear(gRenderer);

	SDL_RenderCopy(gRenderer, Backgroung, 0, &background);

	SDL_RenderCopy(gRenderer, a1_texture, 0, &a1.shell);
}


void updatePositions() {
	toCamCords(Camera, { 0, 0 }, &background.x, &background.y);
	toCamCords(Camera, a1.position, &a1.shell.x, &a1.shell.y);
}