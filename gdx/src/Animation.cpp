#include "stdafx.h"
#include "Animation.h"

Animation::Animation(float frameDuration,const std::list<TextureRegion*>& keyFrames)
{
	m_keyFramesNum = (int)keyFrames.size();
	this->frameDuration = frameDuration;
	m_keyFrames = new TextureRegion*[keyFrames.size()];

	int i = 0;
	for(std::list<TextureRegion*>::const_iterator it = keyFrames.begin(); it != keyFrames.end(); it++)
	{
		m_keyFrames[i] = *it;
		i++;
	}
}


/** Returns a {@link TextureRegion} based on the so called state time. This is the amount of seconds an object has spent in the
* state this Animation instance represents, e.g. running, jumping and so on. The mode specifies whether the animation is
* looping or not.
* @param stateTime the time spent in the state represented by this animation.
* @param looping whether the animation is looping or not.
* @return the TextureRegion representing the frame of animation for the given state time. */
TextureRegion* Animation::getKeyFrame(float stateTime, bool looping)
{
	int frameNumber = (int)(stateTime / frameDuration);

	if(!looping)
	{
		frameNumber = min(m_keyFramesNum - 1, frameNumber);
	}
	else
	{
		frameNumber = frameNumber % m_keyFramesNum;
	}
	return m_keyFrames[frameNumber];
}

/**
* Whether the animation would be finished if played without looping
* given the state time.
* @param stateTime
* @return whether the animation is finished.
*/
bool Animation::isAnimationFinished(float stateTime)
{
	int frameNumber = (int)(stateTime / frameDuration);
	return m_keyFramesNum - 1 < frameNumber;
}

