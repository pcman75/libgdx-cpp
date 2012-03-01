#include "stdafx.h"
#include "Action.h"

Action::Action()
{
  listener = NULL;
}

Action::~Action()
{
}

/** Called by the owner of the action when it can release all its resources, e.g. put itself back into a pool. */
void Action::finish()
{
	if( NULL != listener) 
  {
		listener->completed( this);
	}
}

/** Calls the {@link OnActionCompleted} listener and sets it to null so it won't be called again. */
void Action::callActionCompletedListener()
{
	if( NULL != listener)
  {
		listener->completed(this);
	}
	listener = NULL;
}

/** Sets the listener to be invoked when the action is finished.
	* @param listener
	* @return this */
void Action::setCompletionListener( OnActionCompleted* listener) 
{
	this->listener = listener;
}

/** @return the {@link OnActionCompleted} listener or null. */
OnActionCompleted* Action::getCompletionListener()
{
	return listener;
}

/** Sets the Action back to a vanilla state. */
void Action::reset()
{
	listener = NULL;
}