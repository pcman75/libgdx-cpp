#include "stdafx.h"
#include "Platform.h"
#include "World.h"

const float Platform::PLATFORM_WIDTH = 2;
const float Platform::PLATFORM_HEIGHT = 0.5f;
const int Platform::PLATFORM_TYPE_STATIC = 0;
const int Platform::PLATFORM_TYPE_MOVING = 1;
const int Platform::PLATFORM_STATE_NORMAL = 0;
const int Platform::PLATFORM_STATE_PULVERIZING = 1;
const float Platform::PLATFORM_PULVERIZE_TIME = 0.2f * 4;
const float Platform::PLATFORM_VELOCITY = 2;


Platform::Platform(int type, float x, float y)
	: DynamicGameObject(x, y, PLATFORM_WIDTH, PLATFORM_HEIGHT)
{
	this->type = type;
	this->state = PLATFORM_STATE_NORMAL;
	this->stateTime = 0;
	if (type == PLATFORM_TYPE_MOVING) 
	{
		velocity.x = PLATFORM_VELOCITY;
	}
}

void Platform::update(float deltaTime) 
{
	if (type == PLATFORM_TYPE_MOVING) 
	{
		position.add(velocity.x * deltaTime, 0);
		bounds.x = position.x - PLATFORM_WIDTH / 2;
		bounds.y = position.y - PLATFORM_HEIGHT / 2;

		if (position.x < PLATFORM_WIDTH / 2) 
		{
			velocity.x = -velocity.x;
			position.x = PLATFORM_WIDTH / 2;
		}
		if (position.x > World::WORLD_WIDTH - PLATFORM_WIDTH / 2) 
		{
			velocity.x = -velocity.x;
			position.x = World::WORLD_WIDTH - PLATFORM_WIDTH / 2;
		}
	}

	stateTime += deltaTime;
}

void Platform::pulverize() 
{
	state = PLATFORM_STATE_PULVERIZING;
	stateTime = 0;
	velocity.x = 0;
}

