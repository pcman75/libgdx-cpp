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
#include "TextureRegion.h"

/** <p>
 * An Animation stores a list of {@link TextureRegion}s representing an animated sequence, e.g. for running or jumping. Each
 * region of an Animation is called a key frame, multiple key frames make up the animation.
 * <p>
 */
class GdxDllImportExport Animation
{
private:
	TextureRegion** m_keyFrames;
	int m_keyFramesNum;

public:
	float frameDuration;

public:
	/** Constructor, storing the frame duration and key frames.
	 *
	 * @param frameDuration the time between frames in seconds.
	 * @param keyFrames the {@link TextureRegion}s representing the frames. */
	Animation(float frameDuration,const std::list<TextureRegion*>& keyFrames);

	/** Returns a {@link TextureRegion} based on the so called state time. This is the amount of seconds an object has spent in the
	 * state this Animation instance represents, e.g. running, jumping and so on. The mode specifies whether the animation is
	 * looping or not.
	 * @param stateTime the time spent in the state represented by this animation.
	 * @param looping whether the animation is looping or not.
	 * @return the TextureRegion representing the frame of animation for the given state time. */
	TextureRegion* getKeyFrame(float stateTime, bool looping);

	/**
	 * Whether the animation would be finished if played without looping
	 * given the state time.
	 * @param stateTime
	 * @return whether the animation is finished.
	 */
	bool isAnimationFinished(float stateTime);
};
