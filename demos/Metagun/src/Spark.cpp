#include "stdafx.h"
#include "Spark.h"
#include "Level.h"
#include "Art.h"
#include "Screen.h"

Spark::Spark (double x, double y, double xa, double ya) 
{
	this->x = x;
	this->y = y;
	this->w = 1;
	this->h = 1;
	bounce = 0.2;
	//this->xa = (xa + (random.nextDouble() - random.nextDouble()) * 0.2);
  this->xa = (xa + (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 0.2);

	this->ya = (ya + (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 0.2);

  life = MathUtils::random(20) + 10;
}

void Spark::tick () 
{
	if (life-- <= 0) remove();
	onGround = false;
	tryMove(xa, ya);

	xa *= 0.999;
	ya *= 0.999;
	ya += Level::GRAVITY * 0.15;
}

void Spark::hitWall (double xa, double ya) 
{
	this->xa *= 0.4;
	this->ya *= 0.4;
}

void Spark::render (Screen* g, Camera* camera) 
{
	int xp = (int)x;
	int yp = (int)y;
	g->draw(Art::guys[9][1], xp, yp);
}

