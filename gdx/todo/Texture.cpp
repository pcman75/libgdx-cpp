#include "stdafx.h"
#include "Texture.h"
#include "GL10.h"

bool m_enforcePotImages = true;

//TODO: unused???
bool m_useHWMipMap = true;

//TODO:
//AssetManager assetManager;
Texture::TextureMap Texture::m_managedTextures;

const Texture::TextureFilter Texture::TextureFilter::Nearest = Texture::TextureFilter::TextureFilter(GL10::GDX_GL_NEAREST);
const Texture::TextureFilter Texture::TextureFilter::Linear = Texture::TextureFilter::TextureFilter(GL10::GDX_GL_LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMap = Texture::TextureFilter::TextureFilter(GL10::GDX_GL_LINEAR_MIPMAP_LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMapNearestNearest = Texture::TextureFilter::TextureFilter(GL10::GDX_GL_NEAREST_MIPMAP_NEAREST);
const Texture::TextureFilter Texture::TextureFilter::MipMapLinearNearest = Texture::TextureFilter::TextureFilter(GL10::GDX_GL_LINEAR_MIPMAP_NEAREST);
const Texture::TextureFilter Texture::TextureFilter::MipMapNearestLinear = Texture::TextureFilter::TextureFilter(GL10::GDX_GL_NEAREST_MIPMAP_LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMapLinearLinear = Texture::TextureFilter::TextureFilter(GL10::GDX_GL_LINEAR_MIPMAP_LINEAR);

Texture::TextureFilter::TextureFilter()
{
	m_glEnum = GL10::GDX_GL_NEAREST;
}

/*
Texture::TextureFilter::TextureFilter(const TextureFilter& other)
	:m_glEnum(other.m_glEnum)
{
}

Texture::TextureFilter& Texture::TextureFilter::operator=(const TextureFilter& other)
{
	if (this == &other)
      return *this;  
	
	m_glEnum = other.m_glEnum;
    return *this;
}


*/

Texture::TextureFilter::TextureFilter(int glEnum)
	:m_glEnum(glEnum)
{
}

bool Texture::TextureFilter::isMipMap()
{
	return m_glEnum != GL10::GDX_GL_NEAREST && m_glEnum != GL10::GDX_GL_LINEAR;
}

int Texture::TextureFilter::getGLEnum()
{
	return m_glEnum;
}

const Texture::TextureWrap Texture::TextureWrap::ClampToEdge = Texture::TextureWrap::TextureWrap(GL10::GDX_GL_CLAMP_TO_EDGE);
const Texture::TextureWrap Texture::TextureWrap::Repeat = Texture::TextureWrap::TextureWrap(GL10::GDX_GL_REPEAT);

Texture::TextureWrap::TextureWrap()
{
	m_glEnum = GL10::GDX_GL_CLAMP_TO_EDGE;
}

Texture::TextureWrap::TextureWrap(int glEnum)
	:m_glEnum(glEnum)
{
}

int Texture::TextureWrap::getGLEnum()
{
	return m_glEnum;
}

Texture::~Texture()
{
}

