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
#include "Interpolator.h"

/** An interpolator where the change overshoots the target and springs back to the target position.
 * <p>
 * The factor defines the rate of overshoot.
 * 
 * @author Moritz Post <moritzpost@gmail.com> */
class GdxDllImportExport OvershootInterpolator : public Interpolator 
{
private:
  static float DEFAULT_FACTOR;
	float factor;
	double doubledFactor;

public:
	/** Gets a new {@link OvershootInterpolator} from a maintained pool of {@link Interpolator}s.
	 * 
	 * @param factor the factor controlling the rate of overshoot energy change
	 * @return the obtained {@link OvershootInterpolator} */
	OvershootInterpolator (float factor);
  virtual ~OvershootInterpolator ();
  
	virtual void finished ();
  
	float getInterpolation (float t);
  
	virtual Interpolator* copy ();
};
