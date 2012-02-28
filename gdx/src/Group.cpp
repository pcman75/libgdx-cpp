#include "stdafx.h"
#include "Group.h"
#include "Stage.h"

Texture* Group::debugTexture = NULL;
bool Group::debug = false;

Group::Group() 
{
  transform = true;
	lastTouchedChild = NULL;
  hasCullingArea = false;
}

/** Creates a new Group with the given name.
	* @param name the name of the group */
Group::Group( std::string name) 
  : Actor( name)
{
  transform = true;
	lastTouchedChild = NULL;
  hasCullingArea = false;
}

void Group::act( float delta) 
{
  /*
  super.act(delta);
		for (int i = 0; i < children.size(); i++) {
			Actor child = children.get(i);
			child.act(delta);
			if (child.isMarkedToRemove()) {
				child.markToRemove(false);
				removeActor(child);
				i--;
			}
		}*/

	Actor::act( delta);
  std::list<Actor*>::iterator it;
  std::vector<Actor*> toRemove;
	for( it = children.begin(); it != children.end(); it++) 
  {
		Actor* child = *it;
		child->act( delta);
		if( child->isMarkedToRemove()) 
    {
			child->markToRemove(false);
      toRemove.push_back( child);
		}
	}
  for( int nIdx = 0; nIdx < toRemove.size(); nIdx++)
  {
    removeActor( toRemove[ nIdx]);
  }
}

void Group::draw( SpriteBatch* batch, float parentAlpha) 
{
	if( debug && NULL != debugTexture && NULL != parent)
  {
    batch->draw( debugTexture, x, y, originX, originY, width == 0 ? 200 : width, height == 0 ? 200 : height, scaleX, scaleY, rotation, 0, 0, 
      debugTexture->getWidth(), debugTexture->getHeight(), false, false);
  }

	if( transform) applyTransform( batch);
	{
    drawChildren(batch, parentAlpha);
  }

	if( transform) 
    resetTransform( batch);
}

void Group::setCullingArea( const Rectang& cullingArea) 
{
	this->cullingArea = cullingArea;
  hasCullingArea = true;
}

bool Group::touchDown (float x, float y, int pointer)
{
	if( !touchable || !visible) return false;

  std::stringstream logText;
  logText << name << ": " << x << ", " << y;
	if( debug) Gdx.app->log( "Group", logText.str().c_str());

  std::list<Actor*>::reverse_iterator it;
	for( it = children.rbegin(); it != children.rend(); it++)
  {
		Actor* child = *it;
		if( !child->touchable || !child->visible) 
      continue;

		toChildCoordinates( child, x, y, point);
		if( NULL == child->hit( point.x, point.y)) 
      continue;

		// Allows lastTouchedChild to be the group itself, but means lastTouchedChild is cleared if the group isn't hit.
    if( ObjectGroup == child->type()) 
      ( ( Group*)child)->lastTouchedChild = NULL;

		if( child->touchDown( point.x, point.y, pointer)) 
    {
			// The first actor that accepts touchDown is focused.
			if( NULL != stage && NULL == stage->getTouchFocus( pointer)) 
        stage->setTouchFocus( child, pointer);

			if( ObjectGroup == child->type()) 
      {
				lastTouchedChild = ( ( Group*)child)->lastTouchedChild;
				if( NULL == lastTouchedChild) 
          lastTouchedChild = child; // If still null, the child group itself was touched.
			} 
      else
				lastTouchedChild = child;

			return true;
		}
	}

	lastTouchedChild = NULL;
	return false;
}


bool Group::touchMoved (float x, float y) 
{
	if (!touchable || !visible) return false;

	std::list<Actor*>::reverse_iterator it;
	for( it = children.rbegin(); it != children.rend(); it++)
  {
		Actor* child = *it;
		if( !child->touchable || !child->touchable) 
      continue;

		toChildCoordinates( child, x, y, point);

		if( child->touchMoved(point.x, point.y)) 
      return true;
	}
	return false;
}

Actor* Group::hit( float x, float y) 
{
	std::list<Actor*>::reverse_iterator it;
	for( it = children.rbegin(); it != children.rend(); it++)
  {
		Actor* child = *it;

		toChildCoordinates( child, x, y, point);

		Actor* hit = child->hit( point.x, point.y);
		if( NULL != hit) 
    {
			return hit;
		}
	}
	return x > 0 && x < width && y > 0 && y < height ? this : NULL;
}

