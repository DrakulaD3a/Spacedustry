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
		if (rotation >= 0 && rotation < 90)
		{
			position.x += sin(rotation * M_PI / 180) * speed;
			position.y -= cos(rotation * M_PI / 180) * speed;
		}
		else if (rotation >= 90 && rotation < 180)
		{
			position.x += sin(rotation * M_PI / 180) * speed;
			position.y -= cos(rotation * M_PI / 180) * speed;
		}
		else if (rotation >= 180 && rotation < 270)
		{
			position.x += sin(rotation * M_PI / 180) * speed;
			position.y -= cos(rotation * M_PI / 180) * speed;
		}
		else if (rotation >= 270 && rotation < 360)
		{
			position.x += sin(rotation * M_PI / 180) * speed;
			position.y -= cos(rotation * M_PI / 180) * speed;
		}
	}
	else if (dir == 'R') 
	{
		if (rotation >= 0 && rotation < 90)
		{
			position.x -= sin(rotation * M_PI / 180) * speed;
			position.y += cos(rotation * M_PI / 180) * speed;
		}
		else if (rotation >= 90 && rotation < 180)
		{
			position.x -= sin(rotation * M_PI / 180) * speed;
			position.y += cos(rotation * M_PI / 180) * speed;
		}
		else if (rotation >= 180 && rotation < 270)
		{
			position.x -= sin(rotation * M_PI / 180) * speed;
			position.y += cos(rotation * M_PI / 180) * speed;
		}
		else if (rotation >= 270 && rotation < 360)
		{
			position.x -= sin(rotation * M_PI / 180) * speed;
			position.y += cos(rotation * M_PI / 180) * speed;
		}
	}
	else
	{
		fprintf(stderr, "You want to move in unexisting direction.");
	}
	shell.x = position.x;
	shell.y = position.y;
}