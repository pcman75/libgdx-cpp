/*******************************************************************************
 * Copyright 2011 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
#pragma once

#include "Vector2.h"
#include "Bob.h"
#include "Platform.h"
#include "Spring.h"
#include "Squirrel.h"
#include "Coin.h"
#include "Castle.h"
#include "WorldListener.h"

class World
{
public:
	static const float WORLD_WIDTH;
	static const float WORLD_HEIGHT;
	static const int WORLD_STATE_RUNNING;
	static const int WORLD_STATE_NEXT_LEVEL;
	static const int WORLD_STATE_GAME_OVER;
	static const Vector2 gravity;

	Bob bob;
	std::list<Platform> platforms;
	std::list<Spring> springs;
	std::list<Squirrel> squirrels;
	std::list<Coin> coins;
	Castle castle;
	WorldListener* listener;

	float heightSoFar;
	int score;
	int state;

public:
	World(WorldListener* listener);
	~World();

	void update(float deltaTime, float accelX);
	void updateBob(float deltaTime, float accelX);
	void updatePlatforms(float deltaTime);
	void updateSquirrels(float deltaTime);
	void updateCoins(float deltaTime);
	void checkCollisions();
	void checkPlatformCollisions();
	void checkSquirrelCollisions();
	void checkItemCollisions();
	void checkCastleCollisions();
	void checkGameOver();

private:
	void generateLevel();
};
