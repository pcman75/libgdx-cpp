#include "stdafx.h"
#include "Gunner.h"
#include "Screen.h"
#include "Camera.h"
#include "Bullet.h"
#include "Gunner.h"
#include "Level.h"
#include "HeadGore.h"
#include "Gore.h"
#include "SoundMeta.h"
#include "Player.h"

int Gunner::CHARGE_DURATION = 100;

Gunner::Gunner (double x, double y, double xa, double ya) 
{
  sliding = 0;
  chargeTime = 0;
	this->x = x;
	this->y = y;
	this->w = 6;
	this->h = 6;
	bounce = -0.1;
	this->xa = xa + (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 0.5;
	this->ya = ya + (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 0.5;
}

void Gunner::tick () 
{
	onGround = false;
	tryMove(xa, ya);

	if ((onGround || sliding != 0) && xa * xa < 0.01) 
  {
		if (chargeTime++ >= CHARGE_DURATION) 
    {
			chargeTime = 0;
			double xd = (level->player->x + level->player->w / 2) - (x + w / 2);
			double yd = (level->player->y + level->player->h / 2) - (y + h / 2);
			double dd = sqrt(xd * xd + yd * yd);
			xd /= dd;
			yd /= dd;
			//SoundMeta::hit->play();
			level->add(new Bullet(this, x + 2, y + 2, xd, yd));
		}
	}
	xa *= level->FRICTION;
	ya *= level->FRICTION;
	ya += level->GRAVITY;
}

void Gunner::hitWall (double xa, double ya) 
{
	sliding = 0;
	if (xa != 0) 
  {
		if (xa > 0) 
    {
			this->xa = 1;
			sliding = 1;
		}
		if (xa < 0) 
    {
			this->xa = -1;
			sliding = -1;
		}
	}
	this->xa *= 0.4;
	this->ya *= 0.4;
}

void Gunner::render (Screen* g, Camera* camera) 
{
	// g->setColor(Color.red);
	int xp = (int)x;
	int yp = (int)y;
	// g->fillRect(xp, yp, w, h);

	int xFrame = 0;
	int yFrame = 0;
	if (onGround) 
  {
		double xd = (level->player->x + level->player->w / 2) - (x + w / 2);
		double yd = (level->player->y + level->player->h / 2) - (y + h / 2);
		double dd = sqrt(xd * xd + yd * yd);
		xd /= dd;
		yd /= dd;
		xFrame = 3;
		yFrame = 2;
		double s = 0.3;
		if (xd > s) xFrame++;
		if (xd < -s) xFrame--;
		if (yd > s) yFrame++;
		if (yd < -s) yFrame--;
	} 
  else if (sliding != 0) 
  {
		double xd = (level->player->x + level->player->w / 2) - (x + w / 2);
		double yd = (level->player->y + level->player->h / 2) - (y + h / 2);
		double dd = sqrt(xd * xd + yd * yd);
		xd /= dd;
		yd /= dd;
		xFrame = 0;
		yFrame = 2;
		if (sliding > 0) xFrame = 1;
		double s = 0.3;
		if (yd > s) yFrame++;
		if (yd < -s) yFrame--;
	} 
  else 
  {
		xFrame = (int)(1 - floor(ya * 0.1));
		if (xFrame < 0) xFrame = 0;
		if (xFrame > 2) xFrame = 2;
		yFrame = 0;
	}

	g->draw( Art::guys[xFrame][yFrame], xp, yp);

	std::vector<Entity*> entities = level->getEntities((int)x, (int)y, 1, 1);
	for (int i = 0; i < entities.size(); i++) 
  {
		entities[i]->shove(this);
	}
}

bool Gunner::shot (Bullet* bullet) 
{
	die();
	return true;
}

void Gunner::hitSpikes () 
{
	die();
}

void Gunner::die () 
{
	//SoundMeta::splat->play();
	level->add(new HeadGore(x + 2, y));
	for (int i = 0; i < 10; i++) {
		double xd = (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 4;
		double yd = (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 4;

		level->add(new Gore(x + 2 + MathUtils::randomFloat(1), y + MathUtils::randomFloat(1) * 6, xa + xd, ya + yd));
	}
	remove();
}

void Gunner::shove (Gunner* enemy) 
{

	double xd = enemy->x - x;
	if (xd < 0) 
  {
		xd = -0.01;
	} 
  else if (xd > 0) 
  {
		xd = 0.01;
	} 
  else 
  {
		if (MathUtils::random( 1)) 
    {
			xd = -0.01;
		} 
    else 
    {
			xd = 0.01;
		}
	}

	enemy->xa += xd;
	xa -= xd;
}

void Gunner::explode (Explosion* explosion) 
{
	die();
}

void Gunner::collideMonster (Entity* e) 
{
	die();
}