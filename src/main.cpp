#include "engine.h"
#include "sprite.h"
#include "player.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Forward function declarations
void Update(float dt);
void RenderFrame(float dt);

#define WW 1920
#define WH 1080

SDL_Point mouse;
Player player = { {WW / 2,WH / 2,64,64}, 2 };

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

	// Push functions to the game loop
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
		player.shell.y -= player.speed;
	if (IsKeyDown(SDL_SCANCODE_A))
		player.shell.x -= player.speed;
	if (IsKeyDown(SDL_SCANCODE_S))
		player.shell.y += player.speed;
	if (IsKeyDown(SDL_SCANCODE_D))
		player.shell.x += player.speed;




}

void RenderFrame(float interpolation)
{
	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 65, 105, 225, 255);
	SDL_RenderClear(gRenderer);

	SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
	SDL_RenderFillRect(gRenderer, &player.shell);
}