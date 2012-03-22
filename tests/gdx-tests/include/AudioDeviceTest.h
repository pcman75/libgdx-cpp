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
#include "Threading.h"

class AudioDeviceTest :
	public GdxTest
{
private:
	AudioDevice* m_device;

	/** playing back thread**/
	Thread* m_playbackThread;
	Mutex* m_stopMutex;
	WaitCondition* m_waitCondition;
	bool m_mustStopSound;

public:
	AudioDeviceTest()
	{
	}

	static void play(void* arg)
	{
		AudioDeviceTest* testData = (AudioDeviceTest*)arg;

		float frequency = 440;
		float increment = (float)(2 * MathUtils::PI) * frequency / 44100; // angular increment for each sample
		float angle = 0;
		float samples[1024];

		while (!testData->mustStopSound())
		{
			for (int i = 0; i < 1024; i += 2)
			{
				samples[i] = 0.5f * (float)sin(angle);
				samples[i + 1] = 2 * samples[i];
				angle += increment;
			}

			testData->m_device->writeSamples(samples, 1024);
		}

		testData->soundStopped();
	}

	void create ()
	{
		m_mustStopSound = false;

		m_device = Gdx.app->getAudio()->newAudioDevice(44100, false);

		//create a mutex to sinchronize threads on the stop audio condition
		m_stopMutex = Gdx.threading->createMutex();

		m_waitCondition = Gdx.threading->createWaitCondition();

		// start a thread for playback
		m_playbackThread = Gdx.threading->createThread(play, this);



	}

	bool mustStopSound()
	{
		bool mustStop;
		m_stopMutex->lock();
		mustStop = m_mustStopSound;
		m_stopMutex->unlock();
		return mustStop;
	}

	void stopSound()
	{
		m_stopMutex->lock();
		m_mustStopSound = true;
		m_waitCondition->wait(m_stopMutex, WaitCondition::infinity);
		m_stopMutex->unlock();
	}

	void soundStopped()
	{
		m_waitCondition->signal();
	}
	void dispose ()
	{
		stopSound();

		delete m_playbackThread;
		delete m_stopMutex;
		delete m_waitCondition;

		m_device->dispose();
		delete m_device;
	}

	GDX_DEFINE_CREATOR(AudioDeviceTest);
};
