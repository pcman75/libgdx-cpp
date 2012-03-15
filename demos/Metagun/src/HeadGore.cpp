#include "stdafx.h"
#include "HeadGore.h"
#include "Level.h"
#include "Gore.h"
#include "Screen.h"
#include "Art.h"

HeadGore::HeadGore (double x, double y) 
{
	this->x = x;
	this->y = y;
	this->w = 2;
	this->h = 2;
	bounce = 0.2;
	this->xa = 0 + (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 0.5;
	this->ya = -1 + (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 0.5;

	life = MathUtils::random(60) + 20;
}

void HeadGore::tick () 
{
	if (life-- <= 0) remove();
	onGround = false;
	tryMove(xa, ya);

	xa *= Level::FRICTION;
	ya *= Level::FRICTION;
	ya += Level::GRAVITY * 0.5;
	level->add(new Gore(x + MathUtils::randomFloat(1), y + MathUtils::randomFloat(1) - 1, xa, ya));
}

void HeadGore::hitWall (double xa, double ya) 
{
	this->xa *= 0.8;
	this->ya *= 0.8;
}

void HeadGore::render (Screen* g, Camera* camera) 
{
	int xp = (int)x;
	int yp = (int)y;
	g->draw(Art::guys[6][1], xp, yp);
}

void HeadGore::hitSpikes () 
{
	for (int i = 0; i < 4; i++) 
  {
    xa = (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 6;
		ya = (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 6;
		level->add( new Gore(x + MathUtils::randomFloat(1), y + MathUtils::randomFloat(1) - 1, xa, ya));
	}
	remove();
}
