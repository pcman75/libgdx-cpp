#include "stdafx.h"
#include "VorbisDecoder.h"
#include "GdxRuntimeException.h"
#include "OggFile.h"

VorbisDecoder::VorbisDecoder(const FileHandle& file)
{
	m_buffer = NULL;

	if(file.type() != External && file.type() != Absolute)
		throw new GdxRuntimeException("File must be absolute or external!");
	std::string filename = file.getFullPathName().c_str();

	//m_handle = openFile(file->file().getAbsolutePath());
	m_handle = openFile(filename.c_str());
	if(m_handle == 0)
		throw new GdxRuntimeException("couldn't open file '" + filename + "'");
}

void VorbisDecoder::dispose()
{
	OggFile* file = (OggFile*)m_handle;
	ov_clear(file->ogg);
	free(file->ogg);
	free(file);
	delete m_buffer;
}

float VorbisDecoder::getLength()
{
	OggFile* file = (OggFile*)m_handle;
	return file->length;
}

int VorbisDecoder::getChannels()
{
	OggFile* file = (OggFile*)m_handle;
	return file->channels;
}

int VorbisDecoder::getRate()
{
	OggFile* file = (OggFile*)m_handle;
	return file->rate;
}

int VorbisDecoder::readSamples(short samples[], int numSamples)
{
	OggFile* file = (OggFile*)m_handle;
	int toRead = 2 * numSamples;
	int read = 0;

	while( read != toRead )
	{
		int ret = ov_read( file->ogg, (char*)samples + read, toRead - read, &file->bitstream );
		if( ret == OV_HOLE )
			continue;
		if( ret == OV_EBADLINK || ret == OV_EINVAL || ret == 0 )
			return read / 2;
		read+=ret;
	}
	return read / 2;
}

int VorbisDecoder::skipSamples(int numSamples)
{
	if(!m_buffer)
		new char[10000];

	OggFile* file = (OggFile*)m_handle;
	int toRead = 2 * numSamples;
	int read = 0;

	while( read != toRead )
	{
		int ret = ov_read( file->ogg, m_buffer, (toRead - read)>10000?10000:(toRead-read), &file->bitstream );
		if( ret == OV_HOLE )
			continue;
		if( ret == OV_EBADLINK || ret == OV_EINVAL || ret == 0 )
			return read / 2;
		read+=ret;
	}

	return read / 2;
}

void* VorbisDecoder::openFile(const char* filename)
{
	OggVorbis_File* ogg = new OggVorbis_File();
	FILE* file = fopen(filename, "rb" );

	if( file == 0 )
	{
		delete ogg;
		return 0;
	}

	if( ov_open( file, ogg, NULL, 0 ) != 0 )
	{
		fclose( file );
		delete ogg;
		return 0;
	}

	vorbis_info *info = ov_info( ogg, -1 );
	int channels = info->channels;
	int rate = info->rate;
	float length = (float)ov_time_total(ogg, -1 ) / 1000.0f;

	OggFile* oggFile = new OggFile();
	oggFile->ogg = ogg;
	oggFile->channels = channels;
	oggFile->rate = rate;
	oggFile->length = length;

	return oggFile;
}

