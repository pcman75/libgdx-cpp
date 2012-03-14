#include "stdafx.h"
#include "Simulation.h"
#include "MathUtils.h"

float Simulation::PLAYFIELD_MIN_X = -14;
float Simulation::PLAYFIELD_MAX_X = 14;
float Simulation::PLAYFIELD_MIN_Z = -15;
float Simulation::PLAYFIELD_MAX_Z = 2;

Simulation::Simulation()
	: shipShot(NULL), listener(NULL), multiplier(1), score(0), wave(1)
{
	populate();
}

void Simulation::populate()
{
	for(int row = 0; row < 4; row++)
	{
		for(int column = 0; column < 8; column++)
		{
			Invader invader(Vector3(-PLAYFIELD_MAX_X / 2 + column * 2.f, 0, PLAYFIELD_MIN_Z + row * 2.f));
			invaders.push_back(invader);
		}
	}

	for(int shield = 0; shield < 3; shield++)
	{
		blocks.push_back(Block(Vector3(-10 + (float)shield * 10 - 1, 0, -2)));
		blocks.push_back(Block(Vector3(-10 + (float)shield * 10 - 1, 0, -3)));
		blocks.push_back(Block(Vector3(-10 + (float)shield * 10 + 0, 0, -3)));
		blocks.push_back(Block(Vector3(-10 + (float)shield * 10 + 1, 0, -3)));
		blocks.push_back(Block(Vector3(-10 + (float)shield * 10 + 1, 0, -2)));
	}
}

void Simulation::update(float delta)
{
	ship.update(delta);
	updateInvaders(delta);
	updateShots(delta);
	updateExplosions(delta);
	checkShipCollision();
	checkInvaderCollision();
	checkBlockCollision();
	checkNextLevel();
}

void Simulation::updateInvaders(float delta)
{
	for(Invaders::iterator invader = invaders.begin(); invader != invaders.end(); invader++)
	{
		invader->update(delta, multiplier);
	}
}

void Simulation::updateShots(float delta)
{
	removedShots.clear();

	for(Shots::iterator shot = shots.begin(); shot != shots.end(); shot++)
	{
		shot->update(delta);
		if(shot->hasLeftField)
		{
			removedShots.push_back(*shot);
		}
	}
	for(Shots::iterator shot = removedShots.begin(); shot != removedShots.end(); shot++)
	{
		shots.remove(*shot);
	}

	if(shipShot != NULL && shipShot->hasLeftField) 
		shipShot = NULL;

	if(MathUtils::randomFloat() < 0.01 * multiplier && invaders.size() > 0)
	{
		int index = (int)(MathUtils::randomFloat() * (invaders.size() - 1));
		Invaders::iterator shootingInvader = invaders.begin();
		while(index--)
			shootingInvader++;

		Shot shot(shootingInvader->position, true);
		shots.push_back(shot);
		if(listener != NULL) 
			listener->shot();
	}
}

void Simulation::updateExplosions(float delta)
{
	for(Explosions::iterator explosion = explosions.begin(); explosion != explosions.end(); )
	{
		explosion->update(delta);
		if(explosion->aliveTime > Explosion::EXPLOSION_LIVE_TIME) 
			explosion = explosions.erase(explosion);
		else
			explosion++;

	}

}

void Simulation::checkInvaderCollision()
{
	if(shipShot == NULL) 
		return;

	for(Invaders::iterator invader = invaders.begin(); invader != invaders.end(); )
	{
		if(invader->position.dst(shipShot->position) < Invader::INVADER_RADIUS)
		{
			shots.remove(*shipShot);
			shipShot = NULL;
			explosions.push_back(Explosion(invader->position));
			invader = invaders.erase(invader);

			if(listener != NULL) 
				listener->explosion();
			score += Invader::INVADER_POINTS;
			break;
		}
		else
			invader++;
	}
}

void Simulation::checkShipCollision()
{
	removedShots.clear();

	if(!ship.isExploding)
	{
		for(Shots::iterator shot = shots.begin(); shot != shots.end(); shot++)
		{
			if(!shot->isInvaderShot) 
				continue;

			if(ship.position.dst(shot->position) < Ship::SHIP_RADIUS)
			{
				removedShots.push_back(*shot);
				shot->hasLeftField = true;
				ship.lives--;
				ship.isExploding = true;
				explosions.push_back(Explosion(ship.position));
				if(listener != NULL) 
					listener->explosion();
				break;
			}
		}
		for(Shots::iterator shot = removedShots.begin(); shot != removedShots.end(); shot++)
		{
			shots.remove(*shot);
		}
	}

	for(Invaders::iterator invader = invaders.begin(); invader != invaders.end(); )
	{
		if(invader->position.dst(ship.position) < Ship::SHIP_RADIUS)
		{
			ship.lives--;
			ship.isExploding = true;
			explosions.push_back(Explosion(invader->position));
			explosions.push_back(Explosion(ship.position));
			invader = invaders.erase(invader);
			if(listener != NULL) 
				listener->explosion();
			break;
		}
		else
			invader++;
	}
}

void Simulation::checkBlockCollision()
{
	removedShots.clear();

	for(Shots::iterator shot = shots.begin(); shot != shots.end(); shot++)
	{
		for(Blocks::iterator block = blocks.begin(); block != blocks.end(); )
		{
			if(block->position.dst(shot->position) < Block::BLOCK_RADIUS)
			{
				removedShots.push_back(*shot);
				shot->hasLeftField = true;
				block = blocks.erase(block);
				break;
			}
			else
				block++;
		}
	}

	for(Shots::iterator shot = removedShots.begin(); shot != removedShots.end(); shot++)
		shots.remove(*shot);
}

void Simulation::checkNextLevel()
{
	if(invaders.size() == 0 && ship.lives > 0)
	{
		blocks.clear();
		shots.clear();
		shipShot = NULL;
		Vector3 shipPosition = ship.position;
		int lives = ship.lives;
		populate();
		ship.position.set(shipPosition);
		ship.lives = lives;
		multiplier += 0.1f;
		wave++;
	}
}

void Simulation::moveShipLeft(float delta, float scale)
{
	if(ship.isExploding) 
		return;

	ship.position.x -= delta * Ship::SHIP_VELOCITY * scale;
	if(ship.position.x < PLAYFIELD_MIN_X) 
		ship.position.x = PLAYFIELD_MIN_X;
}

void Simulation::moveShipRight(float delta, float scale)
{
	if(ship.isExploding) return;

	ship.position.x += delta * Ship::SHIP_VELOCITY * scale;
	if(ship.position.x > PLAYFIELD_MAX_X) 
		ship.position.x = PLAYFIELD_MAX_X;
}

void Simulation::shot()
{
	if(shipShot == NULL && !ship.isExploding)
	{
		shipShot = new Shot(ship.position, false);
		shots.push_back(*shipShot);
		if(listener != NULL) 
			listener->shot();
	}
}

