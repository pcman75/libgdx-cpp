/*******************************************************************************
 * Copyright 2011 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License") = 0;
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

/** <p>
 * A Sound is a short audio clip that can be played numerous times in parallel. It's completely loaded into memory so only load
 * small audio files. Call the {@link #dispose()} method when you're done using the Sound.
 * </p>
 *
 * <p>
 * Sound instances are created via a call to {@link Audio#newSound(FileHandle)}.
 * </p>
 *
 * <p>
 * Calling the {@link #play()} or {@link #play(float)} method will return a long which is an id to that instance of the sound. You
 * can use this id to modify the playback of that sound instance.
 * </p>
 */
class Sound
{
public:
	virtual ~Sound() {}

	/** Plays the sound. If the sound is already playing, it will be played again, concurrently.
	 * @return the id of the sound instance. */
	virtual long play() = 0;

	/** Plays the sound. If the sound is already playing, it will be played again, concurrently.
	 * @param volume the volume in the range [0,1]
	 * @return the id of the sound instance */
	virtual long play(float volume) = 0;

	/** Plays the sound, looping. If the sound is already playing, it will be played again, concurrently.
	 * @return the id of the sound instance */
	virtual long loop() = 0;

	/** Plays the sound, looping. If the sound is already playing, it will be played again, concurrently.
	 * @param volume the volume in the range [0, 1]
	 * @return the id of the sound instance */
	virtual long loop(float volume) = 0;

	/** Stops playing all instances of this sound. */
	virtual void stop() = 0;

	/** Releases all the resources. */
	virtual void dispose() = 0;

	/** Stops the sound instance with the given id as returned by {@link #play()} or {@link #play(float)}. If the sound is no longer
	 * playing, this has no effect.
	 * @param soundId the sound id */
	virtual void stop(long soundId) = 0;

	/** Sets the sound instance with the given id to be looping. If the sound is no longer playing this has no effect.s
	 * @param soundId the sound id
	 * @param looping whether to loop or not. */
	virtual void setLooping(long soundId, bool looping) = 0;

	/** Changes the pitch multiplier of the sound instance with the given id as returned by {@link #play()} or {@link #play(float)}.
	 * If the sound is no longer playing, this has no effect.
	 * @param soundId the sound id
	 * @param pitch the pitch multiplier, 1 == default, >1 == faster, <1 == slower */
	virtual void setPitch(long soundId, float pitch) = 0;

	/** Changes the volume of the sound instance with the given id as returned by {@link #play()} or {@link #play(float)}. If the
	 * sound is no longer playing, this has no effect.
	 * @param soundId the sound id
	 * @param volume the volume in the range 0 (silent) to 1 (max volume). */
	virtual void setVolume(long soundId, float volume) = 0;

	/** Sets the panning and volume of the sound instance with the given id as returned by {@link #play()} or {@link #play(float)}.
	 * If the sound is no longer playing, this has no effect.
	 * @param soundId the sound id
	 * @param pan panning in the range -1 (full right) to 1 (full left). 0 is center position.
	 * @param volume the volume in the range [0,1]. */
	virtual void setPan(long soundId, float pan, float volume) = 0;
};
