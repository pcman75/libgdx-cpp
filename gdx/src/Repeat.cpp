#include "stdafx.h"
#include "Repeat.h"

Repeat::Repeat(Action* action, int times) 
{
	this->action = action;
	this->times = times;
}
Repeat::~Repeat()
{
}

void Repeat::reset () 
{
	TemporalAction::reset();
	finishedTimes = 0;
	listener = NULL;
}

void Repeat::setTarget (Actor* actor) 
{
	action->setTarget(actor);
	target = actor;
}

void Repeat::act (float delta) 
{
	action->act(delta);
	if (action->isDone()) 
  {
		finishedTimes++;
		if (finishedTimes < times) 
    {
			Action* oldAction = action;
			action = action->copy();
			oldAction->finish();
			action->setTarget(target);
		} 
    else 
    {
			callActionCompletedListener();
		}
	}
}

bool Repeat::isDone () 
{
	return finishedTimes >= times;
}

void Repeat::finish () 
{
	action->finish();
	TemporalAction::finish();
  delete this;
}

Action* Repeat::copy () 
{
	return new Repeat( action->copy(), times);
}

Actor* Repeat::getTarget () 
{
	return target;
}