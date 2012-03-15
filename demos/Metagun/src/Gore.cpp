#include "stdafx.h"
#include "Gore.h"
#include "Screen.h"
#include "Camera.h"
#include "Level.h"

Gore::Gore (double x, double y, double xa, double ya) 
{
	this->x = x;
	this->y = y;
	this->w = 1;
	this->h = 1;
	bounce = 0.2;
	this->xa = (xa + (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 1) * 0.2;
	this->ya = (ya + (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 1) * 0.2;

	life = MathUtils::random(20) + 10;
}

void Gore::tick () 
{
	if (life-- <= 0) remove();
	onGround = false;
	tryMove(xa, ya);

	xa *= 0.999;
	ya *= 0.999;
	ya += Level::GRAVITY * 0.15;
}

void Gore::hitWall (double xa, double ya) 
{
	this->xa *= 0.4;
	this->ya *= 0.4;
}

void Gore::render (Screen* g, Camera* camera) 
{
	int xp = (int)x;
	int yp = (int)y;
	g->draw(Art::guys[7][1], xp, yp);
}