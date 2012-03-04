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

#include "GdxTest.h"
#include "Gdx.h"
#include "AudioDevice.h"

class AudioDeviceTest :
	public GdxTest
{
private:
	bool stop;
public:
	AudioDeviceTest()
	{
		stop = false;
	}
	void create ()
	{
			AudioDevice* device = Gdx.app->getAudio()->newAudioDevice(44100, false);
			float frequency = 440;
			float increment = (float)(2 * MathUtils::PI) * frequency / 44100; // angular increment for each sample
			float angle = 0;
			float samples[1024];

			//TODO 
			//run audio on a different thread
			while (!stop)
			{
				for (int i = 0; i < 1024; i += 2)
				{
					samples[i] = 0.5f * (float)sin(angle);
					samples[i + 1] = 2 * samples[i];
					angle += increment;
				}

				device->writeSamples(samples, 1024);
			}
			device->dispose();
	}

	void dispose ()
	{
		stop = true;
	}

	GDX_DEFINE_CREATOR(AudioDeviceTest);
};