void Group::addActor( Actor* actor) 
{
	actor->remove();
	children.push_back( actor);
	if( ObjectGroup == actor->type()) 
    groups.push_back( ( Group*) actor);

  if( ! actor->name.empty()) 
    namesToActors.insert( std::map<std::string, Actor*>::value_type( actor->name, actor));

	actor->parent = this;
	setStage( actor, stage);

	childrenChanged();
}

void Group::addActorAt( int index, Actor* actor) 
{
	actor->remove();

  std::list<Actor*>::iterator it = children.begin();
  for( int nIdx = 0; nIdx < index; nIdx++)
  {
    if( it == children.end()) break;
    it++;
  }
	children.insert( it, actor);

	if( ObjectGroup == actor->type()) 
    groups.push_back( ( Group*) actor);

	if( ! actor->name.empty()) 
    namesToActors.insert( std::map<std::string, Actor*>::value_type( actor->name, actor));

	actor->parent = this;
	setStage( actor, stage);
	childrenChanged();
}


void Group::addActorBefore( Actor* actorBefore, Actor* actor) 
{
	actor->remove();

  std::list<Actor*>::iterator it = find( children.begin(), children.end(), actorBefore);

  children.insert( it, actor);

  if( ObjectGroup == actor->type()) groups.push_back( ( Group*) actor);
	if( ! actor->name.empty()) 
    namesToActors.insert( std::map<std::string, Actor*>::value_type( actor->name, actor));

	actor->parent = this;
	setStage( actor, stage);
	childrenChanged();
}

void Group::addActorAfter( Actor* actorAfter, Actor* actor) 
{
	actor->remove();

  std::list<Actor*>::iterator it = find( children.begin(), children.end(), actorAfter);
  if( it != children.end()) it++;
  children.insert( it, actor);


	if( ObjectGroup == actor->type()) 
    groups.push_back( ( Group*)actor);

	if ( ! actor->name.empty()) 
    namesToActors.insert( std::map<std::string, Actor*>::value_type( actor->name, actor));

	actor->parent = this;
	setStage( actor, stage);
	childrenChanged();
}

void Group::removeActor( Actor* actor)
{
	children.remove( actor);

	if( ObjectGroup == actor->type()) 
    groups.remove( ( Group*) actor);
	if( ! actor->name.empty()) 
    namesToActors.erase( actor->name);

	if( NULL != stage) stage->unfocus( actor);

	actor->parent = NULL;
	setStage( actor, NULL);
	childrenChanged();
}

void Group::removeActorRecursive( Actor* actor)
{
  std::list<Actor*>::iterator it = find( children.begin(), children.end(), actor);

	if( it != children.end()) 
  {
    children.remove( *it);

		if( ObjectGroup == actor->type()) 
      groups.remove( ( Group*) actor);

		if( ! actor->name.empty()) namesToActors.erase( actor->name);
		if (stage != NULL) 
      stage->unfocus(actor);

		actor->parent = NULL;
		setStage( actor, NULL);
		return;
	}

  std::list<Group*>::iterator it2;
	for( it2 = groups.begin(); it2 != groups.end(); it2++)
  {
    (*it2)->removeActorRecursive( actor);
	}

	childrenChanged();
}

Actor* Group::findActor( std::string name)
{
  Actor* actor = NULL;
  std::map<std::string, Actor*>::iterator it = namesToActors.find( name);
	if( namesToActors.end() != it) 
  {
    actor = it->second;
    std::list<Group*>::iterator it;
		for( it = groups.begin(); it != groups.end(); it++)
    {
			actor = (*it)->findActor( name);
			if( NULL != actor) return actor;
		}
	}

	return actor;
}

bool Group::swapActor( int first, int second)
{
  std::list<Actor*>::iterator it1 = children.begin();
  std::list<Actor*>::iterator it2 = children.begin();
  while( first)
  {
    it1++;
    first--;
  }
  while( second)
  {
    it2++;
    second--;
  }

  if(  it1 != children.end() 
    && it2 != children.end())
  {
	  //children.swap( it1, it2);
    Actor* pTemp = *it1;
    *it1 = *it2;
    *it2 = pTemp;
    return true;
  }
	return false;
}

