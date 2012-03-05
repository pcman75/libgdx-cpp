#include "stdafx.h"
#include "RotateBy.h"
#include "Actor.h"
#include "Interpolator.h"

RotateBy::RotateBy(float rotation, float duration) 
{
	this->rotation = rotation;
	this->duration = duration;
	this->invDuration = 1 / duration;
}
RotateBy::~RotateBy()
{
}

void RotateBy::setTarget (Actor* actor) 
{
	target = actor;
	startRotation = target->rotation;
	deltaRotation = rotation;
	taken = 0;
	done = false;
}

void RotateBy::act (float delta) 
{
	float alpha = createInterpolatedAlpha(delta);
	if (done) 
  {
		target->rotation = startRotation + rotation;
	} 
  else 
  {
		target->rotation = startRotation + deltaRotation * alpha;
	}
}

void RotateBy::finish () 
{
	AnimationAction::finish();
	delete this;
}

Action* RotateBy::copy () 
{
	RotateBy* rotateBy = new RotateBy(rotation, duration);
	if (NULL != interpolator) 
    rotateBy->setInterpolator( interpolator->copy());
	return rotateBy;
}
