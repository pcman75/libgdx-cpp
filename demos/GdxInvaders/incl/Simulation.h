/*
 * Copyright 2010 Mario Zechner (contact@badlogicgames.com), Nathan Sweet (admin@esotericsoftware.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the
 * License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS"
 * BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 */
#pragma once
#include "Invader.h"
#include "Block.h"
#include "Shot.h"
#include "Explosion.h"
#include "Ship.h"
#include "SimulationListener.h"

class Simulation
{
public:
	static float PLAYFIELD_MIN_X;
	static float PLAYFIELD_MAX_X;
	static float PLAYFIELD_MIN_Z;
	static float PLAYFIELD_MAX_Z;

	typedef std::list<Invader> Invaders;
	typedef std::list<Block> Blocks;
	typedef std::list<Shot> Shots;	
	typedef std::list<Explosion> Explosions;
	
	Invaders invaders;
	Blocks blocks;
	Shots shots;
	Explosions explosions;
	Ship ship;
	Shot* shipShot;
	
	SimulationListener* listener;
	float multiplier;
	int score;
	int wave;

private:
	Shots removedShots;

public:
	Simulation();

	void moveShipLeft(float delta, float scale);
	void moveShipRight(float delta, float scale);
	void shot();
	void update(float delta);

private:
	void populate();
	void updateInvaders(float delta);
	void updateShots(float delta);
	void updateExplosions(float delta);
	void checkInvaderCollision();
	void checkShipCollision();
	void checkBlockCollision();
	void checkNextLevel();
};
