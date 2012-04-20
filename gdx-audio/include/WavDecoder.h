#pragma once


#include "Decoder.h"
#include "FileHandle.h"

/**
* {@link Decoder} implementation for WAV files
*/
class WavDecoder :
	public Decoder
{
private:
	class WavInputStream* m_in;
	FileHandleStream* m_fileHandleStream;

public:
	/**
	* Creates a new WAV decoder. The file can be of any type.
	* @param file the {@link FileHandle}
	*/
	WavDecoder(const FileHandle& file);

	~WavDecoder();

	virtual int readSamples(short samples[], int numSamples);

	virtual int skipSamples(int numSamples);

	int getChannels();

	int getRate();

	float getLength();

	void dispose();
};
