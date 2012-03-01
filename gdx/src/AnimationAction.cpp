#include "stdafx.h"
#include "AnimationAction.h"
#include "Interpolator.h"

AnimationAction::AnimationAction()
{
  target = NULL;
	done = false;
  interpolator = NULL;
}

AnimationAction::~AnimationAction()
{

}


bool AnimationAction::isDone() 
{
	return done;
}

void AnimationAction::finish() 
{
	Action::finish();
	if( NULL != interpolator) 
  {
		interpolator->finished();
	}
}

void AnimationAction::setInterpolator( Interpolator* interpolator) 
{
	this->interpolator = interpolator;
}

float AnimationAction::createInterpolatedAlpha( float delta) 
{
	taken += delta;
	if (taken >= duration) 
  {
		taken = duration;
		done = true;
		return taken;
	} 
  else if( NULL != interpolator)
  {
		return taken * invDuration;
	} 
  else 
  {
		float interpolatedTime = interpolator->getInterpolation(taken / duration) * duration;
		return interpolatedTime * invDuration;
	}
}

Actor* AnimationAction::getTarget() 
{
	return target;
}

void AnimationAction::reset() 
{
	Action::reset();
	interpolator = NULL;
}