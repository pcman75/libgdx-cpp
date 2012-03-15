#include "stdafx.h"
#include "Bullet.h"
#include "Screen.h"


Bullet::Bullet( Entity* source, double x, double y, double xa, double ya) 
{
  source = NULL;
  noHitTime = 10;
	ntick = 0;

	this->source = source;
	this->x = x;
	this->y = y;
	this->w = 1;
	this->h = 1;
	this->xa = xa + ( MathUtils::randomFloat() - MathUtils::randomFloat()) * 0.1;
	this->ya = ya + ( MathUtils::randomFloat() - MathUtils::randomFloat()) * 0.1;

	interactsWithWorld = true;
}

void Bullet::tick () 
{
	ntick++;
	tryMove(xa, ya);

	if (noHitTime > 0) 
  {
		noHitTime--;
		return;
	}
	std::vector<Entity*> entities = level->getEntities((int)x, (int)y, 1, 1);
	for (int i = 0; i < entities.size(); i++) 
  {
		Entity* e = entities[i];
		if (source == e) continue;

		if (e->shot(this)) 
    {
			remove();
		}
	}
}

void Bullet::hitWall (double xa, double ya) 
{
	for (int i = 0; i < 3; i++) 
  {
		level->add( new Spark(x, y, 0, 0));
	}
	remove();
}

void Bullet::render( Screen* g, Camera* camera) 
{
	// FIXME
// if (ntick % 2 == 0) {
// g.setColor(Color.YELLOW);
// int x1 = (int) (x + w / 2 - xa * 3);
// int y1 = (int) (y + h / 2 - ya * 3);
// int x2 = (int) (x + w / 2);
// int y2 = (int) (y + h / 2);
//
// g.drawLine(x1, y1, x2, y2);
// g.setColor(Color.WHITE);
//
// x1 = (int) (x + w / 2 - xa);
// y1 = (int) (y + h / 2 - ya);
// x2 = (int) (x + w / 2 + xa);
// y2 = (int) (y + h / 2 + ya);
//
// g.drawLine(x1, y1, x2, y2);
// } else {
// g.setColor(Color.YELLOW);
// int x1 = (int) (x + w / 2 - xa);
// int y1 = (int) (y + h / 2 - ya);
// int x2 = (int) (x + w / 2 + xa);
// int y2 = (int) (y + h / 2 + ya);
//
// g.drawLine(x1, y1, x2, y2);
// }

	g->draw( &Art::shot, (int)x, (int)y);
	// g.fillRect(xp, yp, w, h);
}