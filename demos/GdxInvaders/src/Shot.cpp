#include "stdafx.h"
#include "Shot.h"
#include "Simulation.h"


const float Shot::SHOT_VELOCITY = 10;

Shot::Shot(const Vector3& position, bool isInvaderShot)
{

	this->position.set(position);
	this->isInvaderShot = isInvaderShot;
	hasLeftField = false;
}

void Shot::update(float delta)
{
	if(isInvaderShot)
		position.z += SHOT_VELOCITY * delta;
	else
		position.z -= SHOT_VELOCITY * delta;

	if(position.z > Simulation::PLAYFIELD_MAX_Z) 
		hasLeftField = true;
	if(position.z < Simulation::PLAYFIELD_MIN_Z) 
		hasLeftField = true;
}

bool Shot::operator==(const Shot& other)
{
	return position.epsilonEquals(other.position, 10E-20f) && 
		hasLeftField == other.hasLeftField && 
		isInvaderShot == other.isInvaderShot;
}