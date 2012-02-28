#include "stdafx.h"
#include "Action.h"

Action::Action()
{
  pListener = NULL;
}

Action::~Action()
{
}

/** Called by the owner of the action when it can release all its resources, e.g. put itself back into a pool. */
void Action::finish()
{
	if( NULL != pListener) 
  {
		pListener->completed( this);
	}
}

/** Calls the {@link OnActionCompleted} listener and sets it to null so it won't be called again. */
void Action::callActionCompletedListener()
{
	if( NULL != pListener)
  {
		pListener->completed(this);
	}
	pListener = NULL;
}

/** Sets the listener to be invoked when the action is finished.
	* @param listener
	* @return this */
void Action::setCompletionListener( OnActionCompleted* pListener) 
{
	this->pListener = pListener;
}

/** @return the {@link OnActionCompleted} listener or null. */
OnActionCompleted* Action::getCompletionListener()
{
	return pListener;
}

/** Sets the Action back to a vanilla state. */
void Action::reset()
{
	pListener = NULL;
}