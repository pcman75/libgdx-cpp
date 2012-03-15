#include "stdafx.h"
#include "Entity.h"
#include "Level.h"
#include "Screen.h"
#include "Camera.h"
#include "Bullet.h"
#include "Gunner.h"
#include "Explosion.h"


Entity::Entity()
{
  xa = ya = 0;
  x = y = 0;
  onGround = false;
  bounce = 0.05;
	w = 10;
  h = 10;
  level = NULL;
  removed = false;
	interactsWithWorld = false;
  xSlot = ySlot = 0;
}

void Entity::init( Level* level) 
{
	this->level = level;
}

void Entity::tryMove (double xa, double ya) 
{
	onGround = false;
	if( level->isFree(this, x + xa, y, w, h, xa, 0)) 
  {
		x += xa;
	} 
  else 
  {
		hitWall(xa, 0);
		if (xa < 0) 
    {
			double xx = x / 10;
			xa = -(xx - ((int)xx)) * 10;
		} 
    else 
    {
			double xx = (x + w) / 10;
			xa = 10 - (xx - ((int)xx)) * 10;
		}
		if (level->isFree(this, x + xa, y, w, h, xa, 0)) 
    {
			x += xa;
		}
		this->xa *= -bounce;
	}
	if (level->isFree(this, x, y + ya, w, h, 0, ya)) 
  {
		y += ya;
	} 
  else 
  {
		if (ya > 0) onGround = true;
		hitWall(0, ya);
		if (ya < 0) 
    {
			double yy = y / 10;
			ya = -(yy - ((int)yy)) * 10;
		} 
    else 
    {
			double yy = (y + h) / 10;
			ya = 10 - (yy - ((int)yy)) * 10;
		}
		if (level->isFree(this, x, y + ya, w, h, 0, ya)) 
    {
			y += ya;
		}
		this->ya *= -bounce;
	}
}

void Entity::hitWall (double xa, double ya) 
{
}

void Entity::remove () 
{
	removed = true;
}

void Entity::tick () 
{
}

bool Entity::shot (Bullet* bullet) 
{
	return false;
}

void Entity::hitSpikes () 
{
}

void Entity::shove( Gunner* enemy) 
{
}

void Entity::outOfBounds () 
{
	if (y < 0) return;
	remove();
}

void Entity::explode( Explosion* explosion) 
{
}

void Entity::collideMonster( Entity* e) 
{
}