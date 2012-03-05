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

/** An interpolator where the rate of change starts out slowly and then accelerates over time.
 * 
 * @author Moritz Post <moritzpost@gmail.com> */
class GdxDllImportExport AccelerateInterpolator : public Interpolator 
{
private:
  static float DEFAULT_FACTOR;
  float factor;
  double doubledFactor;

public:

	/** Gets a new {@link AccelerateInterpolator} from a maintained pool of {@link Interpolator}s.
	 * 
	 * @param factor the factor controlling the rate of change
	 * @return the obtained {@link AccelerateInterpolator} */
	AccelerateInterpolator(float factor);
  virtual ~AccelerateInterpolator ();
  
	virtual void finished ();
  
	float getInterpolation (float input);
  
	virtual Interpolator* copy ();
  
};