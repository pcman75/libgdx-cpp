#include "stdafx.h"
#include "Explosion.h"
#include "Screen.h"
#include "Camera.h"
#include "Level.h"


Explosion::Explosion (int power, int delay, double x, double y, double xa, double ya) 
{
  this->delay = delay;
	this->power = power;
	this->x = x;
	this->y = y;
	this->w = 1;
	this->h = 1;
	bounce = 0.2;
	this->xa = (xa + (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 0.2);
	this->ya = (ya + (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 0.2);

	color = MathUtils::random(3);

	duration = MathUtils::random(20) + 10;
	life = 0;
}

void Explosion::tick () 
{
	if (delay > 0) 
  {
		delay--;
		return;
	}
	if (life++ >= duration) remove();
	interactsWithWorld = (life > 10);
	onGround = false;
	// tryMove(xa, ya);
	x += xa;
	y += ya;

	level->isFree(this, x, y, w, h, 0, 0);
	xa *= 0.95;
	ya *= 0.95;
	ya -= Level::GRAVITY * 0.15;

	if (interactsWithWorld && life < duration * 0.75) 
  {
		std::vector<Entity*> entities = level->getEntities((int)x, (int)y, 1, 1);
		for (int i = 0; i < entities.size(); i++) 
    {
			entities[i]->explode(this);
		}
	}
}

void Explosion::hitWall (double xa, double ya) 
{
	this->xa *= 0.4;
	this->ya *= 0.4;
}

void Explosion::render (Screen* g, Camera* camera) 
{
	int xp = (int)x;
	int yp = (int)y;
	g->draw(Art::guys[(life - 1) * 8 / duration][4 + color], xp - 3, yp - 3);
}