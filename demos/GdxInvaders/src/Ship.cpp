#include "stdafx.h"
#include "Ship.h"
#include "Explosion.h"

const float Ship::SHIP_RADIUS = 1;
const float Ship::SHIP_VELOCITY = 20;

Ship::Ship()
	: lives(3), isExploding(false), explodeTime(0)
{
}

void Ship::update(float delta)
{
	if(isExploding)
	{
		explodeTime += delta;
		if(explodeTime > Explosion::EXPLOSION_LIVE_TIME)
		{
			isExploding = false;
			explodeTime = 0;
		}
	}
}
