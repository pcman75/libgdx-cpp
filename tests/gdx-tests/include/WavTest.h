#pragma once

#include "GdxTest.h"
#include "WavDecoder.h"
#include "AudioDevice.h"
#include "Gdx.h"

class WavTest :
	public GdxTest 
{
private:
	
	/** Decoder to read PCM data from the wav file **/
	WavDecoder* decoder;
	/** an AudioDevice for playing back the PCM data **/
	AudioDevice* device;
	
public:
	void create() 
	{
		/** the file to playback **/
		static const char* FILE = "data/sell_buy_item.wav";

		// Create the decoder and log some properties. 
		//FileHandleStream* file = Gdx.files->internalHandle(FILE).getStream(Read, Binary);
		
		decoder = new WavDecoder(Gdx.files->internalHandle(FILE));
		
		std::stringstream msg;
		msg << "channels: " << decoder->getChannels() << ", rate: " << decoder->getRate() << ", length: " << decoder->getLength() << "\n";
		Gdx.app->log("WavTest", msg.str());

		// Create an audio device for playback
		device = Gdx.audio->newAudioDevice(decoder->getRate(), decoder->getChannels() == 1? true: false);
		
		int readSamples = 0;
		
		// we need a short[] to pass the data to the AudioDevice
		short samples[2048];
				
		// read until we reach the end of the file
		while((readSamples = decoder->readSamples(samples, sizeof(samples)/sizeof(samples[0]))) > 0) 
		{
			std::stringstream msg;
			msg.clear();
			msg << "read " << readSamples << " samples" << "\n";
			Gdx.app->log("WavTest", msg.str());
			
			// write the samples to the AudioDevice
			device->writeSamples(samples, readSamples);
		}

		//delete file;
	}

	void dispose() 
	{
		// we should synchronize with the thread here
		// left as an excercise to the reader :)
		device->dispose();
		decoder->dispose();
	}

	GDX_DEFINE_CREATOR(WavTest);
};
