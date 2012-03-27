/*******************************************************************************
 * Copyright 2011 See AUTHORS file.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#pragma once

#include "InputAdapter.h"
#include "Camera.h"
#include "Vector2.h"
class Group;
class SpriteBatch;
class Actor;


/** A stage is a container for {@link Actor}s and handles distributing touch events, animating actors and asking them to render
 * themselves. A stage is 2D scenegraph with hierarchies of Actors.
 * <p>
 * A stage fills the whole screen. It has a width and height given in device independent pixels. It has a {@link Camera} that maps
 * this viewport to the given real screen resolution. If the stretched attribute is set to true then the viewport is enforced no
 * matter the difference in aspect ratio between the stage object and the screen dimensions. In case stretch is disabled then the
 * viewport is extended in the bigger screen dimensions.
 * <p>
 * Actors have a z-order which is equal to the order they were inserted into the stage. Actors inserted later will be drawn on top
 * of actors added earlier. Touch events that will get distributed to later actors first.
 * <p>
 * Actors can be focused. When your game pauses and resumes be sure to call the {@link Stage#unfocusAll()} method so that the
 * focus states get reset for each pointer id. You also have to make sure that the actors that were focused reset their state if
 * the depend on being focused, e.g. wait for a touch up event. An easier way to tackle this is to recreate the stage if possible.
 * @author mzechner */
class Stage : public InputAdapter
{
protected:
  float m_width;
  float m_height;
  float m_centerX;
  float m_centerY;
  bool m_stretch;

  Group* root;

  bool ownsBatch;
  SpriteBatch* batch;
  Camera* camera;

  Vector2 point;
	Vector2 coords;
  Vector3 tmp;

private:
	Actor* touchFocus[20];
	Actor* keyboardFocus;
  Actor* scrollFocus;
  

public:
	/** Constructs a new Stage object with the given dimensions. If the device resolution does not equal the Stage objects
	 * dimensions the stage object will setup a projection matrix to guarantee a fixed coordinate system. If stretch is disabled
	 * then the bigger dimension of the Stage will be increased to accomodate the actual device resolution.
	 * @param width the width of the viewport
	 * @param height the height of the viewport
	 * @param stretch whether to stretch the viewport to the real device resolution */
	Stage( float width, float height, bool stretch);
  
	/** Constructs a new Stage object with the given dimensions. If the device resolution does not equal the Stage objects
	 * dimensions the stage object will setup a projection matrix to guarantee a fixed coordinate system. If stretch is disabled
	 * then the bigger dimension of the Stage will be increased to accomodate the actual device resolution.
	 * @param width the width of the viewport
	 * @param height the height of the viewport
	 * @param stretch whether to stretch the viewport to the real device resolution
	 * @param batch the {@link SpriteBatch} this Stage should use. Will not be disposed if {@link #dispose()} is called. */
	Stage( float width, float height, bool stretch, SpriteBatch* batch);

  virtual ~Stage();

	/** Sets the viewport dimensions in device independent pixels. If stretch is false and the viewport aspect ratio is not equal to
	 * the device ratio then the bigger dimension of the viewport will be extended (device independent pixels stay quardatic
	 * instead of getting stretched).
	 * 
	 * @param width thew width of the viewport in device independent pixels
	 * @param height the height of the viewport in device independent pixels
	 * @param stretch whether to stretch the viewport or not */
	void setViewport (float width, float height, bool stretch);

	/** 8
	 * @return the width of the stage in dips */
	float width();

	/** @return the height of the stage in dips */
	float height();

	/** @return the x-coordinate of the left edge of the stage in dips */
	int left();

	/** @return the x-coordinate of the right edge of the stage in dips */
	float right();

	/** @return the y-coordinate of the top edge of the stage in dips */
	float top();

	/** @return the y-coordinate of the bottom edge of the stage in dips */
	float bottom();

	/** @return the center x-coordinate of the stage in dips */
	float centerX();

	/** @return the center y-coordinate of the stage in dips */
	float centerY();

	/** @return whether the stage is stretched */
	bool isStretched();

	/** Finds the {@link Actor} with the given name in the stage hierarchy.
	 * @param name
	 * @return the Actor or null if it couldn't be found. */
	Actor* findActor( std::string name);

	/** @return all top level {@link Actor}s */
	const std::list<Actor*>& getActors();

	/** @return all top level {@link Group}s */
	const std::list<Group*>& getGroups();

	
	/** Call this to distribute a touch down event to the stage.
	 * @param x the x coordinate of the touch in screen coordinates
	 * @param y the y coordinate of the touch in screen coordinates
	 * @param pointer the pointer index
	 * @param button the button that's been pressed
	 * @return whether an {@link Actor} in the scene processed the event or not */
	virtual bool touchDown (int x, int y, int pointer, int button);

