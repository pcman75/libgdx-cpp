#pragma once

struct OggFile
{
	OggVorbis_File* ogg;
	int channels;
	int rate;
	float length;
	int bitstream;
};