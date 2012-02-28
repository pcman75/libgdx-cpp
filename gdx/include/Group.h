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
#include "Actor.h"
#include "Cullable.h"
#include "Texture.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector2.h"
#include "Rectang.h"
#include "SpriteBatch.h"



/** A group is an Actor that contains other Actors (also other Groups which are Actors).
 * @author mzechner
 * @author Nathan Sweet */
class GdxDllImportExport Group : public Actor , Cullable 
{
public:
  static Texture* debugTexture;
	static bool debug;

  bool transform;
	Actor* lastTouchedChild;

protected:
  std::list<Actor*> children;
	std::list<Group*> groups;
	std::map<std::string, Actor*> namesToActors;

	Matrix3 localTransform;
	Matrix3 worldTransform;
	Matrix4 batchTransform;
	Matrix4 oldBatchTransform;

	Rectang cullingArea;
  bool hasCullingArea;
	Vector2 point;
	
public:
  Group();
  
	/** Creates a new Group with the given name.
	 * @param name the name of the group */
	Group( std::string name);

  virtual ObjectType type() { return ObjectGroup; }
  
	void act( float delta);
  
	virtual void draw( SpriteBatch* batch, float parentAlpha);
  
  void setCullingArea( const Rectang& cullingArea);
  
	virtual bool touchDown (float x, float y, int pointer);

	virtual bool touchMoved (float x, float y);

	Actor* hit( float x, float y);

  /** Adds an {@link Actor} to this Group. The order Actors are added is reversed for hit testing.
	 * @param actor the Actor */
	void addActor( Actor* actor);

	/** Adds an {@link Actor} at the given index in the group. The first Actor added will be at index 0 and so on. Throws an
	 * IndexOutOfBoundsException in case the index is invalid.
	 * @param index the index to add the actor at. */
	void addActorAt (int index, Actor* actor);

	/** Adds an {@link Actor} before the given Actor.
	 * @param actorBefore the Actor to add the other actor in front of
	 * @param actor the Actor to add */
	void addActorBefore (Actor* actorBefore, Actor* actor);

	/** Adds an {@link Actor} after the given Actor.
	 * @param actorAfter the Actor to add the other Actor behind
	 * @param actor the Actor to add */
	void addActorAfter( Actor* actorAfter, Actor* actor);

	/** Removes an {@link Actor} from this Group.
	 * @param actor */
	void removeActor( Actor* actor);

	/** Removes an {@link Actor} from this Group recursively by checking if the Actor is in this group or one of its child-groups.
	 * @param actor the Actor */
	void removeActorRecursive( Actor* actor);

  	/** Finds the {@link Actor} with the given name in this Group and its children.
	 * @param name the name of the Actor
	 * @return the Actor or null */
	Actor* findActor( std::string name);

	/** Swap two actors' sort order by index. 0 is lowest while getActors().size() - 1 is largest.
	 * @param first first Actor index
	 * @param second second Actor index
	 * @return false if indices are out of bound. */
	bool swapActor( int first, int second);

	/** Swap two actors' sort order by reference.
	 * @param first first Actor
	 * @param second second Actor
	 * @return false if any of the Actors is not the child of this Group. */
	bool swapActor( Actor* first, Actor* second);

  /** @return all child {@link Actor}s as an ordered list. */
	std::list<Actor*>& getActors();
  
	/** @return all child {@link Group}s as an unordered list. */
	std::list<Group*>& getGroups();
  
	/** Clears this Group, removing all contained {@link Actor}s. */
	void clear();
  
	/** Sorts the children via the given {@link Comparator}.
	 * @param comparator the comparator. */
	//void sortChildren( greater<Actor*> comparator);
  
	/** Converts coordinates for this group to those of a descendant actor.
	 * @throws IllegalArgumentException if the specified actor is not a descendant of this group. */
	void toLocalCoordinates( Actor* descendant, Vector2& point);
  
	bool isDescendant( Actor* actor);
  
	/** Transforms the coordinates given in the child's parent coordinate system to the child {@link Actor}'s coordinate system.
	 * @param child the child Actor
	 * @param x the x-coordinate in the Group's coordinate system
	 * @param y the y-coordinate in the Group's coordinate system
	 * @param out the output {@link Vector2} */
	static void toChildCoordinates( Actor* child, float x, float y, Vector2& out);
  
	static void enableDebugging (std::string debugTextureFile);

  static void disableDebugging ();
  
protected:
	void drawChildren( SpriteBatch* batch, float parentAlpha);
  
	void drawChild( Actor* child, SpriteBatch* batch, float parentAlpha);
  
	void applyTransform( SpriteBatch* batch);
  
	Matrix4 updateTransform();
  
	void resetTransform( SpriteBatch* batch);
  
	/** Called when actors are added to or removed from the group. */
	void childrenChanged ();
  
private:
	void setStage( Actor* actor, Stage* stage);
};
