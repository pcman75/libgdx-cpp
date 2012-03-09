#include "stdafx.h"
#include "Bob.h"
#include "World.h"

const int Bob::BOB_STATE_JUMP = 0;
const int Bob::BOB_STATE_FALL = 1;
const int Bob::BOB_STATE_HIT = 2;
const float Bob::BOB_JUMP_VELOCITY = 11;
const float Bob::BOB_MOVE_VELOCITY = 20;
const float Bob::BOB_WIDTH = 0.8f;
const float Bob::BOB_HEIGHT = 0.8f;

Bob::Bob(float x, float y) 
	:DynamicGameObject(x, y, BOB_WIDTH, BOB_HEIGHT)
{
	state = BOB_STATE_FALL;
	stateTime = 0;
}

void Bob::update(float deltaTime) 
{
	velocity.add(World::gravity.x * deltaTime, World::gravity.y * deltaTime);
	position.add(velocity.x * deltaTime, velocity.y * deltaTime);
	bounds.x = position.x - bounds.width / 2;
	bounds.y = position.y - bounds.height / 2;

	if (velocity.y > 0 && state != BOB_STATE_HIT) 
	{
		if (state != BOB_STATE_JUMP) 
		{
			state = BOB_STATE_JUMP;
			stateTime = 0;
		}
	}

	if (velocity.y < 0 && state != BOB_STATE_HIT) 
	{
		if (state != BOB_STATE_FALL) 
		{
			state = BOB_STATE_FALL;
			stateTime = 0;
		}
	}

	if (position.x < 0) 
		position.x = World::WORLD_WIDTH;
	if (position.x > World::WORLD_WIDTH) 
		position.x = 0;

	stateTime += deltaTime;
}

void Bob::hitSquirrel () 
{
	velocity.set(0, 0);
	state = BOB_STATE_HIT;
	stateTime = 0;
}

void Bob::hitPlatform () 
{
	velocity.y = BOB_JUMP_VELOCITY;
	state = BOB_STATE_JUMP;
	stateTime = 0;
}

void Bob::hitSpring () 
{
	velocity.y = BOB_JUMP_VELOCITY * 1.5f;
	state = BOB_STATE_JUMP;
	stateTime = 0;
}

