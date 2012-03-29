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

/**
 * Demonstrates how to read and playback an OGG file with the {@link VorbisDecoder} found
 * in the gdx-audio extension.
 * @author mzechner
 *
 */

#pragma once
#include "GdxTest.h"
#include "VorbisDecoder.h"
#include "AudioDevice.h"
#include "Gdx.h"
#include "Threading.h"

class VorbisTest :
	public GdxTest 
{
	
	/** a VorbisDecoder to read PCM data from the ogg file **/
	VorbisDecoder* m_decoder;
	/** an AudioDevice for playing back the PCM data **/
	AudioDevice* m_device;
	
	/** playing back thread**/
	Thread* m_playbackThread;
	Mutex* m_stopMutex;
	WaitCondition* m_waitCondition;
	bool m_mustStopSound;

public:
	
	void create () 
	{
		m_mustStopSound = false;

		/** the file to playback **/
		static const char* FILE = "c:/cloudconnected.ogg";

		// copy ogg file to SD card, can't playback from assets
		FileHandle* externalFile = Gdx.files->externalHandle(FILE);
		//Gdx.files.internal(FILE).copyTo(externalFile);
		
		// Create the m_decoder and log some properties. Note that we need
		// an external or absolute file
		m_decoder = new VorbisDecoder(externalFile);
		delete externalFile;

		std::stringstream logMsg;
		logMsg << "channels: " << m_decoder->getChannels() << ", rate: " << m_decoder->getRate() << ", length: " << m_decoder->getLength();
		Gdx.app->log("Vorbis", logMsg.str());

		// Create an audio m_device for playback
		m_device = Gdx.audio->newAudioDevice(m_decoder->getRate(), m_decoder->getChannels() == 1? true: false);
		
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

	static void play(void* arg)
	{
		VorbisTest* testData = (VorbisTest*)arg;

		int readSamples = 0;
		// we need a short[] to pass the data to the AudioDevice
		short samples[512];
				
		// read until we reach the end of the file
		while(!testData->mustStopSound() && (readSamples = testData->m_decoder->readSamples(samples, sizeof(samples)/sizeof(samples[0]))) > 0)
		{
			// write the samples to the AudioDevice
			testData->m_device->writeSamples(samples, readSamples);
		}
		testData->soundStopped();
	}

	void dispose() 
	{
		stopSound();

		delete m_playbackThread;
		delete m_stopMutex;
		delete m_waitCondition;

		m_device->dispose();
		m_decoder->dispose();
		delete m_device;
		delete m_decoder;
	}

	GDX_DEFINE_CREATOR(VorbisTest);
};
