#include "stdafx.h"
#include "MoveTo.h"
#include "Actor.h"
#include "Interpolator.h"


MoveTo::MoveTo(float x, float y, float duration) 
{
	this->x = x;
	this->y = y;
	this->duration = duration;
	this->invDuration = 1 / duration;
}
MoveTo::~MoveTo()
{
}

void MoveTo::setTarget (Actor* actor) 
{
	target = actor;
	startX = target->x;
	startY = target->y;
	deltaX = x - target->x;
	deltaY = y - target->y;
	taken = 0;
	done = false;
}

void MoveTo::act (float delta) 
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

void MoveTo::finish()
{
	AnimationAction::finish();
	delete this;
}

Action* MoveTo::copy()
{
	MoveTo* moveTo = new MoveTo(x, y, duration);
	if ( NULL != interpolator) 
    moveTo->setInterpolator( interpolator->copy());
	return moveTo;
}