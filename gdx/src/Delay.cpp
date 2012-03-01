#include "stdafx.h"
#include "Delay.h"


Delay::Delay( Action* action, float duration)
{
  taken = 0.;
  this->duration = duration;
	this->action = action;
}
Delay::~Delay()
{

}


void Delay::reset()
{
	Action::reset();
}

void Delay::setTarget( Actor* actor)
{
	action->setTarget( actor);
	taken = 0;
}

void Delay::act( float delta)
{
	taken += delta;
	if( taken > duration) 
  {
		callActionCompletedListener();
		action->act( delta);
		if( action->isDone()) 
      action->callActionCompletedListener();
	}
}

bool Delay::isDone()
{
	return taken > duration && action->isDone();
}

void Delay::finish()
{
	/*pool.free(this);
	action.finish();
	super.finish();*/

	action->finish();
  delete this;
}

Action* Delay::copy()
{
	return new Delay( action, duration);
}

Actor* Delay::getTarget()
{
	return action->getTarget();
}