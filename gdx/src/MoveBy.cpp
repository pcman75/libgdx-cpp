#include "stdafx.h"
#include "MoveBy.h"
#include "Actor.h"
#include "Interpolator.h"

MoveBy::MoveBy( float x, float y, float duration) 
{
	this->x = this->initialX = x;
	this->y = this->initialY = y;
	this->duration = duration;
	this->invDuration = 1 / duration;
}

MoveBy::~MoveBy()
{
}

void MoveBy::setTarget (Actor* actor) 
{
	target = actor;
	startX = target->x;
	startY = target->y;
	deltaX = x;
	deltaY = y;
	x = target->x + x;
	y = target->y + y;
	taken = 0;
	done = false;
}

void MoveBy::act (float delta) 
{
	float alpha = createInterpolatedAlpha(delta);
	if (done) 
  {
		target->x = x;
		target->y = y;
	} 
  else 
  {
		target->x = startX + deltaX * alpha;
		target->y = startY + deltaY * alpha;
	}
}

void MoveBy::finish()
{
	AnimationAction::finish();
	delete this;
}

Action* MoveBy::copy()
{
	MoveBy* moveBy = new MoveBy( initialX, initialY, duration);
	if ( NULL != interpolator) 
    moveBy->setInterpolator( interpolator->copy());
	return moveBy;
}