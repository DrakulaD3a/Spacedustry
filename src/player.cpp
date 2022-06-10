#include "engine.h"
#include "player.h"
#include "SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


//=============================================================================
Player::Player(float x, float y, int w, int h) {
	shell = { (int)x, (int)y, w, h };
	position = { x, y };
	speed = 2;
	rotation = 0;
	centre = { shell.w / 2, (int)(shell.h / 1.6) };
}


//=============================================================================
void Player::move(const char dir) {
	if (dir == 'F')
	{
		if (rotation < 90 && rotation > 0)
		{
			position.x -= sin(rotation) * speed;
			position.y += cos(rotation) * speed;
		}
	}
	else if (dir == 'R') 
	{
		if (rotation < 90 && rotation > 0)
		{
			position.x += sin(rotation) * speed;
			position.y -= cos(rotation) * speed;
		}
	}
	else
	{
		fprintf(stderr, "You want to move in unexisting direction.");
	}
}