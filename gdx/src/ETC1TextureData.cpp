#include "stdafx.h"
#include "ETC1TextureData.h"
#include "Gdx.h"

void ETC1TextureData::init()
{
	m_width = 0;
	m_height = 0;
	m_isPrepared = false;
}


ETC1TextureData::ETC1TextureData(const FileHandle& file)
	:m_file(file), m_useMipMaps(false)
{
	init();
}

ETC1TextureData::ETC1TextureData(const FileHandle& file, bool useMipMaps)
	:m_file(file), m_useMipMaps(useMipMaps)
{
	init();
}

ETC1TextureData::ETC1TextureData(const ETC1Data& encodedImage, bool useMipMaps)
{
	init();
	m_data = encodedImage;
	m_useMipMaps = useMipMaps;
}


ETC1TextureData::TextureDataType ETC1TextureData::getType()
{
	return CompressedTexture;
}


bool ETC1TextureData::isPrepared()
{
	return m_isPrepared;
}


void ETC1TextureData::prepare()
{
	/*TODO:
	if(m_isPrepared) 
		throw new GdxRuntimeException("Already prepared");
	if(m_file == NULL && m_data == null) 
		throw new GdxRuntimeException("Can only load once from ETC1Data");
	if(m_file != null)
	{
		m_data = new ETC1Data(m_file);
	}
	m_width = m_data.width;
	m_height = m_data.height;
	m_isPrepared = true;
	*/
}


void ETC1TextureData::consumeCompressedData()
{
	/*TODO:
	if(!m_isPrepared) throw new GdxRuntimeException("Call prepare() before calling consumeCompressedData()");

	//TODO: review platforms condition. iPhone does not support ETC1. Windows or Mac does?
	if(Gdx.app->getType() == Application::Windows || Gdx.app->getType() == Application::Mac || Gdx.graphics->isGL20Available() == false)
	{
		Pixmap pixmap;
		ETC1.decodeImage(m_data, Pixmap::Format::RGB565, pixmap);
		Gdx.glTexImage2D(GL_TEXTURE_2D, 0, pixmap.getGLInternalFormat(), pixmap.getWidth(), pixmap.getHeight(), 0,
			pixmap.getGLFormat(), pixmap.getGLType(), pixmap.getPixels());
		if(m_useMipMaps) 
			MipMapGenerator.generateMipMap(pixmap, pixmap.getWidth(), pixmap.getHeight(), false);
		pixmap.dispose();
		m_useMipMaps = false;
	}
	else
	{
		Gdx.glCompressedTexImage2D(GL_TEXTURE_2D, 0, ETC1::ETC1_RGB8_OES, m_width, m_height, 0,
			m_data.compressedData.capacity() - m_data.dataOffset, m_data.compressedData);
		if(useMipMaps()) 
			glGenerateMipmap(GL_TEXTURE_2D);
	}
	m_data.dispose();
	m_data = null;
	m_isPrepared = false;
	*/
}


Pixmap* ETC1TextureData::consumePixmap()
{
	throw new GdxRuntimeException("This TextureData implementation does not return a Pixmap");
}


bool ETC1TextureData::disposePixmap()
{
	throw new GdxRuntimeException("This TextureData implementation does not return a Pixmap");
}


int ETC1TextureData::getWidth()
{
	return m_width;
}


int ETC1TextureData::getHeight()
{
	return m_height;
}


Pixmap::Format ETC1TextureData::getFormat()
{
	return Pixmap::Format::RGB565;
}


bool ETC1TextureData::useMipMaps()
{
	return m_useMipMaps;
}


bool ETC1TextureData::isManaged()
{
	return true;
}

