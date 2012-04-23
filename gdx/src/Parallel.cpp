#include "stdafx.h"
#include "Parallel.h"

Parallel::Parallel( std::vector<Action*> actions) 
{
  target = NULL;

	this->actions.clear();
	if( finished.size() < actions.size())
		finished.resize( actions.size());

	size_t len = actions.size();
	for( size_t i = 0; i < len; i++)
		finished[i] = false;

	for (size_t i = 0; i < len; i++)
		this->actions.push_back( actions[i]);
}

Parallel::~Parallel()
{
}

void Parallel::setTarget (Actor* actor) 
{
	target = actor;
	size_t len = actions.size();
	for (size_t i = 0; i < len; i++)
		actions[i]->setTarget(actor);
}

void Parallel::act (float delta) 
{
	size_t len = actions.size();
	bool allDone = true;
	Action* action;
	for (size_t i = 0; i < len; i++) 
  {
		action = actions[i];
		if (!action->isDone()) 
    {
			action->act(delta);
			allDone = false;
		} 
    else 
    {
			if (!finished[i]) 
      {
				action->finish();
				finished[i] = true;
				allDone &= finished[i];
			}
		}
	}
	if (allDone) callActionCompletedListener();
}

bool Parallel::isDone () 
{
	size_t len = actions.size();
	for (size_t i = 0; i < len; i++)
		if (actions[i]->isDone() == false) return false;

	return true;
}

void Parallel::finish () 
{
	size_t len = actions.size();
	for (size_t i = 0; i < len; i++) 
  {
		if (!finished[i]) actions[i]->finish();
	}
  CompositeAction::finish();

  delete this;
}

Action* Parallel::copy () 
{
	Parallel* parallel = new Parallel( actions);
	return parallel;
}

Actor* Parallel::getTarget () 
{
	return target;
}