#include "stdafx.h"
#include "Gremlin.h"
#include "Camera.h"
#include "PlayerGore.h"
#include "Gore.h"
#include "Explosion.h"
#include "Level.h"
#include "Spark.h"
#include "SoundMeta.h"
#include "Bullet.h"
#include "Screen.h"

int Gremlin::MAX_TEMPERATURE = 80 * 5;


Gremlin::Gremlin (int power, int x, int y) 
{
  temperature = 0;
	power = 0;
  jumpDelay = 0;

	this->power = power;
	this->x = x;
	this->y = y;
	w = 30;
	h = 30;
	bounce = 0;
}

void Gremlin::tick () 
{
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
	xa *= 0.4;
	ya *= level->FRICTION;
	ya += level->GRAVITY;

	if (onGround) 
  {
		if (power == 1 && jumpDelay <= 19) 
    {
			if (jumpDelay % 2 == 0) 
      {
				if (jumpDelay % 4 == 0) 
        {
					//SoundMeta::hit->play();
				}
				double dir = jumpDelay / 32.0f * MathUtils::PI * 2 + 0.1;
				double xa = MathUtils::cos(dir);
				double ya = -MathUtils::sin(dir);
				level->add(new Bullet(this, x + 15, y + 10, xa, ya));
			}
		}
		if (jumpDelay++ > 60) 
    {
			ya = -2;
			jumpDelay = 0;
		}
	}

	std::vector<Entity*> entities = level->getEntities((int)x + 4, (int)y + 4, w - 8, h - 4);
	for (int i = 0; i < entities.size(); i++) 
  {
		entities[i]->collideMonster(this);
	}
}

void Gremlin::render (Screen* g, Camera* camera) 
{
	int xp = (int)x;
	int yp = (int)y;
	if (onGround) 
  {
		g->draw(Art::gremlins[0][power], xp, yp);
	} 
  else 
  {
		g->draw(Art::gremlins[ya > 0 ? 2 : 1][power], xp, yp);
	}
	// FIXME
// g.setColor(Color.BLACK);
// g.fillRect(xp + 5, yp - 8, 20, 3);
// g.setColor(Color.RED);
// g.fillRect(xp + 5, yp - 8, 20 - (20 * temperature / MAX_TEMPERATURE), 2);
}

void Gremlin::hitSpikes () 
{
	die();
}

void Gremlin::die () 
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

bool Gremlin::shot (Bullet* bullet) 
{
	//SoundMeta::pew->play();
	for (int i = 0; i < 4; i++) 
  {
		double xd = (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 4 - bullet->xa * 3;
		double yd = (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 4 - bullet->ya * 3;
		level->add(new Gore(bullet->x, bullet->y, xa + xd, ya + yd));
	}
	//SoundMeta::oof->play();
	temperature += 80;
	if (temperature >= MAX_TEMPERATURE) 
  {
		die();
	} 
  else 
  {
		level->add(new PlayerGore(bullet->x, bullet->y));
	}

	return true;
}

void Gremlin::explode (Explosion* explosion) 
{
	die();
}