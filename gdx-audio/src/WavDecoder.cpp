#include "stdafx.h"
#include "WavDecoder.h"
#include "Gdx.h"
#include "WavInputStream.h"

WavDecoder::WavDecoder(const FileHandle& file)
{
	m_in = new WavInputStream(file);
}

WavDecoder::~WavDecoder()
{
	delete m_in;
}

int WavDecoder::readSamples(short samples[], int numSamples)
{
	return m_in->readData((char*)samples, numSamples * 2) / 2;
}


int WavDecoder::skipSamples(int numSamples)
{
	try
	{
		return (int)m_in->skip(numSamples * 2 * getChannels()) / (2 * getChannels());
	}
	catch(GdxRuntimeException&)
	{
		Gdx.app->error("WavDecoder", "Couldn't skip");
		return 0;
	}
}

int WavDecoder::getChannels()
{
	return m_in->channels;
}

int WavDecoder::getRate()
{
	return m_in->sampleRate;
}

float WavDecoder::getLength()
{
	return (m_in->dataRemaining / (2 * getChannels()) / (float)getRate());
}

void WavDecoder::dispose()
{
}

