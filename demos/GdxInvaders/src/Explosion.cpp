#include "stdafx.h"
#include "Explosion.h"

const float Explosion::EXPLOSION_LIVE_TIME = 1;

Explosion::Explosion(const Vector3& position)
{
	aliveTime = 0;
	this->position.set(position);
}

void Explosion::update(float delta)
{
	aliveTime += delta;
}

