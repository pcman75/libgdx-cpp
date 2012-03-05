#pragma once

#include "FileHandleStream.h"
#include "GdxRuntimeException.h"

class WavInputStream 
{
public:
	int channels, sampleRate, dataRemaining;

private:
	FileHandleStream& m_file;

public:
	WavInputStream(FileHandleStream& file);
	int readData(char buffer[], int bufLen);
	int skip(int count);
	char read();
	int read(char buffer[], int bufLen);

private:
	int seekToChunk(char c1, char c2, char c3, char c4);
};