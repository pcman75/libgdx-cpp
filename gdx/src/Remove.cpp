#include "stdafx.h"
#include "Remove.h"
#include "Actor.h"

Remove::Remove() 
{
	removed = false;
	target = NULL;
}
Remove::~Remove()
{
}

void Remove::setTarget (Actor* actor) 
{
	this->target = actor;
}

void Remove::act (float delta) 
{
	if (!removed) 
  {
		target->markToRemove(true);
		removed = true;
		callActionCompletedListener();
	}
}

bool Remove::isDone () 
{
	return removed;
}

Action* Remove::copy () 
{
	return new Remove;
}

Actor* Remove::getTarget () 
{
	return target;
}