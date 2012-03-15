#include "stdafx.h"
#include "BossNeck.h"
#include "Bullet.h"
#include "Explosion.h"
#include "PlayerGore.h"
#include "Screen.h"

BossNeck::BossNeck (int x, int y, BossPart* child) 
{
  slamTime = 0;
	child = NULL;
	baseRot = MathUtils::PI * 1.25;
	rot = 0;
  rota = 0;
	time = 0;

  this->child = child;
	this->x = x;
	this->y = y;
	w = 12;
	h = 12;
	bounce = 0;
}

void BossNeck::tick () 
{
	if (dieIn > 0) 
  {
		if (--dieIn == 0) die();
	}
	time++;

	rot = MathUtils::sin(time / 40.0) * MathUtils::cos(time / 13.0) * 0.5;
	rota *= 0.9;
	rot *= 0.9;
	double rr = baseRot + rot;
	double xa = MathUtils::sin(rr);
	double ya = MathUtils::cos(rr);
	child->x = x + xa * 8;
	child->y = y + ya * 8;
	child->setRot(rr);

	std::vector<Entity*> entities = level->getEntities((int)x + 4, (int)y + 4, w - 8, h - 4);
	for (int i = 0; i < entities.size(); i++) 
  {
		entities[i]->collideMonster(this);
	}
}

void BossNeck::setRot (double rot) 
{
	baseRot = rot;
}

void BossNeck::render( Screen* screen, Camera* camera) 
{
	int xp = (int)x - 1;
	int yp = (int)y - 1;
	screen->draw( Art::gremlins[4][1], xp, yp);
}

void BossNeck::hitSpikes () 
{
	die();
}

void BossNeck::die () 
{
	child->dieIn = 5;
	for (int i = 0; i < 4; i++) 
  {
		level->add(new PlayerGore(x + MathUtils::randomFloat( 1) * w, y + MathUtils::randomFloat( 1) * h));
	}
	for (int i = 0; i < 4; i++) 
  {
		double dir = i * MathUtils::PI * 2 / 8.0;
		double xa = MathUtils::sin(dir);
		double ya = MathUtils::cos(dir);
		double dist = ((i / 8) + 1);
		level->add(new Explosion(1, i * 3, x + w / 2 + xa * dist, y + h / 2 + ya * dist, xa, ya));
	}
	remove();
}

bool BossNeck::shot (Bullet* bullet) 
{
	return true;
}

void BossNeck::explode (Explosion* explosion) 
{
	if (explosion->power > 0) 
  {
		die();
	}
}