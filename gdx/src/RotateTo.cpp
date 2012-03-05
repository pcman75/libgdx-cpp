#include "stdafx.h"
#include "RotateTo.h"
#include "Actor.h"
#include "Interpolator.h"

RotateTo::RotateTo(float rotation, float duration) 
{
	this->rotation = rotation;
	this->duration = duration;
	this->invDuration = 1 / duration;
}
RotateTo::~RotateTo()
{
}

void RotateTo::setTarget (Actor* actor) 
{
	target = actor;
	startRotation = target->rotation;
	deltaRotation = rotation - target->rotation;
	taken = 0;
	done = false;
}

void RotateTo::act (float delta) 
{
	float alpha = createInterpolatedAlpha(delta);
	if (done) 
  {
		target->rotation = rotation;
	} 
  else 
  {
		target->rotation = startRotation + deltaRotation * alpha;
	}
}

void RotateTo::finish () 
{
	AnimationAction::finish();
	delete this;
}

Action* RotateTo::copy () 
{
	RotateTo* rotateTo = new RotateTo( rotation, duration);
	if (NULL != interpolator) 
    rotateTo->setInterpolator( interpolator->copy());
	return rotateTo;
}