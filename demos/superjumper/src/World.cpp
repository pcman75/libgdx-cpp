#include "stdafx.h"
#include "World.h"
#include "MathUtils.h"
#include "OverlapTester.h"

const float World::WORLD_WIDTH = 10;
const float World::WORLD_HEIGHT = 15 * 20;
const int World::WORLD_STATE_RUNNING = 0;
const int World::WORLD_STATE_NEXT_LEVEL = 1;
const int World::WORLD_STATE_GAME_OVER = 2;
const Vector2 World::gravity(0, -12);

World::World(WorldListener* listener)	
	: bob(5, 1), castle(-1,-1)
{
	this->listener = listener;
	generateLevel();

	this->heightSoFar = 0;
	this->score = 0;
	this->state = WORLD_STATE_RUNNING;
}

World::~World()
{
	/*
	delete bob; 
	bob = NULL;
	delete castle; 
	castle = NULL;
	*/
}


void World::generateLevel()
{
	float y = Platform::PLATFORM_HEIGHT / 2;
	float maxJumpHeight = Bob::BOB_JUMP_VELOCITY * Bob::BOB_JUMP_VELOCITY / (2 * -gravity.y);
	while(y < WORLD_HEIGHT - WORLD_WIDTH / 2)
	{
		int type = MathUtils::randomFloat() > 0.8f ? Platform::PLATFORM_TYPE_MOVING : Platform::PLATFORM_TYPE_STATIC;
		float x = MathUtils::randomFloat() * (WORLD_WIDTH - Platform::PLATFORM_WIDTH) + Platform::PLATFORM_WIDTH / 2;

		Platform platform(type, x, y);
		platforms.push_back(platform);

		if(MathUtils::randomFloat() > 0.9f && type != Platform::PLATFORM_TYPE_MOVING)
		{
			Spring spring(platform.position.x, platform.position.y + Platform::PLATFORM_HEIGHT / 2
				+ Spring::SPRING_HEIGHT / 2);
			springs.push_back(spring);
		}

		if(y > WORLD_HEIGHT / 3 && MathUtils::randomFloat() > 0.8f)
		{
			Squirrel squirrel(platform.position.x + MathUtils::randomFloat(), platform.position.y
				+ Squirrel::SQUIRREL_HEIGHT + MathUtils::randomFloat() * 2);
			squirrels.push_back(squirrel);
		}

		if(MathUtils::randomFloat() > 0.6f)
		{
			Coin coin(platform.position.x + MathUtils::randomFloat(), platform.position.y + Coin::COIN_HEIGHT
				+ MathUtils::randomFloat() * 3);
			coins.push_back(coin);
		}

		y += (maxJumpHeight - 0.5f);
		y -= MathUtils::randomFloat() * (maxJumpHeight / 3);
	}
	castle = Castle(WORLD_WIDTH / 2, y);
}

void World::update(float deltaTime, float accelX)
{
	updateBob(deltaTime, accelX);
	updatePlatforms(deltaTime);
	updateSquirrels(deltaTime);
	updateCoins(deltaTime);
	if(bob.state != Bob::BOB_STATE_HIT) 
		checkCollisions();
	checkGameOver();
}


void World::updateBob(float deltaTime, float accelX)
{
	if(bob.state != Bob::BOB_STATE_HIT && bob.position.y <= 0.5f)
		bob.hitPlatform();
	if(bob.state != Bob::BOB_STATE_HIT) 
		bob.velocity.x = -accelX / 10 * Bob::BOB_MOVE_VELOCITY;
	bob.update(deltaTime);
	heightSoFar = max(bob.position.y, heightSoFar);
}

void World::updatePlatforms(float deltaTime)
{
	for(std::list<Platform>::iterator platform = platforms.begin(); platform != platforms.end(); platform++)
	{
		platform->update(deltaTime);
		if(platform->state == Platform::PLATFORM_STATE_PULVERIZING && platform->stateTime > Platform::PLATFORM_PULVERIZE_TIME)
		{
			platforms.erase(platform);
			break;
		}
	}
}

void World::updateSquirrels(float deltaTime)
{
	for(std::list<Squirrel>::iterator squirrel = squirrels.begin(); squirrel != squirrels.end(); squirrel++)
	{
		squirrel->update(deltaTime);
	}
}

void World::updateCoins(float deltaTime)
{
	for(std::list<Coin>::iterator coin = coins.begin(); coin != coins.end(); coin++)
	{
		coin->update(deltaTime);
	}
}

void World::checkCollisions()
{
	checkPlatformCollisions();
	checkSquirrelCollisions();
	checkItemCollisions();
	checkCastleCollisions();
}

void World::checkPlatformCollisions()
{
	if(bob.velocity.y > 0) 
		return;

	for(std::list<Platform>::iterator platform = platforms.begin(); platform != platforms.end(); platform++)
	{
		if(bob.position.y > platform->position.y)
		{
			if(OverlapTester::overlapRectangles(bob.bounds, platform->bounds))
			{
				bob.hitPlatform();
				listener->jump();
				if(MathUtils::randomFloat() > 0.5f)
				{
					platform->pulverize();
				}
				break;
			}
		}
	}
}

void World::checkSquirrelCollisions()
{
	for(std::list<Squirrel>::iterator squirrel = squirrels.begin(); squirrel != squirrels.end(); squirrel++)
	{
		if(OverlapTester::overlapRectangles(squirrel->bounds, bob.bounds))
		{
			bob.hitSquirrel();
			listener->hit();
		}
	}
}

void World::checkItemCollisions()
{
	for(std::list<Coin>::iterator coin = coins.begin(); coin != coins.end(); coin++)
	{
		if(OverlapTester::overlapRectangles(bob.bounds, coin->bounds))
		{
			coins.erase(coin);
			listener->coin();
			score += Coin::COIN_SCORE;
			break;
		}

	}

	if(bob.velocity.y > 0) 
		return;


	for(std::list<Spring>::iterator spring = springs.begin(); spring != springs.end(); spring++)
	{
		if(bob.position.y > spring->position.y)
		{
			if(OverlapTester::overlapRectangles(bob.bounds, spring->bounds))
			{
				bob.hitSpring();
				listener->highJump();
			}
		}
	}
}

void World::checkCastleCollisions()
{
	if(OverlapTester::overlapRectangles(castle.bounds, bob.bounds))
	{
		state = WORLD_STATE_NEXT_LEVEL;
	}
}

void World::checkGameOver()
{
	if(heightSoFar - 7.5f > bob.position.y)
	{
		state = WORLD_STATE_GAME_OVER;
	}
}
