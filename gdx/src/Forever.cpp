#include "stdafx.h"
#include "Forever.h"


Forever::Forever( Action* action) 
{
	this->action = action;
}
Forever::~Forever()
{
}

void Forever::setTarget( Actor* actor) 
{
	action->setTarget( actor);
	target = actor;
}

void Forever::act( float delta) 
{
	action->act(delta);
	if( action->isDone()) 
  {
		Action* oldAction = action;
		action = action->copy();
		action->setCompletionListener( oldAction->getCompletionListener());
		oldAction->finish();
		action->setTarget( target);
	}
}

bool Forever::isDone () 
{
	return false;
}

void Forever::finish () 
{
	action->finish();
	TemporalAction::finish();
  delete this;
}

Action* Forever::copy ()
{
	return new Forever( action);
}

Actor* Forever::getTarget()
{
	return target;
}