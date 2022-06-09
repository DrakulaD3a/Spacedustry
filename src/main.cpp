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

SDL_Point mouse;
Player player = { { WW / 2, WH / 2, 64, 64 }, 4, WW / 2 - player.shell.w / 2 , WH / 2 - player.shell.h / 2 };
asteroid a1(10, 12, 64, 64, "Fe", "assets/meteor1.png");
SDL_Rect background = { -960, -540, 2 * 3840, 2 * 2160 };
SDL_Texture* Backgroung;
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


	//movement
	if (IsKeyDown(SDL_SCANCODE_W))
	{
		player.y -= player.speed;
		if (player.y <= 200)
		{
			background.y += player.speed; player.y += (float)player.speed / (player.y / 100 + 1);
		}
	}
	if (IsKeyDown(SDL_SCANCODE_A))
	{
		player.x -= player.speed;
		if (player.x <= 400)
		{
			background.x += player.speed; player.x += (float)player.speed / (player.x / 200 + 1);
		}
	}
	if (IsKeyDown(SDL_SCANCODE_S))
	{
		player.y += player.speed;
		if (WH - (player.y + player.shell.h) <= 200)
		{
			background.y -= player.speed; player.y -= (float)player.speed / ((WH - (player.y + player.shell.h)) / 100 + 1);
		}
	}
	if (IsKeyDown(SDL_SCANCODE_D))
	{
		player.x += player.speed;
		if (WW - (player.x + player.shell.w) <= 400)
		{
			background.x -= player.speed; player.x -= (float)player.speed / ((WW - (player.x + player.shell.w)) / 200 + 1);
		}
	}
	if(IsKeyReleased(SDL_SCANCODE_W) || IsKeyReleased(SDL_SCANCODE_A) || IsKeyReleased(SDL_SCANCODE_S) || IsKeyReleased(SDL_SCANCODE_D))
		timer = time(NULL) + 0.5;
	//camera control
	if (!IsKeyDown(SDL_SCANCODE_W) && player.y + player.shell.h / 2 <= WH / 2)
	{
		if (time(NULL) > timer)
		{
			player.y += player.speed; background.y += player.speed;
		}
	}
	if (!IsKeyDown(SDL_SCANCODE_A) && player.x + player.shell.w / 2 <= WW / 2)
	{
		if (time(NULL) > timer)
		{
			player.x += player.speed; background.x += player.speed;
		}
	}
	if (!IsKeyDown(SDL_SCANCODE_S) && player.y + player.shell.h / 2 >= WH / 2)
	{
		if (time(NULL) > timer)
		{
			player.y -= player.speed; background.y -= player.speed;
		}
	}
	if (!IsKeyDown(SDL_SCANCODE_D) && player.x + player.shell.w / 2 >= WW / 2)
	{
		if (time(NULL) > timer)
		{
			player.x -= player.speed; background.x -= player.speed;
		}
	}



	
	player.shell.x = player.x;
	player.shell.y = player.y;
}

void RenderFrame(float interpolation)
{
	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 65, 105, 225, 255);
	SDL_RenderClear(gRenderer);

	SDL_RenderCopy(gRenderer, Backgroung, 0, &background);

	SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
	SDL_RenderFillRect(gRenderer, &player.shell);
}