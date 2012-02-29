#include "StdAfx.h"
#include "mpg123.h"
#include "Mp3File.h"

void cleanup(mpg123_handle *handle)
{
	    mpg123_close(handle);
	    mpg123_delete(handle);
	    mpg123_exit();
}

int readBuffer(Mp3File* mp3)
{
	size_t done = 0;
	int err = mpg123_read( mp3->handle, mp3->buffer, mp3->buffer_size, &done );

	mp3->leftSamples = done / 2;
	mp3->offset = 0;

	if( err != MPG123_OK )
		return 0;
	else
		return done;
}
