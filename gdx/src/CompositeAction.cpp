#include "stdafx.h"
#include "CompositeAction.h"


CompositeAction::CompositeAction()
{
}

CompositeAction::~CompositeAction()
{
}

/** Gets all target {@link Action}s which are affected by the composite action.
	* 
	* @return the {@link Action}s orchestrated by this {@link CompositeAction} */
std::list<Action*>& CompositeAction::getActions() 
{
	return actions;
}