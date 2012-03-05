#include "stdafx.h"
#include "Parallel.h"

Parallel::Parallel( std::vector<Action*> actions) 
{
  target = NULL;

	this->actions.clear();
	if( finished.size() < actions.size())
		finished.resize( actions.size());

	int len = actions.size();
	for (int i = 0; i < len; i++)
		finished[i] = false;

	for (int i = 0; i < len; i++)
		this->actions.push_back( actions[i]);
}

Parallel::~Parallel()
{
}

void Parallel::setTarget (Actor* actor) 
{
	target = actor;
	int len = actions.size();
	for (int i = 0; i < len; i++)
		actions[i]->setTarget(actor);
}

void Parallel::act (float delta) 
{
	int len = actions.size();
	bool allDone = true;
	Action* action;
	for (int i = 0; i < len; i++) 
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
	int len = actions.size();
	for (int i = 0; i < len; i++)
		if (actions[i]->isDone() == false) return false;

	return true;
}

void Parallel::finish () 
{
	int len = actions.size();
	for (int i = 0; i < len; i++) 
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