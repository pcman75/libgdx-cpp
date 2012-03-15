#include "stdafx.h"
#include "PlayerGore.h"
#include "Level.h"
#include "Gore.h"
#include "Art.h"
#include "Screen.h"

PlayerGore::PlayerGore (double x, double y) 
{
	this->x = x;
	this->y = y;
	this->w = 2;
	this->h = 2;
	bounce = 0.8;
	this->xa = 0 + (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 1.5;
	this->ya = -1 + (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 1.5;

	life = MathUtils::random(90) + 60;
}

void PlayerGore::tick () 
{
	if (life-- <= 0) remove();
	onGround = false;
	tryMove(xa, ya);

	xa *= Level::FRICTION;
	ya *= Level::FRICTION;
	ya += Level::GRAVITY * 0.5;
	level->add(new Gore(x + MathUtils::randomFloat(1), y + MathUtils::randomFloat(1) - 1, xa, ya));
}

void PlayerGore::hitWall (double xa, double ya) 
{
	this->xa *= 0.9;
	this->ya *= 0.9;
}

void PlayerGore::render (Screen* g, Camera* camera) 
{
	int xp = (int)x;
	int yp = (int)y;
	g->draw(Art::guys[6][1], xp, yp);
}

void PlayerGore::hitSpikes () 
{
	for (int i = 0; i < 4; i++) 
  {
		xa = (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 6;
		ya = (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 6;
		level->add(new Gore(x + MathUtils::randomFloat(1), y + MathUtils::randomFloat(1) - 1, xa, ya));
	}
	remove();
}

