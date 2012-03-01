#include "stdafx.h"
#include "FadeTo.h"
#include "Actor.h"
#include "Interpolator.h"
#include "MathUtils.h"

FadeTo::FadeTo(float alpha, float duration) 
{
	this->toAlpha = min( max(alpha, 0.0f), 1.0f);
	this->duration = duration;
	invDuration = 1 / duration;
  toAlpha = 0;
	startAlpha = 0;
	deltaAlpha = 0;
}

FadeTo::~FadeTo()
{
}

void FadeTo::setTarget( Actor* actor) 
{
	target = actor;
	startAlpha = target->color.a;
	deltaAlpha = toAlpha - target->color.a;
	taken = 0;
	done = false;
}

void FadeTo::act(float delta) 
{
	float alpha = createInterpolatedAlpha( delta);
	if (done) 
  {
		target->color.a = toAlpha;
	} 
  else 
  {
		float val = startAlpha + deltaAlpha * alpha;
		target->color.a = min(max(val, 0.0f), 1.0f);
	}
}

void FadeTo::finish() 
{
	AnimationAction::finish();
	delete this;
}

Action* FadeTo::copy()
{
	FadeTo* fadeTo = new FadeTo( toAlpha, duration);
	if( NULL != interpolator) 
    fadeTo->setInterpolator( interpolator->copy());
	return fadeTo;
}