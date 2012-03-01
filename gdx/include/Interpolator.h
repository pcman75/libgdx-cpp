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

/** An interpolator defines the rate of change of an animation. This allows the basic animation effects (alpha, scale, translate,
 * rotate) to be accelerated, decelerated etc.
 * 
 * @author Moritz Post <moritzpost@gmail.com> */
class GdxDllImportExport Interpolator 
{
public:
	/** Maps a point in the animation duration to a multiplier to be applied to the transformations of an animation. The Input is a
	 * percentage of the elapsed animation duration.
	 * 
	 * @param input A value between 0 and 1.0 indicating our current point in the animation where 0 represents the start and 1.0
	 *           represents the end
	 * @return The interpolation value. This value can be more than 1.0 for {@link Interpolator}s which overshoot their targets, or
	 *         less than 0 for {@link Interpolator}s that undershoot their targets. */
	virtual float getInterpolation( float input) = 0;

	/** Called when the animation has finished and the {@link Interpolator} is no longer needed. */
	virtual void finished() = 0;

	/** Creates a copy of this interpolator.
	 * @return the copy. */
	virtual Interpolator* copy() = 0;
};
