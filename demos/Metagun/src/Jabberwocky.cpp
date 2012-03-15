#include "stdafx.h"
#include "Jabberwocky.h"
#include "Level.h"
#include "SoundMeta.h"
#include "Spark.h"
#include "Art.h"
#include "Explosion.h"
#include "PlayerGore.h"
#include "Gunner.h"
#include "Screen.h"

int Jabberwocky::MAX_TEMPERATURE = 80 * 5;

Jabberwocky::Jabberwocky (int x, int y) 
{
  temperature = 0;
  slamTime = 0;
	this->x = x;
	this->y = y;
	w = 30;
	h = 20;
	bounce = 0;
}

void Jabberwocky::tick () 
{
	slamTime++;
	if (temperature > 0) 
  {
		temperature--;
		for (int i = 0; i < 1; i++) 
    {
			if (MathUtils::random(MAX_TEMPERATURE) <= temperature) 
      {
				double xd = (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 0.2;
				double yd = (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 0.2;
				level->add(new Spark(x + MathUtils::randomFloat(1) * w, y + MathUtils::randomFloat(1) * h, xa * 0.2 + xd, ya * 0.2 + yd));
			}
		}
	}
	tryMove(xa, ya);
	xa *= Level::FRICTION;
	ya *= Level::FRICTION;
	ya += Level::GRAVITY;

	std::vector<Entity*> entities = level->getEntities((int)x + 4, (int)y + 4, w - 8, h - 4);
	for (int i = 0; i < entities.size(); i++) 
  {
		Entity* e = entities[i];
    Gunner* gunner = dynamic_cast<Gunner*>( e);
		if (gunner) 
    {
			temperature += 10;
			if (temperature >= MAX_TEMPERATURE) 
      {
				die();
			}
		}
		e->collideMonster(this);
	}
}

void Jabberwocky::render (Screen* g, Camera* camera) 
{
	int xp = (int)x;
	int yp = (int)y - 10;
	g->draw(Art::gremlins[3 + (slamTime / 10 % 5 == 2 ? 1 : 0)][0], xp, yp);
	// FIXME
// g.setColor(Color.BLACK);
// yp+=10;
// g.fillRect(xp + 5, yp - 8, 20, 3);
// g.setColor(Color.RED);
// g.fillRect(xp + 5, yp - 8, (20 * temperature / MAX_TEMPERATURE), 2);
}

void Jabberwocky::hitSpikes () 
{
	die();
}

void Jabberwocky::die () 
{
	//SoundMeta::death->play();
	for (int i = 0; i < 16; i++) 
  {
		level->add(new PlayerGore(x + MathUtils::randomFloat(1) * w, y + MathUtils::randomFloat(1) * h));
	}
	//SoundMeta::boom->play();
	for (int i = 0; i < 32; i++) 
  {
		double dir = i * MathUtils::PI * 2 / 8.0;
		double xa = MathUtils::sin(dir);
		double ya = MathUtils::cos(dir);
		double dist = ((i / 8) + 1);
		level->add(new Explosion(0, i * 3, x + w / 2 + xa * dist, y + h / 2 + ya * dist, xa, ya));
	}
	remove();
}

bool Jabberwocky::shot (Bullet* bullet) 
{
	return true;
}

void Jabberwocky::explode (Explosion* explosion) 
{
	die();
}