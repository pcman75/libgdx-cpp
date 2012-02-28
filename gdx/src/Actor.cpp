#include "stdafx.h"
#include "Actor.h"
#include "Group.h"


/** Creates an actor without a name. */
Actor::Actor()
{
  parent = NULL;
	touchable = true;
	visible = true;

  x = y = width = height = originX = originY = 0;
	scaleX = 1;
	scaleY = 1;
  rotation = 0;
	color = Color(1, 1, 1, 1);
  
  stage = NULL;

  toRemove = false;	
}

Actor::Actor(std::string name) 
{
	this->name = name;
}

Actor::~Actor()
{
}

bool Actor::touchDown( float x, float y, int pointer) 
{
	return false;
}

void Actor::touchUp( float x, float y, int pointer) 
{
}

void Actor::touchDragged( float x, float y, int pointer) 
{
}

bool Actor::touchMoved( float x, float y) 
{
	return false;
}

bool Actor::scrolled( int amount) 
{
	return false;
}

bool Actor::keyDown( int keycode) 
{
	return false;
}

bool Actor::keyUp( int keycode) 
{
	return false;
}

bool Actor::keyTyped( char character) 
{
	return false;
}

/** Transforms the given point in stage coordinates to the Actor's local coordinate system.
	* @param point the point */
void Actor::toLocalCoordinates( Vector2& point) 
{
	if( NULL == parent) return;
	parent->toLocalCoordinates( this, point);
	Group::toChildCoordinates( this, point.x, point.y, point);
}

/** Removes this actor from the Stage */
void Actor::remove()
{
	if( NULL != parent) 
    parent->removeActor( this);
}

void Actor::act( float delta) 
{
  /*
  actions.iter();
	Action action;

	while ((action = actions.next()) != null) 
  {
		action.act(delta);
		if (action.isDone()) 
    {
			action.finish();
			actions.remove();
		}
	}*/

  int nToDoBetter;
  std::list<Action*>::iterator it;
  for( it = actions.begin(); it != actions.end(); it++)
  {
    Action* pCurrAction = *it;
    pCurrAction->act( delta);
    if( pCurrAction->isDone())
    {
      pCurrAction->finish();
      delete pCurrAction;
      actions.erase( it);
    }
  }
}

/** Adds an {@link Action} to the Actor. Actions will be automatically performed in the order added to the Actor and will be
	* removed when they are done.
	* 
	* @param action the action */
void Actor::action( Action* action) 
{
	action->setTarget( this);
  actions.push_back( action);
}

/** Clears all actions of this Actor. */
void Actor::clearActions() 
{
  actions.empty();
}

std::string Actor::toString()
{
  std::stringstream name;
  name << this->name.length() ? this->name : "Actor";
  name << " pos=" << x << "," << y << " origin=" << originX << "," << originY << " size=" << width << "," << height;
	return name.str();
}

/** Marks the {@link Actor} to be removed by its parent.
	* <p>
	* The actual removal happens in the {@link Group#act(float)} method of the parent and after the parent has called
	* {@link #act(float)} on this {@link Actor}.
	* 
	* @param remove whether the parent is supposed to remove this {@link Actor} */
void Actor::markToRemove( bool remove) 
{
	toRemove = remove;
}

/** States if this actor is to be removed by its parent.
	* 
	* @return <code>true</code> when the actor is to be removed or <code>false</code> otherwise */
bool Actor::isMarkedToRemove () 
{
	return toRemove;
}

/** Returns the stage that this actor is currently in, or null if not in a stage. */
Stage* Actor::getStage() 
{
	return stage;
}
