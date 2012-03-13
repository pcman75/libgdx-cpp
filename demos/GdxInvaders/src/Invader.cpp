#include "stdafx.h"
#include "Invader.h"
#include "Simulation.h"

const float Invader::INVADER_RADIUS = 0.75f;
const float Invader::INVADER_VELOCITY = 1;
const int Invader::INVADER_POINTS = 40;
const int Invader::STATE_MOVE_LEFT = 0;
const int Invader::STATE_MOVE_DOWN = 1;
const int Invader::STATE_MOVE_RIGHT = 2;


Invader::Invader(const Vector3& position)
{
	this->position.set(position);
	state = STATE_MOVE_LEFT;
	wasLastStateLeft = true;
	movedDistance = Simulation::PLAYFIELD_MAX_X / 2;
}

void Invader::update(float delta, float speedMultiplier)
{
	movedDistance += delta * INVADER_VELOCITY * speedMultiplier;
	if(state == STATE_MOVE_LEFT)
	{
		position.x -= delta * INVADER_VELOCITY * speedMultiplier;
		if(movedDistance > Simulation::PLAYFIELD_MAX_X)
		{
			state = STATE_MOVE_DOWN;
			movedDistance = 0;
			wasLastStateLeft = true;
		}
	}
	if(state == STATE_MOVE_RIGHT)
	{
		position.x += delta * INVADER_VELOCITY * speedMultiplier;
		if(movedDistance > Simulation::PLAYFIELD_MAX_X)
		{
			state = STATE_MOVE_DOWN;
			movedDistance = 0;
			wasLastStateLeft = false;
		}
	}
	if(state == STATE_MOVE_DOWN)
	{
		position.z += delta * INVADER_VELOCITY * speedMultiplier;
		if(movedDistance > 1)
		{
			if(wasLastStateLeft)
				state = STATE_MOVE_RIGHT;
			else
				state = STATE_MOVE_LEFT;
			movedDistance = 0;
		}
	}
}

