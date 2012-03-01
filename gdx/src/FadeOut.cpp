#include "stdafx.h"
#include "FadeOut.h"
#include "Actor.h"
#include "Interpolator.h"

FadeOut::FadeOut(float duration) 
{
	this->duration = duration;
	this->invDuration = 1 / duration;
  startAlpha = 0;
	deltaAlpha = 0;
}
FadeOut::~FadeOut()
{
}

void FadeOut::setTarget( Actor* actor) 
{
	target = actor;
	startAlpha = target->color.a;
	deltaAlpha = -target->color.a;
	taken = 0;
	done = false;
}

void FadeOut::act( float delta)
{
	float alpha = createInterpolatedAlpha( delta);
	if (done) 
  {
		target->color.a = 0.0f;
	} 
  else 
  {
		target->color.a = startAlpha + deltaAlpha * alpha;
	}
}

void FadeOut::finish()
{
	AnimationAction::finish();
	delete this;
}

Action* FadeOut::copy()
{
	FadeOut* fadeOut = new FadeOut( duration);
	if( NULL != interpolator) 
    fadeOut->setInterpolator( interpolator->copy());
	return fadeOut;
}