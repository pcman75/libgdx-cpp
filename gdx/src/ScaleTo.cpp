#include "stdafx.h"
#include "ScaleTo.h"
#include "Actor.h"
#include "Interpolator.h"

ScaleTo::ScaleTo(float scaleX, float scaleY, float duration) 
{
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->duration = duration;
	this->invDuration = 1 / duration;
}
ScaleTo::~ScaleTo()
{
}

void ScaleTo::setTarget (Actor* actor) 
{
	target = actor;
	startScaleX = target->scaleX;
	deltaScaleX = scaleX - target->scaleX;
	startScaleY = target->scaleY;
	deltaScaleY = scaleY - target->scaleY;
	taken = 0;
	done = false;
}

void ScaleTo::act (float delta) 
{
	float alpha = createInterpolatedAlpha(delta);
	if (done) 
  {
		target->scaleX = scaleX;
		target->scaleY = scaleY;
	} 
  else 
  {
		target->scaleX = startScaleX + deltaScaleX * alpha;
		target->scaleY = startScaleY + deltaScaleY * alpha;
	}
}

void ScaleTo::finish () 
{
	AnimationAction::finish();
	delete this;
}

Action* ScaleTo::copy () 
{
	ScaleTo* scaleTo = new ScaleTo(scaleX, scaleY, duration);
	if (NULL != interpolator) 
    scaleTo->setInterpolator( interpolator->copy());
	return scaleTo;
}