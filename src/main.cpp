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
Player player = { { WW / 2, WH / 2, 64, 64 }, 2 };
SDL_Rect background = { -960, -540, 3840, 2160 };
Sprite Backgroung;

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

	Backgroung = LoadSprite("assets/Background.png");

	player.x = WW / 2; player.y = WH / 2;

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
			background.y++; player.y += (float)player.speed / (player.y / 100 + 1);
		}
	}
	if (IsKeyDown(SDL_SCANCODE_A))
	{
		player.x -= player.speed;
		if (player.x <= 200)
		{
			background.x++; player.x += (float)player.speed / (player.x / 100 + 1);
		}
	}
	if (IsKeyDown(SDL_SCANCODE_S))
	{
		player.y += player.speed;
		if (WH - (player.y + player.shell.h) <= 200)
		{
			background.y--; player.y -= (float)player.speed / ((WH - (player.y + player.shell.h)) / 100 + 1);
		}
	}
	if (IsKeyDown(SDL_SCANCODE_D))
	{
		player.x += player.speed;
		if (WW - (player.x + player.shell.w) <= 200)
		{
			background.x--; player.x -= (float)player.speed / ((WW - (player.x + player.shell.w)) / 100 + 1);
		}
	}
	//camera control
	if (!IsKeyDown(SDL_SCANCODE_W) && player.y + player.shell.h / 2 <= WH / 2)
	{
		player.y++; background.y++;
	}
	if (!IsKeyDown(SDL_SCANCODE_A) && player.x + player.shell.w / 2 <= WW / 2)
	{
		player.x++; background.x++;
	}
	if (!IsKeyDown(SDL_SCANCODE_S) && player.y + player.shell.h / 2 >= WH / 2)
	{
		player.y--; background.y--;
	}
	if (!IsKeyDown(SDL_SCANCODE_D) && player.x + player.shell.w / 2 <= WW / 2)
	{
		player.x--; background.x--;
	}


	
	player.shell.x = player.x;
	player.shell.y = player.y;
}

void RenderFrame(float interpolation)
{
	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 65, 105, 225, 255);
	SDL_RenderClear(gRenderer);

	SDL_RenderCopy(gRenderer, Backgroung.texture, 0, &background);

	SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
	SDL_RenderFillRect(gRenderer, &player.shell);
}