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

#include "GdxTest.h"
#include "Mpg123Decoder.h"
#include "AudioDevice.h"
#include "Audio.h"

/**
 * Demonstrates how to read and playback an OGG file with the {@link VorbisDecoder} found
 * in the gdx-audio extension.
 *
 */

class Mpg123Test :
	public GdxTest
{
private:
	

	/** a VorbisDecoder to read PCM data from the ogg file **/
	Mpg123Decoder* decoder;
	
	/** an AudioDevice for playing back the PCM data **/
	AudioDevice* device;

public:
	
	void create()
	{
		/** the file to playback **/
		static const char* FILE = "data/8.12.mp3";

		// copy ogg file to SD card, can't playback from assets
		FileHandle externalFile = Gdx.files->externalHandle(FILE);
		Gdx.files->internalHandle(FILE).copyTo(externalFile);

		// Create the decoder and log some properties. Note that we need
		// an external or absolute file
		decoder = new Mpg123Decoder(externalFile);

		std::stringstream logMessage;
		logMessage << "channels: " << decoder->getChannels() << ", rate: " << decoder->getRate() << ", length: " << decoder->getLength();

		Gdx.app->log("Mp3", logMessage.str());

		
		// Create an audio device for playback
		device = Gdx.audio->newAudioDevice(decoder->getRate(), decoder->getChannels() == 1? true: false);

		int readSamples = 0;
		// we need a short[] to pass the data to the AudioDevice
		short* samples = new short[2048];

		// read until we reach the end of the file
		while((readSamples = decoder->readSamples(samples, 2048)) > 0)
		{
			// write the samples to the AudioDevice
			device->writeSamples(samples, readSamples);
		}
	}

	void dispose()
	{
		// we should synchronize with the thread here
		// left as an excercise to the reader :)
		device->dispose();
		decoder->dispose();
		// kill the file again
		//Gdx.files->external("tmp/test.mp3").delete();
	}

	GDX_DEFINE_CREATOR(Mpg123Test);
};
