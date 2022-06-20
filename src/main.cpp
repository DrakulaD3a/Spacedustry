#include "engine.h"
#include "asteroid.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// Forward function declarations
void Update(float dt);
void RenderFrame(float dt);
void loadAssets();
void updatePositions();

#define WW 1920
#define WH 1080
#define cameraSpeed 240
#define numOfAteroids 32

struct Build {
	SDL_Rect shell;
	bool shown;
};

unsigned int copper = 0, iron = 0, tungsten = 0, gold = 0;



Build buildmenu = { { -999, -999, 128, 256 }, false };
SDL_Rect button1 = { -999, -999, 96, 96 };
SDL_Rect button2 = { -999, -999, 96, 16 };
asteroid a[numOfAteroids];
SDL_Point mouse;
SDL_Rect building[numOfAteroids];
SDL_Rect background = { 0, 0, 3840, 2160 };
SDL_Rect Camera = { background.x / 2, background.y / 2, WW, WH };
SDL_Texture *a1_texture, *backgroung_texture, *cursor_texture;


//=============================================================================
int main(int argc, char* argv[])
{
	srand(time(NULL));
	if (!InitSDL())
	{
		return 1;
	}

	if (!CreateWindow("The Game", WW, WH))
	{
		return 1;
	}


	for(int i = 0; i < numOfAteroids; i++)
	{
		double x = rand() % 3774, y = rand() % 2094;
		a[i] = {{ 0, 0, 64, 64 }, { x, y }, "Fe", "none", false};
	}

	loadAssets();

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
	if (!buildmenu.shown)
	{
		if (IsKeyDown(SDL_SCANCODE_W))
			Camera.y -= cameraSpeed * dt;
		if (IsKeyDown(SDL_SCANCODE_A))
			Camera.x -= cameraSpeed * dt;
		if (IsKeyDown(SDL_SCANCODE_S))
			Camera.y += cameraSpeed * dt;
		if (IsKeyDown(SDL_SCANCODE_D))
			Camera.x += cameraSpeed * dt;
	}

	for (int i = 0; i < numOfAteroids; i++)
	{
		if (SDL_PointInRect(&mouse, &buildmenu.shell))
		{
			if (IsMousePressed(SDL_BUTTON_LMASK) && a[i].clicked)
			{
				if (SDL_PointInRect(&mouse, &button1))
				{
					strcpy(a[i].building, "miner");
					building[i] = { a[i].shell.x + a[i].shell.w / 2, a[i].shell.y + a[i].shell.h / 2 , 32, 32 };
					a[i].clicked = false;
					buildmenu.shown = false;
					buildmenu.shell.x = -999;
					button1.x = -999;
					button2.x = -999;
				}
				else if (SDL_PointInRect(&mouse, &button2))
				{
					strcpy(a[i].building, "none");
					a[i].clicked = false;
					buildmenu.shown = false;
					buildmenu.shell.x = -999;
					button1.x = -999;
					button2.x = -999;
				}
			}
		}
		else if (SDL_PointInRect(&mouse, &a[i].shell))
		{
			if (IsMousePressed(SDL_BUTTON_LMASK))
			{
				a[i].clicked = true;
				buildmenu.shown = true;
				buildmenu.shell.x = mouse.x;
				buildmenu.shell.y = mouse.y;
				button1.x = buildmenu.shell.x + 16;
				button1.y = buildmenu.shell.y + 16;
				button2.x = buildmenu.shell.x + 16;
				button2.y = buildmenu.shell.y + 224;
			}
		}
		else
		{
			a[i].clicked = false;
			buildmenu.shown = false;
			buildmenu.shell.x = -999;
			button1.x = -999;
			button2.x = -999;
		}
	}
	updatePositions();
}


//=============================================================================
void RenderFrame(float interpolation)
{
	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 65, 105, 225, 255);
	SDL_RenderClear(gRenderer);

	//rendering background
	SDL_RenderCopy(gRenderer, backgroung_texture, 0, &background);

	//rendering miner on meteor
	for (int i = 0; i < numOfAteroids; i++)
	{
		SDL_RenderCopy(gRenderer, a1_texture, 0, &a[i].shell);
		if (strcmp(a[i].building, "miner") == 0)
		{
			SDL_SetRenderDrawColor(gRenderer, 225, 0, 0, 255);
			SDL_RenderFillRect(gRenderer, &building[i]);
		}
	}

	//rendering menu
	if (buildmenu.shown)
	{
		SDL_SetRenderDrawColor(gRenderer, 225, 225, 225, 255);
		SDL_RenderFillRect(gRenderer, &buildmenu.shell);

		SDL_SetRenderDrawColor(gRenderer, 225, 0, 0, 255);
		SDL_RenderFillRect(gRenderer, &button1);
		SDL_SetRenderDrawColor(gRenderer, 225, 255, 0, 255);
		SDL_RenderFillRect(gRenderer, &button2);
	}

	
}

//=============================================================================
void loadAssets() {
	a1_texture = IMG_LoadTexture(gRenderer, "assets/Meteor1.png");
	backgroung_texture = IMG_LoadTexture(gRenderer, "assets/Background.png");
}

//=============================================================================
void updatePositions() {
	toCamCords(Camera, { 0, 0 }, &background.x, &background.y);
	for (int i = 0; i < numOfAteroids; i++)
	{
		toCamCords(Camera, a[i].position, &a[i].shell.x, &a[i].shell.y);
		toCamCords(Camera, a[i].position, &building[i].x, &building[i].y);
	}
}