#include "engine.h"
#include "asteroid.h"
#include "button.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

struct Build {
	SDL_Rect shell;
	bool shown = false;
};

// Forward function declarations
void Update(float dt);
void RenderFrame(float dt);
void updatePositions();

#define WW 1920
#define WH 1080
#define cameraSpeed 120

Build buildmenu = { 0, 0, 128, 256 };
Button bmbutton1 = { 0, 0, 128, 128 };
asteroid a1 = { { 0, 0, 64, 64 }, { 30, 30 }, "Fe", "\0"};
SDL_Point mouse;
SDL_Rect building{ a1.shell.x + a1.shell.w / 2, a1.shell.y + a1.shell.h / 2, 32, 32 };
SDL_Rect background = { 0, 0, 3840, 2160 };
SDL_Rect Camera = { background.x / 2, background.y / 2, WW, WH };
SDL_Texture *a1_texture, *backgroung_texture, *cursor_texture;


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
	backgroung_texture = IMG_LoadTexture(gRenderer, "assets/Background.png");

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

	//camera movement
	if (IsKeyDown(SDL_SCANCODE_W))
		Camera.y -= cameraSpeed * dt;
	if (IsKeyDown(SDL_SCANCODE_A))
		Camera.x -= cameraSpeed * dt;
	if (IsKeyDown(SDL_SCANCODE_S))
		Camera.y += cameraSpeed * dt;
	if (IsKeyDown(SDL_SCANCODE_D))
		Camera.x += cameraSpeed * dt;


	if (SDL_PointInRect(&mouse, &a1.shell) || SDL_PointInRect(&mouse, &buildmenu.shell))
	{	
		if (IsMousePressed(SDL_BUTTON_LMASK))
		{
			buildmenu.shown = true;
			bmbutton1.shown = true;
			buildmenu.shell.x = mouse.x;
			buildmenu.shell.y = mouse.y;
			bmbutton1.shell.x = buildmenu.shell.x;
			bmbutton1.shell.y = buildmenu.shell.y;
		}
		if (SDL_PointInRect(&mouse, &buildmenu.shell) && SDL_PointInRect(&mouse, &bmbutton1.shell))
		{
			strcpy(a1.building, "miner");
			buildmenu.shown = false;
			bmbutton1.shown = false;
		}
	}
	else
	{
		buildmenu.shown = false;
		bmbutton1.shown = false;
	}
	updatePositions();
}


//=============================================================================
void RenderFrame(float interpolation)
{
	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 65, 105, 225, 255);
	SDL_RenderClear(gRenderer);

	SDL_RenderCopy(gRenderer, backgroung_texture, 0, &background);

	SDL_RenderCopy(gRenderer, a1_texture, 0, &a1.shell);
	if (buildmenu.shown)
	{
		SDL_SetRenderDrawColor(gRenderer, 225, 225, 225, 255);
		SDL_RenderFillRect(gRenderer, &buildmenu.shell);
	}	
	if (bmbutton1.shown)
	{
		SDL_SetRenderDrawColor(gRenderer, 225, 0, 0, 255);
		SDL_RenderFillRect(gRenderer, &bmbutton1.shell);
	}
	if (a1.building == "miner")
	{
		SDL_SetRenderDrawColor(gRenderer, 225, 0, 0, 255);
		SDL_RenderFillRect(gRenderer, &building);
	}
}


//=============================================================================
void updatePositions() {
	toCamCords(Camera, { 0, 0 }, &background.x, &background.y);
	toCamCords(Camera, a1.position, &a1.shell.x, &a1.shell.y);
}