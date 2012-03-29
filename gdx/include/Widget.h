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
#include "Actor.h"
#include "Layout.h"

/** An {@link Actor} that participates in layout and provides a minimum, preferred, and maximum size.
 * <p>
 * The default preferred size of a widget is 0 and this is almost always overridden by a subclass. The default minimum size
 * returns the preferred size, so a subclass may choose to return 0 if it wants to allow itself to be sized smaller. The default
 * maximum size is 0, which means no maximum size.
 * <p>
 * See {@link Layout} for details on how a widget should participate in layout. A widget's mutator methods should call
 * {@link #invalidate()} or {@link #invalidateHierarchy()} as needed.
 * @author mzechner
 * @author Nathan Sweet */
class Widget :public Actor , Layout 
{
private:
  bool bNeedsLayout;

public:
	/** Creates a new widget without a name. */
	Widget ();
	Widget ( std::string name);

  float getMinWidth () ;

	float getMinHeight () ;
  
	float getPrefWidth () ;
  
	float getPrefHeight () ;
  
	float getMaxWidth () ;
  
	float getMaxHeight () ;
  
	void invalidate () ;
  
	void validate () ;
  
	/** Returns true if the widget's layout has been {@link #invalidate() invalidated}. */
	bool needsLayout () ;
  
	void invalidateHierarchy () ;
  
	void pack () ;
  
	/** If this method is overridden, the super method or {@link #validate()} should be called to ensure the widget is laid out. */
	void draw (SpriteBatch* batch, float parentAlpha) ;
  
	Actor* hit (float x, float y) ;
  
	void layout () ;
  
	bool touchDown (float x, float y, int pointer) ;
  
	void touchUp (float x, float y, int pointer) ;
  
	void touchDragged (float x, float y, int pointer) ;
  
	/** This modifies the specified point in the actor's coordinates to be in the stage's coordinates. Note this method will ONLY
	 * work properly for screen aligned, unrotated, unscaled actors! */
	static void toScreenCoordinates (Actor* actor, Vector2 point) ;
  
};
