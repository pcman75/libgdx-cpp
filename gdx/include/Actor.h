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
#include "GdxDefines.h"
#include "Vector2.h"
#include "Color.h"
#include "Action.h"

class Group;
class Stage;
class SpriteBatch;

enum ObjectType
{
  ObjectActor,
  ObjectGroup
};

/** <p>
 * An Actor is part of a {@link Stage} or a {@link Group} within a Stage. It has a position, a rectangular size given as width and
 * height, a rotation angle, a scale in x and y and an origin relative to the position which is used for rotation and scaling.
 * </p>
 * 
 * <p>
 * The position of an Actor is coincident with its unrotated, unscaled bottom left corner.
 * </p>
 * 
 * <p>
 * An Actor can be a child of a Group or the Stage. The object it belongs to is called the Actor's parent. An Actor's position is
 * always relative to the bottom left corner of its parent.
 * </p>
 * 
 * <p>
 * Every Actor must have a unique name within a Stage.
 * </p>
 * 
 * <p>
 * An Actor can receive touch events when its {@link #touchable} attribute is set to true. The Stage will delegate touch events to
 * an Actor in this case, calling its {@link #touchDown(float, float, int)}, {@link #touchUp(float, float, int)} and
 * {@link #touchDragged(float, float, int)} methods. The coordinates passed to an Actor will be in the Actor's coordinate system,
 * easing the pain of intersection testing. The coordinate system has it's origin at the Actor's rotated and scaled bottom left
 * corner, with the x-axis pointing to the right and the y-axis pointing to the left.
 * </p>
 * 
 * <p>
 * An Actor can be intersection tested via a call this its {@link #hit(float, float)} method. The coordinates given are again in
 * the Actor's coordinate system.
 * </p>
 * 
 * <p>
 * An Actor might render itself when its {@link #draw(SpriteBatch, float)} method is called. The projection and transform matrices
 * are setup so that an Actor can simply call the
 * {@link SpriteBatch#draw(com.badlogic.gdx.graphics.Texture, float, float, float, float, float, float, float, float, float, int, int, int, int, bool, bool)}
 * method to render himself. Using a {@link Sprite} instance is also an option. An Actor might decide to not render itself at all
 * or chose another way to render itself. For the later it has to call {@link SpriteBatch#end()} first, setup up all render states
 * needed to render itself, render itself and then call {@link SpriteBatch#begin()} again so that the rendering for other Actor's
 * is undisturbed. You have to know what you do if you want to try this.
 * </p>
 * 
 * <p>
 * An Actor can be controlled by {@link Action}s. An Action will modify some of the attributes of an Actor such as its position or
 * rotation. Actions can be chained and make for rather sophisticated time based behaviour.
 * <p>
 * 
 * @author mzechner */
class GdxDllImportExport Actor 
{
public:
	Group* parent;
	std::string name;
	bool touchable;
	bool visible;

	float x;
	float y;
	float width;
	float height;
	float originX;
	float originY;
	float scaleX;
	float scaleY;
	float rotation;
	Color color;

  Stage* stage;

  

protected:
	//PooledLinkedList<Action> actions = new PooledLinkedList<Action>(10);
  std::list<Action*> actions;
  

private:
  bool toRemove;

public:
	/** Creates an actor without a name. */
	Actor();
	Actor( std::string name);
  virtual ~Actor();

  virtual ObjectType type() { return ObjectActor; }

	/** Draws the Actor. The spriteBatch is configured so that the Actor can draw in its parents coordinate system. The parent's
	 * alpha is passed to the method in order for the Actor to multiply it with its own alpha. This will allow {@link FadeIn} and
	 * other Actions to have an effect even if they are only set on the parent of the Actor.
	 * 
	 * @param batch the spritebatch to render with
	 * @param parentAlpha the parent's alpha value. */
	virtual void draw( SpriteBatch* pBatch, float parentAlpha) = 0;

	bool touchDown( float x, float y, int pointer);
  
	void touchUp( float x, float y, int pointer);
  
	void touchDragged( float x, float y, int pointer);
  
	bool touchMoved( float x, float y);
  
	bool scrolled( int amount);
  
	bool keyDown( int keycode);
  
	bool keyUp( int keycode);
  
	bool keyTyped( char character);
  
	virtual Actor* hit(float x, float y) = 0;

	/** Transforms the given point in stage coordinates to the Actor's local coordinate system.
	 * @param point the point */
	void toLocalCoordinates( Vector2& point);
  
	/** Removes this actor from the Stage */
	void remove();
  
	void act( float delta);
  
	/** Adds an {@link Action} to the Actor. Actions will be automatically performed in the order added to the Actor and will be
	 * removed when they are done.
	 * 
	 * @param action the action */
	void action( Action* pAction);
  
	/** Clears all actions of this Actor. */
	void clearActions();
  
	virtual	std::string toString();
  
	/** Marks the {@link Actor} to be removed by its parent.
	 * <p>
	 * The actual removal happens in the {@link Group#act(float)} method of the parent and after the parent has called
	 * {@link #act(float)} on this {@link Actor}.
	 * 
	 * @param remove whether the parent is supposed to remove this {@link Actor} */
	void markToRemove( bool remove);
  
	/** States if this actor is to be removed by its parent.
	 * 
	 * @return <code>true</code> when the actor is to be removed or <code>false</code> otherwise */
	bool isMarkedToRemove();
  
	/** Returns the stage that this actor is currently in, or null if not in a stage. */
	Stage* getStage();
  
};