#include "stdafx.h"
#include "FileTextureData.h"
#include "FileHandle.h"
#include "Gdx.h"
#include "MathUtils.h"

bool FileTextureData::copyToPOT = false;

FileTextureData::FileTextureData(const FileHandle& file, Pixmap* preloadedPixmap, Pixmap::Format format, bool useMipMaps)
	:m_pixmap(preloadedPixmap), m_format(format), m_file(file)
{
	m_width = 0;
	m_height = 0;
	m_isPrepared = false;
	
	m_pixmap = preloadedPixmap;
	m_format = format;
	m_useMipMaps = useMipMaps;
	if(m_pixmap != NULL)
	{
		m_pixmap = ensurePot(m_pixmap);
		m_width = m_pixmap->getWidth();
		m_height = m_pixmap->getHeight();
		if(m_format == Pixmap::Format::Unknown) 
			m_format = m_pixmap->getFormat();
	}
}

bool FileTextureData::isPrepared()
{
	return m_isPrepared;
}


void FileTextureData::prepare()
{
	if(m_isPrepared) 
		throw new GdxRuntimeException("Already prepared");
	if(m_pixmap == NULL)
	{
		//TODO: implement cim files
		//if(m_file.extension().equals("cim"))
		//	m_pixmap = PixmapIO.readCIM(m_file);
		//else
			m_pixmap = ensurePot(new Pixmap(m_file));
		m_width = m_pixmap->getWidth();
		m_height = m_pixmap->getHeight();
		if(m_format == Pixmap::Format::Unknown) 
			m_format = m_pixmap->getFormat();
	}
	m_isPrepared = true;
}


Pixmap* FileTextureData::ensurePot(Pixmap* pixmap)
{
	if(!Gdx.isGL20Available() && copyToPOT)
	{
		int pixmapWidth = pixmap->getWidth();
		int pixmapHeight = pixmap->getHeight();
		int potWidth = MathUtils::nextPowerOfTwo(pixmapWidth);
		int potHeight = MathUtils::nextPowerOfTwo(pixmapHeight);
		if(pixmapWidth != potWidth || pixmapHeight != potHeight)
		{
			Pixmap* tmp = new Pixmap(potWidth, potHeight, pixmap->getFormat());
			tmp->drawPixmap(pixmap, 0, 0, 0, 0, pixmapWidth, pixmapHeight);
			pixmap->dispose();
			delete pixmap;
			return tmp;
		}
	}
	return pixmap;
}


Pixmap* FileTextureData::consumePixmap()
{
	if(!m_isPrepared) 
		throw new GdxRuntimeException("Call prepare() before calling getPixmap()");
	m_isPrepared = false;
	Pixmap* pixmap = m_pixmap;
	m_pixmap = NULL;
	return pixmap;
}


bool FileTextureData::disposePixmap()
{
	return true;
}


int FileTextureData::getWidth()
{
	return m_width;
}


int FileTextureData::getHeight()
{
	return m_height;
}


Pixmap::Format FileTextureData::getFormat()
{
	return m_format;
}


bool FileTextureData::useMipMaps()
{
	return m_useMipMaps;
}


bool FileTextureData::isManaged()
{
	return true;
}

FileHandle FileTextureData::getFileHandle()
{
	return m_file;
}


TextureData::TextureDataType FileTextureData::getType()
{
	return PixmapTexture;
}


void FileTextureData::consumeCompressedData()
{
	throw new GdxRuntimeException("This TextureData implementation does not upload data itself");
}