bool Group::swapActor( Actor* first, Actor* second) 
{
  std::list<Actor*>::iterator it1 = find( children.begin(), children.end(), first);
  std::list<Actor*>::iterator it2 = find( children.begin(), children.end(), second);

  if(  it1 != children.end() 
    && it2 != children.end())
  {
	  Actor* pTemp = *it1;
    *it1 = *it2;
    *it2 = pTemp;
    return true;
  }
	return false;
}

std::list<Actor*>& Group::getActors() 
{
	return children;
}

std::list<Group*>& Group::getGroups() 
{
	return groups;
}

void Group::clear() 
{
	children.clear();
	groups.clear();
	namesToActors.clear();
	childrenChanged();
}

/*
void Group::sortChildren( greater<Actor*> comparator) 
{
	children.sort( comparator);
}
*/

void Group::toLocalCoordinates( Actor* descendant, Vector2& point) 
{
	if( descendant->parent == NULL) 
    throw new GdxRuntimeException("Child was not a descendant.");

	// First convert to the actor's parent coordinates.
	if( descendant->parent != this) 
    toLocalCoordinates( descendant->parent, point);

	toChildCoordinates( descendant, point.x, point.y, point);
}

bool Group::isDescendant( Actor* actor) 
{
	while( true) 
  {
		if( actor == NULL) return false;
		if( actor == this) return true;
		actor = actor->parent;
	}
}

/** Transforms the coordinates given in the child's parent coordinate system to the child {@link Actor}'s coordinate system.
	* @param child the child Actor
	* @param x the x-coordinate in the Group's coordinate system
	* @param y the y-coordinate in the Group's coordinate system
	* @param out the output {@link Vector2} */
void Group::toChildCoordinates( Actor* child, float x, float y, Vector2& out)
{
	if( child->rotation == 0) 
  {
		if( child->scaleX == 1 && child->scaleY == 1) 
    {
			out.x = x - child->x;
			out.y = y - child->y;
		} 
    else 
    {
			if (child->originX == 0 && child->originY == 0) 
      {
				out.x = (x - child->x) / child->scaleX;
				out.y = (y - child->y) / child->scaleY;
			} 
      else 
      {
				out.x = (x - child->x - child->originX) / child->scaleX + child->originX;
				out.y = (y - child->y - child->originY) / child->scaleY + child->originY;
			}
		}
	} 
  else 
  {
		float cos = (float) MathUtils::cos(child->rotation * MathUtils::degreesToRadians);
		float sin = (float) MathUtils::sin(child->rotation * MathUtils::degreesToRadians);

		if (child->scaleX == 1 && child->scaleY == 1) 
    {
			if (child->originX == 0 && child->originY == 0) 
      {
				float tox = x - child->x;
				float toy = y - child->y;

				out.x = tox * cos + toy * sin;
				out.y = tox * -sin + toy * cos;
			} 
      else 
      {
				float worldOriginX = child->x + child->originX;
				float worldOriginY = child->y + child->originY;
				float fx = -child->originX;
				float fy = -child->originY;

				float x1 = cos * fx - sin * fy;
				float y1 = sin * fx + cos * fy;
				x1 += worldOriginX;
				y1 += worldOriginY;

				float tox = x - x1;
				float toy = y - y1;

				out.x = tox * cos + toy * sin;
				out.y = tox * -sin + toy * cos;
			}
		} 
    else 
    {
			if (child->originX == 0 && child->originY == 0) 
      {
				float tox = x - child->x;
				float toy = y - child->y;

				out.x = tox * cos + toy * sin;
				out.y = tox * -sin + toy * cos;

				out.x /= child->scaleX;
				out.y /= child->scaleY;
			} 
      else 
      {
				float srefX = child->originX * child->scaleX;
				float srefY = child->originY * child->scaleY;

				float worldOriginX = child->x + child->originX;
				float worldOriginY = child->y + child->originY;
				float fx = -srefX;
				float fy = -srefY;

				float x1 = cos * fx - sin * fy;
				float y1 = sin * fx + cos * fy;
				x1 += worldOriginX;
				y1 += worldOriginY;

				float tox = x - x1;
				float toy = y - y1;

				out.x = tox * cos + toy * sin;
				out.y = tox * -sin + toy * cos;

				out.x /= child->scaleX;
				out.y /= child->scaleY;
			}
		}
	}
}

void Group::enableDebugging( std::string debugTextureFile)
{
  debugTexture = new Texture( Gdx.files->internalHandle(debugTextureFile), false);
	debug = true;
}

