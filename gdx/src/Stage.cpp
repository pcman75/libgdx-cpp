#include "stdafx.h"
#include "Stage.h"
#include "Group.h"
#include "SpriteBatch.h"
#include "Actor.h"
#include "OrthographicCamera.h"


/** Constructs a new Stage object with the given dimensions. If the device resolution does not equal the Stage objects
	* dimensions the stage object will setup a projection matrix to guarantee a fixed coordinate system. If stretch is disabled
	* then the bigger dimension of the Stage will be increased to accomodate the actual device resolution.
	* @param width the width of the viewport
	* @param height the height of the viewport
	* @param stretch whether to stretch the viewport to the real device resolution */
Stage::Stage( float width, float height, bool stretch) 
{
  root = NULL;
  batch = NULL;
  keyboardFocus = NULL;
  scrollFocus = NULL;
  for( int nIdx = 0; nIdx < 20; nIdx++)
  {
    touchFocus[ nIdx] = NULL;
  }

	m_width = width;
	m_height = height;
	m_stretch = stretch;
	root = new Group( "root");
	root->stage = this;
	batch = new SpriteBatch();
	ownsBatch = true;
	camera = new OrthographicCamera();
	setViewport( width, height, stretch);
  
}

/** Constructs a new Stage object with the given dimensions. If the device resolution does not equal the Stage objects
	* dimensions the stage object will setup a projection matrix to guarantee a fixed coordinate system. If stretch is disabled
	* then the bigger dimension of the Stage will be increased to accomodate the actual device resolution.
	* @param width the width of the viewport
	* @param height the height of the viewport
	* @param stretch whether to stretch the viewport to the real device resolution
	* @param batch the {@link SpriteBatch} this Stage should use. Will not be disposed if {@link #dispose()} is called. */
Stage::Stage( float width, float height, bool stretch, SpriteBatch* batch) 
{
  root = NULL;
  batch = NULL;
  keyboardFocus = NULL;
  scrollFocus = NULL;
  for( int nIdx = 0; nIdx < 20; nIdx++)
  {
    touchFocus[ nIdx] = NULL;
  }

	m_width = width;
	m_height = height;
	m_stretch = stretch;
	root = new Group("root");
	root->stage = this;
	this->batch = batch;
	ownsBatch = false;
	camera = new OrthographicCamera();
	setViewport(width, height, stretch);
}

Stage::~Stage()
{


  if( NULL != camera)
  {
    delete camera;
    camera = NULL;
  }

}



/** Sets the viewport dimensions in device independent pixels. If stretch is false and the viewport aspect ratio is not equal to
	* the device ratio then the bigger dimension of the viewport will be extended (device independent pixels stay quardatic
	* instead of getting stretched).
	* 
	* @param width thew width of the viewport in device independent pixels
	* @param height the height of the viewport in device independent pixels
	* @param stretch whether to stretch the viewport or not */
void Stage::setViewport( float width, float height, bool stretch) 
{
	if (!stretch) 
  {
		if (width > height && width / (float)Gdx.graphics->getWidth() <= height / (float)Gdx.graphics->getHeight()) 
    {
			float toDeviceSpace = Gdx.graphics->getHeight() / height;
			float toViewportSpace = height / Gdx.graphics->getHeight();

			float deviceWidth = width * toDeviceSpace;
			m_width = width + (Gdx.graphics->getWidth() - deviceWidth) * toViewportSpace;
			m_height = height;
		} 
    else 
    {
			float toDeviceSpace = Gdx.graphics->getWidth() / width;
			float toViewportSpace = width / Gdx.graphics->getWidth();

			float deviceHeight = height * toDeviceSpace;
			m_height = height + (Gdx.graphics->getHeight() - deviceHeight) * toViewportSpace;
			m_width = width;
		}
	} 
  else 
  {
		m_width = width;
		m_height = height;
	}

	m_stretch = stretch;
	m_centerX = m_width / 2;
	m_centerY = m_height / 2;

	camera->position.set( m_centerX, m_centerY, 0);
	camera->viewportWidth = m_width;
	camera->viewportHeight = m_height;
}

/** 8
	* @return the width of the stage in dips */
float Stage::width () 
{
	return m_width;
}

/** @return the height of the stage in dips */
float Stage::height () 
{
	return m_height;
}

/** @return the x-coordinate of the left edge of the stage in dips */
int Stage::left () 
{
	return 0;
}

/** @return the x-coordinate of the right edge of the stage in dips */
float Stage::right() 
{
	return m_width - 1;
}

/** @return the y-coordinate of the top edge of the stage in dips */
float Stage::top() 
{
	return m_height - 1;
}

/** @return the y-coordinate of the bottom edge of the stage in dips */
float Stage::bottom() 
{
	return 0;
}

/** @return the center x-coordinate of the stage in dips */
float Stage::centerX() 
{
	return m_centerX;
}

