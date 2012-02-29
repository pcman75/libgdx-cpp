#pragma once

struct Mp3File
{
	    mpg123_handle* handle;
	    int channels;
	    long rate;
	    float length;
	    size_t buffer_size;
	    unsigned char* buffer;
	    int leftSamples;
	    int offset;
};

void cleanup( mpg123_handle *handle );
int readBuffer( Mp3File* mp3 );
