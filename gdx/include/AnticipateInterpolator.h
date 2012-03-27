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

#include "Interpolator.h"

/** An {@link Interpolator} where the changes start backwards and than spring forward as the time progresses.
 * 
 * @author Moritz Post <moritzpost@gmail.com> */
class AnticipateInterpolator : public Interpolator 
{
private:
  static float DEFAULT_TENSION;
	float tension;

public:

	/** Gets a new {@link AnticipateInterpolator} from a maintained pool of {@link Interpolator}s.
	 * 
	 * @param tension the tension controlling the rate spring effect of the animation
	 * @return the obtained {@link AccelerateInterpolator} */
	AnticipateInterpolator(float tension);
  virtual ~AnticipateInterpolator ();
  
	virtual void finished ();
  
	float getInterpolation (float t);
  
	virtual Interpolator* copy ();
  
};