	/** Call this to distribute a touch Up event to the stage.
	 * 
	 * @param x the x coordinate of the touch in screen coordinates
	 * @param y the y coordinate of the touch in screen coordinates
	 * @param pointer the pointer index
	 * @return whether an {@link Actor} in the scene processed the event or not */
	virtual bool touchUp (int x, int y, int pointer, int button);

	/** Call this to distribute a touch dragged event to the stage.
	 * @param x the x coordinate of the touch in screen coordinates
	 * @param y the y coordinate of the touch in screen coordinates
	 * @param pointer the pointer index
	 * @return whether an {@link Actor} in the scene processed the event or not */
	virtual bool touchDragged (int x, int y, int pointer);

	/** Call this to distribute a touch moved event to the stage. This event will only ever appear on the desktop.
	 * @param x the x coordinate of the touch in screen coordinates
	 * @param y the y coordinate of the touch in screen coordinates
	 * @return whether an {@link Actor} in the scene processed the event or not */
	virtual bool touchMoved (int x, int y);

	/** Call this to distribute a mouse scroll event to the stage. This event will only ever appear on the desktop.
	 * @param amount the scroll amount.
	 * @return whether an {@link Actor} in the scene processed the event or not. */
	virtual bool scrolled (int amount);

	/** Called when a key was pressed
	 * 
	 * @param keycode one of the constants in {@link Keys}
	 * @return whether the input was processed */
	virtual bool keyDown (int keycode);

	/** Called when a key was released
	 * 
	 * @param keycode one of the constants in {@link Keys}
	 * @return whether the input was processed */
	virtual bool keyUp (int keycode);

	/** Called when a key was typed
	 * 
	 * @param character The character
	 * @return whether the input was processed */
	virtual bool keyTyped (char character);

	/** Calls the {@link Actor#act(float)} method of all contained Actors. This will advance any {@link Action}s active for an
	 * Actor.
	 * @param delta the delta time in seconds since the last invocation */
	void act (float delta);

	/** Renders the stage */
	void draw ();

	/** Disposes the stage */
	void dispose();

	/** Adds an {@link Actor} to this stage
	 * @param actor the Actor */
	void addActor( Actor* actor);

	/** @return the Stage graph as a silly string */
	std::string graphToString();

	void graphToString( std::string& buffer, Actor* actor, int level);

	/** @return the root {@link Group} of this Stage. */
	Group* getRoot();

	/** @return the {@link SpriteBatch} offers its {@link Actor}s for rendering. */
	SpriteBatch* getSpriteBatch();

	/** @return the {@link Camera} of this stage. */
	Camera* getCamera();

	/** Sets the {@link Camera} this stage uses. You are responsible for setting it up properly! The {@link Stage#draw()} will call
	 * the Camera's update() method and use it's combined matrix as the projection matrix for the SpriteBatch.
	 * @param camera the {@link Camera} */
	void setCamera( Camera* camera);

	/** @return the {@link Actor} last hit by a touch event. */
	Actor* getLastTouchedChild();

	/** Returns the {@link Actor} intersecting with the point (x,y) in stage coordinates. Hit testing is performed in the order the
	 * Actors were inserted into the Stage, last inserted Actors being tested first. To get stage coordinates from screen
	 * coordinates use {@link #toStageCoordinates(int, int, Vector2)}.
	 * 
	 * @param x the x-coordinate in stage coordinates
	 * @param y the y-coordinate in stage coordinates
	 * @return the hit Actor or null */
	Actor* hit( float x, float y);

	/** Transforms the given screen coordinates to stage coordinates
	 * @param x the x-coordinate in screen coordinates
	 * @param y the y-coordinate in screen coordinates
	 * @param out the output {@link Vector2}. */
	void toStageCoordinates( int x, int y, Vector2& out);

	/** Clears this stage, removing all {@link Actor}s and {@link Group}s. */
	void clear();

	/** Removes the given {@link Actor} from the stage by trying to find it recursively in the scenegraph.
	 * @param actor the actor */
	void removeActor( Actor* actor);

	void unfocusAll();

	void unfocus( Actor* actor);

	void unfocus( Actor* actor, int pointer);

	void setKeyboardFocus( Actor* actor);

	Actor* getKeyboardFocus();

	void setScrollFocus( Actor* actor);

	Actor* getScrollFocus();

	void setTouchFocus( Actor* actor, int pointer);

	Actor* getTouchFocus( int pointer);
};