void Group::disableDebugging() 
{
	if( debugTexture != NULL) 
  {
    delete debugTexture;
    debugTexture = NULL;
  }
	debug = false;
}




void Group::drawChildren( SpriteBatch* batch, float parentAlpha) 
{
	parentAlpha *= color.a;
	if( hasCullingArea) 
  {
		if( transform) 
    {
      std::list<Actor*>::iterator it;
			for( it = children.begin(); it != children.end(); it++)
      {
				Actor* child = *it;
				if( !child->visible) continue;
				if( child->x <= cullingArea.x + cullingArea.width && child->x + child->width >= cullingArea.x
					&& child->y <= cullingArea.y + cullingArea.height && child->y + child->height >= cullingArea.y) 
        {
					child->draw( batch, parentAlpha);
				}
			}
			batch->flush();
		} 
    else 
    {
			float offsetX = x;
			float offsetY = y;
			x = 0;
			y = 0;
			std::list<Actor*>::iterator it;
			for( it = children.begin(); it != children.end(); it++)
      {
				Actor* child = *it;
				if (!child->visible) continue;
				if (child->x <= cullingArea.x + cullingArea.width && child->x + child->width >= cullingArea.x
					&& child->y <= cullingArea.y + cullingArea.height && child->y + child->height >= cullingArea.y) 
        {
					child->x += offsetX;
					child->y += offsetY;
					child->draw( batch, parentAlpha);
					child->x -= offsetX;
					child->y -= offsetY;
				}
			}
			x = offsetX;
			y = offsetY;
		}
	} 
  else 
  {
		if (transform) 
    {
			std::list<Actor*>::iterator it;
			for( it = children.begin(); it != children.end(); it++)
      {
				Actor* child = *it;
				if (!child->visible) continue;
				child->draw( batch, parentAlpha);
			}
			batch->flush();
		} 
    else 
    {
			float offsetX = x;
			float offsetY = y;
			x = 0;
			y = 0;

			std::list<Actor*>::iterator it;
			for( it = children.begin(); it != children.end(); it++)
      {
				Actor* child = *it;
				if (!child->visible) continue;
				child->x += offsetX;
				child->y += offsetY;
				child->draw( batch, parentAlpha);
				child->x -= offsetX;
				child->y -= offsetY;
			}
			x = offsetX;
			y = offsetY;
		}
	}
}

void Group::drawChild( Actor* child, SpriteBatch* batch, float parentAlpha) 
{
	if (child->visible) child->draw( batch, parentAlpha * color.a);
	if (transform) batch->flush();
}

void Group::applyTransform( SpriteBatch* batch) 
{
	Matrix4 newBatchTransform = updateTransform();
	batch->end();
	oldBatchTransform.set( batch->getTransformMatrix());
	batch->setTransformMatrix( newBatchTransform);
	batch->begin();
}

Matrix4 Group::updateTransform()
{
	Matrix3 temp = worldTransform;
	if( originX != 0 || originY != 0)
		localTransform.setToTranslation(originX, originY);
	else
		localTransform.idt();

	if (rotation != 0) localTransform.mul(temp.setToRotation(rotation));
	if (scaleX != 1 || scaleY != 1) localTransform.mul(temp.setToScaling(scaleX, scaleY));
	if (originX != 0 || originY != 0) localTransform.mul(temp.setToTranslation(-originX, -originY));
	localTransform.trn(x, y);

	Group* parentGroup = parent;
	while( parentGroup != NULL) 
  {
		if( parentGroup->transform) 
      break;
		parentGroup = parentGroup->parent;
	}

	if( parentGroup != NULL) 
  {
		worldTransform.set( parentGroup->worldTransform);
		worldTransform.mul(localTransform);
	} 
  else 
  {
		worldTransform.set(localTransform);
	}

	batchTransform.set( worldTransform);
	return batchTransform;
}

void Group::resetTransform( SpriteBatch* batch) 
{
	batch->end();
	batch->setTransformMatrix( oldBatchTransform);
	batch->begin();
}


/** Called when actors are added to or removed from the group. */
void Group::childrenChanged()
{
}

	

void Group::setStage( Actor* actor, Stage* stage) 
{
	actor->stage = stage;
	if( ObjectGroup == actor->type()) 
  {
    std::list<Actor*>::iterator it;
		for( it = ( ( Group*) actor)->getActors().begin(); it != ( ( Group*) actor)->getActors().end(); it++)
			setStage( *it, stage);
	}
}