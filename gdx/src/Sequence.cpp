#include "stdafx.h"
#include "Sequence.h"

Sequence::Sequence( std::vector<Action*> actions) 
{
  currAction = 0;
	this->actions.clear();
	int len = actions.size();
	for (int i = 0; i < len; i++)
		this->actions.push_back( actions[i]);
}
Sequence::~Sequence()
{
}

void Sequence::setTarget (Actor* actor) 
{
	target = actor;
	if ( actions.size() > 0) actions[0]->setTarget(target);
	currAction = 0;
}

void Sequence::act (float delta) 
{
	if (actions.size() == 0) 
  {
		currAction = 1;
		return;
	}

	if (currAction >= actions.size()) 
  {
		callActionCompletedListener();
		return;
	}

	actions[currAction]->act(delta);
	if (actions[currAction]->isDone()) 
  {
		actions[currAction]->callActionCompletedListener();
		currAction++;
		if (currAction < actions.size()) actions[currAction]->setTarget(target);
	}
}

bool Sequence::isDone () 
{
	return currAction >= actions.size();
}

void Sequence::finish () 
{
  CompositeAction::finish();
  delete this;
}

Action* Sequence::copy () 
{
	Sequence* retAction = new Sequence( std::vector<Action*>());
	int len = actions.size();
	for (int i = 0; i < len; i++) 
  {
    retAction->actions.push_back( actions[i]->copy());
	}
	return retAction;
}

Actor* Sequence::getTarget () 
{
	return target;
}