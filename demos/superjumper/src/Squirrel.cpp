#include "stdafx.h"
#include "Squirrel.h"
#include "World.h"

const float Squirrel::SQUIRREL_WIDTH = 1.f;
const float Squirrel::SQUIRREL_HEIGHT = 0.6f;
const float Squirrel::SQUIRREL_VELOCITY = 3.f;

Squirrel::Squirrel (float x, float y)
	:DynamicGameObject(x, y, SQUIRREL_WIDTH, SQUIRREL_HEIGHT), stateTime(0)
{
	velocity.set(SQUIRREL_VELOCITY, 0);
}

void Squirrel::update(float deltaTime) 
{
	position.add(velocity.x * deltaTime, velocity.y * deltaTime);
	bounds.x = position.x - SQUIRREL_WIDTH / 2;
	bounds.y = position.y - SQUIRREL_HEIGHT / 2;

	if (position.x < SQUIRREL_WIDTH / 2) 
	{
		position.x = SQUIRREL_WIDTH / 2;
		velocity.x = SQUIRREL_VELOCITY;
	}
	if (position.x > World::WORLD_WIDTH - SQUIRREL_WIDTH / 2) 
	{
		position.x = World::WORLD_WIDTH - SQUIRREL_WIDTH / 2;
		velocity.x = -SQUIRREL_VELOCITY;
	}
	stateTime += deltaTime;
}

