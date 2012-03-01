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

/** Provides methods for an actor to participate in layout and to provide a minimum, preferred, and maximum size.
 * @author Nathan Sweet */
class GdxDllImportExport Layout 
{
public:

	/** Computes and caches any information needed for drawing and, if this actor has children, positions and sizes each child and
	 * calls {@link #invalidate()} and then {@link #validate()} on each one. Usually this should not be called directly, instead
	 * {@link #validate()} should be used. */
	virtual void layout() = 0;

	/** Invalidates this actor's layout, causing {@link #layout()} to be called the next time {@link #validate()} is called. This
	 * should be done when state changes in the actor that requires a layout but does not change the minimum, preferred, maximum,
	 * or actual size of the actor (meaning it does not affect the parent actor's layout). */
	virtual void invalidate() = 0;

	/** Invalidates this actor and all its parents, calling {@link #invalidate()} on all involved actors. This method should be
	 * called when state changes in the actor that affects the minimum, preferred, maximum, or actual size of the actor (meaning it
	 * potentially affects the parent actor's layout). */
	virtual void invalidateHierarchy() = 0;

	/** Ensures the actor has been laid out. Calls {@link #layout()} if {@link #invalidate()} has called since the last time
	 * {@link #validate()} was called. This method is usually called in {@link Actor#draw(SpriteBatch, float)} before drawing is
	 * performed. */
	virtual void validate() = 0;

	/** Sizes this actor to its preferred width and height and, if its size was changed, causes the actor to be laid out by calling
	 * {@link #invalidate()} and then {@link #validate()}.
	 * <p>
	 * Generally this method should not be called in a constructor because it calls {@link #layout()}, which means a subclass would
	 * have layout() called before the subclass' constructor. Instead, in a constructor simply set the actors width and height to
	 * {@link #getPrefWidth()} and {@link #getPrefHeight()}. This allows the actor to have a size at construction time for more
	 * convenient use outside of a {@link Table}. */
	virtual void pack() = 0;

	virtual float getMinWidth() = 0;

	virtual float getMinHeight() = 0;

	virtual float getPrefWidth() = 0;

	virtual float getPrefHeight() = 0;

	virtual float getMaxWidth() = 0;

	virtual float getMaxHeight() = 0;
};
