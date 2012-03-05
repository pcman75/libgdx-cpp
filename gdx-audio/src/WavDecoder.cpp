#include "stdafx.h"
#include "WavDecoder.h"
#include "Gdx.h"


WavDecoder::WavDecoder(FileHandleStream& file)
	: m_in( WavInputStream(file))
{
	//m_buffer = new char[1024];
	//m_bufferLength = 1024;
}

int WavDecoder::readSamples(short samples[], int numSamples)
{
	return m_in.readData((char*)samples, numSamples * 2);
	/*
	int offset = 0;
	int read = 0;
	int total = 0;
	if(m_bufferLength < numSamples * 2) 
	{
	delete[] m_buffer;
	m_bufferLength = numSamples * 2;
	m_buffer = new char[m_bufferLength];
	}

	numSamples *= 2;

	while((read = m_in.readData(m_buffer + total, numSamples - total)) > 0)
	{
	for(int j=0; j < read; j+=2)
	{
	samples[offset++] = (short)(((m_buffer[j + 1] << 8) & 0xff00) | (m_buffer[j] & 0xff));
	}
	total += read;
	}
	total = total / 2; // note integer divide, total will always be even, discarding trailing bytes.
	return total;
	*/
}


int WavDecoder::skipSamples(int numSamples)
{
	try
	{
		return (int)m_in.skip(numSamples * 2 * getChannels()) / (2 * getChannels());
	}
	catch(GdxRuntimeException& e)
	{
		Gdx.app->error("WavDecoder", "Couldn't skip");
		return 0;
	}
}

int WavDecoder::getChannels()
{
	return m_in.channels;
}

int WavDecoder::getRate()
{
	return m_in.sampleRate;
}

float WavDecoder::getLength()
{
	return (m_in.dataRemaining / (2 * getChannels()) / (float)getRate());
}

void WavDecoder::dispose()
{
}

