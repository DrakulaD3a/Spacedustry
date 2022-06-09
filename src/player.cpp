#include "engine.h"
#include "player.h"
#include <stdlib.h>
#include <stdio.h>


//=============================================================================
Player::Player(float x, float y, int w, int h) {
	shell = { (int)x, (int)y, w, h };
	position = { x, y };
	speed = 2;
	rotation = 0;
}