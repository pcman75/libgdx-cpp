#include "stdafx.h"
#include "FadeIn.h"
#include "Actor.h"
#include "Interpolator.h"

FadeIn::FadeIn(float duration) 
{
	this->duration = duration;
	this->invDuration = 1 / duration;
  startAlpha = 0;
	deltaAlpha = 0;
}
FadeIn::~FadeIn()
{
}

void FadeIn::setTarget( Actor* actor) 
{
	target = actor;
	startAlpha = target->color.a;
	deltaAlpha = 1 - target->color.a;
	taken = 0;
	done = false;
}

void FadeIn::act( float delta) 
{
	float alpha = createInterpolatedAlpha( delta);
	if (done) 
  {
		target->color.a = 1.0f;
	} 
  else 
  {
		target->color.a = startAlpha + deltaAlpha * alpha;
	}
}

void FadeIn::finish () 
{
	if( NULL != listener) 
  {
		listener->completed(this);
	}
  delete this;
}

Action* FadeIn::copy () 
{
	FadeIn* fadeIn = new FadeIn( duration);
	if( NULL != interpolator) 
    fadeIn->setInterpolator( interpolator->copy());
	return fadeIn;
}