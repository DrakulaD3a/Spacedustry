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

Player player(WW / 2 + 32, WH / 2 + 64, 64, 128);
asteroid a1(10, 12, 64, 64, "Fe");
SDL_Point mouse;
SDL_Rect Camera = { 0, 0, WW, WH };
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


	player.texture = IMG_LoadTexture(gRenderer, "assets/Spaceship.png");
	a1.texture = IMG_LoadTexture(gRenderer, "assets/meteor1.png");
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
		player.position.y -= player.speed; player.rotation = 0;
		if (player.position.y <= 200)
		{
			background.y += player.speed; player.position.y += (float)player.speed / (player.position.y / 100 + 1);
		}
	}
	if (IsKeyDown(SDL_SCANCODE_A))
	{
		player.position.x -= player.speed; player.rotation = 270;
		if (player.position.x <= 400)
		{
			background.x += player.speed; player.position.x += (float)player.speed / (player.position.x / 200 + 1);
		}
	}
	if (IsKeyDown(SDL_SCANCODE_S))
	{
		player.position.y += player.speed; player.rotation = 180;
		if (WH - (player.position.y + player.shell.h) <= 200)
		{
			background.y -= player.speed; player.position.y -= (float)player.speed / ((WH - (player.position.y + player.shell.h)) / 100 + 1);
		}
	}
	if (IsKeyDown(SDL_SCANCODE_D))
	{
		player.position.x += player.speed; player.rotation = 90;
		if (WW - (player.position.x + player.shell.w) <= 400)
		{
			background.x -= player.speed; player.position.x -= (float)player.speed / ((WW - (player.position.x + player.shell.w)) / 200 + 1);
		}
	}
	if(IsKeyReleased(SDL_SCANCODE_W) || IsKeyReleased(SDL_SCANCODE_A) || IsKeyReleased(SDL_SCANCODE_S) || IsKeyReleased(SDL_SCANCODE_D))
		timer = time(NULL) + 0.5;
	//camera control
	if (!IsKeyDown(SDL_SCANCODE_W) && player.position.y + player.shell.h / 2 <= WH / 2)
	{
		if (time(NULL) > timer)
		{
			player.position.y += player.speed; background.y += player.speed;
		}
	}
	if (!IsKeyDown(SDL_SCANCODE_A) && player.position.x + player.shell.w / 2 <= WW / 2)
	{
		if (time(NULL) > timer)
		{
			player.position.x += player.speed; background.x += player.speed;
		}
	}
	if (!IsKeyDown(SDL_SCANCODE_S) && player.position.y + player.shell.h / 2 >= WH / 2)
	{
		if (time(NULL) > timer)
		{
			player.position.y -= player.speed; background.y -= player.speed;
		}
	}
	if (!IsKeyDown(SDL_SCANCODE_D) && player.position.x + player.shell.w / 2 >= WW / 2)
	{
		if (time(NULL) > timer)
		{
			player.position.x -= player.speed; background.x -= player.speed;
		}
	}



	
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
	SDL_RenderCopyEx(gRenderer, player.texture, 0, &player.shell, player.rotation, &player.centre, SDL_FLIP_NONE);
}