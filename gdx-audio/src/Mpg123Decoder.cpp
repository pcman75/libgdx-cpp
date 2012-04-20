/*******************************************************************************
* Copyright 2011 See AUTHORS file.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
******************************************************************************/
#include "stdafx.h"

#include "GdxRuntimeException.h"
#include "mpg123.h"

#include "Mpg123Decoder.h"
#include "Mp3File.h"
#include "Gdx.h"

/** Opens the given file for mp3 decoding. Throws an GdxRuntimeException in case the file could not be opened.
*
* @param filename the filename */
Mpg123Decoder::Mpg123Decoder(const FileHandle& file)
{
	if(file.type() != External && file.type() != Absolute)
		throw new GdxRuntimeException("File must be absolute or external!");
	std::string filename = file.getFullPathName();

	mpg123_handle *mh = NULL;
	int  channels = 0, encoding = 0;
	long rate = 0;
	int  err  = MPG123_OK;

	err = mpg123_init();
	if( err != MPG123_OK || (mh = mpg123_new(NULL, &err)) == NULL
		|| mpg123_open(mh, filename.c_str()) != MPG123_OK
		|| mpg123_getformat(mh, &rate, &channels, &encoding) != MPG123_OK )
	{
		Gdx.app->log( "Mpg123Decoder", (std::string("Trouble with mpg123: ") +
			(mh == NULL ? mpg123_plain_strerror(err) : mpg123_strerror(mh))).c_str() );
		cleanup(mh);
	}

	if(encoding != MPG123_ENC_SIGNED_16)
	{
		// Signed 16 is the default output format anyways; it would actually by only different if we forced it.
		// So this check is here just for this explanation.
		cleanup(mh);
		handle = 0;
		return;
	}
	// Ensure that this output format will not change (it could, when we allow it).
	mpg123_format_none(mh);
	mpg123_format(mh, rate, channels, encoding);

	size_t buffer_size = mpg123_outblock( mh );
	unsigned char* buffer = (unsigned char*)malloc(buffer_size);
	size_t done = 0;
	int samples = 0;

	Mp3File* mp3 = new Mp3File();
	mp3->handle = mh;
	mp3->channels = channels;
	mp3->rate = rate;
	mp3->buffer = buffer;
	mp3->buffer_size = buffer_size;
	int length = mpg123_length( mh );
	if( length == MPG123_ERR )
		mp3->length = 0;
	else
		mp3->length = length / rate;

	handle = mp3;
}

int Mpg123Decoder::readSamples(short samples[], int numSamples)
{
	Mp3File* mp3 = (Mp3File*)handle;

	int idx = 0;
	while( idx != numSamples )
	{
		if( mp3->leftSamples > 0 )
		{
			short* src = ((short*)mp3->buffer) + mp3->offset;
			for( ; idx < numSamples && mp3->offset < mp3->buffer_size / 2; mp3->leftSamples--, mp3->offset++, samples++, src++, idx++ )
			{
				*samples = *src;
			}
		}
		else
		{
			int result = readBuffer( mp3 );
			if( result == 0 )
				return 0;
		}

	}

	if( idx > numSamples )
		return 0;

	return idx;
}

int Mpg123Decoder::skipSamples(int numSamples)
{
	Mp3File* mp3 = (Mp3File*)handle;

	int idx = 0;
	while( idx != numSamples )
	{
		if( mp3->leftSamples > 0 )
		{
			for( ; idx < numSamples && mp3->offset < mp3->buffer_size / 2; mp3->leftSamples--, mp3->offset++, idx++ );
		}
		else
		{
			int result = readBuffer( mp3 );
			if( result == 0 )
				return 0;
		}

	}

	if( idx > numSamples )
		return 0;

	return idx;
}

int Mpg123Decoder::getChannels()
{
	Mp3File* mp3 = (Mp3File*)handle;
	return mp3->channels;
}

int Mpg123Decoder::getRate()
{
	Mp3File* mp3 = (Mp3File*)handle;
	return mp3->rate;
}

float Mpg123Decoder::getLength()
{
	Mp3File* mp3 = (Mp3File*)handle;
	return mp3->length;
}

void Mpg123Decoder::dispose()
{
	Mp3File* mp3 = (Mp3File*)handle;
	free(mp3->buffer);
	cleanup(mp3->handle);
}

