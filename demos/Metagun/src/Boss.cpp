#include "stdafx.h"
#include "Boss.h"
#include "Level.h"
#include "Explosion.h"
#include "Gunner.h"
#include "SoundMeta.h"
#include "Bullet.h"
#include "PlayerGore.h"
#include "Screen.h"
#include "Player.h"

int Boss::MAX_TEMPERATURE = 80 * 5;

Boss::Boss (int x, int y) 
{
  temperature = 0;
  time = 0;
  slamTime = 0;
	xo = yo = 0;


	this->x = x;
	this->y = y;
	w = 14;
	h = 14;
	bounce = 0;
}

void Boss::tick () 
{
	if (dieIn > 0) 
  {
		if (--dieIn == 0) die();
	}
	xa = x - xo;
	ya = y - yo;
	time++;
	if (time % 60 == 0) 
  {
		for (int i = 0; i < 16; i++) 
    {
			double xxa = MathUtils::sin(i * MathUtils::PI * 2 / 16);
			double yya = MathUtils::cos(i * MathUtils::PI * 2 / 16);
			level->add(new Gunner(x + xxa * 4, y + yya * 4, xa * 0.2 + xxa, ya * 0.2 + yya - 1));
		}
	} 
  else if (time % 60 > 20 && time % 60 < 40 && time % 4 == 0) 
  {
		double xd = (level->player->x + level->player->w / 2) - (x + w / 2);
		double yd = (level->player->y + level->player->h / 2) - (y + h / 2);
		double dd = sqrt(xd * xd + yd * yd);
		xd /= dd;
		yd /= dd;
		//SoundMeta::hit->play();
		level->add(new Bullet(this, x + 2, y + 2, xd, yd));
	}
	xo = x;
	yo = y;

	std::vector<Entity*> entities = level->getEntities((int)x + 4, (int)y + 4, w - 8, h - 4);
	for (int i = 0; i < entities.size(); i++) 
  {
		entities[i]->collideMonster(this);
	}
}

void Boss::render (Screen* screen, Camera* camera) 
{
	int xp = (int)x - 2;
	int yp = (int)y - 2;
	screen->draw(Art::gremlins[3][1], xp, yp);
	// FIXME
// g.setColor(Color.BLACK);
// yp += 2;
// xp -= 7;
// g.fillRect(xp + 5, yp - 8, 20, 3);
// g.setColor(Color.RED);
// g.fillRect(xp + 5, yp - 8, 20 - (20 * temperature / MAX_TEMPERATURE), 2);
}

void Boss::hitSpikes () 
{
}

void Boss::die () 
{
	//SoundMeta::death->play();
	for (int i = 0; i < 32; i++) 
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
		level->add(new Explosion(1, i * 3, x + w / 2 + xa * dist, y + h / 2 + ya * dist, xa, ya));
	}
	remove();
}

bool Boss::shot (Bullet* bullet) 
{
	return true;
}

void Boss::explode( Explosion* explosion) 
{
	if (explosion->power > 0) 
  {
		die();
	}
}
