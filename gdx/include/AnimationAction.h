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

#include "Action.h"
class Actor;
class Interpolator;

/** An {@link AnimationAction} performs a transformation on its target {@link Actor}. These transformations physically change the
 * Actor itself.
 * 
 * @author Moritz Post <moritzpost@gmail.com> */
class AnimationAction : public Action 
{
protected:
	float duration;
	float invDuration;
	float taken;
	Actor* target;
	bool done;

	Interpolator* interpolator;

public:
  AnimationAction();
  virtual ~AnimationAction();

  virtual bool isDone();
  
	virtual void finish();
  
	/** Sets an {@link Interpolator} to modify the progression of the animations.
	 * 
	 * @param interpolator the interpolator to use during the animation
	 * @return an instance of self so that the call can be easily chained */
	void setInterpolator( Interpolator* interpolator);
  
	float createInterpolatedAlpha( float delta);

  Actor* getTarget();

	virtual void reset();
};
