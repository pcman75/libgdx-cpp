#pragma once

#include "GdxAudioDefines.h"
#include "Decoder.h"
#include "WavInputStream.h"

/**
* {@link Decoder} implementation for WAV files
*/
class GdxAudioDllImportExport WavDecoder :
	public Decoder
{
private:
	WavInputStream m_in;

public:
	/**
	* Creates a new WAV decoder. The file can be of any type.
	* @param file the {@link FileHandle}
	*/
	WavDecoder(FileHandleStream* file);

	virtual int readSamples(short samples[], int numSamples);

	virtual int skipSamples(int numSamples);

	int getChannels();

	int getRate();

	float getLength();

	void dispose();
};