/** @return the center y-coordinate of the stage in dips */
float Stage::centerY() 
{
	return m_centerY;
}

/** @return whether the stage is stretched */
bool Stage::isStretched() 
{
	return m_stretch;
}

/** Finds the {@link Actor} with the given name in the stage hierarchy.
	* @param name
	* @return the Actor or null if it couldn't be found. */
Actor* Stage::findActor( std::string name) 
{
	return root->findActor(name);
}

/** @return all top level {@link Actor}s */
const std::list<Actor*>& Stage::getActors() 
{
	return root->getActors();
}

/** @return all top level {@link Group}s */
const std::list<Group*>& Stage::getGroups() 
{
	return root->getGroups();
}


/** Call this to distribute a touch down event to the stage.
	* @param x the x coordinate of the touch in screen coordinates
	* @param y the y coordinate of the touch in screen coordinates
	* @param pointer the pointer index
	* @param button the button that's been pressed
	* @return whether an {@link Actor} in the scene processed the event or not */
bool Stage::touchDown( int x, int y, int pointer, int button) 
{
	setKeyboardFocus( NULL);
	Actor* actor = touchFocus[pointer];
	if( actor == NULL) actor = root;
	toStageCoordinates( x, y, coords);
	Group::toChildCoordinates( actor, coords.x, coords.y, point);
	return actor->touchDown( point.x, point.y, pointer);
}

/** Call this to distribute a touch Up event to the stage.
	* 
	* @param x the x coordinate of the touch in screen coordinates
	* @param y the y coordinate of the touch in screen coordinates
	* @param pointer the pointer index
	* @return whether an {@link Actor} in the scene processed the event or not */
bool Stage::touchUp( int x, int y, int pointer, int button) 
{
	Actor* actor = touchFocus[ pointer];
	if (actor == NULL) return false;
	toStageCoordinates(x, y, coords);
	actor->toLocalCoordinates(coords);
	actor->touchUp(coords.x, coords.y, pointer);
	// Clear touch focus if it hasn't changed.
	if (touchFocus[pointer] == actor) 
    touchFocus[pointer] = NULL;
	return true;
}

/** Call this to distribute a touch dragged event to the stage.
	* @param x the x coordinate of the touch in screen coordinates
	* @param y the y coordinate of the touch in screen coordinates
	* @param pointer the pointer index
	* @return whether an {@link Actor} in the scene processed the event or not */
bool Stage::touchDragged( int x, int y, int pointer) 
{
	toStageCoordinates( x, y, coords);
	bool handled = false;
	for (int i = 0, n = 20; i < n; i++) 
  {
		Actor* actor = touchFocus[i];
		if( actor != NULL) 
    {
			point.set( coords);
			actor->toLocalCoordinates(point);
			actor->touchDragged(point.x, point.y, pointer);
			handled = true;
		}
	}
	return handled;
}

/** Call this to distribute a touch moved event to the stage. This event will only ever appear on the desktop.
	* @param x the x coordinate of the touch in screen coordinates
	* @param y the y coordinate of the touch in screen coordinates
	* @return whether an {@link Actor} in the scene processed the event or not */
bool Stage::touchMoved (int x, int y) 
{
	toStageCoordinates( x, y, coords);
	Group::toChildCoordinates( root, coords.x, coords.y, point);
	return root->touchMoved(point.x, point.y);
}

/** Call this to distribute a mouse scroll event to the stage. This event will only ever appear on the desktop.
	* @param amount the scroll amount.
	* @return whether an {@link Actor} in the scene processed the event or not. */
bool Stage::scrolled( int amount) 
{
	if( scrollFocus == NULL) return false;
	return scrollFocus->scrolled(amount);
}

/** Called when a key was pressed
	* 
	* @param keycode one of the constants in {@link Keys}
	* @return whether the input was processed */
bool Stage::keyDown( int keycode) 
{
	if( keyboardFocus == NULL) return false;
	return keyboardFocus->keyDown(keycode);
}

/** Called when a key was released
	* 
	* @param keycode one of the constants in {@link Keys}
	* @return whether the input was processed */
bool Stage::keyUp(int keycode) 
{
	if( keyboardFocus == NULL) return false;
	return keyboardFocus->keyUp(keycode);
}

/** Called when a key was typed
	* 
	* @param character The character
	* @return whether the input was processed */
bool Stage::keyTyped( char character) 
{
	if( keyboardFocus == NULL) return false;
	return keyboardFocus->keyTyped(character);
}

/** Calls the {@link Actor#act(float)} method of all contained Actors. This will advance any {@link Action}s active for an
	* Actor.
	* @param delta the delta time in seconds since the last invocation */
void Stage::act( float delta) 
{
	root->act(delta);
}

