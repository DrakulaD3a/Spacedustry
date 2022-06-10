#include "engine.h"
#include "player.h"
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

#define WW 1920
#define WH 1080

Player player(WW / 2 + 64, WH / 2 + 128, 128, 256);
asteroid a1(10, 12, 64, 64, "Fe");
SDL_Point mouse;
SDL_Rect Camera = { 0, 0, WW, WH };
SDL_Rect background = { -960, -540, 2 * 3840, 2 * 2160 };
SDL_Texture *player_texture, *a1_texture, *Backgroung;
time_t timer = time(NULL) + 0.5;

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


	player_texture = IMG_LoadTexture(gRenderer, "assets/Spaceship.png");
	a1_texture = IMG_LoadTexture(gRenderer, "assets/meteor1.png");
	Backgroung = IMG_LoadTexture(gRenderer, "assets/Background.png");

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
	{
		player.move('F');
	}
	if (IsKeyDown(SDL_SCANCODE_S))
	{
		player.move('R');
	}
	if (IsKeyDown(SDL_SCANCODE_A))
	{
		player.rotation -= player.speedOfRotating;
	}
	if (IsKeyDown(SDL_SCANCODE_D))
	{
		player.rotation += player.speedOfRotating;
	}


	if (player.rotation >= 360)
		player.rotation -= 360;
	if (player.rotation <= -360)
		player.rotation += 360;
	player.shell.x = player.position.x;
	player.shell.y = player.position.y;
}

void RenderFrame(float interpolation)
{
	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 65, 105, 225, 255);
	SDL_RenderClear(gRenderer);

	SDL_RenderCopy(gRenderer, Backgroung, 0, &background);

	SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
	SDL_RenderCopyEx(gRenderer, player_texture, 0, &player.shell, player.rotation, &player.centre, SDL_FLIP_NONE);
}