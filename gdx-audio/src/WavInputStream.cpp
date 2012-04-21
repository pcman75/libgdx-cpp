#include "stdafx.h"
#include "FileHandle.h"
#include "WavInputStream.h"

WavInputStream::WavInputStream(const FileHandle& file)
{
	file.read(m_file);
	if(read() != 'R' || read() != 'I' || read() != 'F' || read() != 'F')
		throw new GdxRuntimeException(std::string() + "RIFF header not found: " + file.name());

	skip(4);

	if(read() != 'W' || read() != 'A' || read() != 'V' || read() != 'E')
		throw new GdxRuntimeException(std::string() + "Invalid wave file header: " + file.name());

	int fmtChunkLength = seekToChunk('f', 'm', 't', ' ');

	int type = read() & 0xff | (read() & 0xff) << 8;
	if(type != 1) 
		throw new GdxRuntimeException(std::string() + "WAV files must be PCM");

	channels = read() & 0xff | (read() & 0xff) << 8;
	if(channels != 1 && channels != 2)
		throw new GdxRuntimeException(std::string() + "WAV files must have 1 or 2 channels");

	sampleRate = read() & 0xff | (read() & 0xff) << 8 | (read() & 0xff) << 16 | (read() & 0xff) << 24;

	skip(6);

	int bitsPerSample = read() & 0xff | (read() & 0xff) << 8;
	if(bitsPerSample != 16) 
		throw new GdxRuntimeException("WAV files must have 16 bits per sample: " + bitsPerSample);

	skip(fmtChunkLength - 16);

	dataRemaining = seekToChunk('d', 'a', 't', 'a');
}


int WavInputStream::seekToChunk(char c1, char c2, char c3, char c4)
{
	while(true)
	{
		bool found = read() == c1;
		found &= read() == c2;
		found &= read() == c3;
		found &= read() == c4;
		int chunkLength = read() & 0xff | (read() & 0xff) << 8 | (read() & 0xff) << 16 | (read() & 0xff) << 24;
		if(chunkLength == -1) 
			throw new GdxRuntimeException("Chunk not found: " + c1 + c2 + c3 + c4);
		if(found) 
			return chunkLength;
		skip(chunkLength);
	}
}

int WavInputStream::skip(int count)
{
	m_file.seekg(count, std::ios_base::cur);
	return !m_file.fail();
}

int WavInputStream::readData(char buffer[], int bufLen)
{
	if(dataRemaining == 0) 
		return -1;
	int length = min(read(buffer, bufLen), dataRemaining);
	if(length == -1) 
		return -1;
	dataRemaining -= length;
	return length;
}

int WavInputStream::read(char buffer[], int bufLen)
{
	m_file.read(buffer, bufLen);
	return m_file.gcount();
}

char WavInputStream::read()
{
	char ret;
	m_file.read(&ret, 1);
	return ret;
}