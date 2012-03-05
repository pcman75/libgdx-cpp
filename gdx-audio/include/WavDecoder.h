#pragma once

#include "Decoder.h"
#include "WavInputStream.h"

/**
* {@link Decoder} implementation for WAV files
*/
class WavDecoder :
	public Decoder
{
private:
	WavInputStream m_in;
	//char* m_buffer;
	//int m_bufferLength;

public:
	/**
	* Creates a new WAV decoder. The file can be of any type.
	* @param file the {@link FileHandle}
	*/
	WavDecoder(FileHandleStream& file);

	virtual int readSamples(short samples[], int numSamples);

	virtual int skipSamples(int numSamples);

	int getChannels();

	int getRate();

	float getLength();

	void dispose();
};