/** Renders the stage */
void Stage::draw () 
{
	camera->update();
	if (! root->visible) return;
	batch->setProjectionMatrix( camera->combined);
	batch->begin();
	root->draw( batch, 1);
	batch->end();
}

/** Disposes the stage */
void Stage::dispose() 
{
	/*if( ownsBatch) 
  {
    batch.dispose();
  }
  */
}

/** Adds an {@link Actor} to this stage
	* @param actor the Actor */
void Stage::addActor( Actor* actor) 
{
	root->addActor(actor);
}

/** @return the Stage graph as a silly string */
std::string Stage::graphToString() 
{
  std::string buffer;
	graphToString( buffer, root, 0);
	return buffer.c_str();
}

void Stage::graphToString( std::string& buffer, Actor* actor, int level) 
{
  std::stringstream buff;

	for (int i = 0; i < level; i++)
		buff << ' ';

	buff << actor->toString();
	buff << "\n";

  buffer += buff.str();
	if( ObjectGroup == actor->type()) 
  {
		Group* group = ( Group*) actor;
    std::list<Actor*>::iterator it;
		for( it = group->getActors().begin(); it != group->getActors().end(); it++)
    {
			graphToString( buffer, *it, level + 1);
    }
	}
}

/** @return the root {@link Group} of this Stage. */
Group* Stage::getRoot () 
{
	return root;
}

/** @return the {@link SpriteBatch} offers its {@link Actor}s for rendering. */
SpriteBatch* Stage::getSpriteBatch () 
{
	return batch;
}

/** @return the {@link Camera} of this stage. */
Camera* Stage::getCamera() 
{
	return camera;
}

/** Sets the {@link Camera} this stage uses. You are responsible for setting it up properly! The {@link Stage#draw()} will call
	* the Camera's update() method and use it's combined matrix as the projection matrix for the SpriteBatch.
	* @param camera the {@link Camera} */
void Stage::setCamera( Camera* camera) 
{
  if( NULL != this->camera)
  {
    delete this->camera;
    this->camera = NULL;
  }
	this->camera = camera;
}

/** @return the {@link Actor} last hit by a touch event. */
Actor* Stage::getLastTouchedChild() 
{
	return root->lastTouchedChild;
}

/** Returns the {@link Actor} intersecting with the point (x,y) in stage coordinates. Hit testing is performed in the order the
	* Actors were inserted into the Stage, last inserted Actors being tested first. To get stage coordinates from screen
	* coordinates use {@link #toStageCoordinates(int, int, Vector2)}.
	* 
	* @param x the x-coordinate in stage coordinates
	* @param y the y-coordinate in stage coordinates
	* @return the hit Actor or null */
Actor* Stage::hit( float x, float y) 
{
	Group::toChildCoordinates( root, x, y, point);
	return root->hit( point.x, point.y);
}



/** Transforms the given screen coordinates to stage coordinates
	* @param x the x-coordinate in screen coordinates
	* @param y the y-coordinate in screen coordinates
	* @param out the output {@link Vector2}. */
void Stage::toStageCoordinates ( int x, int y, Vector2& out) 
{
	camera->unproject( tmp.set( x, y, 0));
	out.x = tmp.x;
	out.y = tmp.y;
}

/** Clears this stage, removing all {@link Actor}s and {@link Group}s. */
void Stage::clear () 
{
	root->clear();
}

/** Removes the given {@link Actor} from the stage by trying to find it recursively in the scenegraph.
	* @param actor the actor */
void Stage::removeActor( Actor* actor) 
{
	root->removeActorRecursive( actor);
}

void Stage::unfocusAll() 
{
	for (int i = 0, n = 20; i < n; i++)
		touchFocus[i] = NULL;
	scrollFocus = NULL;
	keyboardFocus = NULL;
}

void Stage::unfocus( Actor* actor) 
{
	for (int i = 0, n = 20; i < n; i++)
		if (touchFocus[i] == actor) touchFocus[i] = NULL;
	if (scrollFocus == actor) scrollFocus = NULL;
	if (keyboardFocus == actor) keyboardFocus = NULL;
}

void Stage::unfocus( Actor* actor, int pointer) 
{
	if (touchFocus[pointer] == actor) touchFocus[pointer] = NULL;
	if (scrollFocus == actor) scrollFocus = NULL;
	if (keyboardFocus == actor) keyboardFocus = NULL;
}

void Stage::setKeyboardFocus( Actor* actor) 
{
	keyboardFocus = actor;
}

Actor* Stage::getKeyboardFocus() 
{
	return keyboardFocus;
}

void Stage::setScrollFocus( Actor* actor) 
{
	scrollFocus = actor;
}

Actor* Stage::getScrollFocus() 
{
	return scrollFocus;
}

void Stage::setTouchFocus( Actor* actor, int pointer) 
{
	touchFocus[pointer] = actor;
}

Actor* Stage::getTouchFocus( int pointer) 
{
	return touchFocus[pointer];
}