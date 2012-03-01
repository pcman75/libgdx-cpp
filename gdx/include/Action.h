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
#include "OnActionCompleted.h"
class Actor;

/** An Action is used with an {@link Actor} and modifes the Actor's attributes over time.
 * 
 * @author mzechner */
class GdxDllImportExport Action 
{
protected:
  OnActionCompleted* listener;

public:
  Action();
  virtual ~Action();

	/** Sets the {@link Actor} of this action. Will be called when the Action is added to an Actor via {@link Actor#action(Action)}
	 * before any other call to this interface.
	 * 
	 * @param actor the actor. */
	virtual void setTarget( Actor* pActor) = 0;

	/** @return the {@link Actor} this action targets. */
	virtual Actor* getTarget() = 0;

	/** Apply the action.
	 * 
	 * @param delta delta time in seconds */
	virtual void act( float delta) =0;

	/** @return whether the action is done or not */
	virtual bool isDone() = 0;

	/** Called by the owner of the action when it can release all its resources, e.g. put itself back into a pool. */
	void finish();

	/** Calls the {@link OnActionCompleted} listener and sets it to null so it won't be called again. */
	void callActionCompletedListener();
  
	/** Creates a copy of this action. The action must be in a state independent of the original and one must be able to call
	 * {@link #setTarget(Actor)} on it without any side effects. */
	virtual Action* copy() = 0;

	/** Sets the listener to be invoked when the action is finished.
	 * @param listener
	 * @return this */
	void setCompletionListener( OnActionCompleted* listener);
  
	/** @return the {@link OnActionCompleted} listener or null. */
	OnActionCompleted* getCompletionListener();
  
	/** Sets the Action back to a vanilla state. */
	void reset();

};
