#include "stdafx.h"
#include "PixmapTextureData.h"

PixmapTextureData::PixmapTextureData(Pixmap* pixmap, Pixmap::Format format, bool useMipMaps, bool disposePixmap)
	:m_format(Pixmap::Format::Unknown)
{
	m_pixmap = pixmap;
	m_format = format == Pixmap::Format::Unknown ? pixmap->getFormat() : format;
	m_useMipMaps = useMipMaps;
	m_disposePixmap = disposePixmap;
}


bool PixmapTextureData::disposePixmap()
{
	return m_disposePixmap;
}


Pixmap* PixmapTextureData::consumePixmap()
{
	return m_pixmap;
}


int PixmapTextureData::getWidth()
{
	return m_pixmap->getWidth();
}


int PixmapTextureData::getHeight()
{
	return m_pixmap->getHeight();
}


Pixmap::Format PixmapTextureData::getFormat()
{
	return m_format;
}


bool PixmapTextureData::useMipMaps()
{
	return m_useMipMaps;
}


bool PixmapTextureData::isManaged()
{
	return false;
}


TextureData::TextureDataType PixmapTextureData::getType()
{
	return TextureData::PixmapTexture;
}


void PixmapTextureData::consumeCompressedData()
{
	throw new GdxRuntimeException("This TextureData implementation does not upload data itself");
}


bool PixmapTextureData::isPrepared()
{
	return true;
}


void PixmapTextureData::prepare()
{
	throw new GdxRuntimeException("prepare() must not be called on a PixmapTextureData instance as it is already prepared.");
}

